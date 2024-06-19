#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct process
{
    int process_id , arrival_time, burst_time, waiting_time, turn_around_time, remaining_time, completion_time;
};
//i will create 3 queues and 3 waititng queues one before each main queue
//sizes of q0 is 10 and q1 size 20 and q2 size 30
struct process QUEUE0[10], QUEUE1[20], QUEUE2[30];
struct process WaitQ0[200], WaitQ1[200], WaitQ2[100];
int sum_of_pro ;
int n;
int headQ0 = 0, tailQ0 = 0;
int headQ1 = 0, tailQ1 = 0;
int headQ2 = 0, tailQ2 = 0;

// Helper function to remove element and shift all elements to the right
// Helper function to add a process to the waiting queue
void addToWaitQueue(struct process process, int queueNumber)
{
    switch (queueNumber)
    {
    case 0:
        WaitQ0[tailQ0++] = process;
        break;
    case 1:
        WaitQ1[tailQ1++] = process;
        break;
    case 2:
        WaitQ2[tailQ2++] = process;
        break;
    }
}

// Helper function to extract a process from a waiting queue
struct process removeFromWaitQueue(int queueNumber)
{
    struct process process;
    switch (queueNumber)
    {
    case 0:
        process = WaitQ0[headQ0++];
        break;
    case 1:
        process = WaitQ1[headQ1++];
        break;
    case 2:
        process = WaitQ2[headQ2++];
        break;
    }
    return process;
}

// This function is used to generate 100 random processes with ids from 1 to 100 and with random burst time(int) from 1 to 100
void generateRandomProcesses()
{
    int i;
    // int sum =0 ;
    srand(time(NULL));
    for (i = 0; i < 100; i++)
    {
        // each process will have id from 1 to 100 and burst time a random no from 1 to 100 as required
        struct process newProcess;
        newProcess.process_id = i + 1;
        newProcess.arrival_time = 0;
        newProcess.burst_time = rand() % 100 + 1;
        newProcess.remaining_time = newProcess.burst_time;
        sum_of_pro += newProcess.burst_time ;
        addToWaitQueue(newProcess, 0);
    }
    n = 100;
    //  return sum ;
}

// These 3 functions are used to check whether the 3 waiting queues are empty or not
int isWaitQ1Empty()
{
    return headQ1 == tailQ1;
}

int isWaitQ2Empty()
{
    return headQ2 == tailQ2;
}

int isWaitQ0Empty()
{
    return headQ0 == tailQ0;
}
// Main function to handle everything in the first queue
void handleFirstQueue(struct process QUEUE1[], struct process WaitQ1[], int tq1, int *k, int *time, int *r,struct process QUEUE0[], struct process WaitQ0[], int *n, int tq0)
{
    int  i =0 ;
    int timer = 0;
    int extra_flag = 0 ;
    int s = 0;
    while( ! isWaitQ0Empty() && s <10 )
    {
        // printf("\nHELLO FIRST FUNCTioN\n");
        if(timer + 8 > tq0  && WaitQ0[headQ0].burst_time >= 8)
        {
            break ;
        }
        QUEUE0[s] = removeFromWaitQueue(0);
        if(QUEUE0[s].burst_time <=tq1)
        {
            timer += QUEUE0[s].burst_time ;
        }
        else
        {
            timer += tq1;
        }
        if(timer > tq0 )
        {
            break ;
        }
        else
        {
            s++ ;
        }
    }

    while(i<s)
    {


        if (extra_flag ==1)
        {
            break ;
        }
        if (QUEUE0[i].remaining_time <= tq1)
        {
            *time += QUEUE0[i].remaining_time;
            QUEUE0[i].remaining_time = 0;
            QUEUE0[i].waiting_time = *time - QUEUE0[i].arrival_time - QUEUE0[i].burst_time;
            QUEUE0[i].turn_around_time = *time - QUEUE0[i].arrival_time;
            //  timer += QUEUE0[s].burst_time ;
            printf("\n\nProcess with id %d and burst time %d is finished using QUEUE0 and Waiting time is %d and TAT is %d", QUEUE0[i].process_id,
                   QUEUE0[i].burst_time,QUEUE0[i].waiting_time,QUEUE0[i].turn_around_time);
        }
        else
        {
            WaitQ1[tailQ1 ].waiting_time = *time;
            *time += tq1;
            QUEUE0[i].remaining_time -= tq1;
            WaitQ1[tailQ1].burst_time = QUEUE0[i].remaining_time;
            WaitQ1[tailQ1].remaining_time = WaitQ1[tailQ1].burst_time;
            WaitQ1[tailQ1].process_id = QUEUE0[i].process_id;
            (*k)++;
            //timer += tq1 ;

            tailQ1 ++ ;
            printf("\n\nProcess with id %d and burst time %d is passed to waiting queue 1", QUEUE0[i].process_id, QUEUE0[i].burst_time);

        }

        i++ ;
        if( i == s)
        {

            i=0 ;
            s = 0;
            while( ! isWaitQ0Empty() && s <10 )
            {
                if(timer + 8 > tq0  && WaitQ0[headQ0].burst_time >= 8)
                {
                    break ;
                }
                QUEUE0[s] = removeFromWaitQueue(0);

                if(QUEUE0[s].burst_time <=tq1)
                {
                    timer += QUEUE0[s].burst_time ;
                }
                else
                {
                    timer += tq1;
                }
                if(timer > tq0 )
                {
                    extra_flag =1 ;
                    break ;
                }
                else
                {
                    s++ ;
                }
            }

        }
    }
}

int getRandomChoice()
{
    return rand() % 2; // Returns 0 or 1
}

// Main function to handle everything in the second queue
void handleSecondQueue(struct process QUEUE1[], struct process WaitQ1[], int tq1, int *k, int *time, int *r, struct process QUEUE0[], struct process WaitQ0[], int *n, int tq0)
{
    int i = 0;
    int timer = 0;
    while( ! isWaitQ1Empty() )
    {
        //printf("\nWAIT Q2 NOT EMPTY\n");
        if(timer + 16 > tq0  && WaitQ1[headQ1].burst_time >= 16)
        {
            break ;
        }
        QUEUE1[i] = removeFromWaitQueue(1);
        if(QUEUE1[i].burst_time <=tq1)
        {
            timer += QUEUE1[i].burst_time ;
        }
        else
        {
            timer += tq1;
        }
        if(timer > tq0 )
        {
            break ;
        }
        else
        {
            i++ ;
        }
    }

    for(int s =0 ; s<i ; s++)
    {
       if (QUEUE1[s].remaining_time <= 16)
        {
            *time += QUEUE1[s].remaining_time;
            QUEUE1[s].remaining_time = 0;
            QUEUE1[s].waiting_time = *time - tq1 - QUEUE1[s].burst_time;
            QUEUE1[s].turn_around_time = *time - QUEUE1[s].arrival_time;
            timer += QUEUE1[s].burst_time ;
            printf("\n\nProcess with id %d and burst time %d is finished using QUEUE1 with waiting time %d and TAT %d", QUEUE1[s].process_id,
                   QUEUE1[s].burst_time, QUEUE1[s].waiting_time, QUEUE1[s].turn_around_time);
        }
        else
        {
            int x = QUEUE1[s].remaining_time ;
            timer += 16;
            int choice = getRandomChoice();
            if (choice == 0)
            {

                WaitQ2[tailQ2].arrival_time = *time;
                *time += tq1;
                QUEUE1[s].remaining_time -= tq1;
                WaitQ2[tailQ2].burst_time = QUEUE1[s].remaining_time;
                WaitQ2[tailQ2].remaining_time = WaitQ2[tailQ2].burst_time;
                WaitQ2[tailQ2].process_id = QUEUE1[s].process_id;
                (*r)++;

                tailQ2 ++ ;
                printf("\n\nProcess with id %d and burst time %d is passed to WAITING QUEUE 2", QUEUE1[s].process_id, x);
            }
            else
            {

                WaitQ0[tailQ0].arrival_time = *time;
                *time += tq1;
                QUEUE1[s].remaining_time -= tq1;
                WaitQ0[tailQ0].burst_time = QUEUE1[s].remaining_time;
                WaitQ0[tailQ0].remaining_time = WaitQ0[tailQ0].burst_time;
                WaitQ0[tailQ0].process_id = QUEUE1[s].process_id;
                tailQ0 ++ ;
                printf("\n\nProcess with id %d and burst time %d is passed to WAITING QUEUE 0", QUEUE1[s].process_id, x);

            }

        }
    }
}

// Main function to handle everything in the third queue
void handleThirdQueue(struct process QUEUE2[], struct process WaitQ2[], int tq1, int *r, int *time, int tq0)
{
    //printf("\nHello From Third Queue")  ;
    int i = 0;
    int timer = 0;
    while( ! isWaitQ2Empty() )
    {
        if(WaitQ2[headQ2].burst_time + timer > tq0)
        {
            break ;
        }
        else
        {
            timer += WaitQ2[headQ2].burst_time;
        }
        QUEUE2[i] = removeFromWaitQueue(2);


        i++ ;
    }
    //while( ! isWaitQ0Empty() && timer+ QUEUE0[s].burst_time <= tq0)
    for(int s=0 ; s<i ; s++)
    {

        QUEUE2[s].completion_time = QUEUE2[s].burst_time + *time - tq1;

        QUEUE2[s].turn_around_time = QUEUE2[s].completion_time;
        QUEUE2[s].waiting_time = QUEUE2[s].turn_around_time - QUEUE2[s].burst_time;
        printf("\n\nProcess with id %d and burst time %d and waiting time %d and TAT %d is finished using QUEUE2", QUEUE2[s].process_id, QUEUE2[s].burst_time
               ,QUEUE2[s].waiting_time,QUEUE2[s].turn_around_time);
        //s++;
    }
}

int main()
{
    int i, k = 0, r = 0, time = 0, tq0 = 8, tq1 = 16;

    // Generate 100 processes with random burst times
    generateRandomProcesses();

    printf("\n************************************************************************************************************************\n");
    printf("\t\t\t\t\t OS FINAL PROJECT \t\t\t\t\t\n");
    printf("\n************************************************************************************************************************\n");


    time = 0;
    int cpu_time =380 ;
    int emptyq0 = 0 ;
    int emptyq1= 0 ;
    int emptyq2 = 0 ;
    while (! isWaitQ0Empty() || !isWaitQ1Empty() || ! isWaitQ2Empty())
    {
        printf("\n");
        printf("\n*******************************************************************************************************************");
        printf("\nQUEUE0 With QUANTUM = 8 ");

        // Handle the first queue
        handleFirstQueue(QUEUE1, WaitQ1, tq0, &k, &time, &r,QUEUE0, WaitQ0, &n, 0.5*cpu_time);
        if(tailQ0 - headQ0 == 0 ){
            printf("\n\nQUEUE 0 IS EMPTY RIGHT NOW\n\n");
            emptyq0=1 ;
        }
        else {
            emptyq0 = 0 ;
        }

        printf("\n*******************************************************************************************************************");


        printf("\nQUEUE1 With QUANTUM = 16 ");
        // Handle the second queue
        handleSecondQueue(QUEUE1, WaitQ1, tq1, &k, &time, &r, QUEUE0, WaitQ0, &n, 0.3*cpu_time);
        if(tailQ1 - headQ1 == 0 ){
            printf("\n\nQUEUE 1 IS EMPTY RIGHT NOW\n\n");
            emptyq1=1;
        }
        else {
            emptyq1= 0 ;
        }

        printf("\n*******************************************************************************************************************");
        printf("\nQUEUE2 FCFS");
        // Handle the third queue
        if(isWaitQ0Empty() && isWaitQ1Empty()){
                //if q0 and q1 empty use all cpu time on third queue
                handleThirdQueue(QUEUE2, WaitQ2, tq1, &r, &time,  cpu_time);
        }
        else{
                //if not just give it 20% of the cpu time
        handleThirdQueue(QUEUE2, WaitQ2, tq1, &r, &time, 0.2 * cpu_time);
        }

       if(tailQ2 - headQ2 == 0 ){
            printf("\n\nQUEUE 2 IS EMPTY RIGHT NOW\n\n");
        }

    }
    return 0;
}
