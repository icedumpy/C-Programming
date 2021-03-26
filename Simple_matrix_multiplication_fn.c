#include<stdio.h>
#include<stdlib.h>
void Matrix_constant_multiplication(float *m, int row, int col, int cnst)
{
    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++)
            *(m+(col*i)+j)*=cnst;
}

void Matrix_display(float *m, int row, int col)
{
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
            printf("%10.2f", *(m+(i*col)+j));
        printf("\n");
    }
}

void Matrix_multiplication(float *A, float *B, float *C, int rowC, int colC, int colA) // colA or rowB (Middle dimension)
{
    // Using pointer to access 2D-Array 
    // C[2][1] = *(C+(2*colC)+1);
        for(int i=0; i<rowC ; i++)
            for(int j=0 ; j<colC ; j++)
            {
                *(C+(i*colC)+j)=0;
                for(int k=0; k<colA ; k++)
                    // C[i][j]+=A[i][k]*B[k][j];
                    *(C+(i*colC)+j)+=(*(A+(i*colA)+k))*(*(B+(k*colC)+j)); // rowC == rowA, colC == colB, colA == rowB
            }
}

int main()
{
    int rowA, colA, rowB, colB, rowC, colC, i, j, k;
    printf("Input number of row of Matrix A: ");
    scanf("%d",&rowA);
    printf("Input number of column of Matrix A: ");
    scanf("%d",&colA);

    printf("\nInput number of row of Matrix B: ");
    scanf("%d",&rowB);
    printf("Input number of column of Matrix B: ");
    scanf("%d",&colB);

    if (colA != rowB)
    {
        printf("Number of column of Matrix A and Number of row of Matrix B is not equal");
        exit(0);
    }

    rowC = rowA;
    colC = colB;
    printf("\nA(%d, %d), B(%d, %d), C(%d, %d)\n\n", rowA, colA, rowB, colB, rowC, colC);

    float A[rowA][colA], B[rowB][colB], C[rowC][colC];
    // Input matrix A
    for(i=0; i<rowA ; i++)
        for(j=0 ; j<colA ; j++)
        {
            printf("A[%d][%d]: ", i, j);
            scanf("%f", &A[i][j]);
        }
    printf("\n");

    // Input matrix B
    for(i=0; i<rowB ; i++)
        for(j=0 ; j<colB ; j++)
        {
            printf("B[%d][%d]: ", i, j);
            scanf("%f", &B[i][j]);
        }
    
    printf("\n");
    
    // C=AxB 
    Matrix_multiplication(&A[0][0], &B[0][0], &C[0][0], rowC, colC, colA);
    printf("Matrix C:\n");
    for(i=0; i<10*colC ; i++)
        printf("-");
    printf("\n");

    // Display C
    Matrix_display(&C[0][0], rowC, colC);
    return 0;
}