#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "stack.h"
#include <Windows.h>

#define TEST_CONSTANTS 1000000

typedef struct Stack stack;

/*
 * Author:  David Robert Nadeau
 * Site:    http://NadeauSoftware.com/
 * License: Creative Commons Attribution 3.0 Unported License
 *          http://creativecommons.org/licenses/by/3.0/deed.en_US
 */
#if defined(_WIN32)
#include <Windows.h>

#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
#include <unistd.h>
#include <sys/resource.h>
#include <sys/times.h>
#include <time.h>

#else
#error "Unable to define getCPUTime( ) for an unknown OS."
#endif

 /**
  * Returns the amount of CPU time used by the current process,
  * in seconds, or -1.0 if an error occurred.
  */
double getCPUTime()
{
#if defined(_WIN32)
    /* Windows -------------------------------------------------- */
    FILETIME createTime;
    FILETIME exitTime;
    FILETIME kernelTime;
    FILETIME userTime;
    if (GetProcessTimes(GetCurrentProcess(),
        &createTime, &exitTime, &kernelTime, &userTime) != -1)
    {
        SYSTEMTIME userSystemTime;
        if (FileTimeToSystemTime(&userTime, &userSystemTime) != -1)
            return (double)userSystemTime.wHour * 3600.0 +
            (double)userSystemTime.wMinute * 60.0 +
            (double)userSystemTime.wSecond +
            (double)userSystemTime.wMilliseconds / 1000.0;
    }

#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
    /* AIX, BSD, Cygwin, HP-UX, Linux, OSX, and Solaris --------- */

#if defined(_POSIX_TIMERS) && (_POSIX_TIMERS > 0)
    /* Prefer high-res POSIX timers, when available. */
    {
        clockid_t id;
        struct timespec ts;
#if _POSIX_CPUTIME > 0
        /* Clock ids vary by OS.  Query the id, if possible. */
        if (clock_getcpuclockid(0, &id) == -1)
#endif
#if defined(CLOCK_PROCESS_CPUTIME_ID)
            /* Use known clock id for AIX, Linux, or Solaris. */
            id = CLOCK_PROCESS_CPUTIME_ID;
#elif defined(CLOCK_VIRTUAL)
            /* Use known clock id for BSD or HP-UX. */
            id = CLOCK_VIRTUAL;
#else
            id = (clockid_t)-1;
#endif
        if (id != (clockid_t)-1 && clock_gettime(id, &ts) != -1)
            return (double)ts.tv_sec +
            (double)ts.tv_nsec / 1000000000.0;
    }
#endif

#if defined(RUSAGE_SELF)
    {
        struct rusage rusage;
        if (getrusage(RUSAGE_SELF, &rusage) != -1)
            return (double)rusage.ru_utime.tv_sec +
            (double)rusage.ru_utime.tv_usec / 1000000.0;
    }
#endif

#if defined(_SC_CLK_TCK)
    {
        const double ticks = (double)sysconf(_SC_CLK_TCK);
        struct tms tms;
        if (times(&tms) != (clock_t)-1)
            return (double)tms.tms_utime / ticks;
    }
#endif

#if defined(CLOCKS_PER_SEC)
    {
        clock_t cl = clock();
        if (cl != (clock_t)-1)
            return (double)cl / (double)CLOCKS_PER_SEC;
    }
#endif

#endif

    return -1;      /* Failed. */
}


int main() {
    stack* st = stack_ctr(23, sizeof(data));
    //test 1
    double startTime, endTime;

    startTime = getCPUTime();

    for (int i = 0; i < 1000000; i++) {
        if (!push(st, &i)) {

        }
    }
    while (st->size >= 100000) {
        int n = st->size;
        for (int i = 0; i < n / 2; i++) {
            if (!pop(st)) {

            }
        }
        for (int i = 0; i < n / 4; i++) {
            if (!push(st, &i)) {

            }
        }
    }

    endTime = getCPUTime();
    st = stack_dtr(st);
    printf("test 1 = %lf %lf\n", startTime, endTime);
    //
    // test 2

    startTime = getCPUTime();

    st = stack_ctr(23, sizeof(data));
    for (int i = 0; i < 1000000; i++) {
        if (!push(st, &i)) {

        }
    }

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 10000; j++) {
            if (!pop(st)) {

            }
        }
    }
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 10000; j++) {
            if (!push(st, &i))
            {

            }
        }
    }
    while (st->size >= 100000) {
        int n = st->size;
        for (int i = 0; i < n / 2; i++) {
            if (!pop(st)) {

            }
        }
        for (int i = 0; i < n / 4; i++) {
            if (!push(st, &i)) {

            }
        }
    }
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 10000; j++) {
            if (!pop(st)) {

            }
        }
    }
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 10000; j++) {
            if (!push(st, &i)) {

            }
        }
    }

    endTime = getCPUTime();
    st = stack_dtr(st);
    printf("test 2 = %lf %lf\n", startTime, endTime);
    //test 3

    st = stack_ctr(23, sizeof(data));




    for (int i = 0; i < 1000000; i++) {
        if (!push(st, &i)) {

        }
    }

    startTime = getCPUTime();

    for (int i = 0; i < 1000000; i++) {
        if (rand() % 2 == 1) {
            if (!push(st, &i)) {

            }
        }
        else {
            if (!pop(st)) {

            }
        }
    }

    endTime = getCPUTime();
    st = stack_dtr(st);
    printf("test 3 = %lf %lf\n", startTime, endTime);

    //

}