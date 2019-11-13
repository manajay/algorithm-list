#include<iostream>

using namespace std;
#define maxNum 100 //定义邻接举证的最大定点数
int pre[maxNum];
int post[maxNum];
int point=0;//pre和post的值
bool is_DAG=true;//标识位，表示有向无环图
/*
顶点颜色表 color[u]
　　 0 白色，未被访问过的节点标白色
　　 -1 灰色，已经被访问过一次的节点标灰色
　　 1 黑色，当该节点的所有后代都被访问过标黑色
反向边：
　　 如果第一次访问(u,v)时v为灰色，则(u,v)为反向边。在对图的深度优先搜索中没有发现
　　 反向边，则该图没有回路
程序判断依据：
	仍然是按图的节点深度遍历，访问到V时，V若被访问过，那么有2种状态：
	color[u]=-1，程序跳出，存在环
	color[u]=1，程序继续，这不是环
时间复杂度：O(n+e)
*/
int color[maxNum];//顶点颜色表 color[u]
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
	color[i]=-1;
	pre[i]=++point;
	for(int j=1;j<=g->vNum;j++)
	{
		if(g->e[i][j]!=0)
		{	
			if(color[j]==-1)//探索到回边,存在环
			{
				is_DAG=false;//不是有向无环图
			}
			else if(color[j]==0)
				dfs(g,j);
		}
	}
	post[i]=++point;
	color[i]=1;//表示i的后裔节点都被访问过
}
void DFS(graph *g)
{
	int i;
	//初始化color数组，表示一开始所有顶点都未被访问过，//初始化pre和post
	for(i=1;i<=g->vNum;i++)
	{
		color[i]=0;
		pre[i]=0;
		post[i]=0;
	}
	//深度优先搜索
	for(i=1;i<=g->vNum;i++)
	{
		if(color[i]==0)//如果这个顶点为被访问过，则从i顶点出发进行深度优先遍历
		{
			dfs(g,i);
			
		}
	}
}
void createGraph(graph *g)//创建图g
{
	cout<<"正在创建无向图..."<<endl;
	cout<<"请输入顶点个数vNum:";
	cin>>g->vNum;
	cout<<"请输入边的个数eNum:";
	cin>>g->eNum;
	int i,j;
	//初始画图g
	for(i=1;i<=g->vNum;i++)
		for(j=1;j<=g->vNum;j++)
			g->e[i][j]=0;
	//输入边的情况
	cout<<"请输入边的头和尾"<<endl;
	for(int k=1;k<=g->eNum;k++)
	{
		cin>>i>>j;
		g->e[i][j]=1;
	}
}
int main()
{
	graph *g;
	g=(graph*)malloc(sizeof(graph));
	createGraph(g);//创建图g
	DFS(g);//深度优先遍历
	//各顶点的pre和post值
	for(int i=1;i<=g->vNum;i++)
		cout<<"顶点"<<i<<"的pre和post分别为："<<pre[i]<<" "<<post[i]<<endl;
	//判断是否是有向无环图
	if(is_DAG)
		cout<<"图g是有向无环图，没有环"<<endl;
	else
		cout<<"图g不是有向无环图，存在环"<<endl;
	int k;
	cin>>k;
	return 0;
}