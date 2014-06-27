/* 
 * File:   lab1_1.c
 * Author: shashika
 *
 * Created on June 26, 2014, 2:00 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

struct node{
    int val;
    struct node *next;
};

int member(int value, struct node* head){
    
    struct node* temp = head;
    
    while(temp != NULL && temp->val < value){
        temp = temp->next;
    }
    if(temp == NULL || temp->val > value){
        return 0;
    }
    else{
        return 1;
    }
}

int insert(int value, struct node** head){
    struct node* curr = *head;
    struct node* pred = NULL;
    struct node* temp;
    
    while(curr != NULL && curr->val < value){
        pred = curr;
        curr = curr->next;
    }
    if(curr == NULL || curr->val > value){
        temp = malloc(sizeof(struct node));
        temp->val = value;
        temp->next = curr;
        
        if(pred == NULL){
            *head = temp;
        }
        else{
            pred->next = temp;
        }
        return 1;
    }
    else{
        return 0;
    }
}

int delete(int value, struct node** head){

    struct node* curr = *head;
    struct node* pred = NULL;
    
    while(curr != NULL && curr->val < value){
        pred = curr;
        curr = curr->next;        
    }
    
    if(curr != NULL && curr->val == value){
        if(pred == NULL){
            *head = curr->next;
            free(curr);
        }
        else{
            pred->next = curr->next;
            free(curr);
        }
        return 1;
    }
    else{
        return 0;
    }
}


int main() {

    struct node* head;
    double start, finish, elapsed;
    int i;
    
    /*GET_TIME(start);
    //printf("%f",start);
    insert(4,&head);
    printf("%d",member(5,head));
    GET_TIME(finish);
    //elapsed = finish - start;
    printf("%f",(finish-start));*/
    
    GET_TIME(start);
    for(i = 0; i<1000; i++){
        insert(i,&head);
    }
    GET_TIME(finish);
    
    printf("%f",(finish-start));
}

