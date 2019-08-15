#include <iostream>
#include <stdio.h>
#include <windows.h>
using namespace std;
template <class T>
struct sh
{
	T num;
	sh*next;
};
template <class T>
class node
{
	sh<T>*head,*rear,*now;
	int total;
	int store;
public:
	int flag;
	node(){head=rear=now=NULL;total=0;flag=0;store=0;}
	void create();//创建 
	void add();//插入 
	void dele();//删除 
	void print();//输出 
	void read();//存取 
	void search();//查找 
	void deleall();//销毁 
};
int show();
int main(void)
{
	node <int>k=node<int>();
	int type=show();
	while(1)
	{
		switch(type)
		{
			case 1:	 system("cls");
					 k.create();
					 fflush(stdin);
					 getchar();
					 break;
			case 2:  system("cls");
					 k.add();
					 fflush(stdin);
					 if(k.flag)
					 getchar();
					 break;
			case 3:  system("cls");
					 k.dele();
					 fflush(stdin);
					 if(k.flag)
					 getchar();
					 break;
			case 4:  system("cls");
					 k.read();
					 fflush(stdin);
					 if(k.flag)
					 getchar();
					 break;
			case 5:  system("cls");
					 k.search();
					 fflush(stdin);
					 if(k.flag)
					 getchar();
					 break;
			case 6:  system("cls");
					 k.deleall();
					 if(k.flag)
					 getchar();
					 break;
			case 7:  exit(0);
		}
		type=show();
	}
}
template <class T>
void node<T>::create()
{
	now=new sh<T>;
	head=rear=now;
	head->next=NULL;
	printf("=>创建成功，当前含有0个元素\n");
	flag=1;
}
template <class T>
void node<T>::add()
{
	if(!flag)
	{
		printf("还未创建链表，无法插入数据!");
		Sleep(500);
		return;
	}
	printf("当前链表数据:\n");
	print();
	sh<T>*od;
	printf("=>在表头插入数据以-1结束\n");
	T temp;
	cin>>temp;
	while(temp!=-1)
	{
		total++;
		od=new sh<T>;
		od->num=temp;
		od->next=head->next;
		head->next=od;
		now=od;
		cin>>temp;
	}
	printf("=>插入成功\n");
	printf("=>在当前结点后插入数据以-1结束\n");
	cin>>temp;
	while(temp!=-1)
	{
		total++;
		od=new sh<T>;
		od->num=temp;
		od->next=now->next;
		now->next=od;
		now=od;
		cin>>temp;
	}
	printf("=>插入成功\n");
	printf("=>在表尾插入数据以-1结束\n");
	cin>>temp;
	while(rear->next!=NULL)
	{
		rear=rear->next;
	}
	while(temp!=-1)
	{
		total++;
		od=new sh<T>;
		od->num=temp;
		od->next=rear->next;
		rear->next=od;
		rear=od;
		now=rear;
		cin>>temp;
	}
	printf("=>插入成功\n");
	printf("当前链表数据:\n");
	print();
}
template <class T>
void node<T>::print()
{
	if(!head->next)
	{
		printf("无\n");
		return;
	}
	sh<T>*temp=head->next;
	printf("=>");
	for(int m=0;m<total-1;m++)
	{
	printf("%d->",temp->num);
	temp=temp->next;
	}
	printf("%d",temp->num);
	cout<<endl;
}
template <class T>
void node<T>::dele()
{
	if(!flag)
	{
		printf("还未创建链表，无法删除数据!");
		Sleep(800);
		return;
	}
	printf("当前链表数据:\n");
	print();
	sh<T>*temp;
	int n=0;
	while(1)
	{
		if(!head->next)
		{
			printf("链表已空，无法继续删除.\n");
			return;
		}
		printf("请输入您想操作的序号:\n");
		printf("1.删除表头结点%20c2.删除表尾结点\n3.删除当前结点的后继结点%10c4.退出删除功能\n",' ',' ');
		int te;
		while(scanf("%d",&te)!=1||!(te>=1&&te<=4))
			fflush(stdin);
		switch(te)
		{
			case 1:temp=head->next;
				   if(temp!=NULL)
					{
						head->next=temp->next;
						if(now==temp)
						now=temp->next;
						if(rear==temp)
						now=rear=head;
						delete(temp);
						total--;
					}
					printf("\n已删除表头结点\n");
					printf("当前链表数据:\n");
					print();
					break;
			case 2:
					temp=head;
					while(temp->next!=NULL&&temp->next!=rear)
					{
					temp=temp->next;
					}
					if(rear!=NULL)
					{
					temp->next=rear->next;
					if(now==rear)
					now=temp;
					delete(rear);
					total--;
					}
					rear=temp;
					printf("已删除表尾结点\n");
					printf("当前链表数据:\n");
					print();
					break;
			case 3:if(now->next!=NULL)
					{
					temp=now->next;
					now->next=temp->next;
					delete temp;
					total--;
					}
					printf("已删除当前结点的后继结点\n");
					printf("当前链表数据:\n");
					print();
					break;
			case 4: n=1;
					printf("当前链表数据:\n");
					print();
					break;
		}
		if(n)
			return;
	}
}
template<class T>
void node<T>::read()
{
	if(!flag)
	{
		printf("还未创建链表，无法存取数据!");
		Sleep(800);
		return;
	}
	printf("当前链表数据:\n");
	print();
	if(!head->next)
		return;
	int temp;
	cout<<"\n当前位置结点:";
	if(now!=NULL)
		cout<<endl<<now->num<<endl;
	cout<<"\n请输入想存取的位置：\n";
	cin>>temp;
	sh <T>*ps=head->next;
	if(temp>total)
	{
		cout<<"查找不到指定信息\n";
		return;
	}
	for(int m=1;m<=total;m++)
	{
		if(m==temp)
		{
			cout<<"指定位置结点的值为";
			cout<<ps->num<<endl;
			store=ps->num;
			return;
		}
		ps=ps->next;
	}
}
template<class T>
void node<T>::search()
{
	if(!flag)
	{
		printf("还未创建链表，无法搜索数据!");
		Sleep(800);
		return;
	}
	printf("当前链表数据:\n");
	print();
	if(!head->next)
		return;
	T p;
	int flag=0;
	printf("\n请输入想要查找的值:\n");
	cin>>p;
	int m=1;
	sh<T>*temp=head->next;
	cout<<"查找结果为: ";
	for(;m<=total;m++)
	{
		if(temp->num==p)
		{
			cout<<m<<" ";
			now=temp;
			flag=1;
		}
		temp=temp->next;
	}
	if(!flag)
	printf("无此值");
	return;
}
int show()
{
	system("cls");
	for(int m=0;m<20;m++)
		cout<<"▂";
	cout<<endl;
	printf("1.创建单链表%10c2.插入操作\n3.删除操作%10c  4.存取操作\n5.查找操作%12c6.销毁单链表\n7.退出程序\n",' ',' ',' ');
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
template <class T>
void node<T>::deleall()
{
	if(!flag)
	{
		printf("还未创建链表，无法销毁!");
		Sleep(800);
		return;
	}
	if(!head)
		return;
	sh<T>*od=head,*p=od->next;
	while(p!=NULL)
	{
		delete(od);
		od=p;
		p=p->next;
	}
	delete(od);
	head=rear=now=NULL;
	total=0;
	store=0;
	cout<<"已销毁链表";
	Sleep(1000);
	flag=0;
}