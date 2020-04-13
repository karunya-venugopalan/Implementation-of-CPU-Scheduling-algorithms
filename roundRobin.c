#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct process
{
        int pid;
        int cpu_burst_time;
        int waiting_time;
        int tat;
}*p1[50];

void findWaitingTime(struct process* process_array[50],
                     int count, int quantum)
{
    int rem_bt[count], i;
    for (i = 0 ; i < count ; i++)
        rem_bt[i] =  process_array[i]->cpu_burst_time;

    int t = 0; // Current time

    // Keep traversing processes in round robin manner until all of them are not done.
    while(1)
    {
        int done = 1;
        for (i = 0 ; i < count; i++)
        {
            // If burst time of a process is greater than 0 then only need to process further
            if (rem_bt[i] > 0)
            {
                done = 0; // There is a pending process

                if (rem_bt[i] > quantum)
                {
                    // Increase the value of t i.e. shows how much time a process has been processed and decrease remaining burst time by quantum
                    t += quantum;
                    rem_bt[i] -= quantum;
                }

                // If burst time is smaller than or equal to quantum. Last cycle for this process
                else
                {
                    // Increase the value of t i.e. shows how much time a process has been processed
                    t = t + rem_bt[i];
                    // Waiting time is current time minus time used by this process
                    process_array[i]->waiting_time = t - process_array[i]->cpu_burst_time;
                    // As the process gets fully executed make its remaining burst time = 0
                    rem_bt[i] = 0;
                }
            }
        }
        // If all processes are done
        if (done == 1)
          break;
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

void findAverage (struct process* process_array[50], int count, int quantum)
{
    float total_wt = 0, total_tat = 0;
    int i;
    float avg_wt, avg_tat;
    findWaitingTime(process_array, count, quantum);
    findTurnAroundTime(process_array, count);

    printf("Process id          Execution time         Waiting time         Turn around time\n");

    for(i=0; i<count; i++)
    {
        total_wt = total_wt + process_array[i]->waiting_time;
        total_tat = total_tat + process_array[i]->tat;
        printf("%d                %d                          %d                        %d\n",process_array[i]->pid,process_array[i]->cpu_burst_time,process_array[i]->waiting_time,process_array[i]->tat);

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
    int count = 0, time_quantum;
    printf("Do you want to start creation of processes? ");
    scanf("%d",&start_flag);
    srand((unsigned)time(NULL));
    int time_upper = 5, time_lower = 1;
    time_quantum = (rand() % (time_upper - time_lower + 1)) + time_lower;
    printf("Time quantum: %d\n", time_quantum);

    if(start_flag == 1)
    {
        do
        {
           p1[count] = (struct process *)malloc(sizeof(struct process));
           int id_lower = 10000, id_upper = 99999;
           int lower = 0, cpu_lower = 2, upper = 25, time_upper = 10;

           p1[count]->pid = (rand() % (id_upper - id_lower + 1)) + id_lower;
           p1[count]->cpu_burst_time = (rand() % (upper - cpu_lower + 1)) + cpu_lower;

           printf("PID: %d\n",p1[count]->pid);
           printf("CPU BURST TIME: %d\n",p1[count]->cpu_burst_time);

           count++;

           printf("Enter 1 to stop and 0 to continue: ");
           scanf("%d",&stop_flag);
        }while(stop_flag == 0);
        findAverage(p1,count,time_quantum);

    }
    else
    {
        printf("terminated\n");
    }
}

