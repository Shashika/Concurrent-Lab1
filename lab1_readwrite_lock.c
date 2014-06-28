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
#include <math.h>



int totalcount=10000;
int insertcount;
int membercount ;
int deletecount; 
int isInsert = 1;
int isMember = 1;
int isDelete = 1;
int samplecount=25;

typedef struct node{
    int val;
    struct node *next;
}node;

typedef struct linkedlist{
    pthread_rwlock_t rwlock;
    node *head;
}linkedlist;


int init(linkedlist *list){
    if(list->head!=NULL){
        node* temp1=list->head;
        node* temp2=temp1->next;
        while(temp2!=NULL){
            free(temp1);
            temp1=temp2;
            temp2=temp2->next;
        }
        free(temp1);
    }
    list->head=NULL;
    pthread_rwlock_init(&(list->rwlock),NULL);
}


linkedlist list;

int member(int value, linkedlist *list){
    
    node *head=list->head;
    struct node* temp = head;
    
    pthread_rwlock_wrlock(&(list->rwlock)); //locking to avoid reading/changing "membercount" by others 
    if(membercount > 0){
        membercount--;
        pthread_rwlock_unlock(&(list->rwlock));
    }
    else{
        isMember = 0;
        pthread_rwlock_unlock(&(list->rwlock));
        return 0;
    }
 
    pthread_rwlock_rdlock(&(list->rwlock)); //locking to avoid writing to the list by others
    while(temp != NULL && temp->val < value){
        temp = temp->next;
    }
    if(temp == NULL || temp->val > value){
        pthread_rwlock_unlock(&(list->rwlock));
        return 0;
    }
    else{
        pthread_rwlock_unlock(&(list->rwlock));
        return 1;
    }
}


int insert(int value, linkedlist *list){
    
    node *head=list->head;
    struct node* temp = head;
    struct node* curr = head;
    struct node* pred = NULL;
    
    pthread_rwlock_wrlock(&(list->rwlock));
    
    if(insertcount > 0){
        insertcount--;
    }
    else{
        isInsert = 0;
        pthread_rwlock_unlock(&(list->rwlock));
        return 0;
    }
    
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
        pthread_rwlock_unlock(&(list->rwlock));
        return 1;
    }
    else{
        pthread_rwlock_unlock(&(list->rwlock));
        return 0;
    }
}


int delete(int value, linkedlist *list){
    
    node *head=list->head;
    struct node* temp = head;
    struct node* curr = head;
    struct node* pred = NULL;
    
    pthread_rwlock_wrlock(&(list->rwlock));
    
    if(deletecount > 0){
        deletecount--;
    }
    else{
        isDelete = 0;
        pthread_rwlock_unlock(&(list->rwlock));
        return 0;
    }
    
    while(curr != NULL && curr->val < value){
        pred = curr;
        curr = curr->next;        
    }
    
    if(curr != NULL && curr->val == value){
        if(pred == NULL){
            list->head = curr->next;
        }
        else{
            pred->next = curr->next;
            free(curr);
        }
        pthread_rwlock_unlock(&(list->rwlock));
        return 1;
    }
    else{
        pthread_rwlock_unlock(&(list->rwlock));
        return 0;
    }
}


void printAllData(linkedlist *list){
    node *temp =list->head;
    while(temp!=NULL){
        printf("%d->",temp->val);
        temp=temp->next;
    }
}

void populate(linkedlist *list,int count){
    int i,result;
    double ran;
    
    insertcount=10000;
    isInsert=1;
    
    for(i = 0; i<count; i++){
        
        while(1){
            ran = rand() % 10000;
            result = insert(ran,list);
            if(result == 1){
                break;
            }
        }
    }
}

double getMean(double values[],int count){
    int i;
    double total=0;
    for(i=0;i<count;i++){
        total+=values[i];
    }
    return total/count;
}

double getStD(double values[],int count,double mean){
    int i;
    double total=0;
    for(i=0;i<count;i++){
        total+=pow(values[i]-mean,2);
    }
    return pow(total/(count-1),0.5);
}


void* Thread_run(void* id) {
    while(isInsert != 0 || isDelete != 0 || isMember != 0){
        int ran = rand() % 3;
        int random = rand() % 10000;
        if(ran == 0){//insert
            insert(random,&list);
        }else if(ran == 1){
            delete(random,&list);
        }
        else{
            member(random,&list);
        }
    }
}  

int main() {

 
    double start, finish, elapsed,mean,std;
    double elapsedAll[samplecount];
    int i,run,s;
    int thread;
    float insertp,memberp;
    int thread_count=1;   
    pthread_t * thread_handles;
    
    
    for(run=0 ; run<3 ;run++){
        
        if(run==0){
            memberp=0.99;
            insertp=0.005;
        }else if(run==1){
            memberp=0.90;
            insertp=0.05;
        }else{
            memberp=0.50;
            insertp=0.25;
        }
        
        printf("\n===================\nRun %d started...\n",run);
        
        for(thread_count=1;thread_count<=4;thread_count*=2){

            printf("\nUsing Configs:\n");
            printf("Member% = %f\n",memberp);
            printf("Insert% = %f\n",insertp);
            printf("Delete% = %f\n",1-memberp-insertp);
            printf("Thread Count = %d\n",thread_count);
        
            for(s=0;s<samplecount;s++){
                
                init(&list);
                populate(&list,1000);
                
                insertcount = totalcount*insertp;
                membercount = totalcount*memberp;
                deletecount = totalcount*(1-insertp-memberp);

                isInsert = 1;
                isMember = 1;
                isDelete = 1;

                thread_handles = (pthread_t*) malloc (thread_count*sizeof(pthread_t)); 

                thread = 0;
                GET_TIME(start);
                for (thread = 0; thread < thread_count; thread++)  {
                    pthread_create(&thread_handles[thread], NULL,Thread_run, (void*)(&run));  
                }

                for (thread = 0; thread < thread_count; thread++) 
                    pthread_join(thread_handles[thread], NULL); 
                GET_TIME(finish);

                elapsed=finish-start;
                elapsedAll[s]=elapsed;
                printf("Sample %d elapsed : %f\n",s,elapsed);
                //printAllData(&list);
                free(thread_handles);
            }

            mean=getMean(elapsedAll,samplecount);
            std=getStD(elapsedAll,samplecount,mean);

            printf("\nResults:\n");
            printf("Avg Time = %f\n",mean);
            printf("StD Time = %f\n",std);
            printf("-------------\n");
        
        }
        
        printf("\nRun %d finished....\n",run);

    }
}

 