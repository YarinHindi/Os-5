#include "Node.c"
#include <strings.h>
#include <stdio.h>

#define MAX_LENGTH 1024
typedef struct Stack {
    Node *head;
    void * current_adress;
}Stack;

Node *top(Stack **stack) {
    if((*stack)->head!=NULL) {
        return (*stack)->head;
    }
}

void initializeStack(Stack **stack) {
    (*stack)->current_adress = (*stack)+sizeof(Stack);
    (*stack)->head = NULL;
}


void pop(Stack **stack) {
    if ((*stack)  == NULL) {
        return;
    }
    if ((*stack)->head->next  == NULL) {
        (*stack)->head  = NULL;
        return;
    } else {
        Node *temp = (*stack)->head ;
        (*stack)->head = (*stack)->head->next;

        return;
    }

}

void push(Stack **stack, char *data) {
    Node *newNode = (Node*)(*stack)->current_adress;
    newNode->data = (char*)(*stack)->current_adress+sizeof(Node);
    for (int i = 0; i < MAX_LENGTH; ++i) {
        newNode->data[i] = data[i];
    }
    newNode->next = NULL;
    if ((*stack) == NULL) {
        (*stack)->head = newNode;
    } else {
        newNode->next = (*stack)->head ;
        (*stack)->head = newNode;
    }
    (*stack)->current_adress +=MAX_LENGTH+sizeof(Node);
}
void release(Node **stack){
    Node *temp = (*stack);
    Node *temp1 = (*stack);
    while (temp!=NULL){
        temp1 = temp->next;
        temp = temp1;
    }



}
