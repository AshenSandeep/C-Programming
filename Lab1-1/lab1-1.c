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
void run(list *lst) {
    int choice, index;
    char word[MAX_WORD_LENGTH];
    char input[100];
    char *words[100];
    int numWords = 0;
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    // Tokenize the input using strtok
    char *token = strtok(input, ",");
    while (token != NULL && numWords < 100) {
        words[numWords] = malloc(strlen(token) + 1);
        strcpy(words[numWords], token);
        numWords++;
        token = strtok(NULL, ",");
    }
    int size = 0;
    for(int i = 0; i < numWords; i++) {
        insert_node_after(lst, i-1, words[i]);
        size++;
    }

    while (1) {
        scanf("%d", &choice);

        if (choice == 0) {
            break;
        }

        switch (choice) {                       //check the switch cases
            case INSERT_BEFORE:
                scanf("%d %s", &index, word);
                if(index < 0){
                    index += size;
                }
                insert_node_before(lst, index, word);
                size++;
                break;

            case INSERT_AFTER:
                scanf("%d %s", &index, word);
                if(index < 0){
                    index += size;
                }
                insert_node_after(lst, index, word);
                size++;
                break;

            case DELETE_NODE:
                scanf("%d", &index);
                if(index < 0){
                    index += size;
                }
                delete_node(lst, index);
                size--;
                break;

            case DELETE_LIST:
                delete_list(lst);
                break;

            default:
                break;
        }
    }
}
//Print the list contents
void print_list(list * lst)
{
    printf(list_to_sentence(lst));
}
