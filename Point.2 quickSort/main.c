#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "quickSortsMidMid.h"
#include "quickSort3Mid.h"
#include "quickSortCentre.h"
#include "quickSortRandom.h"





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








data* arrayMidMid;
data* arrayCentre;
data* arrayRandom;
data* array3Mid;




double midCentre = 0;
double midMidMid = 0;
double midRandom = 0;
double mid3Mid = 0;


int size = 0;




void fill() {
    for (int j = 0; j < size; j++) {
        data b = rand();
        arrayMidMid[j] = b;
        arrayCentre[j] = b;
        arrayRandom[j] = b;
        array3Mid[j] = b;
    }
}

void steps() {
    fill();
    double startTime, endTime;
    startTime = getCPUTime();
    quickSortRandom(arrayRandom,0, size);
    endTime = getCPUTime();

    midRandom += endTime - startTime;


    startTime = getCPUTime();
    quickSortCentre(arrayCentre,0, size);
    endTime = getCPUTime();



    midCentre += endTime - startTime;



    startTime = getCPUTime();
    quickSortMidMid(arrayMidMid,0,size);
    endTime = getCPUTime();


    midMidMid += endTime - startTime;


    startTime = getCPUTime();
    quickSort3Mid(array3Mid,0, size);
    endTime = getCPUTime();

    mid3Mid += endTime - startTime;


}

int main() {


    double Centre[10];
    double MidMid[10];
    double Random[10];
    double ThreeMid[10];
    double startTime, endTime;

    FILE* file = fopen("testN2.txt", "w");


    for (int i = 1000; i <= 1000000; i += 100000) {

        size = i;
        arrayMidMid = allocateArray(i);
        arrayCentre = allocateArray(i);
        arrayRandom = allocateArray(i);
        array3Mid = allocateArray(i);
        for (int j = 0; j < 5; j++) {
            steps();
        }
        midCentre /= 5;
        midRandom /= 5;
        midMidMid /= 5;
        mid3Mid /= 5;
        MidMid[i / 100000] = midMidMid;
        Random[i / 100000] = midRandom;
        Centre[i / 100000] = midCentre;
        ThreeMid[i / 100000] = mid3Mid;
        midCentre = 0;
        midRandom = 0;
        midMidMid = 0;
        mid3Mid = 0;
        free(arrayMidMid);
        free(arrayCentre);
        free(arrayRandom);
        free(array3Mid);
        arrayMidMid = NULL;
        arrayCentre = NULL;
        arrayRandom = NULL;
        array3Mid = NULL;
    }
    fprintf(file, "midMid");
    for (int i = 0; i < 10; i++) {
        fprintf(file, "%lf,", MidMid[i]);
    }
    fprintf(file, "\n");
    fprintf(file, "Random");
    for (int i = 0; i < 10; i++) {
        fprintf(file, "%lf,", Random[i]);
    }
    fprintf(file, "\n");
    fprintf(file, "Centre");
    for (int i = 0; i < 10; i++) {
        fprintf(file, "%lf,", Centre[i]);
    }
    fprintf(file, "\n");
    fprintf(file, "ThreeMid");
    for (int i = 0; i < 10; i++) {
        fprintf(file, "%lf,", ThreeMid[i]);
    }
    fprintf(file, "\n");

    fclose(file);
}

