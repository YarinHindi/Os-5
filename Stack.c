#include "Node.c"
#include <strings.h>
#include <stdio.h>
#include "heap.c"

#define MAX_LENGTH 1024
typedef struct Stack {
    Node *head;
}Stack;

Node *top(Node **stack) {
    if(*stack==NULL){}
    return (*stack);
}

void initializeStack(Node **stack) {
    (*stack) = NULL;
}


void pop(Node **stack) {
    if ((*stack)  == NULL) {
        return;
    }
    if ((*stack)->next  == NULL) {
        free((*stack)->data);
        free((*stack));
        (*stack)  = NULL;
        return;
    } else {
        Node *temp = (*stack) ;
        (*stack) = (*stack)->next;
        free(temp->data);
        free(temp);
        return;
    }

}

void push(Node **stack, char *data) {
    Node *newNode = (Node*)(malloc)(sizeof(Node));
    newNode->data = (char *)(malloc)(MAX_LENGTH);
    for (int i = 0; i < MAX_LENGTH; ++i) {
        newNode->data[i] = data[i];
    }
    newNode->next = NULL;
    if ((*stack) == NULL) {
        (*stack) = newNode;
    } else {
        newNode->next = (*stack) ;
        (*stack) = newNode;
    }
}
void release(Node **stack){
    Node *temp = (*stack);
    Node *temp1 = (*stack);
    while (temp!=NULL){
        temp1 = temp->next;
        free(temp->data);
        free(temp);
        temp = temp1;
    }



}
