#include <stdio.h>
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char ch)
{
    if (top == MAX - 1)
    {
        printf("Error: Stack overflow.\n");
        return;
    }

    stack[++top] = ch;
}

char pop()
{
    if (top == -1){
        //printf("Stack Underflow\n");
        return '\0';
    }
    return stack[top--];
}

char peek()
{
    if (top == -1){
       // printf("Stack Underflow\n");
        return '\0';
    }
    return stack[top];
}

int precedence(char ch)
{
    if (ch == '/' || ch == '*')
        return 2;

    if (ch == '+' || ch == '-')
        return 1;

    return 0;
}

int isOperator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

void infixToPostfix(char infix[], char postfix[])
{
    int i, j = 0;
    char ch;

    top = -1;

    for (i = 0; infix[i] != '\0'; i++)
    {
        ch = infix[i];

        /* Ignore spaces */
        if (ch == ' ')
            continue;

        /* Check whether ch is a digit */
        if (ch >= '0' && ch <= '9')
        {
            postfix[j++] = ch;
        }

        /* Opening parenthesis */
        else if (ch == '(')
        {
            push(ch);
        }

        /* Closing parenthesis */
        else if (ch == ')')
        {
            while (top != -1 && peek() != '(')
            {
                postfix[j++] = pop();
            }

            if (top == -1)
            {
                printf("Error: Mismatched parentheses.\n");
                postfix[0] = '\0';
                return;
            }

            pop();   /* Remove '(' */
        }

        /* Operator */
        else if (isOperator(ch))
        {
            while (top != -1 &&
                   peek() != '(' &&
                   precedence(peek()) >= precedence(ch))
            {
                postfix[j++] = pop();
            }

            push(ch);
        }

        /* Invalid character */
        else
        {
            printf("Error: Illegal character '%c'.\n", ch);
            postfix[0] = '\0';
            return;
        }
    }

    /* Pop remaining operators */
    while (top != -1)
    {
        if (peek() == '(')
        {
            printf("Error: Mismatched parentheses.\n");
            postfix[0] = '\0';
            return;
        }

        postfix[j++] = pop();
    }

    postfix[j] = '\0';
}

int main()
{
    char infix[MAX];
    char postfix[MAX];

    printf("Enter infix expression: ");
    fgets(infix, MAX, stdin);

    infix[strcspn(infix, "\n")] = '\0';

    infixToPostfix(infix, postfix);

    if (postfix[0] != '\0')
    {
        printf("Postfix expression: %s\n", postfix);
    }

    return 0;
}