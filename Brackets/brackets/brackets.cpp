#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define STACK_MAX_SIZE 100

typedef struct Stack_tag {
    char data[STACK_MAX_SIZE];
    int size;
} Stack_t;

void push(Stack_t* stack, char value) {
    stack->data[stack->size] = value;
    stack->size++;
    /*printf_s("%c", value);*/
}

int pop(Stack_t* stack) {
    stack->size--;
    return stack->data[stack->size];
}

int main(int argc, char* argv[])
{
    Stack_t stack;
    stack.size = 0;
    char rew[] = "-help";
    if (_strcmpi(argv[1], rew) == 0) {
        printf("Help\n");
        return 0;
    }
    FILE* fp1;
    fopen_s(&fp1, argv[1], "r");
    if (fp1 == NULL)
    {
        printf("Error:File1\n");
        return 0;
    }
    else
        printf("File1 is opened\n");
    int r = 0;
    char str[50];
    fgets(str, 80, fp1);
    int m = strlen(str);
    int a = 0;
    int b = 0;
    int t = 0;
    for (int i = 0; i < m; i++) {
        if (str[i] == '"')
        {
            a++;
            continue;
        }
        if (str[i] == '\'')
        {
            b++;
            continue;
        }
        if (a % 2 != 0 || b % 2 != 0)
            continue;
        if (str[i] == '(')
        {
            printf("%c", str[i]);
            push(&stack, str[i]);
            t++;
        }
        else if (str[i] == ')')
        {
            t++;
            if (stack.data[stack.size - 1] == '(') {
                pop(&stack);
                printf("%c", str[i]);
                continue;
            }
            printf("%c", str[i]);
            push(&stack, str[i]);
        }
        else if (str[i] == '[')
        {
            printf("%c", str[i]);
            push(&stack, str[i]);
            t++;
        }
        else if (str[i] == ']')
        {
            t++;
            if (stack.data[stack.size - 1] == '[') {
                pop(&stack);
                printf("%c", str[i]);
                continue;
            }
            printf("%c", str[i]);
            push(&stack, str[i]);
        }
        else if (str[i] == '{')
        {
            printf("%c", str[i]);
            push(&stack, str[i]);
            t++;
        }
        else if (str[i] == '}') {
            t++;
            if (stack.data[stack.size - 1] == '{') {
                pop(&stack);
                printf("%c", str[i]);
                continue;
            }
            printf("%c", str[i]);
            push(&stack, str[i]);
        }
    }
    if (t == 0)
    {
        printf("Error: there are no brackets in the file");
        return 0;
    }
    if (stack.size == 0)
        printf("\nEverything is OK!");
    else
        printf("\nWrong!");
    return 0;
}