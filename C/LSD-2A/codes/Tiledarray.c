#include "stdlib.h"
#include "stdio.h"
#include <time.h>

#define MAX (1024*1024*7)
#define REP 1000
#define B  (16*1024)
int main() {
    char array[MAX];

    // size of short is 2 bytes = 16bits
    //printf("%d\n", sizeof(short));

    // size of char is 1 bytes = 8bits
    //printf("%d\n", sizeof(int));

    // size of double is 8 bytes = 64 bits
    //printf("%d\n", sizeof(double));


    for (int i = 0; i < MAX; i++) {  // warmup to make things equal if array happens to fit in your L3
        array[i] = 0;
    }

    clock_t t1 = clock();

     // Tiled loop
     for (int i = 0; i < MAX; i += B) {
         for (int r = 0; r < REP; r++) {
              for (int j = i; j < (i + B); j+=64) {
                  array[j] = r;
              }
         }
     }
    clock_t t2 = clock();

     // un-tiled loop
    for (int r = 0; r < REP; r++) {
        for (int i = 0; i < MAX; i+=64) {
            array[i] = r;
         }
    }

    clock_t t3 = clock();
    printf ("Tiled: %f sec\n", (double)(t2 - t1) / CLOCKS_PER_SEC);
    printf ("Untiled: %f sec\n", (double)(t3 - t2) / CLOCKS_PER_SEC);
    printf ("array[0] = %d\n", array[0]);    // to prevent optimizing out all the writes
}
