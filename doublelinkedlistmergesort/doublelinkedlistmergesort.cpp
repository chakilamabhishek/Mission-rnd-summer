// doublelinkedlistmergesort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include<stdio.h>

#include<stdlib.h>

struct node {
	int data;
	struct node*left;
	struct node *right;
};

void print(struct node*temp){
	while (temp->right){
		printf("%d-->", temp->data);
		temp = temp->right;
	}
	printf("%d", temp->data);
}

struct node * createnewnode(int data){
	struct node *temp = (struct node*)malloc(sizeof(struct node*));
	temp->data = data;
	temp->left = temp->right = NULL;
	return temp;
}

struct node* create(int *temp, int size){
	int i;
	struct node *head=NULL,*tempnode=NULL,*newnode;
	for (i = 0; i < size; i++){
		if (head == NULL){
			head = createnewnode(temp[i]);
			tempnode = head;
		}
		else{
			newnode = createnewnode(temp[i]);
			newnode->left = tempnode;
			tempnode->right = newnode;
			tempnode = newnode;
		}
	}
	return head;
}
struct node* merge(struct node*l1, struct node*l2){
	if (l1 == NULL)
		return l2;
	if (l2 == NULL)
		return l2;
	struct node *temp;
	while (l1->right&&l2->right){
		if (l1->data > l2->data){
			temp = l1->right;
			l1->right = l2->right;
			l2->right = l1;
			if (l1->right->left)
				l1->right->left = l1;
			l1->left = l2;
			l1 = temp;
		}
		else{
			temp = l2->right;
			l2->right = l1->right;
			if (l1->right->left)
				l1->right->left = l2;
			l1->right = l2;
			l2->left = l1;
			l2 = temp;
		}
	}
	return NULL;
}
struct node* mergesort(struct node* head,int size){
	int i = 0,n=size/2;
	struct node* temp=head,*prev,*l1,*l2;
	if (size > 1){
		for (i = 0; i < n - 1; i++){
			temp = temp->right;
		}
		prev = temp->right;
		temp->right = NULL;
		l1=mergesort(head, n);
		l2=	mergesort(prev, size - n);
		return merge(l1, l2);
	}
}

int main(){
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8 }, size = 8;
	struct node*head = create(arr, size);
	//print(head);
	head=mergesort(head, 8);
	print(head);
	getchar();
	return 0;
}
