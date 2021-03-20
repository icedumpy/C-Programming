#include<stdio.h>
#include<stdlib.h>

int main()
{   
    int RowA, ColA, RowB, ColB, RowC, ColC;
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
    printf("A(%d, %d), B(%d, %d), C(%d, %d)", RowA, ColA, RowB, ColB, RowC, ColC);


    
    return 0;
}