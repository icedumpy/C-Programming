#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
    printf("%d, %d\n", row, col);
    free(row_col);    

    float **m = Matrix_create(row, col);
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
    char *data_name="kc_house_data.csv", *label_name="kc_house_data_label.csv";
    float **X=load_data(data_name), **Y=load_data(label_name);
    int *row_col = get_csv_row_col(data_name), row, col, i, j;
    row = row_col[0];
    col = row_col[1];
    free(row_col);

    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
            printf("%.2f ", X[i][j]);
        printf("Label(%d): %.2f\n", i+1, Y[i][0]);
    }
    return 1;
}
