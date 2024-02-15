#include <stdio.h>
#include <stdlib.h>

struct process_struct
{
    int pid;
    int at;                          // Arrival Time
    int bt;                          // CPU Burst time
    int ct, wt, tat, rt, start_time; // Completion, waiting, turnaround, response time
} ps[100];

int comparatorAT(const void *a, const void *b)
{
    int x = ((struct process_struct *)a)->at;
    int y = ((struct process_struct *)b)->at;
    if (x < y)
        return -1;   // No sorting
    else if (x >= y) // = is for stable sort
        return 1;    // Sort
}

void FIFO_handler()
{
    int choice;
    int pnum, ArrivalTime[500], BurstTime[500];

    printf("\n-----------------------------------------------------\nPlease chosose your type of input:\n1/Manually input\n2/File input\n");
    scanf("%d", &choice);
    if (choice == 1)
    {
        //--------------------------Ask user manually type in the information---------------------------------
        printf("Please enter the number of process\n");
        scanf("%d", &pnum);
        for (int i = 0; i < pnum; i++)
        {
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

    printf("%d", ps[0].at);
    printf("%d", ps[1].at);
}

int main(int argc, char *argv[])
{
    int cpuTypeCode;
    printf("\n-----------------------------------------------------------------------------------\nPlease enter your type of CPU scheduling (Enter the corresponding number to console, Ex: 1 or 2 or 3, ....):\n1/ First-In-First_Out(FIFO)\n2/ Shortest Remaining Time First (SRTF)\n3/ Round Robin (RR)\n3/ Priority Scheduling\n");
    scanf("%d", &cpuTypeCode);
    switch (cpuTypeCode)
    {
    case 1: // First - In - First_Out(FIFO)
        FIFO_handler();
        break;
    case 2: // Shortest Remaining Time First (SRTF)
        break;
    case 3: // Round Robin (RR)
        break;
    case 4: // Priority Scheduling
        break;
    default:
        printf("Please enter the valid format");
    }
}
