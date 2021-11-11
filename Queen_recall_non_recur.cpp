#include<bits/stdc++.h>
using namespace std;

bool check (int a[ ],int n)
{
    for(int i=1;i<=n-1;i++)
    {
        if((abs(a[i]-a[n])==n-i)||(a[i]==a[n]))
            return false;
    }
    return true;
}
int a[100], n, Count;
void backtrack (int n)
{
    int Count = 0;
    int a[100];

    int k = 1;
    a[1]=0;
    while(k>0)
    {
        a[k]=a[k]+1;//对应for循环的1~n
        while((a[k]<=n)&&(!check(a,k)))//搜索第k个皇后位置
        {
            a[k]=a[k]+1;
        }

        if(a[k]<=n)//找到了合理的位置
        {
            if(k==n )
            {//找到一组解

                Count++;
            }
            else
            {
                k=k+1;//继续为第k+1个皇后找到位置，对应下一级for循环
                a[k]=0;//下一个皇后一定要从头开始搜索
            }
        }
        else
        {
            k=k-1;//回溯,对应执行外内层for循环回到更上层
        }
    }
    cout<<Count<<endl;
}


int main()
{
    time_t start, over;
    double run_time;
    srand((unsigned)time(NULL));
    n=8,Count=0;
    start = clock();
    backtrack(14);
    //cout<<Count<<endl;

    over = clock();
    printf("Use Recall method to solve 14-queen costs %f s\n", (double)(over - start)/CLOCKS_PER_SEC);

    return 0;
}
