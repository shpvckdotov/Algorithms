#define _CRT_SECURE_NO_WARNINGS
#include "Avl.h"
#include "Btree.h"
#include "Decart.h"
#include "Naive.h"
#include "RedBlack.h"
#include "Splay.h"

typedef int data;

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
double getCPUTime(){
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
        if (times(&tms) != (double)-1)
            return (double)tms.tms_utime / ticks;
    }
#endif

#if defined(CLOCKS_PER_SEC)
    {
        double cl = getCPUTime);
        if (cl != (double)-1)
            return (double)cl / (double)CLOCKS_PER_SEC;
    }
#endif

#endif

    return -1;      /* Failed. */
}

data* allocateArray(int size) {
    return (data*)malloc(size * sizeof(data));
}

Node* skip_list;

double midBubble = 0;
double midSelect = 0;
double midInsert = 0;

int size = 0;

#define STRT_INSERT_NUM 100000
#define DELTA_INSERT_NUM 100000
#define MAX_INSERT_NUM 1000000
#define CALC_NUM 5

typedef struct Container {
    double insert_time;
    double remove_time;
    double insert_sort_time;
    double remove_sort_time;
} Container;


void skip_list_timetest(FILE* output) {
    for (int size = STRT_INSERT_NUM; size < MAX_INSERT_NUM + 1; size += DELTA_INSERT_NUM) {
        Container test_values;

        for (int iter = 0; iter < CALC_NUM; ++iter) {
            Node* rand_tree = skip_list_ctor();
            Node* sort_tree = skip_list_ctor();

            Container cur_values = skip_list_timetest1(rand_tree, sort_tree, size, output);

            add_test_values(&test_values, &cur_values);
        }
        test_values = avg_test_values(&test_values, CALC_NUM);
        fprintf(output, "size = %d: \tinsert time \t = %.2lf ms, remove_time \t= %.2lf ms,\n"
            "\t\t\t\tinsert_sort_time = %.2lf ms, remove_sort_time = %.2lf;\n",
            size, test_values.insert_time, test_values.remove_time, test_values.insert_sort_time, test_values.remove_sort_time);
        fflush(output);
    }
}

void add_test_values(Container* val1, Container* val2) {

    val1->insert_time += val2->insert_time;
    val1->remove_time += val2->remove_time;
    val1->insert_sort_time += val2->insert_sort_time;
    val1->remove_sort_time += val2->remove_sort_time;
}

Container avg_test_values(Container* values, int calc_num) {

    Container avg_values;

    avg_values.insert_time = values->insert_time / calc_num;
    avg_values.remove_time = values->remove_time / calc_num;
    avg_values.insert_sort_time = values->insert_sort_time / calc_num;
    avg_values.remove_sort_time = values->remove_sort_time / calc_num;

    return avg_values;
}

Container skip_list_timetest1(Node* rand_tree, Node* sort_tree, int insert_num, FILE* output) {

    Container test_values;

    int* rand_arg_arr = (int*)calloc(insert_num, sizeof(int));
    int* sort_arg_arr = (int*)calloc(insert_num, sizeof(int));

    for (int i = 0; i < insert_num; ++i) {
        sort_arg_arr[i] = rand();
    }

    qsort((void*)sort_arg_arr, insert_num, sizeof(int), compare_ints);

    test_values.insert_time = skip_list_insert_test(rand_tree, insert_num, rand_arg_arr);
    test_values.remove_time = skip_list_remove_test(rand_tree, insert_num / 2, insert_num, rand_arg_arr);
    test_values.insert_sort_time = skip_list_sort_insert_test(sort_tree, insert_num, sort_arg_arr);
    test_values.remove_sort_time = skip_list_sort_remove_test(sort_tree, insert_num / 2, insert_num, sort_arg_arr);

    free(rand_arg_arr);
    free(sort_arg_arr);

    return test_values;
}

double skip_list_sort_insert_test(Node* tree, int insert_num, int* arg_arr) {

    double time = 0;

    for (int insert_iter = 0; insert_iter < insert_num; ++insert_iter)
    {
        double insert_start = getCPUTime();
        tree = insertAvl(tree, arg_arr[insert_iter]);
        double insert_end = getCPUTime();

        time += insert_end - insert_start;
    }

    return (time);
}

double skip_list_sort_remove_test(Node* tree, int remove_num, int arr_size, int* arg_arr) {
    double time = 0;

    for (int remove_iter = 0; remove_iter < remove_num; ++remove_iter)
    {
        double remove_start = getCPUTime);
        tree = eraseAvl(tree, arg_arr[remove_iter]);
        double remove_end = getCPUTime);

        time += remove_end - remove_start;
    }


    return time;
}

double skip_list_insert_test(Node* tree, int insert_num, int* arg_arr) {
    double time = 0;

    for (int insert_iter = 0; insert_iter < insert_num; ++insert_iter)
    {
        int arg = rand();

        double insert_start = getCPUTime);
        tree = insertAvl(tree, arg);
        double insert_end = getCPUTime);

        time += insert_end - insert_start;

        arg_arr[insert_iter] = arg;
    }

    return  time;
}

double skip_list_remove_test(Node* tree, int remove_num, int arr_size, int* arg_arr) {
  

    double time = 0;

    for (int remove_iter = 0; remove_iter < remove_num; ++remove_iter)
    {
        int arg = arg_arr[((unsigned int)rand()) % arr_size];

        double remove_start = getCPUTime);
        tree = eraseAvl(tree, arg);
        double remove_end = getCPUTime);

        time += remove_end - remove_start;
    }


    return time ;
}

int compare_ints(const void* val1, const void* val2) {
    int arg1 = *((const int*)val1);
    int arg2 = *((const int*)val2);
    return (arg1 > arg2) - (arg1 < arg2);
}


int main() {
    FILE* output = fopen("skip_list_output.csv", "w+");
    skip_list_timetest(output);
    fclose(output);
}
