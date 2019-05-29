// tempevaluation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>      
#include<ctype.h>     
#include<string.h>

#define SIZE 100
int stack1[SIZE];
int top1 = -1;
char stack[SIZE];
int top = -1;
void push(char item)
{
	if (top >= SIZE - 1)
	{
		printf("\nStack Overflow.");
	}
	else
	{
		top = top + 1;
		stack[top] = item;
	}
}

char pop()
{
	char item;

	if (top <0)
	{
		printf("stack under flow: invalid infix expression");
		getchar();
		exit(1);
	}
	else
	{
		item = stack[top];
		top = top - 1;
		return(item);
	}
}
int is_operator(char symbol)
{
	if (symbol == '^' || symbol == '*' || symbol == '/' || symbol == '+' || symbol == '-')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int precedence(char symbol)
{
	if (symbol == '^')
	{
		return(3);
	}
	else if (symbol == '*' || symbol == '/')
	{
		return(2);
	}
	else if (symbol == '+' || symbol == '-')
	{
		return(1);
	}
	else
	{
		return(0);
	}
}

void InfixToPostfix(char infix_exp[], char postfix_exp[])
{
	int i, j;
	char item;
	char x;

	push('(');
	strcat(infix_exp, ")");

	i = 0;
	j = 0;
	item = infix_exp[i];

	while (item != '\0')
	{
		if (item == '(')
		{
			push(item);
		}
		else if (isdigit(item) || isalpha(item))
		{
			int flag = 0;
			while (infix_exp[i] >= '0' && infix_exp[i] <= '9') {
				postfix_exp[j++] = infix_exp[i++];
				flag = 1;
			}
			postfix_exp[j++] = ' ';
			i--;
		}
		else if (is_operator(item) == 1)
		{
			x = pop();
			while (is_operator(x) == 1 && precedence(x) >= precedence(item))
			{
				postfix_exp[j] = x;
				j++;
				x = pop();
			}
			push(x);

			push(item);
		}
		else if (item == ')')
		{
			x = pop();
			while (x != '(')
			{
				postfix_exp[j] = x;
				j++;
				x = pop();
			}
		}
		else
		{
			printf("\nInvalid infix Expression.\n");
			getchar();
			exit(1);
		}
		i++;


		item = infix_exp[i];
	}
	if (top>0)
	{
		printf("\nInvalid infix Expression.\n");
		getchar();
		exit(1);
	}
	if (top>0)
	{
		printf("\nInvalid infix Expression.\n");
		getchar();
		exit(1);
	}


	postfix_exp[j] = '\0';
}

int isoperator(char symbol)
{
	if (symbol == '^' || symbol == '*' || symbol == '/' || symbol == '+' || symbol == '-')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void push1(int item)
{
	if (top1 >= SIZE - 1)
	{
		printf("\nstack1 Overflow.");
	}
	else
	{
		top1 = top1 + 1;
		stack1[top1] = item;
	}
}

int pop1()
{
	int item;

	if (top1 <0)
	{
		printf("stack1 under flow: invalid infix expression");
		getchar();
		exit(1);
	}
	else
	{
		item = stack1[top1];
		top1 = top1 - 1;
		return(item);
	}
}

int operate(char ch, int x, int y){
	if (ch == '+'){
		//printf("in plus %d %d", x, y);
		return x + y;
	}
	if (ch == '*')
	{
		//printf("x===%d y===%d", x, y);
		return x * y;
	}
	if (ch == '/')
		return x / y;
	if (ch == '-')
		return x - y;
	return 0;
}
int postfixeval(char *postfix){
	int i = 0;
	for (i = 0; postfix[i] != '\0'; i++){
		//printf("\n\n at %c stack1 is ", postfix[i]);
		if (postfix[i] == ' ')
			continue;
		else{
			if (isoperator(postfix[i])){
				int n1 = pop1();
				int n2 = pop1();
				int t = operate(postfix[i], n1, n2);
				push1(t);
			}
			else{
				int temp = 0;
				while (postfix[i] >= '0' && postfix[i] <= '9') {
					temp = temp * 10 + (postfix[i] - '0');
					i++;
				}
				push1(temp);
			}
		}
	}
	return pop1();
}

int main()
{
	char infix[SIZE], postfix[SIZE];
	printf("\nEnter Infix expression : ");
	gets(infix);

	InfixToPostfix(infix, postfix);
	printf("Postfix Expression: ");
	puts(postfix);
	printf("evaluation of postfix is %d", postfixeval(postfix));
	getchar();
	return 0;
}
