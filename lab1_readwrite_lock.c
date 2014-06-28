/* 
 * File:   lab1_readwrite_lock.c
 * Author: shashika
 *
 * Created on June 27, 2014, 4:35 PM
 */


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

/*

int totalcount=10;
int insertcount;
int membercount ;
int deletecount; 
int isInsert = 1;
int isMember = 1;
int isDelete = 1;



typedef struct node{
    int val;
    struct node *next;
}node;

typedef struct linkedlist{
    pthread_rwlock_t rwlock;
    node *head;
}linkedlist;


int init(linkedlist *list){
    list->head=NULL;
    pthread_rwlock_init(&(list->rwlock),NULL);
}

linkedlist list;

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
        if(membercount > 0){
            membercount--;
        }
        else{
            isMember = 0;
        }
        
        return 1;
    }
}


int insert(int value, linkedlist *list){
    
    node *head=list->head;
    struct node* temp = head;
    struct node* curr = head;
    struct node* pred = NULL;
    
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
        
        if(insertcount > 0){
            insertcount--;
        }
        else{
            isInsert = 0;
        }
        return 1;
    }
    else{
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
        
        if(deletecount > 0){
            deletecount--;
        }
        else{
            isDelete = 0;
        }
        return 1;
    }
    else{
        return 0;
    }
}

void* Thread_run(void* id) {
    while(isInsert != 0 || isDelete != 0 || isMember != 0){
        int ran = rand() % 3;

        if(ran == 0){//insert
            int random = rand() % 10000;
            pthread_rwlock_wrlock(&(list->rwlock));
            insert(random,&list);
            pthread_rwlock_unlock(&(list->rwlock));
        }else if(ran == 1){
            int random = rand() % 10000;
            pthread_rwlock_rdlock(&(list->rwlock));
            member(random,&list);
            pthread_rwlock_unlock(&(list->rwlock));
        }
        else{
            int random = rand() % 10000;
            pthread_rwlock_wrlock(&(list->rwlock));
            delete(random,&list);
            pthread_rwlock_unlock(&(list->rwlock));
        }
    }
}  



int main() {

 
    init(&list);
    insertcount = totalcount*0.5;
    membercount = totalcount*0.3;
    deletecount = totalcount*0.2;
    
    double start, finish, elapsed;
    int i;
    int thread_count=2;
    int thread;

    pthread_t * thread_handles;
    thread_handles = (pthread_t*) malloc (thread_count*sizeof(pthread_t)); 
    
   GET_TIME(start);
   for (thread = 0; thread < thread_count; thread++)  
      pthread_create(&thread_handles[thread], NULL,Thread_run, (void*)thread);  

   for (thread = 0; thread < thread_count; thread++) 
      pthread_join(thread_handles[thread], NULL); 
   GET_TIME(finish);
      
    printf("%f\n",(finish-start)); 
}

 */