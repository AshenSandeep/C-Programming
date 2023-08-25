// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()

// user-defined header files
#include "node.c"

// macros

#define INSERT_BEFORE 1
#define INSERT_AFTER 2
#define DELETE_NODE 3
#define DELETE_LIST 4

// function prototypes
void print_list(list * lst); 
void run(list * lst);


int main()
{
    list * lst = (list *) malloc(sizeof(list));
    lst->head = NULL;
	run(lst);
    print_list(lst);
    free(lst);
	return 0;
}

// parse the input
void run(list *lst) 
{
	insert_node_before(lst,0,"as");
    insert_node_before(lst,0,"kk");
    insert_node_after(lst,-1,"fuck");
}

//Print the list contents
void print_list(list * lst)
{
    printf(list_to_sentence(lst));




//    node *temp = lst->head;
//    for (int i=0; i<3;i++)
//    {
//     printf(temp->word);
//     temp= temp->next;
//    }
   
}

