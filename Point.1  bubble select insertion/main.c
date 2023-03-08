#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "sortMethods.h"

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

data* allocateArray(int size) {
    return (data*)malloc(size * sizeof(data));
}





data* arraySelect;
data* arrayBubble;
data* arrayInsertion;




double midBubble = 0;
double midSelect = 0;
double midInsert = 0;


int size = 0;




void fill() {
    for (int j = 0; j < size; j++) {
        data b = rand();
        arraySelect[j] = b;
        arrayBubble[j] = b;
        arrayInsertion[j] = b;
    }
}

void steps() {
    fill();
    double startTime, endTime;  
    startTime = getCPUTime();
    insertionSort(arrayInsertion, size);
    endTime = getCPUTime();

    midInsert += endTime - startTime;


    startTime = getCPUTime();
    bubbleSort(arrayBubble, size);
    endTime = getCPUTime();



    midBubble += endTime - startTime;



    startTime = getCPUTime();
    selectSort(arraySelect, size);
    endTime = getCPUTime();


    midSelect += endTime - startTime;

}

int main() {


    double bubble[10];
    double select[10];
    double insertion[10];
    double startTime, endTime;

    FILE* file = fopen("testN2.txt","w");


    for (int i = 1000; i <= 100000; i+= 10000) {

        size = i;
        arraySelect = allocateArray(i);
        arrayBubble = allocateArray(i);
        arrayInsertion = allocateArray(i);
        for (int j = 0; j < 5; j++) {
            steps();
        }
        midBubble /= 5;
        midInsert /= 5;
        midSelect /= 5;
        select[i / 10000] = midSelect;
        insertion[i / 10000] = midInsert;
        bubble[i / 10000] = midBubble;
        midBubble = 0;
        midInsert = 0;
        midSelect = 0;
        free(arraySelect);
        free(arrayBubble);
        free(arrayInsertion);
        arraySelect = NULL;
        arrayBubble = NULL;
        arrayInsertion = NULL;

        
    }
    fprintf(file, "select,");
    for (int i = 0; i < 10; i++) {
        fprintf(file, "%lf,", select[i]);
    }
    fprintf(file, "\n");
    fprintf(file, "insertion,");
    for (int i = 0; i < 10; i++) {
        fprintf(file, "%lf,", insertion[i]);
    }
    fprintf(file, "\n");
    fprintf(file, "bubble,");
    for (int i = 0; i < 10; i++) {
        fprintf(file, "%lf,", bubble[i]);
    }
    fprintf(file, "\n");
}
