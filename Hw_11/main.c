#include <stdio.h>
#include "util.h"

/*----- MAIN ------*/

int main(){
    struct Node* familyTree = NULL;
    char fileName[50];
    int choice;

    FILE *file;
    int i = 1;

    main_menu:
    reset_terminal();
    printf("Family Tree System Menu:\n");
    printf("1- Add Family Tree\n2- Remove Family Tree\n3- Load Family Tree\n4- Exit\n>");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        

        fileOpen:
        sprintf(fileName, "familytree%d.txt", i);
        file = fopen(fileName, "r");
        if (file != NULL)
        {
            i++;
            fclose(file);
            goto fileOpen;
        }
        file = fopen(fileName, "w+");
        
        add_menu:
        reset_terminal();
        printf("1- Add node\n2- Save Fammily Tree\n3- Exit\n>");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addPerson(familyTree);
            break;
        case 2:
            
            break;
        case 3:
            goto main_menu;
        default:
            break;
        }
    
    case 2:
        
        break;

    case 3:
        
        break;

    case 4:

        break;

    default:
        break;
    }
}