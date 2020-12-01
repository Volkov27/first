#include <stdio.h>
#include <stdlib.h>

struct Stack{
    int num1[100];
    int size;
};

int push(int a, struct Stack * st){
    if(st->size==100){
        return 1;
    } else{
        st->num1[st->size++]=a;
        return 0;
    }
}

int pop(struct Stack * st, int * b){
    if(st->size==0){
        return 1;
    } else{
        *b = st->num1[st->size-- -1];
        return 0;
    }
}

void print(struct Stack * st){
    for(int i=0; i<st->size; i++){
        printf("\t%d\n", st->num1[st->size-i-1]);
    }
}

int main(int argc, char * argv[]){
    struct Stack Stack_1;
    int value, number;
    char oper;
    Stack_1.size=0;
    printf("'+[num]' to push element\n'-' to pop element\n'=' to print stack\n'x' to exit\n");
    while(1){
        printf(":");
        scanf(" %c", &oper);
        switch(oper){
            case '+':
                scanf("%d", &number);
                if(push(number, &Stack_1)){
                    printf("\tOverflow\n");
                };
                break;
            case '-':
                if(pop(&Stack_1, &value)){
                    printf("\tUnderflow\n");
                } else{
                    printf("\t%d\n", value);
                }
                break;
            case '=':
                print(&Stack_1);
                break;
            case 'x':
                printf("\tExit");
                return 0;
            default :
                printf("\tIncorrect operation");
                break;
        }
    }
    return 0;
}
