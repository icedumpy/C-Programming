#include<stdio.h>
#include<stdlib.h>

int main()
{   
    int RowA, ColA, RowB, ColB, RowC, ColC, i, j, k;
    printf("Input number of row of Matrix A: ");
    scanf("%d",&RowA);
    printf("Input number of column of Matrix A: ");
    scanf("%d",&ColA);

    printf("\nInput number of row of Matrix B: ");
    scanf("%d",&RowB);
    printf("Input number of column of Matrix B: ");
    scanf("%d",&ColB);

    if (ColA != RowB)
    {
        printf("Number of column of Matrix A and Number of row of Matrix B is not equal");
        exit(0);
    }

    RowC = RowA;
    ColC = ColB;
    printf("\nA(%d, %d), B(%d, %d), C(%d, %d)\n\n", RowA, ColA, RowB, ColB, RowC, ColC);
    
    float A[RowA][ColA], B[RowB][ColB], C[RowC][ColC];

    // Input matrix A
    for(i=0; i<RowA ; i++)
        for(j=0 ; j<ColA ; j++)
        {
            printf("A[%d][%d]: ", i, j);
            scanf("%f", &A[i][j]);
        }
    printf("\n");

    // Input matrix B
    for(i=0; i<RowB ; i++)
        for(j=0 ; j<ColB ; j++)
        {
            printf("B[%d][%d]: ", i, j);
            scanf("%f", &B[i][j]);
        }
    printf("\n");
    // C=AxB
    /*
    ij = ...
    C[00] = A[00]*B[00] + A[01]*B[10] + A[02]*B[20]
    C[01] = A[00]*B[01] + A[01]*B[11] + A[02]*B[21]
    */
    for(i=0; i<RowC ; i++)
        for(j=0 ; j<ColC ; j++)
        {
            C[i][j] = 0;
            for(k=0; k<ColA ; k++)
                C[i][j]+=A[i][k]*B[k][j];
        }

    printf("AxB = \n");
    for(i=0; i<RowC ; i++)
    {
        for(j=0 ; j<ColC ; j++)
            printf("%.2f ", C[i][j]);
        printf("\n");
    }    

    return 0;
}