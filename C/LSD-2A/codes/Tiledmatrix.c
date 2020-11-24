#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


//2n2 + 2n3 loads and stores in total
// we do roughly the same number of memory
//transfer operations as we do
//arithmetic operations
void Multiply_basic(int n, double** a, double** b, double** c)
{

     for (int i = 0; i < n; i++){
        for (int j = 0; j < n ; j++){
            // load C
            for (int k = 0; k < n ; k++){
            //load A and B
            c[i][j] += a[i][k]* b[k][j];
            }
            //store C
        }
    }
}

void Multiply_flipjk(int n, double** a, double** b, double** c)
{

    for (int i = 0; i < n; i++){
        for (int k = 0; k < n ; k++){
            for (int j = 0; j < n ; j++){
            c[i][j] += a[i][k]* b[k][j];
            }
        }
    }
}




void Multiply_block(int n, double** a, double** b, double** c)
{
    int bi=0;
    int bj=0;
    int bk=0;
    int kk=0;
    int jj=0;
    int i=0;
    int j=0;
    int k=0;
    int blockSize=10;

//    for(bi=0; bi<n; bi+=blockSize)
//        for(bj=0; bj<n; bj+=blockSize)
//            for(bk=0; bk<n; bk+=blockSize)
//                for(i=0; i<blockSize; i++)
//                    for(j=0; j<blockSize; j++)
//                        for(k=0; k<blockSize; k++)
//                            c[bi+i][bj+j] += a[bi+i][bk+k]*b[bk+k][bj+j];

    for (kk = 0; kk < n ; kk+=blockSize)
        for (jj = 0; jj < n ; jj+=blockSize)
            for (i = 0; i < n ; i++)
                for (j = jj; j < jj + blockSize; j++)
                    for (k = kk; k <kk + blockSize; k++)
                        c[i][j] += a[i][k] * b[k][j];
}


int main(void)
{
    int n, REP;
    double** A;
    double** B;
    double** C;
    int i=0;
    int j=0;
    struct timeval tv1, tv2;
    struct timezone tz;
    double elapsed_basic, elapsed_flipjk, elapsed_block;
    printf ("Please enter matrix dimension n : ");
    scanf("%d", &n);
    printf ("Please enter number of repetition REP : ");
    scanf("%d", &REP);
    // allocate memory for the matrices

    ///////////////////// Matrix A //////////////////////////

    A =(double **)malloc(n*sizeof(double *));
    A[0] = (double *)malloc(n*n*sizeof(double));
    if(!A)
    {
        printf("memory failed \n");
        exit(1);
    }
    for(i=1; i<n; i++)
    {
        A[i] = A[0]+i*n;
        if (!A[i])
        {
            printf("memory failed \n");
            exit(1);
        }
    }

    ///////////////////// Matrix B //////////////////////////

    B =(double **)malloc(n*sizeof(double *));
    B[0] = (double *)malloc(n*n*sizeof(double));
    if(!B)
    {
        printf("memory failed \n");
        exit(1);
    }
    for(i=1; i<n; i++)
    {
        B[i] = B[0]+i*n;
        if (!B[i])
        {
            printf("memory failed \n");
            exit(1);
        }
    }

    ///////////////////// Matrix C //////////////////////////
    C =(double **)malloc(n*sizeof(double *));
    C[0] = (double *)malloc(n*n*sizeof(double));
    if(!C)
    {
        printf("memory failed \n");
        exit(1);
    }
    for(i=1; i<n; i++)
    {
        C[i] = C[0]+i*n;
        if (!C[i])
        {
            printf("memory failed \n");
            exit(1);
        }
    }

    // initialize the matrices
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            A[i][j] = 1;
            B[i][j] = 2;
        }
    }

    //basic multiplication matrices
    gettimeofday(&tv1, &tz);
    for (int r = 0; r < REP; r++)
        Multiply_basic(n,A,B,C);
    gettimeofday(&tv2, &tz);
    elapsed_basic += (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    printf("Time of basic multiplication= %lf \n",elapsed_basic);


    ///////////////////// Matrix C //////////////////////////
    C =(double **)malloc(n*sizeof(double *));
    C[0] = (double *)malloc(n*n*sizeof(double));
    if(!C)
    {
        printf("memory failed \n");
        exit(1);
    }
    for(i=1; i<n; i++)
    {
        C[i] = C[0]+i*n;
        if (!C[i])
        {
            printf("memory failed \n");
            exit(1);
        }
    }

    //flip jk multiply matrices
    gettimeofday(&tv1, &tz);
    for (int r = 0; r < REP; r++)
        Multiply_flipjk(n,A,B,C);
    gettimeofday(&tv2, &tz);
    elapsed_flipjk += (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    printf("Time of multiplication  fliping jk = %lf \n",elapsed_flipjk);

    ///////////////////// Matrix C //////////////////////////
    C =(double **)malloc(n*sizeof(double *));
    C[0] = (double *)malloc(n*n*sizeof(double));
    if(!C)
    {
        printf("memory failed \n");
        exit(1);
    }
    for(i=1; i<n; i++)
    {
        C[i] = C[0]+i*n;
        if (!C[i])
        {
            printf("memory failed \n");
            exit(1);
        }
    }

    //block multiply matrices
    gettimeofday(&tv1, &tz);
    for (int r = 0; r < REP; r++)
        Multiply_block(n,A,B,C);
    gettimeofday(&tv2, &tz);
    elapsed_block += (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    printf("Time of blocking matrix multiplication = %lf \n",elapsed_block);




    free(A[0]);
    free(A);
    free(B[0]);
    free(B);
    free(C[0]);
    free(C);
    return 0;
}
