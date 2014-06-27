
#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
/*struct node{
    int val;
    struct node *next;
}*head,*var;


void insert(int value){
    
    var = malloc(sizeof(struct node));
    var->val = value;
    
    if(head == NULL){
        
        head = var;
        var->next = NULL;
    }
    else{
        var->next = head;
        head = var;
    }
}

void printList(){

    struct node *temp;
    temp = head;
    
    while(temp != NULL){
        int val = temp->val;
        printf("%d\n",val);
        temp = temp->next;
    }
}

int member(int value, struct node* head){
    
    struct node* temp = head;
  
    int co = 0;
    
     while(temp != NULL){
         if(temp->val == value){
             co++;
         }
         temp = temp->next;
     }
    return co;
}

int delete(int value){

    struct node *temp;
    temp = head;
    
    int co = 0;
    
     while(temp != NULL){
         if(temp->val == value){
             co++;
         }
         temp = temp->next;
     }
    return co;
}

int main() {

    insert(2);
    insert(4);
    insert(1);
    printList();
//    printf("%d",member(5));
}

*/