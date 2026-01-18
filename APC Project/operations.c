#include <stdio.h>
#include <stdlib.h>
#include "dll.h"

// Addition
Node* addNumbers(Node* num1, Node* num2) {
    Node* res = NULL;
    Node *tail1 = num1, *tail2 = num2;

    while (tail1 && tail1->next) tail1 = tail1->next;
    while (tail2 && tail2->next) tail2 = tail2->next;

    int carry = 0;
    while (tail1 || tail2 || carry) {
        int sum = carry;
        if (tail1) { sum += tail1->digit; tail1 = tail1->prev; }
        if (tail2) { sum += tail2->digit; tail2 = tail2->prev; }
        insertEnd(&res, sum % 10);
        carry = sum / 10;
    }
    return reverseList(res);
}

// Subtraction (num1 - num2, assume num1 >= num2)
Node* subtractNumbers(Node* num1, Node* num2) {
    Node* res = NULL;
    Node *tail1 = num1, *tail2 = num2;

    while (tail1 && tail1->next) tail1 = tail1->next;
    while (tail2 && tail2->next) tail2 = tail2->next;

    int borrow = 0;
    while (tail1) {
        int diff = tail1->digit - borrow - (tail2 ? tail2->digit : 0);
        if (diff < 0) { diff += 10; borrow = 1; }
        else borrow = 0;
        insertEnd(&res, diff);
        tail1 = tail1->prev;
        if (tail2) tail2 = tail2->prev;
    }

    // Remove leading zeros
    Node* temp = res;
    while (temp && temp->next) temp = temp->next;
    while (temp && temp->digit == 0 && temp->prev) {
        Node* toDelete = temp;
        temp = temp->prev;
        temp->next = NULL;
        free(toDelete);
    }

    return reverseList(res);
}

// Multiplication (num1 * num2)
Node* multiplyNumbers(Node* num1, Node* num2) {
    Node* res = createNode(0);

    Node *tail2 = num2;
    while (tail2 && tail2->next) tail2 = tail2->next;

    int pos2 = 0;
    for (Node* n2 = tail2; n2; n2 = n2->prev) {
        Node* tempRes = NULL;
        int carry = 0;

        Node *tail1 = num1;
        while (tail1 && tail1->next) tail1 = tail1->next;

        for (Node* n1 = tail1; n1; n1 = n1->prev) {
            int prod = n1->digit * n2->digit + carry;
            insertEnd(&tempRes, prod % 10);
            carry = prod / 10;
        }
        if (carry) insertEnd(&tempRes, carry);

        tempRes = reverseList(tempRes);

        for (int i = 0; i < pos2; i++) insertEnd(&tempRes, 0);

        Node* sum = addNumbers(res, tempRes);
        res = sum;
        pos2++;
    }

    return res;
}

// Helper: Compare two numbers (returns 1 if num1 >= num2 else 0)
int compareNumbers(Node* num1, Node* num2) {
    Node* t1 = num1;
    Node* t2 = num2;
    int len1 = 0, len2 = 0;

    while (t1) { len1++; t1 = t1->next; }
    while (t2) { len2++; t2 = t2->next; }

    if (len1 > len2) return 1;
    if (len1 < len2) return 0;

    t1 = num1; t2 = num2;
    while (t1 && t2) {
        if (t1->digit > t2->digit) return 1;
        if (t1->digit < t2->digit) return 0;
        t1 = t1->next;
        t2 = t2->next;
    }
    return 1; // equal
}

// Division (integer division)
Node* divideNumbers(Node* dividend, Node* divisor) {
    Node* quotient = NULL;
    Node* remainder = NULL;

    Node* current = dividend;
    while (current) {
        insertEnd(&remainder, current->digit);

        int count = 0;
        while (compareNumbers(remainder, divisor)) {
            Node* temp = subtractNumbers(remainder, divisor);
            remainder = temp;
            count++;
        }

        insertEnd(&quotient, count);
        current = current->next;
    }

    // Remove leading zeros in quotient
    Node* temp = quotient;
    while (temp && temp->next) temp = temp->next;
    while (temp && temp->digit == 0 && temp->prev) {
        Node* toDelete = temp;
        temp = temp->prev;
        temp->next = NULL;
        free(toDelete);
    }

    return quotient;
}
