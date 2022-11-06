#include <assert.h>
#include <cmath>
#include <cfloat>

double seconds_difference(double time_1, double time_2)
{
    return time_2 - time_1;
}

double hours_difference(double time_1, double time_2)
{
    return seconds_difference(time_1, time_2) / 3600.;
}

double to_float_hours(int hours, int minutes, int seconds)
{
    assert(minutes >= 0 && minutes < 60);
    assert(seconds >= 0 && seconds < 60);
    return hours + minutes / 60. + seconds / 3600.;
}

double to_24_hour_clock(double hours)
{
    assert(hours >= 0);
    double hrs, frac;
    frac = modf(hours, &hrs);
    return ((int)hrs) % 12 + frac;
}

int get_hours(int seconds) { return seconds / 3600; }
int get_minutes(int seconds) { return (seconds % 3600) / 60; }
int get_seconds(int seconds) { return (seconds % 3600) % 60; }

double time_to_utc(int utc_offset, double time)
{
    double answ = time - utc_offset;
    if (answ < 0) {
        answ += 24;
    }
    else if (fabs(answ - 24.0) < DBL_EPSILON || answ > 24.0) {
        answ -= 24;
    }
    return answ;
}

double time_from_utc(int utc_offset, double time)
{
    double answ = time + utc_offset;
    if (answ < 0) {
        answ += 24;
    }
    else if (fabs(answ - 24.0) < DBL_EPSILON || answ > 24.0) {
        answ -= 24;
    }
    return answ;
}

int main() {
    assert(fabs(seconds_difference(1800.0, 3600.0) - 1800) < DBL_EPSILON);
    assert(fabs(seconds_difference(3600.0, 1800.0) + 1800) < DBL_EPSILON);
    assert(fabs(seconds_difference(1800.0, 2160.0) - 360) < DBL_EPSILON);
    assert(fabs(seconds_difference(1800.0, 1800.0)) < DBL_EPSILON);

    assert(fabs(hours_difference(1800.0, 3600.0) - 0.5) < DBL_EPSILON);
    assert(fabs(hours_difference(3600.0, 1800.0) + 0.5) < DBL_EPSILON);
    assert(fabs(hours_difference(1800.0, 2160.0) - 0.1) < DBL_EPSILON);
    assert(fabs(hours_difference(1800.0, 1800.0)) < DBL_EPSILON);

    assert(fabs(to_float_hours(0, 15, 0) - 0.25) < DBL_EPSILON);
    assert(fabs(to_float_hours(2, 45, 9) - 2.7525) < DBL_EPSILON);
    assert(fabs(to_float_hours(1, 0, 36) - 1.01) < DBL_EPSILON);

    assert(fabs(to_24_hour_clock(24)) < DBL_EPSILON);
    assert(fabs(to_24_hour_clock(48)) < DBL_EPSILON);
    assert(fabs(to_24_hour_clock(25) - 1) < DBL_EPSILON);
    assert(fabs(to_24_hour_clock(4) - 4) < DBL_EPSILON);
    assert(fabs(to_24_hour_clock(28.5) - 4.5) < DBL_EPSILON);

    assert(fabs(get_hours(3800) - 1) < DBL_EPSILON);
    assert(fabs(get_minutes(3800) - 3) < DBL_EPSILON);
    assert(fabs(get_seconds(3800) - 20) < DBL_EPSILON);

    assert(fabs(time_to_utc(+0, 12.0) - 12) < DBL_EPSILON);
    assert(fabs(time_to_utc(+1, 12.0) - 11) < DBL_EPSILON);
    assert(fabs(time_to_utc(-1, 12.0) - 13) < DBL_EPSILON);
    assert(fabs(time_to_utc(-11, 18.0) - 5) < DBL_EPSILON);
    assert(fabs(time_to_utc(-1, 0.0) - 1) < DBL_EPSILON);
    assert(fabs(time_to_utc(-1, 23.0)) < DBL_EPSILON);

    assert(fabs(time_from_utc(+0, 12.0) - 12) < DBL_EPSILON);
    assert(fabs(time_from_utc(+1, 12.0) - 13) < DBL_EPSILON);
    assert(fabs(time_from_utc(-1, 12.0) - 11) < DBL_EPSILON);
    assert(fabs(time_from_utc(+6, 6.0) - 12) < DBL_EPSILON);
    assert(fabs(time_from_utc(-7, 6.0) - 23) < DBL_EPSILON);
    assert(fabs(time_from_utc(-1, 0.0) - 23) < DBL_EPSILON);
    assert(fabs(time_from_utc(-1, 23.0) - 22) < DBL_EPSILON);
    assert(fabs(time_from_utc(+1, 23.0)) < DBL_EPSILON);
}
