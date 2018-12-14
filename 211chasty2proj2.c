#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Cody Hasty
CS 211 W 3-450
chasty2 663068521
Project 2: Balanced Symbol Checker
Written in: Code::Blocks on Windows 10
*/

//setup booleans
#define TRUE 1
#define FALSE 0
//debug mode
int debugMode = 0;

//------------------------------------------------------------------

typedef struct stack{
    int size;   //space allocated
    int top;    //top of stack
    char *darr;  //pointer to dynamic array
}stack;

//------------------------------------------------------------------

//initializeStack creates the struct that will
//demonstrate the properties of the stack
void initializeStack (stack *s)
{
    s->size = 2;
    char *array = (char*)malloc(sizeof(char)*(s->size));
    s->darr = array;
    s->top = 0;
}

//------------------------------------------------------------------

//push checks the amount of space currently on
//the stack, and grows it if necessary. Then,
//it adds value to the top of the stack
void push(stack *s, int value, int debugMode)
{
    if(debugMode == TRUE){
        printf("\nDEBUG MODE: PUSH\n");
    }
    if(s->top == s->size){
        //grow array
        int i = 0;
        //malloc new array & copy values over
        char *temp = (char*)malloc((sizeof(char)*(s->size))+2);
        for(i = 0; i < s->size; i++){
            temp[i] = s->darr[i];
        }
        if(debugMode == TRUE){
            printf("\nNumber of values copied: %d\n", i);
        }
        //free old array and update size
        free(s->darr);
        s->darr = temp;
        if(debugMode == TRUE){
            printf("\nOld size: %d", s->size);
        }
        s->size +=2;
        if(debugMode == TRUE){
            printf("\nNew size: %d", s->size);
        }
    }

    //add value to stack
    s->darr[s->top] = value;
    if(debugMode == TRUE){
            printf("\n%c pushed onto stack\n", s->darr[s->top]);
    }

    //increment top
    (s->top) += 1;
    if(debugMode == TRUE){
            printf("\nNew top value: %d", s->top);
    }
}//end push

//------------------------------------------------------------------

//isEmpty checks if the stack is empty
int isEmpty (stack* s)
{
  if ( s->top == 0)
    return TRUE;
  else
    return FALSE;
}//end isEmpty

//------------------------------------------------------------------

//the pop function removes the character on the top of the stack
//from the array
void pop(stack *s, int debugMode)
{
    if(debugMode == TRUE){
        printf("\nDEBUG MODE: POP\n");
        printf("\n%c popped off stack", s->darr[s->top]);
    }
    //decrement top
    (s->top) -= 1;
    if(debugMode == TRUE){
        printf("\nNew top value: %d\n", s->top);
    }
    //pop off top value
    s->darr[s->top] = 0;
}//end pop

//------------------------------------------------------------------

//returnTop returns the top of the array
char returnTop(stack *s)
{
    return s->darr[s->top - 1];
}//end returnTop

//------------------------------------------------------------------

//reset stack empties and reallocates a stack of default size
void resetStack(stack *s)
{
	s->size = 2;
	s->top = 0;
	char *newDarr = (char*)malloc(sizeof(char)*(s->size));
	free(s->darr);
	s->darr = newDarr;
}//end resetStack

//------------------------------------------------------------------

//printStack, well, prints the stack

void printStack(stack*s)
{
    int i = 0;
    printf("Stack: ");
    for(i = 0; i < s->size; i++){
        printf("%c ", s->darr[i]);
    }
    printf("\n\n");
}//end printStack

//------------------------------------------------------------------

int main(int argc, char** argv)
{
    //declare variables
    int maxLength = 300;
    int antiInfiniteLoop = 0;
    char input[maxLength];
    char symbol = 0;
    int balanceCheck = 1;
    int i = 0;
    int j = 0;
    stack s;
    initializeStack(&s);

    //initialize debugMode
    for(i = 0; i < argc; i++){
        if(strcmp(argv[i], "-d") == 0){
            printf("\nDEBUG MODE ON\n");
            debugMode = TRUE;
        }
    }

    //while loop runs symbol checker
    while(antiInfiniteLoop < 1000){
        //read in input from stdin
        fgets(input, maxLength, stdin);

        //quit if q or Q is input
        if(input[0] == 'q' || input[0] == 'Q'){
            printf("\nExiting Program...Goodbye\n\n");
            break;
        }

        //for loop enters symbols into stack and checks balance
        for(i = 0; i < strlen(input)-1; i++){
            if(input[i] == '(' || input[i] == '{' || input[i] == '[' || input[i] == '<'){
                push(&s, input[i], debugMode);
            }
            //check stack if closing symbol is encountered
            if(input[i] == ')' || input[i] == '}' || input[i] == ']' || input[i] == '>'){
                if(input[i] == ')'){
                    symbol = '(';
                }
                else if(input[i] == '}'){
                    symbol = '{';
                }
                else if(input[i] == ']'){
                    symbol = '[';
                }
                else {
                    symbol = '<';
                }
            
                //pop stack if closing symbol matches top of stack
                if(returnTop(&s) == symbol){
                    pop(&s, debugMode);
                    continue;
                }
            
                //break if missing symbol
                if(returnTop(&s) != symbol){
                    if(isEmpty(&s) == 0){
                        if(returnTop(&s) == '('){
                            symbol = ')';
                        }
                        else if(returnTop(&s) == '{'){
                            symbol = '}';
                        }
                        else if(returnTop(&s) == '['){
                            symbol = ']';
                        }
                        else{
                            symbol = '>';
                        }

                        for(j = 0; j< i; j++){
                            printf(" ");
                        }
                        printf("^ missing %c\n\n", symbol);
                        break;
                    }
                    else if(isEmpty(&s) == 1){
                        for(j = 0; j < i; j++){
                            printf(" ");
                            printf("^ missing %c\n\n", symbol);
                            balanceCheck = 0;
                            break;
                        }
                    }
                    
                }
            }
        }//end for loop

        //missing symbol & unbalanced
        if(isEmpty(&s) == 0){
                if(returnTop(&s) == '('){
                    symbol = ')';
                }
                else if(returnTop(&s) == '{'){
                    symbol = '}';
                }
                else if(returnTop(&s) == '['){
                    symbol = ']';
                }
                else{
                    symbol = '>';
                }

                for(j = 0; j< i; j++){
                    printf(" ");
                }
                printf("^ missing %c\n\n", symbol);
        }
        //balanced array
        if (balanceCheck == 1){
            if(isEmpty(&s) == TRUE){
                printf("Expression is balanced\n\n");
                continue;
            }
        }
        resetStack(&s);
    }// end while loop
    return 0;
}
