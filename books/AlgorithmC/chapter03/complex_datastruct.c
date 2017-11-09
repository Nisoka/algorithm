#include "complex_datastruct.h"
#include <math.h>
/*
3.7 复合数据结构
    数组、链表、字符串 为顺序组织数据 提供了简单结构,
    提供了第一层抽象(将内存数据 抽象为程序可操作数组)并且这些结构高速可操作.
    在层次模型中, 利用 数组、链表、字符串来构建更复杂的数据结构 -- 多维数组 链表数组 字符串数组.

*/

//1 二维数组 矩阵乘法
void multiply_N_matrix(int* a[], int* b[]){
    int i = 0;
    int j = 0;
    int k = 0;
    int c[10][10] = {};

    for(i = 0; i < 10; i++){
        for(j = 0; j< 10; j++){
            //c i j += aik*bkj
            for(k = 0, c[i][j] = 0; k < N_MAX; k++)
                c[i][j] += a[i][k]*b[k][j];
        }
    }
}

//二维数组的 动态内存分配形式(静态的就是 array[][])
int **malloc2d(int r, int c){
    int i = 0;
    // malloc(r * sizeof(int *)) 申请r 个 int* 的地址, 给t
    //int **t --- int ** 指向 int指针 的指针 也就是 int指针 数组.
    // 每个int* 指针都是一个 int 数组.
    int **t = malloc(r * sizeof(int *));
    for(i = 0; i < r; i++){
        t[i] = malloc(c * sizeof(int));
    }
    //返回指针对象的内容(保存的是一个地址)
    return t;
}


//5  82
/*
 2 字符串数组 我们可以把字符串数组 组织为 多维字符数组的形式.
但是在C程序中 所有的字符串的字符数据都保存到一个 一维数组中, 而字符串具体表示的是一个指向对应字符数组的指针.
/// 因此在C中 字符串数组 被组织成为的是 字符指针数组的形式.
char ** 指向char*的指针,
*(char **) 得到 指向char 的指针, 即 char 数组, 字符串.
本例 是一个 处理字符的典型情况, 将字符串数据都读入到一个一维字符数组中, 保存每个字符串数据的指针构成字符串数组
 如此即可通过字符串数组直接操作字符串.(指针的最基本使用)
*/

char buf[MMax];
int M = 0;
int compare(void *i, void *j){
    return strcmp(*(char **)i, *(char **)j);
}

int pointer_sort_string(){
    int i, N;
    //char* 数组 -- 字符串数组.
    char* a[NMax];
    //buf 字符串缓冲区 一个一维数组 保存所有字符串, 然后使用一个字符串数组 引用这些字符串地址.
    for(N = 0; N < NMax; N++){
        a[N] = &buf[M];     //取缓冲区可输入地址.
        if(scanf("%s", a[N]) == EOF)
            break;
        M += strlen(a[N])+1;        //缓冲区index增长
    }

//    qsort(a, N, sizeof(char *), compare);
    for(i = 0; i < N; i++){
        printf("%s \n", a[i]);
    }

    N = 0;
    M = 0;
    return 0;
}


/*
 3 多重链表
    也可以只 使用链表来构造符合数据结构.
    link_node 中含有多个链域, 每个链域维持各自的链式组织表.

    稀疏矩阵的链式表示(存储) 使用多维链表来表示每个非0值.
    每个链接 代表一个维度.
    降低了存储空间, 但是 增加了算法的计算时间, 遍历多个链表才能访问到元素.
*/


/*
 *  4 图  组合对象(由多个不同项 组合形成的对象)
为了见识更多的复合数据结构, 并且 突出 索引数据结构(数组) 和 链表数据结构的差别,
引入 表示 图的数据结构. 图 是一种基本的组合对象, 由 顶点集合 和 顶点之间的边连接 集合组成.


*/


#define V 10
//表示图的方法1 二维数组--邻接矩阵.
void adjoin_matrix_for_map(){
    int i, j, adj[V][V];
    for(i = 0; i < V; i++){
        for(j = 0; j < V; j++){
            adj[i][j] = 0;
        }
    }
    for(i = 0; i < V; i++){
        adj[i][i] = 1;
    }
    //scanf程序可以正常的继续下去执行的话,返回值应该是2.
    while(scanf("%d %d", &i, &j) == 2){
        adj[i][j] = 1;
        adj[j][i] = 1;
    }
}

/*
  图的表示方法2 --- 邻接表 （链表数组）
  使用链表数组的方式, link[];
  为每个顶点创建一个链表
  注意要 以顶点为考虑, 所以创建一个链表,每个链表下的元素 是连接到该顶点的其他顶点.
*/
//表示图的方法2 链表数组--邻接表.
typedef struct node* link;
struct node{
    int v;
    link next;
};

link new_node(int v, link next){
    link x = malloc(sizeof(*x));
    x->v = v;
    x->next = next;
    return x;
}

void adjoin_link_for_map(){
    int i, j;
    link adj[V];
    for(i = 0; i < V; i ++){
        adj[i] = NULL;
    }
    while(scanf("%d %d", &i, &j) == 2){
        adj[i] = new_node(j, adj[i]);
        adj[j] = new_node(i, adj[j]);
    }
}







/*
//例子3.8中 求单位正方形内 N个点间距离小于d的点对.
// 3.8是 通过数组保存point, 然后 for(0 - N) for(i+1 N) 来嵌套循环求distance求解的 时间复杂度N^2
//  总结本章 使用复合数据结构 --  二维数组链表 来改进程序.
// 方法是 将正方形继续划分为多个小格子. 然后每个格子d长度, 格子中的点肯定是<d的 而相邻格子也可能<d。
//但是 不相邻的格子 绝对不可能<d。 这样就将需要for(0 - N) for(i+1 N)的问题 变成了for(0-N/d) for(0 - N/d)了.

// 这个是不是就是分治算法.????

这个二维数组链表数据结构 可以是其他几何问题的基础.

// 这是一种问题, 类似量影子 求杆长度那样的一种  换一种处理问题的思维模式. 算法中尤其重要.

*/

typedef struct{
    float x;
    float y;
}point;

typedef struct node_point* link_point;
struct node_point{
    point p;
    link_point next;
};
float rand_float(){
    return 1.0*rand()/RAND_MAX;
}

float distance(point a, point b){
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y,2));
}

//link_point 指针的指针(link_point指针的数组(link_point数组的数组--二维数组链表))
link_point **_grid;
float G;
float d;
int cnt = 0;

//返回的是 link 的指针(link 数组)的指针(数组的数组)
link_point **malloc2d_link(int r, int c){
    //t 是数组的数组, 是个数组, 所以t 是一个数组名 是一个指针,返回指针的话 返回的是指针保存的地址.
    //有了地址 就可以访问到指针实际数据.
    link_point **t = malloc(r*sizeof(link_point *));
    int i;
    for(i = 0; i < r; i++){
        t[i] = malloc(c*sizeof(struct node_point));
    }
    return t;
}

void gridinsert(float x, float y){
    int i, j; link_point s;
    //G 格子行数. X列 Y行
    int X = x*G + 1;
    int Y = y*G + 1;
    link_point t = malloc(sizeof(struct node_point));
    t->p.x = x; t->p.y = y;

    //在 X-1 - X - X+1 几个格子进行距离判断(边界呢? 边界已经在 grid中构建时创建了)
    //在创建过程中已经进行了距离计算, 只考虑临近的格子内的点 降低了计算时间复杂度.
    for(i = X-1; i <= X+1; i++){
        for(j = Y-1; j <= Y+1; j++){
            //当前格子内的点的链表grid[i][j]
            for(s = _grid[i][j]; s!=NULL; s = s->next){
                if(distance(s->p, t->p) < d)
                    cnt ++;
            }
        }
    }
    //按所处格子 形成链表 保存新入的点.
    t->next = _grid[X][Y];
    _grid[X][Y] = t;
}

void distance_shorter_in_grid(){
    int i, j, n_cnt = 100;
    d = 0.1;
    G = 1/d;
    _grid = malloc2d_link(G+2, G+2);
    for(i = 0; i < G+2; i++){
        for(j = 0; j < G+2; j++)
            _grid[i][j] = NULL;
    }

    for(i = 0; i< n_cnt; i++){
        gridinsert(rand_float(), rand_float());
    }
    printf(" distances shorter than %f cnt is %d \n", d, cnt);
}

int main(){
    distance_shorter_in_grid();

    //所有的 x == 1
//    float y = 0.3;
//    x = y+1;
//    printf("%d \n", x);
//    x = 0.5+1;
//    printf("%d \n", x);
//    x = 0.8+1;
//    printf("%d \n", x);
    return 0;
}
