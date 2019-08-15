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
	void create();//���� 
	void add();//���� 
	void dele();//ɾ�� 
	void print();//��� 
	void read();//��ȡ 
	void search();//���� 
	void deleall();//���� 
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
	printf("=>�����ɹ�����ǰ����0��Ԫ��\n");
	flag=1;
}
template <class T>
void node<T>::add()
{
	if(!flag)
	{
		printf("��δ���������޷���������!");
		Sleep(500);
		return;
	}
	printf("��ǰ��������:\n");
	print();
	sh<T>*od;
	printf("=>�ڱ�ͷ����������-1����\n");
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
	printf("=>����ɹ�\n");
	printf("=>�ڵ�ǰ�������������-1����\n");
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
	printf("=>����ɹ�\n");
	printf("=>�ڱ�β����������-1����\n");
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
	printf("=>����ɹ�\n");
	printf("��ǰ��������:\n");
	print();
}
template <class T>
void node<T>::print()
{
	if(!head->next)
	{
		printf("��\n");
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
		printf("��δ���������޷�ɾ������!");
		Sleep(800);
		return;
	}
	printf("��ǰ��������:\n");
	print();
	sh<T>*temp;
	int n=0;
	while(1)
	{
		if(!head->next)
		{
			printf("�����ѿգ��޷�����ɾ��.\n");
			return;
		}
		printf("������������������:\n");
		printf("1.ɾ����ͷ���%20c2.ɾ����β���\n3.ɾ����ǰ���ĺ�̽��%10c4.�˳�ɾ������\n",' ',' ');
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
					printf("\n��ɾ����ͷ���\n");
					printf("��ǰ��������:\n");
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
					printf("��ɾ����β���\n");
					printf("��ǰ��������:\n");
					print();
					break;
			case 3:if(now->next!=NULL)
					{
					temp=now->next;
					now->next=temp->next;
					delete temp;
					total--;
					}
					printf("��ɾ����ǰ���ĺ�̽��\n");
					printf("��ǰ��������:\n");
					print();
					break;
			case 4: n=1;
					printf("��ǰ��������:\n");
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
		printf("��δ���������޷���ȡ����!");
		Sleep(800);
		return;
	}
	printf("��ǰ��������:\n");
	print();
	if(!head->next)
		return;
	int temp;
	cout<<"\n��ǰλ�ý��:";
	if(now!=NULL)
		cout<<endl<<now->num<<endl;
	cout<<"\n���������ȡ��λ�ã�\n";
	cin>>temp;
	sh <T>*ps=head->next;
	if(temp>total)
	{
		cout<<"���Ҳ���ָ����Ϣ\n";
		return;
	}
	for(int m=1;m<=total;m++)
	{
		if(m==temp)
		{
			cout<<"ָ��λ�ý���ֵΪ";
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
		printf("��δ���������޷���������!");
		Sleep(800);
		return;
	}
	printf("��ǰ��������:\n");
	print();
	if(!head->next)
		return;
	T p;
	int flag=0;
	printf("\n��������Ҫ���ҵ�ֵ:\n");
	cin>>p;
	int m=1;
	sh<T>*temp=head->next;
	cout<<"���ҽ��Ϊ: ";
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
	printf("�޴�ֵ");
	return;
}
int show()
{
	system("cls");
	for(int m=0;m<20;m++)
		cout<<"�y";
	cout<<endl;
	printf("1.����������%10c2.�������\n3.ɾ������%10c  4.��ȡ����\n5.���Ҳ���%12c6.���ٵ�����\n7.�˳�����\n",' ',' ',' ');
	for(int m=0;m<20;m++)
		cout<<"�y";
	cout<<endl;
	int type;
	while(scanf("%d",&type)!=1||!(type>=1&&type<=7))
	{
		fflush(stdin);
		cout<<"������������������"<<endl;
	}
	return type;
}
template <class T>
void node<T>::deleall()
{
	if(!flag)
	{
		printf("��δ���������޷�����!");
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
	cout<<"����������";
	Sleep(1000);
	flag=0;
}