//chain.c implementation
#include "chain.h"
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
#include <string.h> // includes strlen(), memcpy()
#include <ctype.h> // includes toupper(), tolower()

matrix *create_matrix(int num_rows, int num_cols)
{
    matrix *mat = (matrix *)malloc(sizeof(matrix));     // allocate the memory to the matrix


    mat->num_rows = num_rows;
    mat->num_cols = num_cols;
    mat->data = (int **)malloc(sizeof(int *) * num_rows);       // Allocate memory for rows of the matrix
    for (int i = 0; i < num_rows; i++){                         // Allocate memory for each row's columns
        mat->data[i] = (int *)malloc(sizeof(int) * num_cols);
    }  	                     
    

    
    // Initialize matrix elements to 0
    for (int row = 0; row < num_rows; row++)
    {
        for (int column = 0; column < num_cols; column++)
        {
            mat->data[row][column] = 0;
        }
    }

    return mat;

}
//function to calculate power
int calculatePower(int num, int power)
{
    int result = 1;
    for (int i = 0; i < power; i++)
    {
        result *= num;
    }
    return result;
}

void add_row(matrix *mat, int *row)
{
    mat->data = realloc(mat->data, sizeof(int *) * (mat->num_rows + 1));
    int *new_row = (int *)malloc(sizeof(int *) * (mat->num_cols));          //allocate the memory for newRow
    for (int i = 0; i < mat->num_cols; i++)
    {
        new_row[i] = row[i];
    }
    mat->data[mat->num_rows] = new_row;
    mat->num_rows += 1;                     //increment the no of rows
}

void add_col(matrix *mat, int *col)
{
    for (int i = 0; i < mat->num_rows; i++)
    {
        mat->data[i] = (int *)realloc(mat->data[i], sizeof(int) * (mat->num_cols + 1));
        mat->data[i][mat->num_cols] = col[i];
    }
    mat->num_cols++;                        //increment the no of columns
}

void increment(matrix *mat, int num)
{
    for (int i = 0; i < (mat->num_rows); i++)
    {
        for (int j = 0; j < (mat->num_cols); j++)
        {
            mat->data[i][j] += num;                 //add num to each of the elements in the matrix
        }
    }
}

void scalar_multiply(matrix *mat, int num)
{
    for (int i = 0; i < (mat->num_rows); i++)
    {
        for (int j = 0; j < (mat->num_cols); j++)
        {
            mat->data[i][j] *= num;                 //multiply the every elements in the matrix by num
        }
    }
}

void scalar_divide(matrix *mat, int num)
{
    if (num != 0)                                       //check whether the num is not equal to zero. If num equal to zero print an error
    {
        for (int i = 0; i < (mat->num_rows); i++)
        {
            for (int j = 0; j < (mat->num_cols); j++)
            {
                mat->data[i][j] /= num;             //devide the every elements in the matrix by num
            }
        }
    }
    else
    {
        printf("Error: Cannot divide by zero");
    }
}

void scalar_power(matrix *mat, int num)
{

    for (int i = 0; i < (mat->num_rows); i++)
    {
        for (int j = 0; j < (mat->num_cols); j++)
        {
            mat->data[i][j] = calculatePower(mat->data[i][j], num);     //using 'calculatePower' function calculate the power ofthe each element.
        }
    }
}

void delete_matrix(matrix *mat)
{

    for (int i = 0; i < mat->num_rows; i++)
    {
        free(mat->data[i]);         //free the memory of each rows
    }
    
    free(mat);                      //free the matrix
}


void print_matrix(matrix *mat) 
{
    int row_idx, col_idx;
    for(row_idx = 0; row_idx < mat->num_rows; ++row_idx) {
        for(col_idx = 0; col_idx < mat->num_cols; ++col_idx) {
            if (col_idx == mat->num_cols-1) {
                printf("%d\n", mat->data[row_idx][col_idx]);
            } else {
                printf("%d ", mat->data[row_idx][col_idx]);
            }
        }
    }
}


void insert_node_before(chain *chn, int index, matrix *mat)
{
    node *new_node = (node *)malloc(sizeof(node));

    if (new_node == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    new_node->mat = mat;

    if (chn->head == NULL)
    {

        new_node->prev = new_node;
        new_node->next = new_node;
        chn->head = new_node; // if the only node is head so, the previous and next also be itself.

        return;
    }

    else
    {

        // Find the node before which to insert the new node
        node *current = chn->head;

        if (index >= 0)
        {

            for (int i = 0; i < index; i++)
            {
                current = current->next;
            }
        }
        else
        {
            for (int i = 0; i < -index; i++)
            {
                current = current->prev;
            }
        }
        // Insert the new node before the current node
        current->prev->next = new_node;
        new_node->prev = current->prev;
        new_node->next = current;
        current->prev = new_node;
    }
}
void insert_node_after(chain *chn, int index, matrix *mat)
{
    int afterIndex = index + 1;     //add 1 to current index. Then use 'insert_node_before' again 

    insert_node_before(chn, afterIndex, mat);
}

void delete_node(chain *chn, int index)
{
    node *current = chn->head;
    if (index >= 0)
    {
        for (int i = 0; i < index; i++)         // loop to find the correct indexed node
        {
            current = current->next;
        }
    }
    else
    {
        for (int i = 0; i < -index; i++)
        {
            current = current->prev;
        }
    }
    // Update the neighboring nodes and make the new connection
    current->prev->next = current->next;
    current->next->prev = current->prev;

    if (current == chn->head)
    {
        chn->head = current->next;      //update the head as next
    }

    free(current);
}

//function to delete list
void delete_list(chain *chn)
{
    node *current = chn->head;
    if (current != NULL)
    {
        while (1)
        {
            node *nextnode = current->next;
            free(current->mat);         //free the memory
            free(current);
            current = nextnode;         //update the current as next node
            if (current == chn->head)

            {

                free(current);
                break;
            }
        }
    }
    else
    {
        printf("%s\n", "The list is empty");
    }
}
