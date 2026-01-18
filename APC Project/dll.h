#ifndef DLL_H
#define DLL_H

typedef struct Node {
    int digit;
    struct Node* prev;
    struct Node* next;
} Node;

// DLL functions
Node* createNode(int digit);
void insertEnd(Node** head, int digit);
void displayNumber(Node* head);
Node* reverseList(Node* head);

#endif
