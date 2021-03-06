## 8-Queen & N-Queen problem

涉及的所有代码完整版均在我的github仓库中（https://github.com/ECNUACRush）

note：代码整理后上传，可能会有延迟。

### 问题形式化

搜索五要素为：状态空间S，后继函数ｓｕｃｃｅｓｓｏｒｓ，初始状态ｓ０，目标测试GOAL以及路径耗散ｃｏｓｔ。

皇后问题是经典的搜索问题，具体体现在：

1. 任意放置ｎ个皇后的布局可以视为一个ｓｔａｔｅ。

2. 任意一个皇后移动，定义为后继函数。

3. 初态可以是任意一个布局，终态为满足条件（无法互相攻击）的布局。

4. 路径耗散：每次移动的代价视为１.

5. 搜索问题的解：初态到终态的移动方法，或最终合理的状态有多少。

   

### 皇后问题

> 基本释义：八皇后问题要求在8*8的国际象棋摆放八个皇后，任意两个皇后都不能在同一行、同一列或同一斜线上，有多少种摆法。

<img src="https://imgconvert.csdnimg.cn/aHR0cDovL2ltZy5ibG9nLmNzZG4ubmV0LzIwMTcxMTA4MDEzNjMzMzE2?x-oss-process=image/format,png" alt="这里写图片描述" style="zoom: 67%;" />

> 客户端硬件：CPU I5-7300，内存 8G，机械硬盘：1T，算力约１ｅ７／ｓ



### １.暴力法

最暴力的方法是使用8重循环+check的方法。这里核心是check如何定义，即检查每个点和其他7个点的关系。每次在循环中存下8个点的坐标，用check函数进行检查。

> check函数设置：
> 首先循环中保证了不在同一行，需要保证不在同一列和同一对角线即可。
> 同一列容易保证：检查保存的点的列坐标是否有相似即可。
> 对角线检查：根据几何观察得出公式为|y1-y2| != |x1-x2| 其中x1,y1是第一个皇后的横纵坐标，x2,y2是第二个皇后的横纵坐标。



**核心部分代码：**

```cpp
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
```

**耗时计算部分：**

```cpp
time_t start, over;
double run_time;
srand((unsigned)time(NULL));

start = clock();
/* 
	八重循环处
*/
over = clock();
printf("Use brute force to solve 8-queen costs %f s\n", (double)(over - start)/CLOCKS_PER_SEC);
```

最终得出合理的摆放共有92种，耗时1.187s。

<img src="C:\Users\Hz\AppData\Roaming\Typora\typora-user-images\image-20211104211951628.png" alt="image-20211104211951628" style="zoom:50%;" />



**复杂度分析：** 时间复杂度非常差，八皇后共有8^8情况需要检查，同时每次检查也不是O(1)的操作。如果扩展到N皇后问题则为**O(N^N * N^2)** = **O(N^(N+2))**级别，比指数复杂度还要差。空间复杂度优秀，为常数级别。

**扩展方面：**对于N皇后拓展，首先N对应N重循环，代码复用性较差，难以拓展。

综上所述，用暴力法解决八皇后乃至N皇后问题是不可取的。



### ２.回溯法

#### 2.1 递归版

> **回溯法**（[英语](https://zh.wikipedia.org/wiki/英语)：backtracking）是[暴力搜寻法](https://zh.wikipedia.org/wiki/暴力搜尋法)中的一种。
>
> 回溯法采用[试错](https://zh.wikipedia.org/wiki/试错)的思想，它尝试分步的去解决一个问题。在分步解决问题的过程中，当它通过尝试发现现有的分步答案不能得到有效的正确的解答的时候，它将取消上一步甚至是上几步的计算，再通过其它的可能的分步解答再次尝试寻找问题的答案。

这是回溯法的wiki定义 。

简单来说，回溯法仍然是一种暴力方法，但它在8皇后问题的解决中能较大程度的提升效率。

**核心代码：**

```cpp
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
bool check (int a[ ],int n)
{
    for(int i=1;i<=n-1;i++)
    {
        if((abs(a[i]-a[n])==n-i)||(a[i]==a[n]))
            return false;
    }
    return true;
}
```

回溯函数是经典的dfs思想，如果当前放置无冲突才会进入下一层递归。这里不用return进行返回，是因为backtrack完成后会自动返回上一层的for循环中，置新的a[k]并进行检测。

这里对于check函数也做了优化，放弃了原先使用的pair的两维度，引入了一维数组a。默认数组a的下标为第一维度即行，数组的数据值为第二维度即列，这样对于是否在对角线以及同列的判断会简洁许多。



![image-20211105110059201](C:\Users\Hz\AppData\Roaming\Typora\typora-user-images\image-20211105110059201.png)

**复杂度分析**：可以看到，不仅能得出正确的结果，耗时也仅仅需要1ms，大约是原来的千分之一。

**拓展方面：**同时，可拓展性方向也非常优秀，只需要在main函数中修改n的值就可以算出9皇后，10皇后……等等问题。

**存在问题：**由于回溯法本质上仍然是暴力算法。导致程序耗时在n增加的时候上升的很快，如图：

<img src="C:\Users\Hz\AppData\Roaming\Typora\typora-user-images\image-20211105112325218.png" alt="image-20211105112325218" style="zoom:50%;" />

<img src="C:\Users\Hz\AppData\Roaming\Typora\typora-user-images\image-20211105112428077.png" alt="image-20211105112428077" style="zoom:50%;" />

<img src="C:\Users\Hz\AppData\Roaming\Typora\typora-user-images\image-20211105112517953.png" alt="image-20211105112517953" style="zoom:50%;" />

**拓展n皇后存在的问题：**

12皇后需要0.26s，13皇后为1.71s，当n=14时，已经需要12s之多了。同时可行的解也成倍数增加，显然当n达到一定值时，可行解用longlong都无法表示，同时需要使用高精度才能完成计数了。



#### 2.2 非递归版

非递归版思想和递归版一样，只是因为我们都知道，一定可以找到某种合适的方法将递归算法转为迭代算法。这里主要是对其性能进行同样的测试。

**核心代码：**

```cpp
void backtrack (int n)
{
    int Count = 0;
    int a[100];

    int k = 1;
    a[1]=0;
    while(k>0)
    {
        a[k] += 1;//对应for循环的1~n
        while((a[k]<=n)&&(!check(a,k)))//搜索第k个皇后位置
        {
            a[k] += 1;
        }

        if(a[k]<=n)//找到了合理的位置
        {
            if(k==n)
            {//找到一组解
                Count++;
            }
            else
            {
                k += 1;//继续为第k+1个皇后找到位置，对应下一轮for循环
                a[k] = 0;//下一个皇后从头开始搜索
            }
        }
        else
            k -= 1;//回溯
    }
    cout<<Count<<endl;
}
```

<img src="C:\Users\Hz\AppData\Roaming\Typora\typora-user-images\image-20211105113532180.png" alt="image-20211105113532180" style="zoom:50%;" />

发现当n = 14时，同样需要近12s。说明无论是递归还是非递归版，回溯算法的时间效率是类似的。可拓展性方面同上分析。

<img src="C:\Users\Hz\AppData\Roaming\Typora\typora-user-images\image-20211105113704217.png" alt="image-20211105113704217" style="zoom:50%;" />

### 3.位运算法

相比于回溯法，位运算法用位来代表信息而不是数组，其性能明显较优，可拓展性也较好。



**核心代码：**

```cpp
void test(long row, long ld, long rd)
{
    if (row != upperlim)
    {
        // row，ld，rd进行“或”运算，求得所有可以放置皇后的列,对应位为0，
        // 再取反后“与”上全1的数，求得所有可放置皇后的位置，对应列改为1
        // 目的：求当前哪些列可放置皇后
        long pos = upperlim & ~(row | ld | rd);
        while (pos)    // 0 表示皇后没有地方可放，回溯
        {
            // copy pos最右边为1的bit，其余bit置0
            // 目的：取得可以放皇后的最右边的列
            long p = pos & -pos;

            // 将pos最右边为1的bit清零
            // 目的：为获取下一次的最右可用列使用做准备，
            // 回溯到这个位置继续试探
            pos -= p;

            // row + p，当前列置1，记录这次皇后放置的列。
            // (ld + p) << 1，标记当前皇后左边相邻的列不允许下一个皇后放置。
            // (ld + p) >> 1，标记当前皇后右边相邻的列不允许下一个皇后放置。
            // 此处的移位操作实际上是记录对角线上的限制，只是因为问题都化归到一行网格上来解决，所以表示为列的限制就可以了。
            // 移位在每次选择列之前进行，N×N网格中某个已放置的皇后针对其对角线上产生的限制都被记录下来
            test(row + p, (ld + p) << 1, (rd + p) >> 1);
        }
    }
    else
        //回溯
        sum++;
}
```

相比于回溯算法n=14时，需要12s，此时只需1s。效率提升了10倍以上。

<img src="C:\Users\Hz\AppData\Roaming\Typora\typora-user-images\image-20211105151027699.png" alt="image-20211105151027699" style="zoom:50%;" />

**分析：**巧妙之处在于：以前需要在一个N*N的正方形网格中挪动皇后进行试探性回溯，每走一步观察和记录一个格子前后左右对角线上格子的信息，当用bit位进行存储时，可以在一行格子（即1xN）个格子中进行试探回溯，对角线上的限制被转化位列限制，有效提高了效率。

**提升：**如果考虑对称性，在N比较大的情况下计算效率会更高。



### 对比相关论文

通过查阅了相关文献，对其中具有代表性的进行对比。

> [1]刘娟, 欧阳建权, 陈良军. 用混合遗传算法求解N皇后问题[J]. 国防科技大学,湘潭大学, 2007(02):40-44.

本文提出用局部搜索与简单遗传算法(SGA)相结合的混合遗传算法(HGA)来求解N皇后问题。

用N皇后的约束条件作为遗传算法的适应值函数。设计了高效的染色体编码、初始化种群方法、遗传算子以及局部搜索算子，使它们符合求解问题的需要。

通过与回溯法和相关的遗传算法比较，实验证实了用混合遗传算法求解N皇后的有效性。

#### 文章亮点

SGA算法在局部搜索中局限性明显，本文提出了引入局部搜索算子用来改善SGA的局部搜索能力。具体做法是：

1.染色体表示、译码

使用自然数串编码机制，染色体长度为N，染色体中每个基因代表一个皇后所在列的位置，基因值代表皇后的行位置。

<img src="C:\Users\Hz\AppData\Roaming\Typora\typora-user-images\image-20211107171123032.png" alt="image-20211107171123032" style="zoom:50%;" />



2.初始化种群

确定种群大小及初始的种群。根据N皇后问题特点，种群大小在这里设置为N，首先为每个体的染色体的基因位从1到N，然后随机交换两个基因位的值，每个个体共交换N/2次，每个个体都作上述操作。

3.适应值函数设计

遗传算法的适应值函数设计在求解问题中是至关重要的，关系到整个算法是否能求解问题，本文将N皇后问题的约束条件作为适应值函数，适应值低的个体违反约束少，认为是较优的个体。

4.遗传算子

引入了选择算子、交叉算子、变异算子三种算子分别进行实验。

5.局部搜索

依次交换染色体的基因位，发现得到的新个体的适应值小于交换前，就停止局部搜索，这种算法改良了当前代的最优个体的染色体。为了提高算法效率，只对当前种群中最好的个体进行局部搜索。

#### 效率对比

根据文章的描述，其提出的算法求解n皇后相对于传统的回溯算法有明显的改善，具体如下：

<img src="C:\Users\Hz\AppData\Roaming\Typora\typora-user-images\image-20211107172620860.png" alt="image-20211107172620860" style="zoom:50%;" />

<img src="C:\Users\Hz\AppData\Roaming\Typora\typora-user-images\image-20211107172711499.png" alt="image-20211107172711499" style="zoom:50%;" />

该算法是一个基于种群的搜索算法，所以它求解问题的快慢和初始种群有较大关系，对于同一个问题，初始种群不同可能带来相差几倍甚至几十倍的代数，所以文章也提到进一步改进可以考虑通过启发式算法得到一个较好的初始化种群，来加快收敛速度。



### 结论

N皇后问题作为一个经典的NP问题，研究如何更快更好地求解N皇后问题有很重大的意义，不管是我提到的几种经典方法，还是引用的paper中提到的，以及一些没有写在这里的paper提到的算法，都还存在一定的局限性。像遗传算法虽然能提高算法的收敛性，同时证明其有效性。但只能求得一个有效解，而不能求出所有的解。

除此之外，还有采用**并行改进回溯算法**，用计算机集群，加以考虑棋盘矩阵顺时针旋转的部分解重复特性，改进回溯算法。以及**片上多核并行混合遗传算法**等等。



### Reference

> [1]刘娟, 欧阳建权, 陈良军. 用混合遗传算法求解N皇后问题[J]. 国防科技大学,湘潭大学, 2007(02):40-44.
>
> [2]韩宇南, 吕英华, 黄小红. 并行改进回溯算法实现N皇后问题的快速计数[J]. 计算机工程与应用, 2006.
>
> [3]吴帆, 李肯立. 基于自组装的N皇后问题DNA计算算法[J]. 电子学报, 2013, 41(11):2174-2180.
>
> [4]潘大志, 杜勇, 谭代伦,等. 位运算在N皇后问题中的应用[J]. 计算机工程与应用, 2009, 45(32):61-62.
>
> [5]张步忠, 程玉胜, 王一宾. 求解N皇后问题的片上多核并行混合遗传算法[J]. 计算机工程, 2015.
>
> [6]韩宇南, 吕英华, 黄小红. 并行改进回溯算法实现N皇后问题的快速计数[J]. 计算机工程与应用, 2006.
>
> 











