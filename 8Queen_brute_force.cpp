#include<bits/stdc++.h>
#define N 9
using namespace std;
vector< pair<int, int >>v;

bool check()
{
    for(int i = 0; i < N; ++i)
    {
        for(int j = i+1; j < N; ++j)
        {
            if((v[i].second == v[j].second)
               || (abs(v[i].first - v[j].first) == abs(v[i].second - v[j].second))
              )
            return false;
        }
    }
    return true;
}
int main()
{
    time_t start, over;
    double run_time;
    srand((unsigned)time(NULL));
    pair<int, int> p;
    p.first = 1, p.second = 1;
    int i = 7, ans = 0;
    while(i--){
        v.push_back(p);
    }
    start = clock();
    for(int a = 1; a < N; ++a)
    {
        p.first = 1, p.second = a;
        v[0] = p;
        for(int b = 1; b < N; ++ b)
        {
            p.first = 2, p.second = b;
            v[1] = p;
            for(int c = 1; c < N; ++ c)
            {
                p.first = 3, p.second = c;
                v[2] = p;
                for(int d = 1; d < N; ++ d)
                {
                    p.first = 4, p.second = d;
                    v[3] = p;
                    for(int e = 1; e < N; ++e)
                    {
                        p.first = 5, p.second = e;
                        v[4] = p;
                        for(int f = 1; f < N; ++ f)
                        {
                            p.first = 6, p.second = f;
                            v[5] = p;
                            for(int g = 1; g < N; ++ g)
                            {
                                p.first = 7, p.second = g;
                                v[6] = p;
                                for(int h = 1; h < N; ++ h)
                                {
                                    p.first = 8, p.second = h;
                                    v[7] = p;
                                    if(check())
                                        ans++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    over = clock();
    printf("Use brute force to solve 8-queen costs %f s\n", (double)(over - start)/CLOCKS_PER_SEC);
    cout << ans << endl;

    return 0;
}
