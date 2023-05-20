#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Fenwick.h"

#define SIZE_TREE 1000000
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

void modify(long long* tree, int i, int x, int n){
    while (i < n){
        tree[i] += x;
        i = i | (i + 1);
    }
}

void setTree(long long* tree, int i, int x, long long* a, int n){
    long long delta = x - a[i];
    a[i] = x;
    while (i < n){
        tree[i] += x;
        i = i | (i + 1);
    }
}

void buildTree(long long* a, long long* tree, int n){
    for (int i = 0; i < n; i++){
        modify(tree, i, a[i], n);
    }
}

long long getSum(long long* tree, int l, int r){
    long long sum = 0;
    long long s1 = 0;
    long long s2 = 0;
    l--;
    while (l >= 0)
    {
        s1 += tree[l];
        l = (l & (l + 1)) - 1;
    }
    while (r >= 0){
        s2 += tree[r];
        r = (r & (r + 1)) - 1;
    }
    sum = s2 - s1;
    return sum;
}



int main(){
    long long* tree = (long long*)calloc(SIZE_TREE, sizeof(long long));
    long long* a = (long long*)calloc(SIZE_ARR + 10, sizeof(long long));
    long time = 0;
    FILE* fp = fopen("fenwick.txt", "w+");
    for (int i = 0; i < N_TEST; i++) {
        for (int j = 0; j <= SIZE_ARR; j++){
            a[j] = random() % 1000;
        }
        buildTree(a, tree, SIZE_ARR);
        double startTime = getCPUTime();
        for (int j = 0; j < SIZE_ARR; j++){
            char op = random() % 2;
            if (op){
                int l = rand() % (SIZE_ARR - 10);
                l++;
                int len = rand() % (SIZE_ARR - l - 2);
                int r = l + len;
                long long sum = getSum(tree, l, r);
            }
            else
            {
                int x = rand() % 1000;
                int idx = rand() % SIZE_ARR;
                setTree(tree, idx, x, a, SIZE_ARR);
            }
        }
        double endTime = getCPUTime();
        fprintf(fp, "%lf\n", endTime - startTime);
    }
    fclose(fp);
    free(a);
    free(tree);
}