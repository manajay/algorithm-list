#include<iostream>
// #include <malloc.h>

using namespace std;
#define maxNum 100 //定义邻接举证的最大定点数
int visited[maxNum];//通过visited数组来标记这个顶点是否被访问过，0表示未被访问，1表示被访问
int DFS_Count;//连通部件个数，用于测试无向图是否连通，DFS_Count=1表示只有一个连通部件，所以整个无向图是连通的
int pre[maxNum];
int post[maxNum];
int point;//pre和post的值

//图的邻接矩阵表示结构
typedef struct
{
	char v[maxNum];//图的顶点信息
	int e[maxNum][maxNum];//图的顶点信息
	int vNum;//顶点个数
	int eNum;//边的个数
}graph;
void createGraph(graph *g);//创建图g
void DFS(graph *g);//深度优先遍历图g
void dfs(graph *g,int i);//从顶点i开始深度优先遍历与其相邻的点
void dfs(graph *g,int i)
{
	//cout<<"顶点"<<g->v[i]<<"已经被访问"<<endl;
	cout<<"顶点"<<i<<"已经被访问"<<endl;
	visited[i]=1;//标记顶点i被访问
	pre[i]=++point;
	for(int j=1;j<=g->vNum;j++)
	{
		if(g->e[i][j]!=0&&visited[j]==0)
			dfs(g,j);
	}
	post[i]=++point;
}

void DFS(graph *g)
{
	int i;
	//初始化visited数组，表示一开始所有顶点都未被访问过
	for(i=1;i<=g->vNum;i++)
	{
		visited[i]=0;
		pre[i]=0;
		post[i]=0;
	}
	//初始化pre和post
	point=0;
	//初始化连通部件数为0
	DFS_Count=0;
	//深度优先搜索
	for(i=1;i<=g->vNum;i++)
	{
		if(visited[i]==0)//如果这个顶点为被访问过，则从i顶点出发进行深度优先遍历
		{
			DFS_Count++;//统计调用void dfs(graph *g,int i);的次数
			dfs(g,i);
		}
	}
}
void createGraph(graph *g)//创建图g
{
	cout<<"正在创建无向图..."<<endl;
	cout<<"请输入顶点个数vNum:"<<endl;
	cin>>g->vNum;
	cout<<"请输入边的个数eNum:"<<endl;
	cin>>g->eNum;
	int i,j;
	//输入顶点信息
	//cout<<"请输入顶点信息："<<endl;
	//初始画图g
	for(i=1;i<=g->vNum;i++)
		for(j=1;j<=g->vNum;j++)
			g->e[i][j]=0;
	//输入边的情况
	cout<<"请输入边的头和尾"<<endl;
	for(int k=0;k<g->eNum;k++)
	{
		cin>>i>>j;
		g->e[i][j]=1;
		g->e[j][i]=1;//无向图对称
	}
}
int main()
{
	graph *g;
	g=(graph*)malloc(sizeof(graph));
	createGraph(g);//创建图g
	DFS(g);//深度优先遍历
	//连通部件数，用于判断是否连通图
	cout<<"连通部件数量："<<endl;
	cout<<DFS_Count<<endl;
	if(DFS_Count==1)
		cout<<"图g是连通图"<<endl;
	else if(DFS_Count>1)
		cout<<"图g不是连通图"<<endl;
	//各顶点的pre和post值
	for(int i=1;i<=g->vNum;i++)
		cout<<"顶点"<<i<<"的pre和post分别为："<<pre[i]<<" "<<post[i]<<endl;
	//cout<<endl;
	//判断无向图中是否有环
	if(g->eNum+DFS_Count>g->vNum)
		cout<<"图g中存在环"<<endl;
	else
		cout<<"图g中不存在环"<<endl;
	int k;
	cin>>k;
	return 0;
}