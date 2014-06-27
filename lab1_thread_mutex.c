/* 
 * File:   lab1_1.c
 * Author: shashika
 *
 * Created on June 26, 2014, 2:00 PM
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "timer.h"




typedef struct node{
    int val;
    struct node *next;
}node;

typedef struct linkedlist{
    pthread_mutex_t lock;
    node *head;
}linkedlist;


int init(linkedlist *list){
    list->head=NULL;
    pthread_mutex_init(&(list->lock), NULL);
}

int member(int value, linkedlist *list){
    
    node *head=list->head;
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


int insert(int value, linkedlist *list){
    
    node *head=list->head;
    struct node* temp = head;
    struct node* curr = head;
    struct node* pred = NULL;
    
    pthread_mutex_lock(&(list->lock));
    
    while(curr != NULL && curr->val < value){
        pred = curr;
        curr = curr->next;
    }
    if(curr == NULL || curr->val > value){
        temp = malloc(sizeof(struct node));
        temp->val = value;
        temp->next = curr;
        
        if(pred == NULL){
            list->head = temp;
        }
        else{
            pred->next = temp;
        }
        pthread_mutex_unlock(&(list->lock));
        return 1;
    }
    else{
        pthread_mutex_unlock(&(list->lock));
        return 0;
    }
}

int delete(int value, linkedlist *list){
    
    node *head=list->head;
    struct node* temp = head;
    struct node* curr = head;
    struct node* pred = NULL;
    
    while(curr != NULL && curr->val < value){
        pred = curr;
        curr = curr->next;        
    }
    
    if(curr != NULL && curr->val == value){
        if(pred == NULL){
            list->head = curr->next;
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



void* Thread_sum(void* rank) {
   return NULL;
}  



int main() {

    linkedlist list;
    init(&list);
    
    double start, finish, elapsed;
    int i;
    int thread_count=2;
    int thread;

    pthread_t * thread_handles;
    thread_handles = (pthread_t*) malloc (thread_count*sizeof(pthread_t)); 
    
   GET_TIME(start);
   for (thread = 0; thread < thread_count; thread++)  
      pthread_create(&thread_handles[thread], NULL,Thread_sum, thread);  

   for (thread = 0; thread < thread_count; thread++) 
      pthread_join(thread_handles[thread], NULL); 
   GET_TIME(finish);
   
   
    /*
    GET_TIME(start);
    for(i = 0; i<5; i++){
        insert(i,&list);
    }
    GET_TIME(finish);
    
     */
   
    printf("%f",(finish-start));
    
    
    
}
