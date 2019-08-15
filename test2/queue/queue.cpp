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
	sh<T>*front,*rear;
	int total;
public:
	int flag;
	node(){front=rear=NULL;total=0;flag=0;}
	void create();
	void insert();
	void dele();
	void deleall();
	T read();
	void print();
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
					 k.insert();
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
					 k.deleall();
					 fflush(stdin);
					 if(k.flag)
					 getchar();
					 break;
			case 6:  exit(0);
		}
		type=show();
	}
	return 0;
}
template <class T>
void node<T>::create()
{
	front=rear=new sh<T>;
	rear->next=NULL;
	printf("�����ɹ�����ǰ����0��Ԫ��\n");
	flag=1;
}
template <class T>
void node<T>::insert()
{
	if(!flag)
	{
		cout<<"��δ��������,�޷���������\n";
		Sleep(500);
		return;
	}
	sh<T>*temp;
	printf("****���(��-1����)******\n");
	T te;
	cin>>te;
	while(te!=-1)
	{
		total++;
		temp=new sh<T>;
		temp->num=te;
		rear->next=temp;
		rear=temp;
		cin>>te;
	}
	printf("=>����ɹ�\n");
	printf("��ǰ������Ϣ:\n");
	print();
}
template <class T>
T node<T>::read()
{
	if(!flag)
	{
		cout<<"��δ��������,�޷���ȡ����\n";
		Sleep(500);
		return -1;
	}
	if(front->next!=NULL)
	{
		cout<<"��ȡֵΪ:"<<front->next->num;
		return front->next->num;
	}
	else
		return -1;
}
template <class T>
void node<T>::print()
{
	if(!total)
	{
		printf("��\n");
		return;
	}
	cout<<"\n=>";
	sh<T> *temp=front->next;
	for(int m=1;m<=total;m++)
	{
		cout<<temp->num<<" ";
		temp=temp->next;
	}
	printf("\n");
}
template <class T>
void node<T>::dele()
{
	if(!flag)
	{
		cout<<"��δ��������,�޷�ɾ������\n";
		Sleep(500);
		return;
	}
	printf("��ǰ������Ϣ:\n");
	print();
	if(front->next!=NULL)
	{
		sh<T>*temp=front->next;
		front->next=temp->next;
		total--;
		delete(temp);
		cout<<"ɾ�����";
		printf("\n��ǰ������Ϣ:\n");
		print();
	}
	else
		return;
}
int show()
{
	system("cls");
	for(int m=0;m<20;m++)
		cout<<"�y";
	cout<<endl;
	printf("1.��������%10c2.�������\n3.ɾ������%10c4.��ȡ����\n5.���ٶ���%10c6.�˳�����\n",' ',' ',' ');
	for(int m=0;m<20;m++)
		cout<<"�y";
	cout<<endl;
	int type;
	while(scanf("%d",&type)!=1||!(type>=1&&type<=6))
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
		printf("��δ�������У��޷�����!");
		Sleep(800);
		return;
	}
	if(!front)
		return;
	sh<T>*od=front,*p=od->next;
	while(p!=NULL)
	{
		delete(od);
		od=p;
		p=p->next;
	}
	delete(od);
	front=rear=NULL;
	total=0;
	cout<<"�����ٶ���";
	Sleep(1000);
	flag=0;
}
