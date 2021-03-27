#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void Matrix_display(float **m, int row, int col)
{
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
            printf("%10.2f", m[i][j]);
        printf("\n");
    }
}

float** Matrix_create(int row, int col, int is_random)
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
                {
                    if (is_random)
                        m[i][j] = 2*(float)rand()/(float)(RAND_MAX)-1; // [-1, 1]
                    else
                        m[i][j] = 0;
                }
                    
        }
        return m;
    }
    return NULL;
}

float** Matrix_transpose(float **m, int row, int col)
{
    float **mT=Matrix_create(col, row, 0);
    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++)
        {
            mT[j][i]=m[i][j];
        }
    return mT;
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


int main()
{
    float **A = Matrix_create(2, 1, 1);
    float **B = Matrix_create(1, 2, 1);
    float **C = Matrix_create(2, 2, 0);
    Matrix_multiplication(A, B, C, 2, 2, 1);
    Matrix_display(A, 2, 1);
    printf("\n");
    Matrix_display(B, 1, 2);
    printf("\n");
    Matrix_display(C, 2, 2);
    return 1;
}