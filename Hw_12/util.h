#ifndef _UTIL_H_
#define _UTIL_H_

// Node struct
typedef struct Node{
    void *data;
    struct Node* next;
} Node;

// Asset structs
typedef struct {
    char type[20];
    int ivals[1];
    double svals[1];
} Asset1;

typedef struct {
    char type[20];
    double svals[2];
    int ivals[2];
} Asset2;

typedef struct {
    char type[20];
    char string1[50];
    char string2[50];
} Asset3;

typedef struct {
    char type[20];
    double value1;
    float value2;
    double value3;
} Asset4;

void fillLinkedList(struct Node** head);

void serializeLinkedList(struct Node* head);

void deserializeLinkedList(struct Node** head);

void printLinkedList(struct Node *head);

void freeLinkedList(struct Node *head);

#endif /* _UTIL_H_ */