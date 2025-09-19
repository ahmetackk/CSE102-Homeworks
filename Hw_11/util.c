#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

/*-------------------------------- HELPER FUNCTIONS -------------------------------------------*/

void reset_terminal(){
    printf("\033[2J");
    printf("\033[0;0f");
}

/*--------------------------------- MAIN FUNCTIONS ---------------------------------------*/

void addPerson(Node** root){
    char name[50];
    int age;
    char motherName[50];
    char fatherName[50];

    printf("Enter person's name: ");
    scanf("%s", name);
    printf("Enter person's age: ");
    scanf("%d", &age);
    printf("Enter person's mother's name: ");
    scanf("%s", motherName);
    printf("Enter person's father's name: ");
    scanf("%s", fatherName);

    Node *mother = NULL;
    Node *father = NULL;
    if (*root != NULL)
    {
        mother = findPerson(*root, motherName);
        if (mother == NULL)
        {
            printf("Mother not found in the family tree.\n");
            return;
        }

        father = findPerson(*root, fatherName);
        if (father == NULL)
        {
            printf("Father not found in the family tree.\n");
            return;
        }
    }
    

    Node *newNode = (Node*)malloc(sizeof(struct Node));

    strcpy(newNode->name, name);
    newNode->mother = mother;
    newNode->father = father;
    newNode->age = age;
    
    *root = newNode;
    printf("Person added to the family tree.\n");
}

Node *findPerson(Node* root, char* name){

    if (root == NULL) return NULL;
    if (strcmp(root->name, name) == 0) return root;
    
    Node *foundNode = findPerson(root->mother, name);
    if (foundNode == NULL) foundNode = findPerson(root->father, name);
    
    return foundNode;
}

void saveTree(Node* root, FILE *file){
    if (root == NULL) return;
    
    
}