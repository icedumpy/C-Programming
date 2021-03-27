#include<stdio.h>
#include<stdlib.h>
void Matrix_constant_multiplication(float **m, int row, int col, int cnst)
{
    // M = c*M
    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++)
            m[i][j]*=cnst;
}

void Matrix_display(float **m, int row, int col)
{
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
            printf("%10.2f", m[i][j]);
        printf("\n");
    }
}

void Matrix_multiplication(float **A, float **B, float **C, int rowC, int colC, int colA) // colA or rowB (Middle dimension)
{
    // C = AxB
    for(int i=0; i<rowC ; i++)
        for(int j=0 ; j<colC ; j++)
        {
            C[i][j]=0;
            for(int k=0; k<colA ; k++)
                C[i][j]+=A[i][k]*B[k][j];
        }
}

float** Matrix_create(int row, int col)
{   
    // Create zeros matrix
    float **m = (float**)malloc(row*sizeof(float*));
    if (m != NULL)
    {
        for(int i=0; i<row; i++)
        {
            m[i] = (float*)malloc(col*sizeof(float));
            if (m[i] == NULL)
                break;
            else
                for(int j=0; j<col; j++)
                    m[i][j] = 0;
        }
        return m;
    }
    return NULL;
}

void Matrix_input(float **m, int row, int col)
{
    // Manually input data for each element of matrix
    for(int i=0; i<row ; i++)
        for(int j=0 ; j<col ; j++)
        {
            printf("[%d][%d]: ", i, j);
            scanf("%f", &m[i][j]);
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

        float **A=Matrix_create(rowA, colA), **B=Matrix_create(rowB, colB), **C=Matrix_create(rowC, colC);
        printf("Input Matrix A:\n");
        Matrix_input(A, rowA, colA);
        printf("\nInput Matrix B:\n");
        Matrix_input(B, rowB, colB);

        printf("\nA = \n");
        Matrix_display(A, rowA, colA);
        printf("\nB = \n");
        Matrix_display(B, rowB, colB);

        // C=AxB
        Matrix_multiplication(A, B, C, rowC, colC, colA);
        printf("\nAxB = \n");
        Matrix_display(C, rowC, colC);
}