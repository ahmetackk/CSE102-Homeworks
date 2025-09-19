#ifndef _UTIL_H_
#define _UTIL_H_

typedef struct Node {
    char name[50];
    int age;
    struct Node * mother;
    struct Node * father;
} Node;

void reset_terminal();

void addPerson(Node ** root);

Node *findPerson(Node * root, char * name);

#endif /* _UTIL_H_ */