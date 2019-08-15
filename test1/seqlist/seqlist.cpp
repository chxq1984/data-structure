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
	cout<<"请输入结点个数:"<<endl;
	cin>>sum;
	head=new int[sum*2];
	insert();
}
void node::insert()
{
	cout<<"输入插入位置和数据,以-1 -1结束"<<endl;
	int position,weight;
	cin>>position>>weight;
	while(!(position==-1&&weight==-1))
	{
		head[position]=weight;
		cin>>position>>weight;
	}
	cout<<"=>插入成功"<<endl;
}
int node::read()
{
	cout<<"请输入结点位置"<<endl;
	int temp;
	cin>>temp;
	return head[temp];
}
void node::dele()
{
	int temp;
	cout<<"请输入结点位置"<<endl;
	cin>>temp;
	for(int m=temp;m<sum-1;m++)
	{
		head[m]=head[m+1];
	}
	sum--;
}
void node::find()
{
	cout<<"请输入值"<<endl;
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
	cout<<"未找到"<<endl;
}
void node::insertone()
{
	cout<<"请输入您想插入的位置"<<endl;
	int temp;
	cin>>temp;
	cout<<"请输入您想插入的值"<<endl;
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