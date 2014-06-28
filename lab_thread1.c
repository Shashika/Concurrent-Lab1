/* 
 * File:   lab1_1.c
 * Author: shashika
 *
 * Created on June 26, 2014, 2:00 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "timer.h"
#include <stdlib.h>
#include <math.h>

int totalcount=10000;
int samplecount=25;
int insertcount;
int membercount ;
int deletecount; 
int isInsert;
int isMember;
int isDelete;

typedef struct node{
    int val;
    struct node *next;
}node;

struct node* head=NULL;

int init(struct node** head){
    if(*head!=NULL){
        node* temp1=*head;
        node* temp2=temp1->next;
        while(temp2!=NULL){
            free(temp1);
            temp1=temp2;
            temp2=temp2->next;
        }
        free(temp1);
    }
    *head=NULL;
}

int member(int value, struct node* head){
    
    struct node* temp = head;
    
    if(membercount > 0){
        membercount--;
    }
    else{
        isMember = 0;
        return 0;
    }
    
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
    
    if(insertcount > 0){
        insertcount--;
    }
    else{
        isInsert = 0;
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
    
    if(deletecount > 0){
        deletecount--;
    }
    else{
        isDelete = 0;
        return 0;
    }
    
    while(curr != NULL && curr->val < value){
        pred = curr;
        curr = curr->next;        
    }
    
    if(curr != NULL && curr->val == value){
        if(pred == NULL){
            *head = curr->next;
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



void printAllData(struct node** head){
    node *temp =*head;
    while(temp!=NULL){
        printf("%d->",temp->val);
        temp=temp->next;
    }
}

void populate(struct node** head,int count){
    int i,result;
    double ran;
    
    for(i = 0; i<count; i++){
        insertcount=count;
        while(1){
            ran = rand() % 10000;
            result = insert(ran,head);
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


void serial_run() {
    while(isInsert != 0 ){// || isMember != 0 || isDelete != 0){
        int ran = rand() % 1;
        int random = rand() % 10000;
        if(ran == 0){//insert
            insert(random,&head);
        }else if(ran == 1){
            member(random,head);
        }
        else{
            delete(random,&head);
        }
    }
}  

int main() {

    
    int i,ran,result,run,s;
    double start, finish, elapsed,mean,std;
    double elapsedAll[samplecount];
    float insertp,memberp;
    
    printf("Enter sample count :");
    scanf("%d",&samplecount);
    
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
        printf("\nUsing Configs:\n");
        printf("Member%% = %f\n",memberp);
        printf("Insert%% = %f\n",insertp);
        printf("Delete%% = %f\n",1-memberp-insertp);

        for(s=0;s<samplecount;s++){

            init(&head);
            populate(&head,1000);

            insertcount = totalcount*insertp;
            membercount = totalcount*memberp;
            deletecount = totalcount*(1-insertp-memberp);

            isInsert = 1;
            isMember = 1;
            isDelete = 1;


            GET_TIME(start);
            serial_run();
            GET_TIME(finish);

            elapsed=finish-start;
            elapsedAll[s]=elapsed;
            printf("Sample %d elapsed : %f\n",s,elapsed);
            //printAllData(&list);
        }
        mean=getMean(elapsedAll,samplecount);
        std=getStD(elapsedAll,samplecount,mean);

        printf("\nResults:\n");
        printf("Avg Time = %f\n",mean);
        printf("StD Time = %f\n",std);
        printf("-------------\n");

        printf("\nRun %d finished....\n",run);

    }
    
    
}

