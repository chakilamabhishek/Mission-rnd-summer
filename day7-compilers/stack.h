#include<stdio.h>
#define stacksize 50
int pop(int *stack, int *top){
	if (*top == -1){
		printf("stack is underflow");
		return -1;
	}
	else
	{
		int ans = stack[*top];
		*top = *top - 1;
		return ans;
	}
}

void push(int *stack,int *top,int data){
	if (*top >= stacksize)
		printf("stack overflow");
	else{
		*top = *top + 1;
		stack[*top] = data;
		
	}
}