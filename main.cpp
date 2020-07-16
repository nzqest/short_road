#include<Windows.h>
#include<iostream>


using namespace std;
#define MAXSIZE 1024

typedef struct _EdgeNode{//与节点连接的边的定义

	int adjvex;	//邻接的顶点
	int weight;	//权重
	struct _EdgeNode *next;//下一条边
}EdgeNode;

typedef struct _VerexNode{//顶点的节点
	
	char date;//节点的数据
	_EdgeNode *first;//指向l临阶的第一条边
	
}VertexNode,AdjList;

typedef struct _AdjListGraph{
	
	AdjList *adjlist;
	int vex;//顶点数
	int edge;//边数

}AdjListGraph;

//图的初始化
void initgraph(AdjListGraph &G);
//图的创建
void Create(AdjListGraph &G);
//
int Location(AdjListGraph &G,char c);

void DFS(AdjListGraph &G,int start,int end,int weights);


bool visit[MAXSIZE]={0};//用来记录是否已被访问
int min_weight = 0x7FFFFFFF;//最大的整数的2的32次方
int steps =0;	//已走过的步数
int path[MAXSIZE]={0};	//保存走过的路径
int shorrtest_path[MAXSIZE]={0}; //保存最短的路

//图的初始化
void initgraph(AdjListGraph &G){
	G.adjlist = new AdjList[MAXSIZE];
	G.edge = 0;
	G.vex = 0;
	for(int i=0;i<MAXSIZE;i++){
	visit[i] = false;
		}
}



//图的创建
void Create(AdjListGraph &G){
	cout<<"请输入该图的顶点数和边数:"<<endl;
	cin>>G.vex>>G.edge;

	cout<<"请输入相关的顶点:"<<endl;
	for(int i=0;i<G.vex;i++){
		cin>>G.adjlist[i].date;
		G.adjlist[i].first=NULL;
	
	}

	char v1=0,v2=0;	//保存输入的顶点的字符
	int i1,i2;
	int weight =0;//保存边的权重

	cout<<"请输入相关联边的顶点及其权重:"<<endl;

	for(int i=0;i<G.edge;i++){
		cin>>v1>>v2>>weight;
		i1 = Location(G,v1);
		i2 = Location(G,v2);

		
	if(i1!=-1&&i2!=-1){//通过顶点名字找到对应数组下标
		EdgeNode *tmp =new EdgeNode;	//创建一条边
		tmp->adjvex = i2;
		tmp->next=G.adjlist[i1].first;
		tmp->weight = weight;
		G.adjlist[i1].first=tmp;
		}
	}

}

//通过对应字符寻找顶点在图中的邻接点
int Location(AdjListGraph &G,char c){
		
	for(int i=0;i<G.vex;i++){
	
		if(G.adjlist[i].date==c){

		return i;
			}
		}
	return -1;

	}
// 



//深度遍历求解从起点到终点的最短路径*/
void DFS(AdjListGraph &G,int start,int end,int weights){
	int cur =-1;

	cur = start;
	if(start==end){//已找到终点,不用继续遍历
		//打印所有经过的路径
		for(int i=0;i<steps;i++){
			cout<<G.adjlist[path[i]].date<<"";//输出可能的路径

			}
		printf("\t\t该路径的长度是:%d\n",weights);

		if(min_weight>weights){
			min_weight=weights;
			memcpy(shorrtest_path,path,steps*sizeof(int));
		}
		//return ;
	}
	visit[start]=true;
	EdgeNode *tmp =G.adjlist[start].first;

	while(tmp){
		int weight = tmp->weight;
		cur =tmp->adjvex;

		if(visit[cur]==false){

		visit[cur]=true;//标记cur已经访问
		path[steps++]=cur;
		DFS(G,cur,end,weight+weights);
		visit[cur]=false;//前一步完成后，置cur顶点为为未选择状态
		path[--steps]=0;
		}
		tmp=tmp->next;
	

	
		}
		
}



int main(void){

	AdjListGraph G;


	//初始化图
	initgraph(G);

	//创建图
	Create(G);

	char start,end;
	cout<<"请输入要查询的起点和终点:"<<endl;
	cin>>start>>end;

	DFS(G,Location(G,start),Location(G,end),0);

	cout<<"最小路径长度为："<<min_weight<<endl;
	cout<<"路径：";
	int i=0;
	while(i<MAXSIZE&&shorrtest_path[i]>0){
	
		cout<<G.adjlist[shorrtest_path[i]].date<<" ";
		i++;
	
		}
	cout<<endl;
	//深度遍历
	//DFS_main(G);


	system("pause");
	return 0;
}