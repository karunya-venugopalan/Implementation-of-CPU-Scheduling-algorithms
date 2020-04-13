#include<stdio.h>
#include<stdlib.h>
#include<time.h>
struct process
{
        int pid;
        int arr_time;
        int cpu_burst_time;
        int waiting_time;
        int tat;
        int priority;
}*p1[50];

void sort(struct process* process_array[50], int count)
{
    int i,j;
    for(i=0; i<count; i++)
    {
        for(j = i+1; j<count; j++)
        {
            if(process_array[j]->arr_time < process_array[i]->arr_time)
            {
                struct process *temp;
                temp = process_array[i];
                process_array[i] = process_array[j];
                process_array[j] = temp;
            }
        }
    }

    int curr_time = 0;
    curr_time = process_array[0]->arr_time + process_array[0]->cpu_burst_time;
    for(i=1; i<count; i++)
    {
        for(j=i+1; j<count; j++)
        {
            if(process_array[j]->priority < process_array[i]->priority && process_array[j]->arr_time <= curr_time)
            {
                struct process *temp;
                temp = process_array[i];
                process_array[i] = process_array[j];
                process_array[j] = temp;
            }
        }
        curr_time += process_array[i]->cpu_burst_time;
    }
}

void findWaitingTime(struct process* process_array[50], int count)
{
    // waiting time for first process is 0
    process_array[0]->waiting_time = process_array[0]->arr_time;

    // calculating waiting time
    int i,j;
    for (i = 1; i < count ; i++)
    {
        process_array[i]->waiting_time =  process_array[0]->arr_time;
        for(j=0; j<=(i-1); j++)
        {
            process_array[i]->waiting_time += process_array[j]->cpu_burst_time;
        }
        if(process_array[i]->waiting_time >= process_array[i]->arr_time)
            process_array[i]->waiting_time -= process_array[i]->arr_time;
        else
            process_array[i]->waiting_time = 0;
    }

}

void findTurnAroundTime (struct process* process_array[50], int count)
{
    int i;
    for(i=0; i<count; i++)
    {
        process_array[i]->tat = process_array[i]->waiting_time + process_array[i]->cpu_burst_time;
    }
}

void findAverage (struct process* process_array[50], int count)
{
    float total_wt = 0, total_tat = 0;
    int i;
    float avg_wt, avg_tat;
    findWaitingTime(process_array, count);
    findTurnAroundTime(process_array, count);

    printf("Process id          Arrival time          Execution time          Priority         Waiting time         Turn around time\n");

    for(i=0; i<count; i++)
    {
        total_wt = total_wt + process_array[i]->waiting_time;
        total_tat = total_tat + process_array[i]->tat;
        printf("%d                 %d                %d                    %d                          %d                        %d\n",process_array[i]->pid, process_array[i]->arr_time,process_array[i]->cpu_burst_time,process_array[i]->priority,process_array[i]->waiting_time,process_array[i]->tat);

    }
    avg_wt = total_wt/count;
    avg_tat = total_tat/count;

    printf("Average waiting time is: %f\n",avg_wt);
    printf("Average turn around time is: %f",avg_tat);
}

void main()
{
    int start_flag;
    int stop_flag;
    int count = 0;
    printf("Do you want to start creation of processes? ");
    scanf("%d",&start_flag);
    if(start_flag == 1)
    {
        do
        {
           p1[count] = (struct process *)malloc(sizeof(struct process));
           int id_lower = 10000, id_upper = 99999;
           int lower = 0, cpu_lower = 2, upper = 25,priority_lower=1, priority_upper = 10;
           srand((unsigned)time(NULL));
           p1[count]->pid = (rand() % (id_upper - id_lower + 1)) + id_lower;
           p1[count]->arr_time = (rand() % (upper - lower + 1)) + lower;
           p1[count]->cpu_burst_time = (rand() % (upper - cpu_lower + 1)) + cpu_lower;
           p1[count]->priority = (rand() % (priority_upper - priority_lower + 1)) + priority_lower  ;

           printf("PID: %d\n",p1[count]->pid);
           printf("ARRIVAL TIME: %d\n", p1[count]->arr_time);
           printf("CPU BURST TIME: %d\n",p1[count]->cpu_burst_time);
           printf("Priority: %d\n",p1[count]->priority);
           count++;

           printf("Enter 1 to stop and 0 to continue: ");
           scanf("%d",&stop_flag);
        }while(stop_flag == 0);
        sort(p1,count);
        findAverage(p1,count);

    }
    else
    {
        printf("terminated\n");
    }
}

