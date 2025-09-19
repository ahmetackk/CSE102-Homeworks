#include <stdio.h>
#include <stdlib.h>
#include "util.h"

/*----- MAIN ------*/

int main(){
    struct Node *head = NULL;

    // Fill and serialize
    fillLinkedList(&head);
    serializeLinkedList(head);
    printLinkedList(head);
    
    printf("-------------------------\n");

    // Deserialize
    deserializeLinkedList(&head);
    printLinkedList(head);

    freeLinkedList(head);
}