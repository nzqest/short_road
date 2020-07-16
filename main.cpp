#include<Windows.h>
#include<iostream>


using namespace std;
#define MAXSIZE 1024

typedef struct _EdgeNode{//��ڵ����ӵıߵĶ���

	int adjvex;	//�ڽӵĶ���
	int weight;	//Ȩ��
	struct _EdgeNode *next;//��һ����
}EdgeNode;

typedef struct _VerexNode{//����Ľڵ�
	
	char date;//�ڵ������
	_EdgeNode *first;//ָ��l�ٽ׵ĵ�һ����
	
}VertexNode,AdjList;

typedef struct _AdjListGraph{
	
	AdjList *adjlist;
	int vex;//������
	int edge;//����

}AdjListGraph;

//ͼ�ĳ�ʼ��
void initgraph(AdjListGraph &G);
//ͼ�Ĵ���
void Create(AdjListGraph &G);
//
int Location(AdjListGraph &G,char c);

void DFS(AdjListGraph &G,int start,int end,int weights);


bool visit[MAXSIZE]={0};//������¼�Ƿ��ѱ�����
int min_weight = 0x7FFFFFFF;//����������2��32�η�
int steps =0;	//���߹��Ĳ���
int path[MAXSIZE]={0};	//�����߹���·��
int shorrtest_path[MAXSIZE]={0}; //������̵�·

//ͼ�ĳ�ʼ��
void initgraph(AdjListGraph &G){
	G.adjlist = new AdjList[MAXSIZE];
	G.edge = 0;
	G.vex = 0;
	for(int i=0;i<MAXSIZE;i++){
	visit[i] = false;
		}
}



//ͼ�Ĵ���
void Create(AdjListGraph &G){
	cout<<"�������ͼ�Ķ������ͱ���:"<<endl;
	cin>>G.vex>>G.edge;

	cout<<"��������صĶ���:"<<endl;
	for(int i=0;i<G.vex;i++){
		cin>>G.adjlist[i].date;
		G.adjlist[i].first=NULL;
	
	}

	char v1=0,v2=0;	//��������Ķ�����ַ�
	int i1,i2;
	int weight =0;//����ߵ�Ȩ��

	cout<<"������������ߵĶ��㼰��Ȩ��:"<<endl;

	for(int i=0;i<G.edge;i++){
		cin>>v1>>v2>>weight;
		i1 = Location(G,v1);
		i2 = Location(G,v2);

		
	if(i1!=-1&&i2!=-1){//ͨ�����������ҵ���Ӧ�����±�
		EdgeNode *tmp =new EdgeNode;	//����һ����
		tmp->adjvex = i2;
		tmp->next=G.adjlist[i1].first;
		tmp->weight = weight;
		G.adjlist[i1].first=tmp;
		}
	}

}

//ͨ����Ӧ�ַ�Ѱ�Ҷ�����ͼ�е��ڽӵ�
int Location(AdjListGraph &G,char c){
		
	for(int i=0;i<G.vex;i++){
	
		if(G.adjlist[i].date==c){

		return i;
			}
		}
	return -1;

	}
// 



//��ȱ���������㵽�յ�����·��*/
void DFS(AdjListGraph &G,int start,int end,int weights){
	int cur =-1;

	cur = start;
	if(start==end){//���ҵ��յ�,���ü�������
		//��ӡ���о�����·��
		for(int i=0;i<steps;i++){
			cout<<G.adjlist[path[i]].date<<"";//������ܵ�·��

			}
		printf("\t\t��·���ĳ�����:%d\n",weights);

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

		visit[cur]=true;//���cur�Ѿ�����
		path[steps++]=cur;
		DFS(G,cur,end,weight+weights);
		visit[cur]=false;//ǰһ����ɺ���cur����ΪΪδѡ��״̬
		path[--steps]=0;
		}
		tmp=tmp->next;
	

	
		}
		
}



int main(void){

	AdjListGraph G;


	//��ʼ��ͼ
	initgraph(G);

	//����ͼ
	Create(G);

	char start,end;
	cout<<"������Ҫ��ѯ�������յ�:"<<endl;
	cin>>start>>end;

	DFS(G,Location(G,start),Location(G,end),0);

	cout<<"��С·������Ϊ��"<<min_weight<<endl;
	cout<<"·����";
	int i=0;
	while(i<MAXSIZE&&shorrtest_path[i]>0){
	
		cout<<G.adjlist[shorrtest_path[i]].date<<" ";
		i++;
	
		}
	cout<<endl;
	//��ȱ���
	//DFS_main(G);


	system("pause");
	return 0;
}