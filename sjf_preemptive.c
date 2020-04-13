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
}*p1[50];

void sort(struct process* process_array[50], int count)
{
      process_array[count] = (struct process *)malloc(sizeof(struct process));
      int temp[50], waiting_time = 0, prev_waiting_time;
      int i, smallest, time, current_count=0;
      double end;

      for(i = 0; i < count; i++)
      {
            temp[i] = process_array[i]->cpu_burst_time;
      }
      temp[count] = 9999;

      for(time = 0; current_count != count; time++)
      {
            smallest = count;
            for(i = 0; i < count; i++)
            {
                  if(process_array[i]->arr_time <= time && temp[i] < temp[smallest] && temp[i] > 0)
                  {
                        smallest = i;
                  }
            }

            temp[smallest]--;
            if(temp[smallest] == 0)
            {
                  current_count++;
                  end = time + 1;
                  prev_waiting_time = waiting_time;
                  waiting_time = waiting_time + end - process_array[smallest]->arr_time - process_array[smallest]->cpu_burst_time;
                  process_array[smallest]->waiting_time = waiting_time - prev_waiting_time;
            }
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

    findTurnAroundTime(process_array, count);

    printf("Process id          Arrival time          Execution time         Waiting time         Turn around time\n");

    for(i=0; i<count; i++)
    {
        total_wt = total_wt + process_array[i]->waiting_time;
        total_tat = total_tat + process_array[i]->tat;
        printf("%d                 %d                %d                          %d                        %d\n",process_array[i]->pid, process_array[i]->arr_time,process_array[i]->cpu_burst_time,process_array[i]->waiting_time,process_array[i]->tat);

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
    printf("========================================================================================================================\n");
    printf("                                         SJF Algorithm (Preemptive)                                                \n");
    printf("========================================================================================================================\n");
    printf("Do you want to start creation of processes? ");
    scanf("%d",&start_flag);
    if(start_flag == 1)
    {
        do
        {
           p1[count] = (struct process *)malloc(sizeof(struct process));


           int id_lower = 10000, id_upper = 99999;
           int lower = 0, cpu_lower = 2, upper = 25;
           srand((unsigned)time(NULL));
           p1[count]->pid = (rand() % (id_upper - id_lower + 1)) + id_lower;
           p1[count]->arr_time = (rand() % (upper - lower + 1)) + lower;
           p1[count]->cpu_burst_time = (rand() % (upper - cpu_lower + 1)) + cpu_lower;

           printf("    PID: %d\n",p1[count]->pid);
           printf("    ARRIVAL TIME: %d\n", p1[count]->arr_time);
           printf("    CPU BURST TIME: %d\n",p1[count]->cpu_burst_time);

            /*
           scanf("%d",&p1[count]->pid);
           scanf("%d",&p1[count]->arr_time);
           scanf("%d",&p1[count]->cpu_burst_time);*/
           count++;

           printf("Enter 1 to stop and 0 to continue: ");
           scanf("%d",&stop_flag);
           printf("\n");
        }while(stop_flag == 0);
        sort(p1,count);
        findAverage(p1,count);

    }
    else
    {
        printf("terminated\n");
    }
}
