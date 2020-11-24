#include "stdlib.h"
#include "stdio.h"
#include <time.h>

#define MAX (1024*1024*7)
#define REP 100
#define B  (16*1024)
int main() {
    int i,j,r;
    char array[MAX];

    for (i = 0; i < MAX; i++) {  // warmup to make things equal if array happens to fit in your L3
       array[i] = 0;
    }

    clock_t t1 = clock();

    // Tiled loop
    for (i = 0; i < MAX; i += B) {
        for (r = 0; r < REP; r++) {
             for (j = i; j < (i + B); j+=64) {
                 array[j] = r;
             }
        }
    }
    clock_t t2 = clock();

    // un-tiled loop
    for (r = 0; r < REP; r++) {
        for (i = 0; i < MAX; i+=64) {
             array[i] = r;
        }
    }

    clock_t t3 = clock();
    printf ("Tiled: %f sec\n", (double)(t2 - t1) / CLOCKS_PER_SEC);
    printf ("Untiled: %f sec\n", (double)(t3 - t2) / CLOCKS_PER_SEC);
    printf ("array[0] = %d\n", array[0]);    // to prevent optimizing out all the writes
}
