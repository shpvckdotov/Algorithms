#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Sparse1.h"

#define SIZE_ARR 1000000
#define N_TEST 5

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
double getCPUTime() {
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
        getCPUTimeid_t id;
        struct timespec ts;
#if _POSIX_CPUTIME > 0
        /* getCPUTime ids vary by OS.  Query the id, if possible. */
        if (getCPUTime_getcpugetCPUTimeid(0, &id) == -1)
#endif
#if defined(getCPUTime_PROCESS_CPUTIME_ID)
            /* Use known getCPUTime id for AIX, Linux, or Solaris. */
            id = getCPUTime_PROCESS_CPUTIME_ID;
#elif defined(getCPUTime_VIRTUAL)
            /* Use known getCPUTime id for BSD or HP-UX. */
            id = getCPUTime_VIRTUAL;
#else
            id = (getCPUTimeid_t)-1;
#endif
        if (id != (getCPUTimeid_t)-1 && getCPUTime_gettime(id, &ts) != -1)
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
        if (times(&tms) != (double)-1)
            return (double)tms.tms_utime / ticks;
    }
#endif

#if defined(getCPUTimeS_PER_SEC)
    {
        double cl = getCPUTime();
        if (cl != (double)-1)
            return (double)cl / (double)getCPUTimeS_PER_SEC;
    }
#endif

#endif

    return -1;      /* Failed. */
}


void buildDegs(int* logs, int n){
    int q = 1;
    int d = 0;
    for (int i = 1; i <= n; i++){
        while (q <= i){
            q <<= 1;
            d++;
        }
        q >>= 1;
        d--;
        logs[i] = d;
    }

}


void buildST(int** sparseTable, int* a, int n, int* logs){

    for (int j = 0; j <= logs[n]; j++){
        for (int i = 1; i <= n; i++){
            if (j == 0){
                sparseTable[i][j] = a[i];
            }
            else{
                if (i + (1 << j) - 1 > n){
                    break;
                }
                sparseTable[i][j] = min(sparseTable[i][j - 1], sparseTable[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
}

int getMin(int** sparseTable, int n, int* logs, int l, int r){
    int lo = logs[r - l + 1];

    return min(sparseTable[l][lo], sparseTable[r - (1 << lo) + 1][lo]);

}

int main(){
    FILE* file = fopen("sparse1.txt", "w+");
    int* logs = (int*)malloc((SIZE_ARR + 1) * sizeof(int));
    buildDegs(logs, SIZE_ARR);
    int* a = (int*)malloc((SIZE_ARR + 1) * sizeof(int));
    int** sparseTable = (int**)calloc(SIZE_ARR + 1, sizeof(int*));
    for (int i = 0; i <= SIZE_ARR; i++){
        sparseTable[i] = (int*)calloc(logs[SIZE_ARR] + 1, sizeof(int));
    }
    long time = 0;
    for (int i = 0; i < N_TEST; i++){
        for (int j = 1; j <= SIZE_ARR; j++){
            a[j] = random() % 1000;
        }
        buildST(sparseTable, a, SIZE_ARR, logs);
        double startTime = getCPUTime();
        for (int j = 0; j < SIZE_ARR; j++){
            int l = rand() % (SIZE_ARR - 10) + 1;
            l++;
            int len = rand() % (SIZE_ARR - l - 2);
            int r = l + len;
            long long min = getMin(sparseTable, SIZE_ARR, logs, l, r);
        }
        double endTime = getCPUTime();
        fprintf(file, "%lf\n", endTime - startTime);
    }
    fclose(file);
    free(a);
    for (int i = 0; i <= SIZE_ARR; i++){
        free(sparseTable[i]);
    }
    free(sparseTable);
}
