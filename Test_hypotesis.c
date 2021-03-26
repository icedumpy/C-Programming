#include<stdio.h>
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
        
void main()
{
    float A[2][2] = {
        {2, 5}, 
        {3, 10}
    };
    Matrix_display(A, 2, 2);
    Matrix_constant_multiplication(A, 2, 2, 2);
    printf("\n");
    Matrix_display(A, 2, 2);
}