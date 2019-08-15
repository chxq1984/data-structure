#include <iostream>
#include <windows.h>
using namespace std;
#include <stdio.h>
#define NUM 50
struct node
{
	node*firstchild,*nextbrother;
	node(char x){ch=x;firstchild=nextbrother=NULL;}
	char ch;
};
struct shed
{
	node**p;
	int top;
	shed(){top=-1;p=new node*[NUM];}
	void push(node *temp){p[++top]=temp;}
	node *read(){return p[top];}
	node*pop(){return p[top--];}
};
struct tree
{
	node *head;
	int sum;
	tree(){sum=0;head=NULL;}
	node **forest;
	void build();
	void readpre(node *p);
	void printpre_handover(node *p);
	void printbac_handover(node *p);
	void printpre_iteration();
	void printbac_iteration();
	void print_layer();
	void insert_tree();
	node *find_itself(char);
	node *find_leftend(node *);
	void search();
	void deleall(node *);
	void deleson();
	void delealltree();
};
class box
{
public:
    node *position;
    box*next;
};
class duilie
{
public:
    box *front,*rear;
    duilie(){front=rear=NULL;}
    void push(node *p);
    node*pop();
    void putout();
};
int show();
void show_print(tree *p);
int main()
{
	int type=show();
	char up,down;
	char begin,end,temtype;
	tree k;
	while(1)
	{
		switch(type)
		{
			case 1:	 system("cls");
					 k.build();
					 fflush(stdin);
					 getchar();
					 break;
			case 2:  system("cls");
					 show_print(&k);
					 fflush(stdin);
					 if(k.head)
					 getchar();
					 else
					 Sleep(500);
					 break;
			case 3:  system("cls");
					 k.insert_tree();
					 fflush(stdin);
					 if(k.head)
					 getchar();
					 else
					 Sleep(500);
					 break;
			case 4:  system("cls");
					 k.search();
					 fflush(stdin);
					 if(k.head)
					 getchar();
					 else 
					 Sleep(500);
					 break;
			case 5:  system("cls");
					 k.deleson();
					 fflush(stdin);
					 if(k.head)
					 getchar();
					 else 
					 Sleep(500);
					 break;
			case 6:  system("cls");
					 k.delealltree();
					 getchar();
					 break;
			case 7:  exit(0);
		}
		type=show();
	}
}
void tree::build()
{
	cout<<"请输入森林所包含的树的数量:";
	cin>>sum;
	if(!sum)
	{
		head=NULL;
		return;
	}
	forest=new node*[sum];
	shed sd;
	for(int h=0;h<sum;h++)
	{
	cout<<endl<<"请输入第"<<h+1<<"棵树的信息"<<endl;
	char temp;
	cin>>temp;
	node *temhead;
	if(temp==')')
	{
		temhead=NULL;
		head=NULL;
		return;
	}
	else
	{
		temhead=new node(temp);
		sd.push(temhead);
	}
	int flag=1;
	node *p;
	while(sd.top!=-1)
	{
		cin>>temp;
		if(temp!=')')
		{
			node *s=new node(temp);
			if(flag)
			{
				node*q=sd.read();
				q->firstchild=s;
			}
			else
			{
				p->nextbrother=s;
				flag=1;
			}
			sd.push(s);
		}
		else
		{
			p=sd.pop();
			flag=0;
		}
	}
	forest[h]=temhead;
	}
	for(int h=0;h<sum-1;h++)
		forest[h]->nextbrother=forest[h+1];
	head=forest[0];
	cout<<endl<<"森林构建完成！"<<endl;
}
void tree::printpre_handover(node*p)
{
	if(!p)
		return;
	cout<<p->ch;
	printpre_handover(p->firstchild);
	printpre_handover(p->nextbrother);
}
void tree::printbac_handover(node*p)
{
	if(!p)
		return;
	printbac_handover(p->firstchild);
	cout<<p->ch;
	printbac_handover(p->nextbrother);
}
void duilie::push(node*p)
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
node*duilie::pop()
{
    if(!front)
        return NULL;
    node *temp=front->position;
    box *del=front;
    front=front->next;
    delete del;
    return temp;
}
void duilie::putout()
{
    box*temp=front;
    while(temp)
    {
        printf("%c ",temp->position->ch);
        temp=temp->next;
    }
    printf("\n");
}
void tree::print_layer()
{
	if(!head)
		return;
	duilie sp;
	sp.push(head);
	while(sp.front)
	{
		node *temp=sp.pop();
		while(temp)
		{
			cout<<temp->ch;
			if(temp->firstchild)
				sp.push(temp->firstchild);
			temp=temp->nextbrother;
		}
	}
}
void tree::printpre_iteration()
{
	shed p;
	node *temp=head;
	if(!temp)
		return;
	p.push(temp);
	while(p.top!=-1)
	{
		temp=p.pop();
		cout<<temp->ch;
		if(temp->nextbrother)
			p.push(temp->nextbrother);
		if(temp->firstchild)
			p.push(temp->firstchild);
	}
}
void tree::printbac_iteration()
{
	shed p;
	node*temp=head;
	if(!temp)
		return;
	p.push(temp);
	while(p.top!=-1)
	{
		if(temp)
		{
		for(temp=temp->firstchild;temp;temp=temp->firstchild)
		{
			p.push(temp);
		}
		}
		temp=p.pop();
		cout<<temp->ch;
		temp=temp->nextbrother;
		if(temp)
			p.push(temp);
	}
}
node*tree::find_itself(char position)
{
	shed p;
	node *temp=head;
	if(!temp)
		return NULL;
	p.push(temp);
	while(p.top!=-1)
	{
		temp=p.pop();
		if(temp->ch==position)
			return temp;
		if(temp->nextbrother)
			p.push(temp->nextbrother);
		if(temp->firstchild)
			p.push(temp->firstchild);
	}
	return NULL;
}
void tree::insert_tree()
{
	if(!head)
	{
		cout<<"森林为空，无法进行此操作!"<<endl;
		Sleep(500);
		return;
	}
	char chup,chdown;
	cout<<"请输入您想插入的具体位置，包括上下结点位置，若结点为空则输入')'";
	cin>>chup>>chdown;
	node*up;
	if(chup==')')
	up=NULL;
	else
	up=find_itself(chup);
	node *down;
	if(chdown==')')
	down=NULL;
	else
	down=find_itself(chdown);
	if(up==NULL)
	{
		if(head->ch!=chdown)
		{
		cout<<endl<<"插入位置输入错误!";
		return;
		}
	}
	cout<<"请输入您想插入的树的信息:"<<endl;
	shed sd;
	char temp;
	cin>>temp;
	node *temhead;
	if(temp==')')
	{
		temhead=NULL;
		return;
	}
	else
	{
		temhead=new node(temp);
		sd.push(temhead);
	}
	int flag=1;
	node *p;
	while(sd.top!=-1)
	{
		cin>>temp;
		if(temp!=')')
		{
			node *s=new node(temp);
			sum++;
			if(flag)
			{
				node*q=sd.read();
				q->firstchild=s;
			}
			else
			{
				p->nextbrother=s;
				flag=1;
			}
			sd.push(s);
		}
		else
		{
			p=sd.pop();
			flag=0;
		}
	}//建立插入树的信息
	node *tofind=up;
	if(!up)
	{
		node*back=find_leftend(temhead);
		back->firstchild=head;
		head=temhead;
	}
	else//分情况 
	{
	if(tofind->firstchild==down)
	{
		node*catchpre=tofind->firstchild;
		up->firstchild=temhead;
		if(catchpre)
		temhead->nextbrother=catchpre->nextbrother;
		else
		temhead->nextbrother=NULL;
		node*back=find_leftend(temhead);
		back->firstchild=catchpre;
		if(catchpre)
		catchpre->nextbrother=NULL;
	}
	else
	{
		for(tofind=up->firstchild;tofind;tofind=tofind->nextbrother)
		{
			if(tofind->nextbrother==down)
				break;
		}
		node*catchpre=tofind->nextbrother;
		tofind->nextbrother=temhead;
		if(catchpre)
		temhead->nextbrother=catchpre->nextbrother;
		else
		temhead->nextbrother=NULL;
		node*back=find_leftend(temhead);
		back->firstchild=catchpre;
		if(catchpre)
		catchpre->nextbrother=NULL;
	}
	}
	cout<<"插入完成!"<<endl;
}
node*tree::find_leftend(node *head)
{
	if(!head)
		return NULL;
	if(!head->firstchild)
		return head;
	node *temp=head->firstchild;
	for(;temp->firstchild;temp=temp->firstchild);
		return temp;
}
void tree::search()
{
	if(!head)
	{
		cout<<endl<<"树为空，无法进行此操作"<<endl;
		Sleep(500);
		return;
	}
	char from,to;
	cout<<endl<<"请输入查询数据域:";
	cin>>from>>to;
	duilie sp;
	sp.push(head);
	while(sp.front)
	{
		node *temp=sp.pop();
		while(temp)
		{
			if(temp->ch>=from&&temp->ch<=to)
			cout<<temp->ch;
			if(temp->firstchild)
				sp.push(temp->firstchild);
			temp=temp->nextbrother;
		}
	}
}
void tree::deleall(node *top)
{
	if(!top)
	return;
	deleall(top->firstchild);
	deleall(top->nextbrother);
	delete(top);
}
void tree::deleson()
{
	char position;
	if(!head)
	{
		cout<<endl<<"树为空，无法进行此操作"<<endl;
		Sleep(500);
		return;
	}
	cout<<endl<<"请输入您想删除的结点信息:";
	cin>>position;
	if(head->ch==position)//删除首结点
	{
		node *detemp=head;
		head=head->nextbrother;
		detemp->nextbrother=NULL;
		deleall(detemp);
		return;
	}
	duilie sp;
	sp.push(head);
	node*temp=find_itself(position);//找到此结点
	if(!temp)
	{
		cout<<"未找到此结点!";
		return;
	}
	while(sp.front)
	{
		temp=sp.pop();
		while(temp)
		{
			if(temp->firstchild&&temp->firstchild->ch==position||temp->nextbrother&&temp->nextbrother->ch==position)
			{
				sp.front=NULL;//找到指向它的结点则退出
				break;
			}
			if(temp->firstchild)
				sp.push(temp->firstchild);
			temp=temp->nextbrother;
		}
	}
	if(temp->firstchild&&temp->firstchild->ch==position)//分为两种情况
	{
		node *deles=temp->firstchild;
		temp->firstchild=deles->nextbrother;
		deles->nextbrother=NULL;
		deleall(deles);
	}
	else if(temp->nextbrother&&temp->nextbrother->ch==position)
	{
		node *deles=temp->nextbrother;
		temp->nextbrother=deles->nextbrother;
		deles->nextbrother=NULL;
		deleall(deles);
	}
	cout<<endl<<"删除完成!";
}
int show()
{
	system("cls");
	for(int m=0;m<20;m++)
		cout<<"▂";
	cout<<endl;
	printf("1.创建森林%13c2.遍历森林\n3.插入树%13c  4.按条件域搜索结点\n5.删除结点及左右子树%3c6.销毁森林\n7.退出程序\n",' ',' ',' ');
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
void show_print(tree *p)
{
	if(!p->head)
	{
		cout<<endl<<"不存在树，无法进行此操作"<<endl;
		Sleep(500);
		return;
	}
	for(int m=0;m<20;m++)
		cout<<"▂";
	cout<<endl;
	printf("1.先根遍历(递归)%10c2.先根遍历(迭代)\n3.后根遍历(递归)%10c4.后根遍历(迭代)\n",' ',' ');
	printf("5.层次遍历\n");
	for(int m=0;m<20;m++)
		cout<<"▂";
	cout<<endl;
	int type;
	cin>>type;
	switch(type)
	{
		case 1:p->printpre_handover(p->head);
			   break;
		case 2:p->printpre_iteration();
			   break;
	    case 3:p->printbac_handover(p->head);
	    	   break;
	    case 4:p->printbac_iteration();
	           break;
	    case 5:p->print_layer();
	    	   break;
	}
}
void tree::delealltree()
{
	if(!head)
	{
		cout<<endl<<"树为空，无需进行此操作"<<endl;
		Sleep(500);
		return;
	}
	deleall(head);
	head=NULL;
	sum=0;
	delete [] forest;
	cout<<"销毁完成！";
	Sleep(500);
	return;
}
