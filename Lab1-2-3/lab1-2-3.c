// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()

// user-defined header files
#include "chain.c"

// function prototypes
void print_chain(chain * chn); 
void run(chain * chn);


int main()
{
    chain * chn = (chain *) malloc(sizeof(chain));
    chn->head = NULL;
	run(chn);
    print_chain(chn);
    free(chn);
	return 0;
}
matrix *copy_matrix(matrix *mat)
{
    matrix *new_mat = create_matrix(mat->num_rows, mat->num_cols);
    for (int i = 0; i < mat->num_rows; i++)
    {
        for (int j = 0; j < mat->num_cols; j++)
        {
            new_mat->data[i][j] = mat->data[i][j];
        }
    }
    return new_mat;
}

// parse the input
void run(chain *chn)
{
    int row = 0;

    scanf("%d", &row);

    char *input = (char *)malloc(sizeof(char) * 100);
    getchar();


    fgets(input, 100, stdin);
    char *token = strtok(input, " ");

    int i = 0;
    int array[100];

    while (token != NULL)
    {

        array[i] = atoi(token);
        //  printf("%d\n", array[i]);
        i++;
        token = strtok(NULL, " ");
    }

    matrix *mat = create_matrix(row, i);
    for (int j = 0; j < i; j++)
    {
        mat->data[0][j] = array[j];
    }

    for (int k = 1; k < row; k++)
    {
        fgets(input, 100, stdin);
        char *token = strtok(input, " ");
        int i = 0;
        while (token != NULL)
        {
            mat->data[k][i] = atoi(token);
            i += 1;
            token = strtok(NULL, " ");
        }
    }
    insert_node_before(chn, 0, copy_matrix(mat));
    int query = 0;
    scanf("%d", &query);
    while (query != 0)

    {
        switch (query)
        {

        case 2:
            int array1[100];
            for (int i = 0; i < mat->num_cols; i++)
            {
                scanf("%d", &array1[i]);
            }
            add_row(mat, array1);
            break;

        case 3:
            int array2[100];
            for (int i = 0; i < mat->num_rows; i++)
            {
                scanf("%d", &array2[i]);
            }
            add_col(mat, array2);
            break;

        case 4:
            int num = 0;
            scanf("%d", &num);
            increment(mat, num);
            break;
        case 5:
            int num2 = 0;
            scanf("%d", &num2);
            scalar_multiply(mat, num2);
            break;
        case 6:
            int num3 = 0;
            scanf("%d", &num3);
            scalar_divide(mat, num3);
            break;

        case 7:
            int num1 = 0;
            scanf("%d", &num1);
            scalar_power(mat, num1);
            break;
        }
        insert_node_after(chn, -1, copy_matrix(mat));
        scanf("%d", &query);
    }
}

//Print the chain
void print_chain(chain *chn)
{

    node *current = chn->head;
    if (current != NULL)
    {
        // print the list with space after each word
        do
        {
            
            print_matrix(current->mat);
            printf("\n");

            current = current->next;
        } while (current != chn->head);
    }

    else
    {
        printf("The list is empty.\n");
    }
}

