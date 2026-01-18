#include <stdio.h>
#include <stdlib.h>
#include "dll.h"

// Create a new node
Node* createNode(int digit) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->digit = digit;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Insert at the end of DLL
void insertEnd(Node** head, int digit) {
    Node* newNode = createNode(digit);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next) temp = temp->next;
    temp->next = newNode;
    newNode->prev = temp;
}

// Display number
void displayNumber(Node* head) {
    while (head) {
        printf("%d", head->digit);
        head = head->next;
    }
    printf("\n");
}

// Reverse DLL
Node* reverseList(Node* head) {
    Node* prev = NULL;
    Node* curr = head;
    Node* next;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        curr->prev = next;
        prev = curr;
        curr = next;
    }
    return prev;
}
