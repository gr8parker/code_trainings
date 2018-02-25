#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct node* createNode(int data)
{
    struct node *nd = NULL;
    nd = (struct node*)malloc(sizeof(struct node));
    
    nd->data = data;
    nd->next = NULL;

    return nd;
}

void push_front(struct node** head, int data)
{
    if (*head == NULL){
	*head = createNode(data);
	return;
    }
    
    struct node *nd = NULL;
    nd = (struct node*)malloc(sizeof(struct node));
    
    nd->data = data;
    nd->next = *head;

    *head = nd;    
}

int pop_front(struct node** head)
{
    struct node* front = *head;
    int data = front->data;
    
    *head = (*head)->next;
    
    free(front);
   
    return data;
}

int value_at(struct node* head, int index)
{
    struct node* current = head;
    while (--index >= 0) {
	current = current->next;
    }
    
    return current->data;
}

int length(struct node* head)
{
    if (head == NULL)
	return 0;
    
    int len = 1;
    while (head->next != NULL) {
	len++;
	head = head->next;
    }
    return len;
}

void push_back(struct node **head, int data)
{
    if (*head == NULL) {
	*head = createNode(data);
	return;
    }
    
    struct node* current = *head;
    while (current->next != NULL)
	current = current->next;
    
    struct node* nd = createNode(data);
    current->next = nd;
}

int pop_back(struct node **head)
{
    if ((*head)->next == NULL) {
	int data = (*head)->data;
	free(*head);
	*head = NULL;
	return data;
    }
	
    struct node* current = *head;
    while(current->next->next != NULL) {
	current = current->next;
    }
    
    int data = current->next->data;
    
    free(current->next);
    current->next = NULL;
    
    return data;
}

int front(struct node* head)
{
    return head->data;
}

int back(struct node* head)
{
    while(head->next != NULL)
	head = head->next;
    
    return head->data;
}

void insert(struct node** head, int index, int data)
{
    if (index == 0)
	return push_front(head, data);

    struct node* current = *head;
    while (--index > 1) {
	current = current->next;
    }
    
    struct node* nd = createNode(data);
    nd->next = current->next;
    
    current->next = nd;
}

void erace(struct node** head, int index)
{
    if (index == 0) {
       pop_front(head);
       return;
    }
    
    struct node* current = *head;
    while(--index > 1) {
	current = current->next;
    }
    
    struct node* to_remove = current->next;
    
    current->next = current->next->next;
    
    free(to_remove);
}

void remove_value(struct node **head, int value)
{
    int index = 0;
    struct node* current = *head;
    while (current->next != NULL && current->data != value) {
	index++;
	current = current->next;
    }

    if (current->next != NULL || current->data == value)
	erace(head, index);
}

void reverse(struct node **head) 
{
    struct node* newhead = NULL;
    struct node* current = *head;
    while (current != NULL) {
	push_front(&newhead, current->data);
	struct node* next = current->next;
	free(current);
	current = next;
    }
    *head = newhead;
}

void print(struct node* head)
{
    while (head != NULL){ 
	printf("%d ", head->data);
	head = head->next;
    }
    printf("\n");
}

int main()
{
}
