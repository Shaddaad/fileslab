#include <stdio.h>

void bestFit(int m, int n, int ps[], int bs[])
{
    int allocation[n];
    for(int i=0;i<n;i++)
    {
        allocation[i]=-1;
    }

    for(int i=0;i<n;i++)
    {
        int bestidx =-1;
        for(int j=0; j<m;j++)
        {
            if(bs[j]>=ps[i])
            {
                if(bestidx==-1 || bs[i]<bs[bestidx])
                {
                    bestidx=j;
                }
                
            }
    
        }
        if(bestidx!=-1)
                {
                    allocation[i]=bestidx;
                    bs[bestidx]-=ps[i];
                }
    }
}