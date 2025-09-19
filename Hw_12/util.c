#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "util.h"

void fillLinkedList(struct Node** head){
    // Random key
    srand(time(NULL));
    // Rand number of assets
    int numAssets = rand() % 11 + 10;
    
    for(int i = 0; i < numAssets; i++){
        // Dynamic mem allocation
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->next = NULL;
        // Rand asset type
        int assetType = rand() % 4 + 1;

        // Randomize along to the asset type
        switch (assetType)
        {
            case 1: 
            {
                Asset1* asset = (Asset1*)malloc(sizeof(Asset1));
                strcpy(asset->type, "Asset1");
                asset->ivals[0] = rand() % 100;
                asset->svals[0] = (double)(rand() % 1000) / 10.0;
                newNode->data = asset;
                break;
            }
            case 2:
            {
                Asset2* asset2 = (Asset2*)malloc(sizeof(Asset2));
                strcpy(asset2->type, "Asset2");
                asset2->svals[0] = (double)(rand() % 1000) / 10.0;
                asset2->svals[1] = (double)(rand() % 1000) / 10.0;
                asset2->ivals[0] = rand() % 100;
                asset2->ivals[1] = rand() % 100;
                newNode->data = asset2;
                break;
            }   
            case 3:
            {
                Asset3* asset3 = (Asset3*)malloc(sizeof(Asset3));
                strcpy(asset3->type, "Asset3");
                sprintf(asset3->string1, "String%d", rand() % 100);
                sprintf(asset3->string2, "String%d", rand() % 100);
                newNode->data = asset3;
                break;
            }
            case 4:
            {
                Asset4* asset4 = (Asset4*)malloc(sizeof(Asset4));
                strcpy(asset4->type, "Asset4");
                asset4->value1 = (double)(rand() % 1000) / 10.0;
                asset4->value2 = (float)(rand() % 100) / 10.0f;
                asset4->value3 = (double)(rand() % 1000) / 10.0;
                newNode->data = asset4;
                break;
            }
            default:
                break;
        }

        // Add new node to the linked list
        if (*head == NULL)
        {
            *head = newNode;
        } 
        else
        {
            Node* temp = *head;
            while (temp->next != NULL) temp = temp->next;
            temp->next = newNode;
        }
    }
}

void serializeLinkedList(struct Node* head){
    // Open file
    FILE* file = fopen("linkedlist.bin", "wb");
    if (file == NULL)
    {
        printf("File cannot opened!\n");
        return;
    }
    // Take head of linked list
    Node* current = head;

    // Write linked list along to the asset type
    while (current != NULL)
    {
        if(strcmp(((Asset1*)current->data)->type, "Asset1") == 0)
        {
            fwrite(current->data, sizeof(Asset1), 1, file);
        } 
        else if(strcmp(((Asset2*)current->data)->type, "Asset2") == 0)
        {
            fwrite(current->data, sizeof(Asset2), 1, file);
        } 
        else if(strcmp(((Asset3*)current->data)->type, "Asset3") == 0)
        {
            fwrite(current->data, sizeof(Asset3), 1, file);
        }
        else if(strcmp(((Asset4*)current->data)->type, "Asset4") == 0)
        {
            fwrite(current->data, sizeof(Asset4), 1, file);
        }
        current = current->next;
    }

    fclose(file);
}

void deserializeLinkedList(struct Node** head){
    // Open file
    FILE* file = fopen("linkedlist.bin", "rb");
    if (file == NULL)
    {
        printf("File cannot opened!\n");
        return;
    }

    Node* current = *head;

    // Read linked list from file along to the asset type
    while (current != NULL)
    {
        if (strcmp(((Asset1*)current->data)->type, "Asset1") == 0) 
        {
            fread(current->data, sizeof(Asset1), 1, file);
        } 
        else if (strcmp(((Asset2*)current->data)->type, "Asset2") == 0)
        {
            fread(current->data, sizeof(Asset2), 1, file);
        } 
        else if (strcmp(((Asset3*)current->data)->type, "Asset3") == 0) 
        {
            fread(current->data, sizeof(Asset3), 1, file);
        } 
        else if (strcmp(((Asset4*)current->data)->type, "Asset4") == 0) 
        {
            fread(current->data, sizeof(Asset4), 1, file);
        }

        current = current->next;
    }

    fclose(file);
}

// Print linked list to the terminal
void printLinkedList(struct Node *head){
    struct Node* current = head;

    while (current != NULL)
    {
        if (strcmp(((Asset1*)current->data)->type, "Asset1") == 0)
        {
            Asset1* asset = current->data;
            printf("Asset1: ivals[0] = %d, svals[0] = %lf\n", asset->ivals[0], asset->svals[0]);
        } 
        else if (strcmp(((Asset2*)current->data)->type, "Asset2") == 0)
        {
            Asset2* asset2 = (Asset2*)current->data;
            printf("Asset2: svals[0] = %lf, svals[1] = %lf, ivals[0] = %d, ivals[1] = %d\n", asset2->svals[0], asset2->svals[1], asset2->ivals[0], asset2->ivals[1]);
        } 
        else if (strcmp(((Asset3*)current->data)->type, "Asset3") == 0)
        {
            Asset3* asset3 = (Asset3*)current->data;
            printf("Asset3: string1 = %s, string2 = %s\n", asset3->string1, asset3->string2);
        } 
        else if (strcmp(((Asset4*)current->data)->type, "Asset4") == 0)
        {
            Asset4* asset4 = (Asset4*)current->data;
            printf("Asset4: value1 = %lf, value2 = %f, value3 = %lf\n", asset4->value1, asset4->value2, asset4->value3);
        }
        current = current->next;
    }
}

// Free
void freeLinkedList(struct Node *head){
    struct Node* current = head;
    struct Node* prev;

    while (current != NULL)
    {   
        prev = current;
        current = current->next;
        free(prev->data);
        free(prev);
    }
    head = NULL;
}