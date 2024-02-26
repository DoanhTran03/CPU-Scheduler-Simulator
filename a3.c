/*
Student Name: Ngoc Doanh Tran
Student ID: 110092702
Homework Number: Assignment 3
Date: 2/26/2024
Class: COMP 3300
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <conio.h>

#define MIN -9999;

//--------Supporting function for FIFO_handler()-----------
struct process_struct
{
    int pid;
    int at;                          // Arrival Time
    int bt;                          // CPU Burst time
    int ct, wt, tat, rt, start_time; // Completion, waiting, turnaround, response time
    int bt_remaining;
    int priority;
    int temp;
} ps[100];

int findmax(int a, int b)
{
    return a > b ? a : b;
}

int comparatorAT(const void *a, const void *b)
{
    int x = ((struct process_struct *)a)->at;
    int y = ((struct process_struct *)b)->at;
    if (x < y)
        return -1;   // No sorting
    else if (x >= y) // = is for stable sort
        return 1;    // Sort
}
int comparatorPID(const void *a, const void *b)
{
    int x = ((struct process_struct *)a)->pid;
    int y = ((struct process_struct *)b)->pid;
    if (x < y)
        return -1; // No sorting
    else if (x >= y)
        return 1; // Sort
}
//-------End of Supporting function for FIFO_handler()------------

void FIFO_handler()
{
    int choice;
    int pnum;
    int sum_tat = 0, sum_wt = 0;

    printf("\n-----------------------------------------------------\nPlease chosose your type of input:\n1/Manually input\n2/File input\n");
    scanf("%d", &choice);
    if (choice == 1)
    {
        //--------------------------Ask user manually type in the information---------------------------------
        printf("Please enter the number of process\n");
        scanf("%d", &pnum);
        for (int i = 0; i < pnum; i++)
        {
            ps[i].pid = i;
            printf("Please enter arrival time for proccess #%d\n", i);
            scanf("%d", &ps[i].at);
            printf("Please enter bursttime for process #%d\n", i);
            scanf("%d", &ps[i].bt);
        }
    }
    else if (choice == 2)
    {
        //-------------------------Ask input by file type-------------------------
        int array[500], i = 0, arrayLength;
        char filename[30];

        printf("\n-----------------------------------------------------\nPlease enter the file name:\n");
        scanf("%s", filename);
        FILE *fp;

        fp = fopen(filename, "r");

        while (fscanf(fp, "%d", &array[i]) != EOF)
        {
            i++;
        }
        fclose(fp);
        pnum = i / 2;

        i = 0;
        for (int j = 0; j < pnum * 2; j = j + 2)
        {
            ps[i].pid = i;
            ps[i].at = array[j];
            ps[i].bt = array[j + 1];
            i++;
        }
    }

    qsort((void *)ps, pnum, sizeof(struct process_struct), comparatorAT);

    for (int i = 0; i < pnum; i++)
    {
        ps[i].start_time = (i == 0) ? ps[i].at : findmax(ps[i].at, ps[i - 1].ct);
        ps[i].ct = ps[i].start_time + ps[i].bt;
        ps[i].tat = ps[i].ct - ps[i].at;
        ps[i].wt = ps[i].tat - ps[i].bt;

        sum_tat += ps[i].tat;
        sum_wt += ps[i].wt;
    }

    // sort so that process ID in output comes in Original order (just for interactivity)
    qsort((void *)ps, pnum, sizeof(struct process_struct), comparatorPID);

    // Print out the result on console.
    printf("\n------------------------------------------------------");
    printf("\nProcess_No.\tArrival_Time\tCPU_Burst_Time\tCompletion_Time\tTurn_Around_Time\tWait_Time\n");
    for (int i = 0; i < pnum; i++)
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", ps[i].pid, ps[i].at, ps[i].bt, ps[i].ct, ps[i].tat, ps[i].wt);

    printf("\nAverage Turn Around time= %f ", (float)(sum_tat / pnum));
    printf("\nAverage Waiting Time= %f ", (float)(sum_wt / pnum));
}

void SRTF_handler()
{
    int choice;
    int pnum;
    float bt_remaining[100];
    bool is_completed[100] = {false}, is_first_process = true;
    int current_time = 0;
    int completed = 0;
    float sum_tat = 0, sum_wt = 0, prev = 0;

    printf("\n-----------------------------------------------------\nPlease chosose your type of input:\n1/Manually input\n2/File input\n");
    scanf("%d", &choice);
    if (choice == 1)
    {
        //--------------------------Ask user manually type in the information---------------------------------
        printf("Please enter the number of process\n");
        scanf("%d", &pnum);
        for (int i = 0; i < pnum; i++)
        {
            ps[i].pid = i;
            printf("Please enter arrival time for proccess #%d\n", i);
            scanf("%d", &ps[i].at);
            printf("Please enter bursttime for process #%d\n", i);
            scanf("%d", &ps[i].bt);
            ps[i].pid = i;
            bt_remaining[i] = ps[i].bt;
        }
    }
    else if (choice == 2)
    {
        //-------------------------Ask input by file type-------------------------
        int array[500], i = 0, arrayLength;
        char filename[30];

        printf("\n-----------------------------------------------------\nPlease enter the file name:\n");
        scanf("%s", filename);
        FILE *fp;

        fp = fopen(filename, "r");

        while (fscanf(fp, "%d", &array[i]) != EOF)
        {
            i++;
        }
        fclose(fp);
        pnum = i / 2;

        i = 0;
        for (int j = 0; j < pnum * 2; j = j + 2)
        {
            ps[i].pid = i;
            ps[i].at = array[j];
            ps[i].bt = array[j + 1];
            bt_remaining[i] = ps[i].bt;
            i++;
        }
    }

    while (completed != pnum)
    {
        // find process with min. burst time in ready queue at current time
        int min_index = -1;
        int minimum = INT_MAX;
        for (int i = 0; i < pnum; i++)
        {
            if (ps[i].at <= current_time && is_completed[i] == false)
            {
                if (bt_remaining[i] < minimum)
                {
                    minimum = bt_remaining[i];
                    min_index = i;
                }
                if (bt_remaining[i] == minimum)
                {
                    if (ps[i].at < ps[min_index].at)
                    {
                        minimum = bt_remaining[i];
                        min_index = i;
                    }
                }
            }
        }

        if (min_index == -1)
        {
            current_time++;
        }
        else
        {
            if (bt_remaining[min_index] == ps[min_index].bt)
            {
                ps[min_index].start_time = current_time;
                is_first_process = false;
            }
            bt_remaining[min_index] -= 1;
            current_time++;
            prev = current_time;
            if (bt_remaining[min_index] == 0)
            {
                ps[min_index]
                    .ct = current_time;
                ps[min_index].tat = ps[min_index].ct - ps[min_index].at;
                ps[min_index].wt = ps[min_index].tat - ps[min_index].bt;

                sum_tat += ps[min_index].tat;
                sum_wt += ps[min_index].wt;
                completed++;
                is_completed[min_index] = true;
            }
        }
    }
    // Output the result to the console
    printf("-------------------------------------------------------");
    printf("\nProcess No.\tArrival_Time\tCPU_Burst_Time\tCompletion_Time\tTurn_Around_Time\tWait_Time\n");
    for (int i = 0; i < pnum; i++)
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", ps[i].pid, ps[i].at, ps[i].bt, ps[i].ct, ps[i].tat, ps[i].wt);

    printf("\nAverage Turn Around time= %f ", (float)sum_tat / pnum);
    printf("\nAverage Waiting Time= %f ", (float)sum_wt / pnum);
}

void RR_handler()
{
    int choice;
    int pnum, index;

    bool visited[100] = {false}, is_first_process = true;
    int current_time = 0;
    int completed = 0, tq;
    int queue[100], front = -1, rear = -1;
    float sum_tat = 0, sum_wt = 0;

    printf("\n-----------------------------------------------------\nPlease chosose your type of input:\n1/Manually input\n2/File input\n");
    scanf("%d", &choice);
    if (choice == 1)
    {
        //--------------------------Ask user manually type in the information---------------------------------
        printf("Please enter the number of process\n");
        scanf("%d", &pnum);
        printf("Please enter the time quantum\n");
        scanf("%d", &tq);

        for (int i = 0; i < pnum; i++)
        {
            printf("Please enter arrival time for proccess #%d\n", i);
            scanf("%d", &ps[i].at);
            ps[i].pid = i;
            printf("Please enter bursttime for process #%d\n", i);
            scanf("%d", &ps[i].bt);
            ps[i].bt_remaining = ps[i].bt;
        }
    }
    else if (choice == 2)
    {
        //-------------------------Ask input by file type-------------------------
        int array[500], k = 0;
        char filename[30];

        printf("\n-----------------------------------------------------\nPlease enter the file name:\n");
        scanf("%s", filename);
        FILE *fp;

        fp = fopen(filename, "r");

        while (fscanf(fp, "%d", &array[k]) != EOF)
        {
            k++;
        }
        fclose(fp);
        pnum = k / 2;
        k = 0;
        tq = array[0]; // Get the time quantum as the first number of the file
        for (int j = 1; j < pnum * 2; j = j + 2)
        {
            ps[k].pid = k;
            ps[k].at = array[j];
            ps[k].bt = array[j + 1];
            ps[k].bt_remaining = ps[k].bt;
            k++;
        }
    }

    // sort structure on the basis of Arrival time in increasing order
    qsort((void *)ps, pnum, sizeof(struct process_struct), comparatorAT);
    // q.push(0);
    front = rear = 0;
    queue[rear] = 0;
    visited[0] = true;

    while (completed != pnum)
    {
        index = queue[front];
        // q.pop();
        front++;

        if (ps[index].bt_remaining == ps[index].bt)
        {
            ps[index].start_time = findmax(current_time, ps[index].at);
            current_time = ps[index].start_time;
            is_first_process = false;
        }

        if (ps[index].bt_remaining - tq > 0)
        {
            ps[index].bt_remaining -= tq;
            current_time += tq;
        }
        else
        {
            current_time += ps[index].bt_remaining;
            ps[index].bt_remaining = 0;
            completed++;

            ps[index].ct = current_time;
            ps[index].tat = ps[index].ct - ps[index].at;
            ps[index].wt = ps[index].tat - ps[index].bt;

            sum_tat += ps[index].tat;
            sum_wt += ps[index].wt;
        }
        // check which new Processes needs to be pushed to Ready Queue from Input list
        for (int i = 1; i < pnum; i++)
        {
            if (ps[i].bt_remaining > 0 && ps[i].at <= current_time && visited[i] == false)
            {
                // q.push(i);
                queue[++rear] = i;
                visited[i] = true;
            }
        }

        if (ps[index].bt_remaining > 0)
            // q.push(index);
            queue[++rear] = index;

        if (front > rear)
        {
            for (int i = 1; i < pnum; i++)
            {
                if (ps[i].bt_remaining > 0)
                {
                    queue[rear++] = i;
                    visited[i] = true;
                    break;
                }
            }
        }
    } // end of while

    // sort so that process ID in output comes in Original order (just for interactivity- Not needed otherwise)
    qsort((void *)ps, pnum, sizeof(struct process_struct), comparatorPID);

    // Output
    printf("\nProcess_No.\tArrival_Time\tCPU_Burst_Time\tStart_Time\tCompletion_Time\tTurn_Around_Time\tWait_Time\n");
    for (int i = 0; i < pnum; i++)
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", i, ps[i].at, ps[i].bt, ps[i].start_time, ps[i].ct, ps[i].tat, ps[i].wt);
    printf("\nAverage Turn Around time= %.2f", (float)(sum_tat / pnum));
    printf("\nAverage Waiting Time= %.2f", (float)(sum_wt / pnum));
}

void PS_handler()
{
    int choice;
    int pnum, index;
    printf("\n-----------------------------------------------------\nPlease chosose your type of input:\n1/Manually input\n2/File input\n");
    scanf("%d", &choice);
    if (choice == 1)
    {
        //--------------------------Ask user manually type in the information---------------------------------
        printf("Please enter the number of process\n");
        scanf("%d", &pnum);

        for (int i = 0; i < pnum; i++)
        {
            ps[i].pid = i;
            printf("Please enter arrival time for proccess #%d\n", i);
            scanf("%d", &ps[i].at);
            printf("Please enter bursttime for process #%d\n", i);
            scanf("%d", &ps[i].bt);
            printf("Please enter the priority for the process #%d\n", i);
            scanf("%d", &ps[i].priority);
            ps[i].bt_remaining = ps[i].bt;
        }
    }
    else if (choice == 2)
    {
        //-------------------------Ask input by file type-------------------------
        int array[500], k = 0;
        char filename[30];

        printf("\n-----------------------------------------------------\nPlease enter the file name:\n");
        scanf("%s", filename);
        FILE *fp;

        fp = fopen(filename, "r");

        while (fscanf(fp, "%d", &array[k]) != EOF)
        {
            k++;
        }
        fclose(fp);
        pnum = k / 3;
        k = 0;
        for (int j = 0; j < pnum * 3; j = j + 3)
        {
            ps[k].pid = k;
            ps[k].at = array[j];
            ps[k].bt = array[j + 1];
            ps[k].priority = array[j + 2];
            ps[k].bt_remaining = ps[k].bt;
            k++;
        }
    }

    struct process_struct temp;
    int i, j;
    int wt[pnum];
    int ta[pnum];
    int ct[pnum];
    int total_wt = 0;
    int total_ta = 0;
    bool completed[pnum];
    int current_time = 0;
    int pio_index = 0;
    printf("\nProcess_number\tCompletion_Time\tTurnaround_Time\tWaiting Time\n");
    for (i = 0; i < pnum; i++)
    {
        wt[i] = 0;
    }

    while (true)
    {
        bool completed_all = true;
        pio_index = 0;
        for (i = 0; i < pnum; i++)
        {
            if (!completed[i])
            {
                completed_all = false;
                if (ps[i].priority != 100 && ps[i].at <= current_time && ps[i].priority <= ps[pio_index].priority)
                {
                    pio_index = i;
                }
            }
        }
        for (i = 0; i < pnum; i++)
        {
            if (ps[i].at <= current_time && i != pio_index && ps[i].bt_remaining != 0)
            {
                wt[i] += 1;
            }
        }
        if (completed_all)
        {
            break;
        }
        ps[pio_index].bt_remaining--;
        if (ps[pio_index].bt_remaining == 0)
        {
            completed[pio_index] = true;
            ps[pio_index].priority = 100;
            // break;
        }
        current_time++;
    }
    for (i = 0; i < pnum; i++)
    {
        ta[i] = wt[i] + ps[i].bt;
        ct[i] = ta[i] + ps[i].at;
        total_ta += ta[i];
        total_wt += wt[i];
        printf("%d\t\t%d\t\t%d\t\t%d\n", ps[i].pid, ct[i], ta[i], wt[i]);
    }
    printf("\nAverage Turnaround Time: %.2f", (double)total_ta / pnum);
    printf("\nAverage Waiting Time: %.2f\n\n", (double)total_wt / pnum);
}

int main(int argc, char *argv[])
{
    int cpuTypeCode;
    printf("\n-----------------------------------------------------------------------------------\nPlease enter your type of CPU scheduling (Enter the corresponding number to console, Ex: 1 or 2 or 3, ....):\n1/ First-In-First_Out(FIFO)\n2/ Shortest Remaining Time First (SRTF)\n3/ Round Robin (RR)\n4/ Priority Scheduling\n5/ Multilevel Feedback Queue\n");
    scanf("%d", &cpuTypeCode);
    switch (cpuTypeCode)
    {
    case 1: // First - In - First_Out(FIFO)
        FIFO_handler();
        break;
    case 2: // Shortest Remaining Time First (SRTF)
        SRTF_handler();
        break;
    case 3: // Round Robin (RR)
        RR_handler();
        break;
    case 4: // Priority Scheduling
        PS_handler();
        break;
    case 5: // Multilevel Queue Scheduling
        printf("This is multi queue schedule");
        break;
    default:
        printf("Please enter the valid format");
        exit(1);
    }
}
