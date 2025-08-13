#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100


struct Stack {
    int top;
    char items[MAX_SIZE];
};

void initializeStack(struct Stack *s) {
    s->top = -1;
}

int isEmpty(struct Stack *s) {
    return s->top == -1;
}

int isFull(struct Stack *s) {
    return s->top == MAX_SIZE - 1;
}

void push(struct Stack *s, char item) {
    if (isFull(s)) {
        printf("Stack Overflow Error\n");
    } else {
        s->items[++s->top] = item;
    }
}

char pop(struct Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow Error\n");
        return -1; 
    } else {
        return s->items[s->top--];
    }
}

char peek(struct Stack *s) {
    if (isEmpty(s)) {
        return -1; 
    }
    return s->items[s->top];
}


int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^': 
            return 3;
        default:
            return 0; 
    }
}

void infixToPostfix(char* infix, char* postfix) {
    struct Stack s;
    initializeStack(&s);

    int i = 0; 
    int j = 0; 
    char token;

    while ((token = infix[i++]) != '\0') {
        if (token == ' ' || token == '\t') {
            continue;
        }

        if (isalnum(token)) {
            postfix[j++] = token;
        }
        else if (token == '(') {
            push(&s, token);
        }
        else if (token == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[j++] = pop(&s);
            }
            if (!isEmpty(&s) && peek(&s) == '(') {
                pop(&s);
            }
        }
        else {
            while (!isEmpty(&s) && precedence(token) <= precedence(peek(&s))) {
                postfix[j++] = pop(&s);
            }
            push(&s, token);
        }
    }

    while (!isEmpty(&s)) {
        postfix[j++] = pop(&s);
    }

    postfix[j] = '\0';
}


int main() {
    char infix[MAX_SIZE];
    char postfix[MAX_SIZE];

    printf("Enter an infix expression: ");
    if (fgets(infix, sizeof(infix), stdin) != NULL) {
        infix[strcspn(infix, "\n")] = 0;
    }

    infixToPostfix(infix, postfix);

    printf("\nInfix Expression:   %s\n", infix);
    printf("Postfix Expression: %s\n", postfix);

    return 0;
}
