#include <iostream>
using namespace std;
struct node
{
	int *head;
	int sum;
	node(){head=NULL;sum=0;}
	void build();
	void insert();
	int read();
	void dele();
	void find();
	void insertone();
	void output();
};
int main()
{
	node start;
	start.build();
	start.output();
	start.insertone();
	start.output();
	start.read();
	start.dele();
	start.output();
	start.find();
}
void node::build()
{
	cout<<"�����������:"<<endl;
	cin>>sum;
	head=new int[sum*2];
	insert();
}
void node::insert()
{
	cout<<"�������λ�ú�����,��-1 -1����"<<endl;
	int position,weight;
	cin>>position>>weight;
	while(!(position==-1&&weight==-1))
	{
		head[position]=weight;
		cin>>position>>weight;
	}
	cout<<"=>����ɹ�"<<endl;
}
int node::read()
{
	cout<<"��������λ��"<<endl;
	int temp;
	cin>>temp;
	return head[temp];
}
void node::dele()
{
	int temp;
	cout<<"��������λ��"<<endl;
	cin>>temp;
	for(int m=temp;m<sum-1;m++)
	{
		head[m]=head[m+1];
	}
	sum--;
}
void node::find()
{
	cout<<"������ֵ"<<endl;
	int temp;
	cin>>temp;
	for(int m=0;m<sum;m++)
	{
		if(head[m]==temp)
		{
			cout<<m;
			return;
		}
	}
	cout<<"δ�ҵ�"<<endl;
}
void node::insertone()
{
	cout<<"��������������λ��"<<endl;
	int temp;
	cin>>temp;
	cout<<"��������������ֵ"<<endl;
	int num;
	cin>>num;
	for(int m=sum;m>temp;m--)
	{
		head[m]=head[m-1];
	}
	head[temp+1]=num;
	sum++;
}
void node::output()
{
	for(int m=0;m<sum;m++)
		cout<<head[m]<<" ";
}