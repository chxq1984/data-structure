#include <iostream>
#include <queue>
using namespace std;
#define MAX 10000
class node
{
public:
	int sum;
	int **map;
	int **path;
	int *lowcost;//用于Prim算法
	int *vex;
	int *mark;
	void build();
	void putout();
	node(){map=NULL;sum=0;lowcost=vex=mark=NULL;}
	void readweight();
	void readnext();
	void DFS(int);
	void BFS();
	void Floyd();
	void find_Floyd(int,int);
	int** copymap();
	void Prim();
	void Kruskal();
	void show_overroute();
	void show_smalltree();
};
class box
{
public:
    int position;
    box*next;
};
class duilie
{
public:
    box *front,*rear;
    duilie(){front=rear=NULL;}
    void push(int p);
    int pop();
};
class union_find//并查集
{
public:
	int *father;
	int number;
	void make_set();
	int find(int x);
	void unions(int x,int y);
	int juge(int x,int y);
	union_find(int x){number=x;}
};
class queue_fast
{
public:
	int from,to;
	int weight;
	friend bool operator <(queue_fast a,queue_fast b)
	{
		return a.weight>b.weight;
	}
};
int show();
int main()
{
	node start;
	int type=show();
	while(1)
	{
		switch(type)
		{
			case 1:	 system("cls");
					 start.build();
					 fflush(stdin);
					 getchar();
					 break;
			case 2:  system("cls");
					 start.readweight();
					 fflush(stdin);
					 getchar();
					 break;
			case 3:  system("cls");
					 start.readnext();
					 fflush(stdin);
					 getchar();
					 break;
			case 4:  system("cls");
					 start.show_overroute();
					 break;
			case 5:  system("cls");
					 start.Floyd();
					 fflush(stdin);
					 getchar();
					 break;
			case 6:  system("cls");
					 start.show_smalltree();
					 fflush(stdin);
					 getchar();
					 break;
			case 7:  exit(0);
		}
		type=show();
	}
}
void node::build()
{
	cout<<"请输入点数:"<<endl;
	cin>>sum;
	map=new int*[sum+1];
	for(int m=0;m<sum+1;m++)
	{
		map[m]=new int[sum]();
	}
	cout<<"请输入边数:"<<endl;
	int eagenum;
	cin>>eagenum;
	cout<<"请输入每条边的详细信息"<<endl;
	for(int n=0;n<eagenum;n++)
	{
		int from,to,weight;
		cin>>from>>to>>weight;
		map[from][to]=weight;
		map[to][from]=weight;
	}
	for(int m=1;m<=sum;m++)
	for(int n=1;n<=sum;n++)
	{
		if(!map[m][n]&&m!=n)
			map[m][n]=MAX;
	}
	cout<<"构建完成！"<<endl;
}
void node::putout()
{
	for(int m=1;m<=sum;m++)
	{
	for(int n=1;n<=sum;n++)
	{
		cout<<map[m][n];
	}
	cout<<endl;
	}
}
void node::readweight()
{
	fflush(stdin);
	cout<<"请输入您想查找的边:"<<endl;
	int from,to;
	cin>>from>>to;
	if(map[from][to]>=MAX)
	{
		cout<<"不存在此边！"<<endl;
		return;
	}
	cout<<map[from][to];
}
void node::readnext()
{
	cout<<"请输入您想查找的顶点:"<<endl;
	fflush(stdin);
	int tip;
	cin>>tip;
	if(tip>sum)
	{
		cout<<"无此点"<<endl;
		return;
	}
	for(int m=1;m<=sum;m++)
	{
		if(map[tip][m]>0&&map[tip][m]<MAX)
		{
			cout<<m;
			return;
		}
	}
	cout<<"此点为孤立点，无相邻点"<<endl;
}
void node::DFS(int p)
{
	cout<<p;
	static int *visit=new int[sum+1]();
	visit[p]=1;
	for(int m=1;m<=sum;m++)
	{
		if(map[p][m]>0&&map[p][m]<MAX&&!visit[m])
			DFS(m);
	}
}
void duilie::push(int p)
{
    if(!front)
    {
        front=new box;
        front->position=p;
        rear=front;
        rear->next=NULL;
    }
    else
    {
        box *temp=new box;
        temp->position=p;
        rear->next=temp;
        rear=temp;
        rear->next=NULL;
    }
}
int duilie::pop()
{
    if(!front)
        return 0;
    int temp=front->position;
    box *del=front;
    front=front->next;
    delete del;
    return temp;
}
void node::BFS()
{
	int *mark=new int[sum+1]();
	duilie p;
	p.push(1);
	mark[1]=1;
	while(p.front)
	{
		int temp=p.pop();
		cout<<temp;
		for(int m=1;m<=sum;m++)
		{
			if(map[temp][m]>0&&map[temp][m]<MAX&&!mark[m])
			{
				p.push(m);
				mark[m]=1;
			}
		}
	}
}
void node::Floyd()
{
	int **copy=copymap();
	path=new int*[sum+1];
	for(int m=1;m<=sum;m++)
	{
		path[m]=new int[sum]();
	}
	for(int m=1;m<=sum;m++)
	for(int n=1;n<=sum;n++)
	{
		if(map[m][n]==MAX||map[m][n]==0)
			path[m][n]=-1;
		else
			path[m][n]=m;
	}
	for(int m=1;m<=sum;m++)
	for(int n=1;n<=sum;n++)
	for(int h=1;h<=sum;h++)
	{
		if(copy[n][m]+copy[m][h]<copy[n][h])
		{
			copy[n][h]=copy[n][m]+copy[m][h];
			path[n][h]=m;
		}
	} 
	cout<<"请输入您想查找的边"<<endl;
	fflush(stdin);
	int from,to;
	cin>>from>>to;
	find_Floyd(from,to);
	delete [] copy;
}
int**node::copymap()
{
	int **copy=new int*[sum+1];
	for(int m=0;m<sum+1;m++)
	{
		copy[m]=new int[sum]();
	}
	for(int m=1;m<=sum;m++)
	for(int n=1;n<=sum;n++)
	{
		copy[m][n]=map[m][n];
	}
	return copy;
}
void node::find_Floyd(int from,int to)
{
	if(from==path[from][to])
	{
		cout<<"<"<<from<<","<<to<<">"<<endl;
		return;
	}
	find_Floyd(from,path[from][to]);
	find_Floyd(path[from][to],to);
}
void node::Prim()
{
	lowcost=new int [sum+1];
	vex=new int [sum+1];
	mark=new int[sum+1]();
	for(int m=1;m<=sum;m++)
	{
		lowcost[m]=MAX;
		vex[m]=1;
	}
	vex[1]=-1;
	lowcost[1]=0;
	for(int m=2;m<=sum;m++)//初始化
	{
		lowcost[m]=map[1][m];
		vex[m]=1;
	}
	mark[1]=1;
	for(int m=1;m<sum;m++)
	{
		int temmax=MAX;
		int position=-1;
		for(int n=1;n<=sum;n++)
		{
			if(!mark[n]&&temmax>lowcost[n])
			{
				temmax=lowcost[n];
				position=n;
			}
		}
		mark[position]=1;
		for(int m=1;m<=sum;m++)
		{
			if(!mark[m]&&map[position][m]<lowcost[m])
			{
				lowcost[m]=map[position][m];
				vex[m]=position;
			}
		}
	}
	int distance=0;
	for(int m=1;m<=sum;m++)
		distance+=lowcost[m];
	cout<<"最小生成树总距离为:"<<distance<<endl;
}
int union_find::find(int x)
{
	if(father[x]<=0)
		return x;
	return find(father[x]);
}
void union_find::make_set()
{
	father=new int[number+1];
	for(int m=1;m<=number;m++)
		father[m]=0;
}
void union_find::unions(int x,int y)
{
	int xfat=find(x);
    int yfat=find(y);
    if(xfat==yfat)
    return;
    if(father[xfat]<father[yfat])
    {
        father[yfat]=xfat;
        return;
    }
    else if(father[xfat]==father[yfat])
        {
            father[xfat]--;
            father[yfat]=xfat;
            return;
        }
        else if(father[xfat]>father[yfat])
        {
            father[xfat]=yfat;
            return;
        }
}
int union_find::juge(int x,int y)
{
	if(find(x)==find(y))
		return 1;
	else return 0;
}
priority_queue<queue_fast> q;//优先队列
void node::Kruskal()
{
	int distance=0;
	union_find ufin(sum);//并查集
	ufin.make_set();
	for(int m=1;m<=sum;m++)//排序
	for(int n=m+1;n<=sum;n++)
	{
		queue_fast temp;
		temp.from=m;
		temp.to=n;
		temp.weight=map[m][n];
		q.push(temp);
	}
	for(int m=1;m<sum;m++)//构建生成树
	{
		queue_fast temp(q.top());
		while(ufin.juge(temp.from,temp.to))
		{
			q.pop();
			temp=q.top();
		}
		q.pop();
		ufin.unions(temp.from,temp.to);
		distance+=map[temp.from][temp.to];
	}
	cout<<"最小生成树总距离为:"<<distance<<endl;
	
}
int show()
{
	system("cls");
	for(int m=0;m<20;m++)
		cout<<"▂";
	cout<<endl;
	printf("1.创建无向图%12c2.返回指定边权值\n3.查找邻接顶点%10c4.图的遍历\n5.最短路径%14c6.最小生成树\n7.退出程序\n",' ',' ',' ');
	for(int m=0;m<20;m++)
		cout<<"▂";
	cout<<endl;
	int type;
	while(scanf("%d",&type)!=1||!(type>=1&&type<=7))
	{
		fflush(stdin);
		cout<<"输入有误，请重新输入"<<endl;
	}
	return type;
}
void node::show_overroute()
{
	cout<<"请输入您想选择的操作"<<endl;
	cout<<"1.深度优先遍历      2.广度优先遍历"<<endl;
	fflush(stdin);
	int type;
	cin>>type;
	if(type==1)
		DFS(1);
	else if(type==2)
		BFS();
	fflush(stdin);
	getchar();
	cout<<endl;
}
void node::show_smalltree()
{
	cout<<"请输入您想选择的生成方式"<<endl;
	cout<<"1.Kruskal       2.Prim"<<endl;
	int type;
	fflush(stdin);
	cin>>type;
	if(type==1)
		Kruskal();
	else if(type==2)
		Prim();
}