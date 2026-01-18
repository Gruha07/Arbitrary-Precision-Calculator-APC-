#include <stdio.h>
#include "dll.h"

Node* addNumbers(Node* num1, Node* num2);
Node* subtractNumbers(Node* num1, Node* num2);
Node* multiplyNumbers(Node* num1, Node* num2);
Node* divideNumbers(Node* num1, Node* num2);

int main() {
    Node* num1 = NULL;
    Node* num2 = NULL;

    char str1[100], str2[100];
    printf("Enter first number: ");
    scanf("%s", str1);
    printf("Enter second number: ");
    scanf("%s", str2);

    for (int i = 0; str1[i]; i++) insertEnd(&num1, str1[i]-'0');
    for (int i = 0; str2[i]; i++) insertEnd(&num2, str2[i]-'0');

    Node* sum = addNumbers(num1, num2);
    Node* diff = subtractNumbers(num1, num2);
    Node* prod = multiplyNumbers(num1, num2);
    Node* quot = divideNumbers(num1, num2);

    printf("Sum: ");
    displayNumber(sum);
    printf("Difference: ");
    displayNumber(diff);
    printf("Product: ");
    displayNumber(prod);
    printf("Quotient: ");
    displayNumber(quot);

    return 0;
}
