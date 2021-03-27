#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void Matrix_constant_multiplication(float **m, int row, int col, float cnst)
{
    // M = c*M
    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++)
            m[i][j]*=cnst;
}

void Matrix_copy(float **A, float **B, int row, int col)
{
    //copy B to A
    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++)
            A[i][j]=B[i][j];    
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

void Matrix_addition(float **A, float **B, float**C, int row, int col)
{
    // C = A+B
    for(int i=0; i<row ; i++)
        for(int j=0 ; j<col ; j++)
        {
            C[i][j]=A[i][j]+B[i][j];
        }
}

void Matrix_subtraction(float **A, float **B, float**C, int row, int col)
{
    // C = A+B
    for(int i=0; i<row ; i++)
        for(int j=0 ; j<col ; j++)
        {
            C[i][j]=A[i][j]-B[i][j];
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
            mT[j][i]=m[i][j];
    return mT;
}

int* get_csv_row_col(char *file_name)
{
    int *row_col = (int*)malloc(2*sizeof(int));
    int row=0, col, first_flag=0;
    FILE *the_file = fopen(file_name, "r");
    if (the_file == NULL)
    {    
        printf("Unable to open the file");
        exit(1);
    }

    char line[1000];
    while(fgets(line, sizeof(line), the_file))
    {
        char *token;
        token = strtok(line, ",");

        col=0;
        while (token != NULL)
        {
            col++;
            token = strtok(NULL, ",");
        }
        row++;
    }
    row_col[0]=row;
    row_col[1]=col;
    return row_col;
}

float** load_data(char *file_name)
{
    int *row_col = get_csv_row_col(file_name), row, col, i, j;
    row = row_col[0];
    col = row_col[1];
    printf("%s\t(row:%d, col:%2d)\n", file_name,row, col);
    free(row_col);    

    float **m = Matrix_create(row, col, 0);
    FILE *the_file = fopen(file_name, "r");
    if (the_file == NULL)
    {    
        printf("Unable to open the file");
        exit(1);
    }

    char line[1000];
    i=0;
    while(fgets(line, sizeof(line), the_file))
    {
        char *token;
        token = strtok(line, ",");
        
        j=0;
        while (token != NULL)
        {
            m[i][j++]=atof(token);
            token = strtok(NULL, ",");
        }   
        i++;
    }
    return m;
}

int main()
{
    float learning_rate = 0.1;

    // Load data into 2D-array
    // char *data_name="kc_house_data.csv", *label_name="kc_house_data_label.csv";
    // float **X=load_data(data_name), **Y=load_data(label_name);
    // int *row_col = get_csv_row_col(data_name), rowX, colX, rowY, colY;
    // rowX = rowY = row_col[0];
    // colX = row_col[1];
    // colY = 1;
    // free(row_col);

    int rowX = 11, rowY = 11, colX = 1, colY = 1;
    float **X=Matrix_create(11, 1, 0), **Y=Matrix_create(11, 1, 0);
    X[0][0] = 65;
    X[1][0] = 67;
    X[2][0] = 71;
    X[3][0] = 71;
    X[4][0] = 66;
    X[5][0] = 75;
    X[6][0] = 67;
    X[7][0] = 70;
    X[8][0] = 71;
    X[9][0] = 69;
    X[10][0] = 69;

    Y[0][0] = 175;
    Y[1][0] = 133;
    Y[2][0] = 185;
    Y[3][0] = 163;
    Y[4][0] = 126;
    Y[5][0] = 198;
    Y[6][0] = 153;
    Y[7][0] = 163;
    Y[8][0] = 159;
    Y[9][0] = 151;
    Y[10][0] = 159;

    // Initialize weight
    int rowW = colX;
    int colW = colY;
    float **W = Matrix_create(rowW, colW, 1);

    // Initialize bias
    int rowB = rowY;
    int colB = colY;
    float **B = Matrix_create(rowB, colB, 1);

    printf("\nX[%d][%d], W[%d][%d], Y[%d][%d], b[%d][%d]\n", rowX, colX, rowW, colW, rowY, colY, rowB, colB);

    // Define backward variables
    float **Y_hat = Matrix_create(rowY, colY, 0);
    float **Y_hat_sub_Y = Matrix_create(rowY, colY, 0);
    float **dL_dW = Matrix_create(rowW, colW, 0);
    float **dL_dB = Matrix_create(rowB, colB, 0);
    float loss;

    for(int iteration=0; iteration<10; iteration++)
    {
        // Forward propagation
        Matrix_multiplication(X, W, Y_hat, rowY, colY, colX);
        Matrix_addition(Y_hat, B, Y_hat, rowY, colY);

        // Backward propagation
        
        // dL_dW
        Matrix_subtraction(Y_hat, Y, Y_hat_sub_Y, rowY, colY); // (Y'-Y) # ' is hat
        float **X_T = Matrix_transpose(X, rowX, colX); // X transpose
        Matrix_multiplication(X_T, Y_hat_sub_Y, dL_dW, rowW, colW, rowY); // X x (Y'-Y)
        Matrix_constant_multiplication(dL_dW, rowW, colW, learning_rate*2.0/(float)rowX);
        // Update W
        Matrix_subtraction(W, dL_dW, W, rowW, colW);

        // dL_dB
        Matrix_copy(dL_dB, Y_hat_sub_Y, rowB, colB);
        Matrix_constant_multiplication(dL_dB, rowB, colB, learning_rate*2.0/(float)rowX);
        // Update B
        Matrix_subtraction(B, dL_dB, B, rowB, colB);

        // Show loss
        loss = 0;
        for(int n=0; n<rowY; n++)
        {
            loss+=(Y_hat_sub_Y[n][0]*Y_hat_sub_Y[n][0]);
        }
        loss/=rowX;
        printf("Iteration(%03d), Loss: %f\n", iteration+1, loss);

        // Free transposed matrix
        for(int n=0; n<colX; n++)
        {
            free(X_T[n]);    
        }
        free(X_T);
    }

    return 1;
}