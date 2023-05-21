#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_tables"


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

char FILE_NAME_RAND_ARR[20] = "rand_arr.txt";


int* creat_rand_arr(int size, int range, char* file_name)
{
    
    char com[1000] = "/usr/bin/python3 creat_rand_arr.py ";
    char si[100];
    char ra[100];
    sprintf(si, "%d", size);
    sprintf(ra, "%d", range);
    strcat(com, si);
    strcat(com, " ");
    strcat(com, ra);
    strcat(com, " ");
    strcat(com, file_name);
    strcat(com, "\n");
    system(com);

    int* b = (int*) malloc(size * sizeof(int));

    FILE* fp = fopen(file_name, "r");

    for (int i = 0; i < size; i++)
    {
        fscanf(fp, "%d", &b[i]);

    }

    fclose(fp);

    return b;

}


int main(){
    int l = 10000;
    int r = 1000000;
    int step = 10000;
    int n_tests = 1;
    int n_steps = (r - l) / step + 1;
    long times[n_steps + 5];
    long ti = 0;
    memset(times, 0, (n_steps + 5) * sizeof(long int));
    for (int len = l, j = 0; len <= r; len += step, j++){
        for (int p = 0; p < n_tests; p++){
            HashTable* h_t = HashTableCTOR(1000000);
            int* b = creat_rand_arr(len, 1000000, FILE_NAME_RAND_ARR);
            for (int k = 0; k < len; k++){
                int h = b[k];
                int c = rand() % 4;
                if (c == 0 || c == 1){
                    hashTabInsert(h_t, h);
                }
                if (c == 2){
                    hashTabFind(h_t, h);
                }
                if (c == 3){
                    hashTabDel(h_t, h);
                }
            }
            times[j] += time_stop();
            free(b);
            HashTableDTR(h_t);
        }
    }
    FILE* fp = fopen(FILE_NAME_INSERT_RAND, "w");
    for (int len = l; len <= r; len += step){
        fprintf(fp, "%d ", len);

    }
    fprintf(fp, "\n");
    for (int j = 0; j < n_steps; j++){
        fprintf(fp, "%ld ", times[j] / n_tests);
    }
    fprintf(fp, "\n");
    fclose(fp);
}