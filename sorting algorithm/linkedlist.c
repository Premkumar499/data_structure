#include<stdio.h>
#include<stdlib.h>

struct lnode
{
    int data;
    struct lnode* next;
};

typedef struct lnode node;

node* head = NULL;

void insertAtbeginning(int val){
    node* newNode = (node*)malloc(sizeof(node));
    if(newNode == NULL){
        printf("Out of memory\n");
        return;
    }
    newNode->data = val;
    newNode->next = head;
    head = newNode;
    printf("Value %d inserted at beginning\n", val);
}

void display(){
    if(head == NULL){
        printf("List is empty\n");
        return;
    }
    node* temp = head;
    printf("Linked List: ");
    while(temp != NULL){
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void insertThevalue(int pos, int val){
    if(pos < 1){
        printf("Position should be >= 1\n");
        return;
    }
    
    if(pos == 1){
        insertAtbeginning(val);
        return;
    }
    
    node* newNode = (node*)malloc(sizeof(node));
    if(newNode == NULL){
        printf("Out of memory\n");
        return;
    }
    
    newNode->data = val;
    
    node* temp = head;
    for(int i = 1; i < pos - 1 && temp != NULL; i++){
        temp = temp->next;
    }
    
    if(temp == NULL){
        printf("Position out of range\n");
        free(newNode);
        return;
    }
    
    newNode->next = temp->next;
    temp->next = newNode;
    printf("Value %d inserted at position %d\n", val, pos);
}

void deleteAtposition(int pos){
    if(head == NULL){
        printf("List is empty\n");
        return;
    }
    
    if(pos < 1){
        printf("Position should be >= 1\n");
        return;
    }
    
    node* temp = head;
    
    if(pos == 1){
        head = head->next;
        printf("Value %d deleted from position %d\n", temp->data, pos);
        free(temp);
        return;
    }
    
    for(int i = 1; i < pos - 1 && temp != NULL; i++){
        temp = temp->next;
    }
    
    if(temp == NULL || temp->next == NULL){
        printf("Position out of range\n");
        return;
    }
    
    node* nodeToDelete = temp->next;
    temp->next = nodeToDelete->next;
    printf("Value %d deleted from position %d\n", nodeToDelete->data, pos);
    free(nodeToDelete);
}

int main(){
    int choice, val, pos;
    while(1){
        printf("\n-------Linked List Menu--------\n");
        printf("1. Insert at beginning\n");
        printf("2. Display the list\n");
        printf("3. Insert at specific position\n");
        printf("4. Delete at specific position\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice)
        {
        case 1:
            printf("Enter the value: ");
            scanf("%d", &val);
            insertAtbeginning(val);
            break;
            
        case 2:
            display();
            break;
            
        case 3:
            printf("Enter the position: ");
            scanf("%d", &pos);
            printf("Enter the value: ");
            scanf("%d", &val);
            insertThevalue(pos, val);
            break;
            
        case 4:
            printf("Enter the position: ");
            scanf("%d", &pos);
            deleteAtposition(pos);
            break;
            
        case 5:
            printf("Exiting program...\n");
            exit(0);
            break;
            
        default:
            printf("Wrong choice! Please try again.\n");
            break;
        }
    }
    return 0;
}
