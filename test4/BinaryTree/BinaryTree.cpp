#include <iostream>
#include <windows.h>
#include <stdio.h>
using namespace std;
class node
{
public:
	char ch;
	node*left,*right;
	node(){left=right=NULL;}
};
class nodeback//用于后根遍历的栈 
{
public:
	node *p;
	nodeback*left,*right;
	int i;//标志 
	nodeback(){i=0;p=NULL;left=right=NULL;}
};
class shed//栈
{
	node**shedtop;
public:
	int top;
	shed(){shedtop=NULL;top=-1;}
	void buildshed(int sum){shedtop=new node*[100];}
	void push(node *p){shedtop[++top]=p;}
	node *pop(){return shedtop[top--];}
};
class shedback//后根栈 
{
	nodeback **shedtop;
public:
	int top;
	shedback(){shedtop=NULL;top=-1;}
	void buildshed(int sum){shedtop=new nodeback*[sum+1];}
	void push(nodeback *p){shedtop[++top]=p;}
	nodeback *pop(){return shedtop[top--];}
};
class box
{
public:
    node *position;
    box*next;
};
class duilie//队列 
{
public:
    box *front,*rear;
    duilie(){front=rear=NULL;}
    void push(node *p);
    node*pop();
};
class tree
{
	node*top;
public:
	int sum;//结点个数
	tree(){top=NULL;sum=0;}
	node *build();
	void printpre_handover(node *p);
	void printmid_handover(node *p);
	void printbac_handover(node *p);
	void printpre_iteration();
	void printmid_iteration();
	void printbac_iteration();
	void print_layer();
	node *findfather(node*,char);
	node*& readtop(){return top;}
	void search(node *p,char begin,char end);
	void deleall(node*);
	void delson(char);
	nodeback*copy(node* top);
	node *search(node*,char);
};
int show();
void show_print(tree *p);
int main()
{
	int type=show();
	tree k;
	char in;
	char begin,end;
	char temtype;
	node*father;
	while(1)
	{
		switch(type)
		{
			case 1:	 system("cls");
					 cout<<"请输入二叉树结点信息："<<endl;
					 k.readtop()=k.build();
					 fflush(stdin);
					 getchar();
					 break;
			case 2:  system("cls");
					 show_print(&k);
					 fflush(stdin);
					 if(k.sum)
					 getchar();
					 Sleep(500);
					 break;
			case 3:  system("cls");
					 if(!k.sum)
					 {
					 	cout<<endl<<"二叉树为空，无法进行此操作"<<endl;
					 	Sleep(500);
					 	break;
					 }
					 cout<<endl<<"请输入您想要寻找的对象:";
					 fflush(stdin);
					 cin>>in;
					 father=k.findfather(k.readtop(),in);
					 if(father)
					 cout<<endl<<"父结点为"<<father->ch;
					 else
					 cout<<endl<<"未找到其父结点";
					 fflush(stdin);
					 getchar();
					 break;
			case 4:  system("cls");
					if(!k.sum)
					 {
					 	cout<<endl<<"二叉树为空，无法进行此操作"<<endl;
					 	Sleep(500);
					 	break;
					 }
					 cout<<endl<<"请输入查询数据域:";
					 cin>>begin>>end;
					 k.search(k.readtop(),begin,end);
					 fflush(stdin);
					 getchar();
					 break;
			case 5:  system("cls");
					 if(!k.sum)
					 {
					 	cout<<endl<<"二叉树为空，无法进行此操作"<<endl;
					 	Sleep(500);
					 	break;
					 }
					 cout<<endl<<"请输入您想删除的结点信息:";
					 cin>>temtype;
					 k.delson(temtype);
					 fflush(stdin);
					 getchar();
					 break;
			case 6:  system("cls");
					 if(!k.sum)
					 {
					 	cout<<endl<<"二叉树为空，无需进行此操作"<<endl;
					 	Sleep(500);
					 	break;
					 }
					 k.deleall(k.readtop());
					 cout<<"销毁完成！";
					 fflush(stdin);
					 getchar();
					 break;
			case 7:  exit(0);
		}
		type=show();
	}
}
node *tree::build()
{
	char temp;
	cin>>temp;
	if(temp=='#')
		return NULL;
	sum++;
	node *mid=new node;
	mid->ch=temp;
	mid->left=build();
	mid->right=build();
	return mid;
}
void tree::printpre_handover(node*p)
{
	if(!p)
		return;
	cout<<p->ch;
	printpre_handover(p->left);
	printpre_handover(p->right);
}
void tree::printmid_handover(node*p)
{
	if(!p)
		return;
	printmid_handover(p->left);
	cout<<p->ch;
	printmid_handover(p->right);
}
void tree::printbac_handover(node*p)
{
	if(!p)
		return;
	printbac_handover(p->left);
	printbac_handover(p->right);
	cout<<p->ch;
}
void tree::printpre_iteration()
{
	shed p;
	p.buildshed(sum);
	node *temp=readtop();
	if(!temp)
		return;
	p.push(temp);
	while(p.top!=-1)
	{
		temp=p.pop();
		cout<<temp->ch;
		if(temp->right)
			p.push(temp->right);
		if(temp->left)
			p.push(temp->left);
	}
}
void tree::printmid_iteration()
{
	shed p;
	p.buildshed(sum);
	node*temp=readtop();
	if(!temp)
		return;
	p.push(temp);
	while(p.top!=-1)
	{
		if(temp)
		{
		for(temp=temp->left;temp;temp=temp->left)
		{
			p.push(temp);
		}
		}
		temp=p.pop();
		cout<<temp->ch;
		temp=temp->right;
		if(temp)
			p.push(temp);
	}
}
node *tree::findfather(node*temtop,char son)
{
	if(top->ch==son||temtop==NULL)
		return NULL;
	if(temtop->left&&temtop->left->ch==son||temtop->right&&temtop->right->ch==son)
		return temtop;
	return findfather(temtop->left,son);
	return findfather(temtop->right,son);
}
void tree ::search(node *p,char begin,char end)
{
	if(!p)
		return;
	if(p->ch>=begin&&p->ch<=end)
		cout<<p->ch<<" ";
	search(p->left,begin,end);
	search(p->right,begin,end);
}
void tree::deleall(node*top)
{
	if(!top)
	return;
	deleall(top->left);
	deleall(top->right);
	delete(top);
	sum--;
}
void tree::delson(char son)
{
	if(top==NULL)
		return;
	if(top->ch==son)
	{
		deleall(top);
		top=NULL;
		return;
	}
	node *father=findfather(top,son);
	node *fson=search(top,son);
	if(!father||!fson)
	{
		cout<<"无法找到该点"<<endl;
		return;
	}
	if(father->left==fson)
		father->left=NULL;
	if(father->right==fson)
		father->right=NULL;
	deleall(fson);
}
node *tree::search(node*top,char ch)
{
	duilie p;
	p.push(top);
	while(p.front)
	{
		node *mid=p.pop();
		if(mid->ch==ch)
			return mid;
		if(mid->left)
			p.push(mid->left);
		if(mid->right)
			p.push(mid->right);
	}
	return NULL;
}
nodeback*tree::copy(node *top)
{
	if(!top)
		return NULL;
	nodeback*temp=new nodeback;
	temp->left=copy(top->left);
	temp->right=copy(top->right);
	temp->p=top;
	return temp;
}
void tree::printbac_iteration()
{
	nodeback*copytree=copy(readtop());
	if(!copytree)
		return;
	shedback shed;
	shed.buildshed(sum);
	shed.push(copytree);
	while(shed.top!=-1)
	{
		nodeback*temp=shed.pop();
		if(temp->i==0)//置入左儿子 
		{
			temp->i++;
			shed.push(temp);
			if(temp->left)
			shed.push(temp->left);
		}
		else if(temp->i==1)//置入右儿子 
		{
			temp->i++;
			shed.push(temp);
			if(temp->right)
			shed.push(temp->right);
		}
		else if(temp->i==2)//输出 
			cout<<temp->p->ch;
	}
}
int show()
{
	system("cls");
	for(int m=0;m<20;m++)
		cout<<"▂";
	cout<<endl;
	printf("1.创建二叉树%12c2.二叉树遍历\n3.搜索父节点%10c  4.按条件域搜索结点\n5.删除结点及左右子树%4c6.销毁二叉树\n7.退出程序\n",' ',' ',' ');
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
	if(!p->sum)
	{
		cout<<endl<<"二叉树为空，无法进行此操作"<<endl;
		Sleep(500);
		return;
	}
	for(int m=0;m<20;m++)
		cout<<"▂";
	cout<<endl;
	printf("1.先根遍历(递归)%10c2.先根遍历(迭代)\n3.中根遍历(递归)%10c4.中根遍历(迭代)\n",' ',' ');
	printf("5.后根遍历(递归)%10c6.后根遍历(迭代)\n7.层次遍历\n",' ');
	for(int m=0;m<20;m++)
		cout<<"▂";
	cout<<endl;
	int type;
	cin>>type;
	switch(type)
	{
		case 1:p->printpre_handover(p->readtop());
			   break;
		case 2:p->printpre_iteration();
			   break;
	    case 3:p->printmid_handover(p->readtop());
	    	   break;
	    case 4:p->printmid_iteration();
	           break;
	    case 5:p->printbac_handover(p->readtop());
	    	   break;
	    case 6:p->printbac_iteration();
	    	   break;
	    case 7:p->print_layer();
	    	   break;
	}
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
void tree::print_layer()
{
	duilie p;
	p.push(top);
	while(p.front)
	{
		node *mid=p.pop();
		cout<<mid->ch;
		if(mid->left)
			p.push(mid->left);
		if(mid->right)
			p.push(mid->right);
	}
}