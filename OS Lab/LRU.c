#include<stdio.h>
#include<stdlib.h>

//3 cases: 
//page requested and frames not full 
//page requested and already exists in frames and full
//page requested and doesn't exist in frames and full

int LRU(int time[],int numframe)
{
    int min = time[0], pos=0;
    for(int i = 0; i <numframe; i++)
    {
        if(min > time[i])
        {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}


int main()
{
    int *page,*frames,*time;
    int count = 0,flag1,flag2,numframe,numpage,faults = 0,pos;

    printf("Enter no of frames and pages: \n");
    scanf("%d  %d",&numframe,&numpage);

    page = (int*)malloc(numpage*sizeof(int));
    frames = (int*)malloc(numframe*sizeof(int));
    time = (int*)malloc(numframe*sizeof(int));

    printf("Enter the page reference string: \n");
    for(int i = 0; i < numpage; i++)
        scanf("%d", &page[i]);

    for(int i = 0; i < numframe; i++)
        frames[i] = -1;
        
    for(int i = 0; i < numpage ; i++)
    {
        flag1 = flag2 = 0;
        
        for(int j = 0; j < numframe; j++)  //case 1
        {
            if(page[i] == frames[j])
            {
                flag1 = flag2 = 1;
                count++;
                time[j] = count;
                break;
            }
        }
        if(flag1 == 0)                     //case 2
        {
            for(int j = 0; j < numframe; j++)
            {
                if(frames[j] == -1)
                {
                    flag2 = 1;
                    count++;
                    faults++;
                    frames[j] = page[i]; 
                    time[j] = count;
                    break;
                }
            }
        }
        if(flag2 == 0)                     //case 3
        {
            pos = LRU(time, numframe);
            count++;
            flag2 = 1;
            frames[pos] = page[i];
            time[pos] = count;  
        }
        printf("\nFrames after accessing page %d: ", page[i]);
        for (int j = 0; j < numframe; ++j) 
        {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
    
    }
    printf("\n\nTotal Page Faults = %d\n", faults);

    // Free dynamically allocated memory
    free(frames);
    free(page);
    free(time);

    return 0;

}

