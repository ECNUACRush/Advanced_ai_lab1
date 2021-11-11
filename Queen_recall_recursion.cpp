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
void backtrack(int k)
{
    if (k>n)
        Count++;
    
    else
    {
        for (int i = 1;i <=n; i++)
        {
            a[k] = i;
            if (check(a,k) == 1)
            {backtrack(k+1);}
        }
    }

}

int main()
{
    time_t start, over;
    double run_time;
    srand((unsigned)time(NULL));
    n=8,Count=0;
    start = clock();
    backtrack(1);
    cout<<Count<<endl;

    over = clock();
    printf("Use Recall method to solve 8-queen costs %f s\n", (double)(over - start)/CLOCKS_PER_SEC);

    return 0;
}
