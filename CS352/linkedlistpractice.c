#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
	int data;
	struct Node* next;
};

struct Node* head;
Insert(int x)
{
	if (head == NULL)
	{
		struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
		temp->data = x;
		temp->next = head;
		head = temp;
	}
	else
	{
		struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
		temp->data = x;
		temp->next = NULL;
		struct Node* temp1 = head;
		while(temp1->next != NULL)
		{
			temp1 = temp1->next;
		}
		temp1->next = temp;
	}
}
SymbolTable()
{
	struct Node* temp = head;
	while(temp != NULL)
	{
		printf("lineno %d (pos)", temp->data);
		temp = temp->next;
		printf("\n");
	}
	printf("\n");
}
main(){

	head = NULL;
	printf("How many numbers?\n");
	int n, i, x;
	scanf("%d",&n);
	for(i = 0; i < n; i++)
	{
		printf("Enter the number \n");
		scanf("%d", &x);
		Insert(x);
	}
		SymbolTable(x);
}