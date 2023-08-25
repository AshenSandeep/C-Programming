// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
#include <string.h> // includes strlen(), memcpy()
#include <ctype.h> // includes toupper(), tolower()

// user-defined header files
#include "node.h" // do not modify this file

void insert_node_before(list *lst, int index, char *word)
{	

	node *newNode= (node *)malloc(sizeof(node));
	newNode->word = (char *)malloc(strlen(word) + 1);
	strcpy(newNode->word, word);
	newNode->next = NULL;
	newNode->prev = NULL;

	if(index == 0){							//if the index is eual to zero
		if(lst->head == NULL){				//if the head is null, make the newe node as the head
			lst->head = newNode;
			lst->head->next = newNode;
			lst->head->prev = newNode;
		}else{
			newNode->next = lst->head;
			newNode->prev = lst->head->prev;
			lst->head->prev->next = newNode;
			lst->head->prev = newNode;
			lst->head = newNode;
		}
	}else{
		node *temp =  lst->head;
		for(int i =0; i<index && temp!=NULL;i++){  //loop for find the correct indexed node
			temp = temp->next;
		}
		if(temp != NULL){
			newNode->next = temp;
			newNode->prev = temp->prev;
			temp->prev->next = newNode;
			temp->prev = newNode;
		}else{
			printf("index out of range");
			free(newNode->word);
			free(newNode);
		}
	}

	
}

void insert_node_after(list *lst, int index, char *word)
{
	
	insert_node_before(lst,index+1,word);

}

char *list_to_sentence(list *lst)
{
	if(lst->head == NULL){
		return NULL;
	}
	int length = 0;              
	node *temp = lst->head;

	do{
		length += strlen(temp->word) + 1;			//calculate the length 
		temp = temp->next;
	}while (temp != lst->head);

	char *sentence = (char *)malloc(length * sizeof(char)); 			//allocate the momory to the sentence
	sentence[0]='\0'; 				//intialized the sentence

	temp = lst->head;
	do{
		strcat(sentence,temp->word);
		if(temp->next != lst->head){
			strcat(sentence," ");
		}
		temp = temp->next;
	}while (temp != lst->head);

	return sentence;
}

void delete_node(list *lst, int index)
{
	if(lst->head == NULL){				//check whether the list is empty
	printf("empty list. \n");
	}

	if(index ==0){
		if(lst->head->next == lst->head){
			free(lst->head);
			free(lst);
			lst->head =NULL;
		}else{
			node *preNode = lst->head->prev;
			node *nextNode = lst->head->next;
			preNode->next = nextNode;
			nextNode->prev = preNode;
			// free(lst->head->word);
			// free(lst->head);
			lst->head = nextNode;
		}
	}else{
		node *temp =  lst->head;
			for(int i =0; i<index && temp!=NULL;i++){  //loop for find the correct indexed node
				temp = temp->next;
			}
		if(temp!=NULL){
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			// free(temp->word);
			// free(temp);
			// temp=NULL;
		}else{
			printf("index out of range");
		}
	}
}

void delete_list(list *lst)
{
	while (lst->head != NULL) {
        delete_node(lst, 0);
    }
	free(lst);

}
