#include <stdio.h>
#define MAX 100
/* ---------------- OPERATOR STACK ---------------- */
char operatorStack[MAX];
int operatorTop = -1;

void pushOperator(char ch)
{
    if (operatorTop == MAX - 1)
    {
        printf("Operator Stack Overflow\n");
        return;
    }
    operatorStack[++operatorTop] = ch;
}

char popOperator()
{
    if (operatorTop == -1)
    {
        printf("Operator Stack Underflow\n");
        return '\0';
    }
    return operatorStack[operatorTop--];
}

char peekOperator()
{
    if (operatorTop == -1)
        return '\0';
    return operatorStack[operatorTop];
}

int isOperatorEmpty()
{
    return operatorTop == -1;
}
/* ---------------- VALUE STACK ---------------- */
int valueStack[MAX];
int valueTop = -1;

void pushValue(int value)
{
    if (valueTop == MAX - 1)
    {
        printf("Value Stack Overflow\n");
        return;
    }
    valueStack[++valueTop] = value;
}

int popValue()
{
    if (valueTop == -1)
    {
        printf("Value Stack Underflow\n");
        return 0;
    }
    return valueStack[valueTop--];
}

int peekValue()
{
    if (valueTop == -1)
        return 0;
    return valueStack[valueTop];
}

int isValueEmpty()
{
    return valueTop == -1;
}
/* ---------------- PRIORITY ---------------- */
int priority(char ch)
{
    if (ch == '*' || ch == '/')
        return 2;

    if (ch == '+' || ch == '-')
        return 1;
    return 0;
}
/* ---------------- CHECK OPERATOR ---------------- */
int isOperator(char ch)
{
    if (ch == '+' || ch == '-' ||
        ch == '*' || ch == '/')
        return 1;
    return 0;
}
/* ---------------- CHECK DIGIT ---------------- */
int isDigit(char ch)
{
    if (ch >= '0' && ch <= '9')
        return 1;
    return 0;
}
/* ---------------- CALCULATE ---------------- */
int calculate(int a, int b, char op, int *success)
{
    if (op == '+')
    {
        return a + b;
    }

    if (op == '-')
    {
        return a - b;
    }

    if (op == '*')
    {
        return a * b;
    }
    if (op == '/')
    {
        if (b == 0)
        {
            printf("Error: Division by zero\n");
            *success = 0;
            return 0;
        }
        return a / b;
    }
    *success = 0;
    return 0;
}
/* ---------------- APPLY ONE OPERATOR ---------------- */
int applyOperator(int *success)
{
    /*  We need two operands. */
    if (valueTop < 1)
    {
        printf("Error: Missing operand\n");
        *success = 0;
        return 0;
    }
    int b = popValue();
    int a = popValue();
    char op = popOperator();
    int result = calculate(a, b, op, success);
    if (*success == 0)
        return 0;
    pushValue(result);
    return 1;
}
/* ---------------- EVALUATE INFIX ---------------- */
int evaluate(char str[], int *success)
{
    /* Reset stacks */
    operatorTop = -1;
    valueTop = -1;
    int expectingOperand = 1;
    int foundSomething = 0;
    int i = 0;
    while (str[i] != '\0')
    {
        char ch = str[i];
        /* Ignore spaces */
        if (ch == ' ' || ch == '\n' || ch == '\t')
        {
            i++;
            continue;
        }
        /* ---------- NUMBER ---------- */
        if (isDigit(ch))
        {
            /*
               If we already read a number or ')',
               another number means an operator is missing.
            */
            if (!expectingOperand)
            {
                printf("Error: Missing operator\n");
                *success = 0;
                return 0;
            }
            int number = 0;
            /*
               Read complete number.

               Example:
               23

               number = 2
               number = 2 * 10 + 3
                       = 23
            */
            while (isDigit(str[i]))
            {
                number = number * 10 + (str[i] - '0');
                i++;
            }
           pushValue(number);
            expectingOperand = 0;
            foundSomething = 1;
            continue;
        }
       /* ---------- OPENING PARENTHESIS ---------- */
        else if (ch == '(')
        {
            /*
               '(' can only come where an operand
               is expected.
               Example:
               2(3+4)  -> invalid
            */
            if (!expectingOperand)
            {
                printf("Error: Missing operator before '('\n");
                *success = 0;
                return 0;
            }
            pushOperator(ch);
            expectingOperand = 1;
            foundSomething = 1;
        }
        /* ---------- CLOSING PARENTHESIS ---------- */
        else if (ch == ')')
        {
            /*
               ')' cannot come immediately after
               an operator or '('.
            */
            if (expectingOperand)
            {
                printf("Error: Invalid expression near ')'\n");
                *success = 0;
                return 0;
            }
            /*
               Calculate everything inside parentheses.
            */
            while (!isOperatorEmpty() &&
                   peekOperator() != '(')
            {
                if (!applyOperator(success))
                    return 0;
            }
            /*
               If there is no '(' then ')' has no
               matching opening parenthesis.
            */
            if (isOperatorEmpty())
            {
                printf("Error: Mismatched parentheses\n");
                *success = 0;
                return 0;
            }
            /* Remove '(' */
            popOperator();
            expectingOperand = 0;
        }
        /* ---------- OPERATOR ---------- */
        else if (isOperator(ch))
        {
            /*
               Operator cannot appear when an operand
               is expected.

               Examples:
               +2
               2++3
               2+*3
            */
            if (expectingOperand)
            {
                printf("Error: Operator '%c' appears where an operand is expected\n",
                       ch);

                *success = 0;
                return 0;
            }
            /*
               Apply operators having greater or equal
               priority.

               Example:

               2 + 3 * 4

               When we see '*', '+' has lower priority,
               so '+' stays.

               For:
               2 * 3 + 4

               '*' has higher priority than '+',
               so '*' is applied first.
            */
            while (!isOperatorEmpty() &&
                   peekOperator() != '(' &&
                   priority(peekOperator()) >= priority(ch))
            {
                if (!applyOperator(success))
                    return 0;
            }
            pushOperator(ch);
            expectingOperand = 1;
        }
        /* ---------- INVALID CHARACTER ---------- */
        else
        {
            printf("Error: Invalid character '%c'\n", ch);
            *success = 0;
            return 0;
        }
        i++;
    }
    /* ---------- FINAL CHECKS ---------- */
    if (!foundSomething)
    {
        printf("Error: Empty expression\n");
        *success = 0;
        return 0;
    }
    /*
       If we are still expecting an operand,
       expression ended with an operator or '('.
       Example:
       2+
       (2+
       2*
    */
    if (expectingOperand)
    {
        printf("Error: Expression is incomplete\n");
        *success = 0;
        return 0;
    }
    /* ---------- APPLY REMAINING OPERATORS ---------- */
    while (!isOperatorEmpty())
    {
        /*
           If '(' remains, there is no matching ')'.
        */
        if (peekOperator() == '(')
        {
            printf("Error: Mismatched parentheses\n");
            *success = 0;
            return 0;
        }
        if (!applyOperator(success))
            return 0;
    }
    /*
       At the end there should be exactly
       one value in the value stack.
    */
    if (valueTop != 0)
    {
        printf("Error: Invalid expression\n");
        *success = 0;
        return 0;
    }
    *success = 1;
    return popValue();
}
/* ---------------- MAIN ---------------- */
int main()
{
    char str[MAX];
    int success;
    printf("Enter the expression: ");
    fgets(str, MAX, stdin);
    int answer = evaluate(str, &success);
    if (success)
    {
        printf("Result: %d\n", answer);
    }
    return 0;
}