#include <iostream>
#include <queue>
#include <stdio.h>
#define MAX 10000//����dijkstra�㷨
#include <windows.h>
using namespace std;
struct map//ͼ�ĵ�һ�������
{
	int code;
	int weight;
	map *next;
	map*down;//������
	map(){weight=0;next=down=NULL;}
};
struct total
{
	int sum;
	map *head;
	int *visit;
	int *path;
	int *distance;
	total(){head=NULL;sum=0;}
	void build();
	void BFS();
	void DFS(int x);
	void FZ_dfs();
	void shortroad(int x);
	void readweight();
	void dele();
	void insert();
	void searchnear();
	void clearvisit();//��ʼ��
	void Dijkstra();
	map*find(int,map*);
	void TopoOrder();//��������
	void critical_path();//�ؼ�·��
	map*critical_path_copyroute();//���췴��ͼ
	void critical_path_topoorder(map*,int *,int,int *);//�ؼ�·����������
	void randon_short_route();//�������·��
	void show_choose_overroute();
	void show_choose_shortway();
};
class node//�������ȶ��е�����
{
public:
	int id;
	int distance;
	friend bool operator <(node a,node b)
	{
		return a.distance>b.distance;
	}
};
class box
{
public:
    map *position;
    box*next;
};
class duilie
{
public:
    box *front,*rear;
    duilie(){front=rear=NULL;}
    void push(map *p);
    map*pop();
};
priority_queue<node> p;//�����������·�������ȶ���
int show();
int main()
{
	total start;
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
					 break;
			case 3:  system("cls");
					 start.insert();
					 fflush(stdin);
					 getchar();
					 break;
			case 4:  system("cls");
					 start.dele();
					 getchar();
					 break;
			case 5:  system("cls");
					 start.searchnear();
					 fflush(stdin);
					 getchar();
					 break;
			case 6:  system("cls");
					 start.show_choose_overroute();
					 fflush(stdin);
					 getchar();
					 break;
			case 7:  system("cls");
					 start.show_choose_shortway();
					 fflush(stdin);
					 getchar();
					 break;
			case 8:	 system("cls");
					 start.TopoOrder();
					 fflush(stdin);
					 getchar();
					 break;
			case 9:  system("cls");
					 start.critical_path();
					 fflush(stdin);
					 getchar();
					 break;
			case 10: exit(0);
		}
		type=show();
	}
}
void total::build()
{
	cout<<"�������ĸ���: ";
	cin>>sum;
	cout<<endl;
	head=new map;
	head->code=1;
	map*front=head;
	visit=new int [sum*2+1];//����ռ䴦��ɾ���������
	for(int m=2;m<=sum;m++)
	{
		map*temp=new map;
		temp->code=m;
		front->down=temp;
		front=temp;
		front->down=NULL;
		visit[m]=0;
	}
	cout<<"������ߵĸ���: ";
	int temp;
	cin>>temp;
	cout<<endl;
	cout<<"������ߵ���Ϣ"<<endl;
	for(int m=1;m<=temp;m++)
	{
		int from,to,weight;
		cin>>from>>to>>weight;
		map *temp=new map;
		temp->code=to;
		temp->weight=weight;
		map*mid=head;
		while(mid&&mid->code!=from)
			mid=mid->down;
		map*hj=mid->next;
		if(hj==NULL)
			mid->next=temp;
		else
		{
		while(hj->next)
		{
			hj=hj->next;
		}
			hj->next=temp;
		}
		temp->next=NULL;
	}
}
void total::BFS()
{
	clearvisit();
	for(map*tot=head;tot;tot=tot->down)
	{
	int x=tot->code;
	duilie em;
	map*temp=find(x,head);
	if(!visit[temp->code])
	em.push(temp);
	visit[temp->code]=1;
	while(em.front)
	{
		map*temp=em.pop();
		cout<<temp->code;
		map*p;
		for(p=temp->next;p;p=p->next)
		{
			if(!visit[p->code])
			{
				map*mid=find(p->code,head);
				em.push(mid);
				visit[p->code]=1;
			}
		}
	}
	}
}
void duilie::push(map*p)
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
map*duilie::pop()
{
    if(!front)
        return NULL;
    map *temp=front->position;
    box *del=front;
    front=front->next;
    return temp;
}
void total::readweight()
{
	cout<<"�����������ѯ�ı�:"<<endl;
	int from,to;
	cin>>from>>to;
	map*temp=find(from,head);
	for(temp=temp->next;temp;temp=temp->next)
	{
		if(temp->code==to)
		{
			cout<<"ȨֵΪ"<<temp->weight<<endl;
			fflush(stdin);
			getchar();
			return;
		}
	}
	cout<<"�޴˱���Ϣ"<<endl;
	fflush(stdin);
	getchar();
	return;
}
map*total::find(int x,map*head)
{
	map*temp=head;
	while(temp&&temp->code!=x)
		temp=temp->down;
	return temp;
}
void total::insert()
{
	cout<<"ѡ��������еĲ���:"<<endl;
	cout<<"1.���붥��       2.�����"<<endl;
	int type,from,to,weight;
	map*teminsert,*mid;
	map *pre,*newcode;
	cin>>type;
	switch(type)
	{
		case 1:
		teminsert=new map;
		cout<<"�������������Ķ������:"<<endl;
		cin>>teminsert->code;
		mid=head;
		pre=NULL;
		while(mid)
		{
			pre=mid;
			mid=mid->down;
		}
		if(!pre)//headΪ��
		{
			head=teminsert;
			head->down=NULL;
		}
		else
		{
			pre->down=teminsert;
			teminsert->down=NULL;
		}
		sum++;
		cout<<"�Ƿ��������ߣ�"<<endl;
		cout<<"1.��      2.��"<<endl;
		fflush(stdin);
		cin>>type;
		if(type==2)
		break;
		case 2:
		cout<<"�������������ıߵ���Ϣ:"<<endl;
		cin>>from>>to>>weight;
		teminsert=head;
		while(teminsert&&teminsert->code!=from)
			teminsert=teminsert->down;
		if(teminsert)
		{
			mid=teminsert;
			while(mid->next)
				mid=mid->next;
			newcode=new map;
			newcode->code=to;
			newcode->weight=weight;
			mid->next=newcode;
			newcode->next=NULL;
		}
		else
		{
			cout<<"δ�ҵ�����ָ������ʼ��!"<<endl;
			return;
		}

	}
}
void total::dele()
{
	int type,code,from,to,flag=0;
	map*found,*temp,*mid=NULL,*pre,*posi=NULL;
	map*ios;
	cout<<"������������������"<<endl;
	cout<<"1.ɾ������     2.ɾ����"<<endl;
	fflush(stdin);
	cin>>type;
	switch(type)
	{
		case 1:
		cout<<"����������ɾ���ĵ�����"<<endl;
		cin>>code;
		found=find(code,head);
		if(!found)
		{
			cout<<"�޷��ҵ��˵�"<<endl;
			return;
		}
		else
		{
			if(code==head->code)
			{
				ios=head->down;
				flag=1;
			}
			temp=found->next;
			mid=head;
			while(mid!=NULL)//ɾ�����������ڵ���Ϣ
			{
				pre=mid->next;
				posi=mid;
				while(pre&&pre->code!=code)
				{
					posi=pre;
					pre=pre->next;
				}
				if(pre)
				{
					posi->next=pre->next;
					delete pre;
				}
				mid=mid->down;
			}
			while(temp)
			{
				mid=temp;
				temp=temp->next;
				delete mid;//ɾ�����������ı�
			}
			if(!flag)
			{
			pre=head;//
			while(pre->down!=found)
				pre=pre->down;
			pre->down=found->down;//ɾ��������
			}
			else
			{
				head=head->down;
			}
			sum--;
			delete found;
			cout<<"ɾ�����"<<endl;
		}
		break;
		case 2:
		cout<<"����������ɾ���ıߵ���Ϣ:"<<endl;
		cin>>from>>to;
		found=find(from,head);
		if(!found)
		{
			cout<<"δ�鵽�����������ʼ����Ϣ!"<<endl;
			return;
		}
		else
		{
			mid=found;
			for(pre=found->next;pre&&pre->code!=to;pre=pre->next)
				mid=pre;
			if(!pre)
			{
				cout<<"δ�鵽�����������ֹ����Ϣ!"<<endl;
				return;
			}
			else
			{
					delete pre;
					mid->next=NULL;
					cout<<"ɾ�����"<<endl;
					return;
			}
		}
		
	}
}
void total::searchnear()
{
	int type;
	cout<<"���������������Ķ���:"<<endl;
	cin>>type;
	map*found=find(type,head);
	if(found->next)
	{
		cout<<"����ѯ���ڽӶ���Ϊ";
		cout<<found->next->code<<endl;
	}
	else
	{
		cout<<"�˵�Ϊ������"<<endl;
	}
}
void total::DFS(int x)
{
	cout<<x;
	map*temp=find(x,head);
	for(temp=temp->next;temp;temp=temp->next)
	{
		if(!visit[temp->code])
		{
			visit[temp->code]=1;
			DFS(temp->code);
		}
	}
}
void total::clearvisit()
{
	for(int m=0;m<=sum*2+1;m++)
		visit[m]=0;
	while(!p.empty())
		p.pop();
}
priority_queue<node> q;
void total::Dijkstra()
{
	int *read=new int[sum*2+1];
	int top=-1;
	clearvisit();
	path=new int[sum*2+1];
	distance=new int [sum*2+1];
	cout<<"���������������Ķ���"<<endl;
	int x;
	cin>>x;
	node mid[sum*2+1];//�������ȶ��еĲ���
	for(int m=1;m<=sum;m++)
	{
		mid[m].id=m;
		mid[m].distance=MAX;
		path[m]=m;
		distance[m]=MAX;
	}
	mid[x].distance=0;
	distance[x]=0;
	path[x]=-1;
	q.push(mid[x]);
	while(!q.empty())
	{
		node i=q.top();
		map*temp=find(i.id,head);
		q.pop();
		if(visit[i.id])
			continue;
		visit[i.id]=1;
		for(temp=temp->next;temp;temp=temp->next)
		{
			if(!visit[temp->code]&&distance[i.id]+temp->weight<distance[temp->code])
			{
				distance[temp->code]=distance[i.id]+temp->weight;
				path[temp->code]=i.id;
				mid[temp->code].distance=distance[temp->code];
				q.push(mid[temp->code]);
			}
		}
	}
	cout<<endl<<"���������뵽��Ķ���"<<endl;
	int type,k;
	cin>>type;
	k=type;
	cout<<endl;
	if(path[type]==type)
	{
		cout<<"�޷����"<<endl;
		return;
	}
	while(path[type]!=-1)
	{
		read[++top]=type;
		type=path[type];
	}
	cout<<type;
	for(int m=top;m>=0;m--)
		cout<<read[m];
	cout<<" ����Ϊ"<<distance[k]<<endl;
}
void total::TopoOrder()
{
	int *count=new int [sum*2+1]();
	int top=-1;
	for(map*e=head;e;e=e->down)
	{
		int m=e->code;
		map*mid=find(m,head);
		for(map*temp=mid->next;temp;temp=temp->next)
		{
			count[temp->code]++;
		}
	}
	for(int n=1;n<=sum;n++)
	{
		if(!count[n])
		{
			count[n]=top;
			top=n;
		}
	}
	for(int n=1;n<=sum;n++)
	{
		if(top==-1)
		{
			cout<<"Error!";
			return;
		}
		map*mid=find(top,head);
		top=count[top];
		cout<<mid->code;
		for(map*temp=mid->next;temp;temp=temp->next)
		{
			count[temp->code]--;
			if(!count[temp->code])
			{
				count[temp->code]=top;
				top=temp->code;
			}
		}
	}
}
void total::critical_path()
{
	int *ve=new int[sum*2+1]();
	int *vl=new int[sum*2+1]();
	int *count=new int [sum*2+1]();
	critical_path_topoorder(head,ve,0,NULL);
	map*temphead=critical_path_copyroute();
	critical_path_topoorder(temphead,vl,1,ve);
	for(map*temp=head;temp;temp=temp->down)
	for(map*mid=temp->next;mid;mid=mid->next)
	{
		int e=ve[temp->code];
		int l=vl[mid->code]-mid->weight;
		if(e==l)
			cout<<temp->code<<"->"<<mid->code<<endl;
	}
}
map*total::critical_path_copyroute()
{
	map*temhead=new map(*head);
	temhead->next=NULL;
	temhead->down=NULL;
	map*pre=temhead;
	for(map*temp=head->down;temp;temp=temp->down)
	{
		map*tem=new map(*temp);
		pre->down=tem;
		pre=tem;
		pre->down=NULL;
		pre->next=NULL;
	}
	for(map*temp=head;temp;temp=temp->down)//�ⲿ
	for(map*mid=temp->next;mid;mid=mid->next)//�ڲ�
	{
		map*p=find(mid->code,temhead);
		if(!p->next)
		{
			map*s=new map(*temp);
			s->weight=mid->weight;
			p->next=s;
			s->next=NULL;
			s->down=NULL;
		}
		else
		{
			map*s;
			for(s=p->next;s->next;s=s->next);
			map*u=new map(*temp);
			u->weight=mid->weight;
			s->next=u;
			u->next=NULL;
			u->down=NULL;
		}
	}
	return temhead;
}
void total::critical_path_topoorder(map*temhead,int *v,int flag,int *v2)//flag=0:ǰ�Һ�flag=1:����ǰ
{
	if(flag)
	{
		for(int m=1;m<=sum*2+1;m++)
			v[m]=MAX;
	}
	int *count=new int [sum*2+1]();
	int top=-1;
	for(int m=1;m<=sum;m++)
	{
		map*mid=find(m,temhead);
		for(map*temp=mid->next;temp;temp=temp->next)
		{
			count[temp->code]++;
		}
	}
	for(int n=1;n<=sum;n++)
	{
		if(!count[n])
		{
			count[n]=top;
			top=n;
		}
	}
	for(int n=1;n<=sum;n++)
	{
		if(top==-1)
		{
			cout<<"Error!";
			return;
		}
		map*mid=find(top,temhead);
		top=count[top];
		if(!flag)
		{
			for(map*temp=mid->next;temp;temp=temp->next)
			{
				if(temp->weight+v[mid->code]>v[temp->code])
					v[temp->code]=temp->weight+v[mid->code];
			}
		}
		else
		{
			if(n==1)
			{
				v[mid->code]=v2[mid->code];
			}
			for(map*temp=mid->next;temp;temp=temp->next)
			{
				if(v[mid->code]-temp->weight<v[temp->code])
					v[temp->code]=v[mid->code]-temp->weight;
			}
		}
		for(map*temp=mid->next;temp;temp=temp->next)
		{
			count[temp->code]--;
			if(!count[temp->code])
			{
				count[temp->code]=top;
				top=temp->code;
			}
		}
	}
}
void total::randon_short_route()
{
	map*tempout=head;
	for(;tempout;tempout=tempout->down)
	{
	int *read=new int[sum*2+1];
	int top=-1;
	clearvisit();
	path=new int[sum*2+1];
	distance=new int [sum*2+1];
	int x;//������ʼ��
	x=tempout->code;
	node mid[sum*2+1];//�������ȶ��еĲ���
	for(int m=1;m<=sum;m++)
	{
		mid[m].id=m;
		mid[m].distance=MAX;
		path[m]=m;
		distance[m]=MAX;
	}
	mid[x].distance=0;
	distance[x]=0;
	path[x]=-1;
	p.push(mid[x]);
	while(!p.empty())
	{
		node i=p.top();
		map*temp=find(i.id,head);
		p.pop();
		if(visit[i.id])
			continue;
		visit[i.id]=1;
		for(temp=temp->next;temp;temp=temp->next)
		{
			if(!visit[temp->code]&&distance[i.id]+temp->weight<distance[temp->code])
			{
				distance[temp->code]=distance[i.id]+temp->weight;
				path[temp->code]=i.id;
				mid[temp->code].distance=distance[temp->code];
				p.push(mid[temp->code]);
			}
		}
	}
	int type,k;//tyke:��Ҫ����Ķ���
	for(map*tl=head;tl;tl=tl->down)
	{
	type=tl->code;
	if(type==tempout->code)
		continue;
	cout<<tempout->code<<"->"<<tl->code<<":";
	k=type;
	if(path[type]==type)
	{
		cout<<"�޷����"<<endl;
		continue;
	}
	while(path[type]!=-1)
	{
		read[++top]=type;
		type=path[type];
	}
	cout<<type;
	for(int m=top;m>=0;m--)
		cout<<read[m];
	cout<<" ����Ϊ"<<distance[k]<<endl;
	top=-1;//��ʼ��readջ
	}
	}
}
int show()
{
	system("cls");
	for(int m=0;m<20;m++)
		cout<<"�y";
	cout<<endl;
	printf("1.��������ͼ%12c2.����ָ����Ȩֵ\n3.�������%14c4.ɾ������\n5.�����ڽӶ���%10c6.ͼ�ı���\n7.���·��%14c8.��������\n9.�ؼ�·��%14c10.�˳�����\n",' ',' ',' ',' ',' ');
	for(int m=0;m<20;m++)
		cout<<"�y";
	cout<<endl;
	int type;
	while(scanf("%d",&type)!=1||!(type>=1&&type<=10))
	{
		fflush(stdin);
		cout<<"������������������"<<endl;
	}
	return type;
}
void total::show_choose_overroute()
{
	cout<<"����������ѡ��Ĳ���"<<endl;
	cout<<"1.������ȱ���      2.������ȱ���"<<endl;
	int type;
	cin>>type;
	fflush(stdin);
	if(type==1)
		FZ_dfs();
	else if(type==2)
		BFS();
	cout<<endl;
}
void total::show_choose_shortway()
{
	cout<<"����������ѡ��Ĳ���"<<endl;
	cout<<"1.��Դ���·      2.���ⶥ�����·"<<endl;
	int type;
	cin>>type;
	if(type==1)
	{
		Dijkstra();
	}
	else
	{
		randon_short_route();
	}
}
void total::FZ_dfs()
{
	clearvisit();
	for(map*temp=head;temp;temp=temp->down)
	{
		int x=temp->code;
		if(!visit[x])
		{
			visit[x]=1;
		DFS(x);
		}
	}
}