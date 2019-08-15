#include <iostream>
#include<fstream>
#include <string>
#include <queue>
#include <vector>
#include <stdio.h>
using namespace std;
#define cin fin
ofstream fout("out.cxq");
struct box
{
	int num;
	box*next;
	box(){next=NULL;}
};
struct duilie
{
	box*front,*rear;
	int pop();
	void push(int x);
	duilie(){front=rear=NULL;}
};
struct date
{
	unsigned char ch;
	int time;
	date*left,*right;
	date(){time=0;left=right=NULL;ch='*';}
	friend bool operator <(date a,date b)
	{
		return a.time>b.time;
	}
};
struct node
{
	string v;
    date *top;
    date *storech;
	unsigned char **maptop;
	unsigned char *temnumber;
	int numbertop;
	int number;
	int sum;
	node(){top=NULL;numbertop=-1;sum=0;}
	void build();
	void sort(date*);
	void putout();
	void buildmap(date*top);
	void compress();
	void setup();
	void copy(int x);
	void debug(date*top);
	void inputcode(int x);
	void compress_tree();
	void inputmap();//输出编码
	void max_small();
};
struct denode
{
	int sum;
	date*storech;
	date *top;
	int number;
	fstream infilete; 
	void build();
	void sort(date*top);
	void debug(date*top);
	void decompress();
};
priority_queue <date> que;
int main()
{
	node start;
	start.setup();
	start.build();
	start.buildmap(start.top);
	start.compress();
	start.compress_tree();
	start.inputmap();
	denode st;
	st.build();
	st.decompress();
	start.max_small();
}
void node::build()//建立哈夫曼树
{
	storech=new date[60];
	for(int m=0;m<60;m++)
	{
		if(m<=25)
		storech[m].ch='a'+m;
		else if(m<52)
		storech[m].ch='A'+m-26;
		else if(m==52)
		storech[m].ch=',';
		else if(m==53)
		storech[m].ch='.';
		else if(m==54)
		storech[m].ch='?';
		else if(m==55)
		storech[m].ch='!';
		else if(m==56)
		storech[m].ch='\"';
		else if(m==57)
		storech[m].ch='\'';
		else if(m==58)
		storech[m].ch=' ';
		else if(m==59)
		storech[m].ch='\n';
	}
	unsigned char temp;
	ifstream infile; 
    infile.open("test.txt");
    infile >> noskipws;
    infile>>temp;
    while (!infile.eof())
    {
		if(temp>='a'&&temp<='z')
		storech[temp-'a'].time++;
		else if(temp>='A'&&temp<='Z')
		storech[temp-'A'+26].time++;
		else if(temp==',')
		storech[52].time++;
		else if(temp=='.')
		storech[53].time++;
		else if(temp=='?')
		storech[54].time++;
		else if(temp=='!')
		storech[55].time++;
		else if(temp=='\"')
		storech[56].time++;
		else if(temp=='\'')
		storech[57].time++;
		else if(temp==' ')
		storech[58].time++;
		else if(temp=='\n')
		storech[59].time++;
		infile>>temp;
	}
	infile.close();
	sort(storech);
	//
	date *temptop;
	while(!(que.empty()))
	{
		temptop=new date;
		date *pre=new date;
		*pre=que.top();
		que.pop();
		if(que.empty())
		{
			top=pre;
			return;
		}
		date *bac=new date;
		*bac=que.top();
		que.pop();
		temptop->time=pre->time+bac->time;
		if(pre->time<=bac->time)
		{
			temptop->left=pre;
			temptop->right=bac;
		}
		else 
		{
			temptop->right=pre;
			temptop->left=bac;
		}
		que.push(*temptop);
	}
	top=temptop;
	number=top->time;
}
void node::sort(date*top)
{
	for(int m=0;m<60;m++)
	{
		if(top[m].time)
		{
			que.push(top[m]);
			sum++;
		}
	}
}
void node::putout()
{
	for(int m=0;m<60;m++)
	{
		int n=0;
		if(maptop[m][n]!='*')
		{
		while(maptop[m][n]!='*')
		{
			cout<<maptop[m][n];
			n++;
		}
		cout<<endl;
		}
	}
}
void node::setup()
{
	maptop=new unsigned char*[60];
	for(int m=0;m<60;m++)
	{
		maptop[m]=new unsigned char[126];
		for(int n=0;n<126;n++)
			maptop[m][n]='*';
	}
	temnumber=new unsigned char[126];
	for(int m=0;m<126;m++)
		temnumber[m]='*';
}
void duilie::push(int x)
{
	if(!front)
	{
		front=new box;
		front->num=x;
		rear=front;
	}
	else
	{
		box*temp=new box;
		temp->num=x;
		rear->next=temp;
		rear=temp;
	}
}
int duilie::pop()
{
	int temp=front->num;
	box*dele=front;
	front=front->next;
	delete dele;
	return temp;
}
void node::buildmap(date*top)
{
	if(top->ch!='*')
	{
		unsigned char temp=top->ch;
		if(temp>='a'&&temp<='z')
			copy(temp-'a');
		else if(temp>='A'&&temp<='Z')
			copy(temp-'A'+26);
		else if(temp==',')
			copy(52);
		else if(temp=='.')
			copy(53);
		else if(temp=='?')
			copy(54);
		else if(temp=='!')
			copy(55);
		else if(temp=='\"')
			copy(56);
		else if(temp=='\'')
			copy(57);
		else if(temp==' ')
			copy(58);
		else if(temp=='\n')
			copy(59);
		temnumber[numbertop--]='*';
		return;
	}
	if(top->left)
	{
	temnumber[++numbertop]='0';
	buildmap(top->left);
	}
	if(top->right)
	{
	temnumber[++numbertop]='1';
	buildmap(top->right);
	}
	temnumber[numbertop--]='*';
}
void node::copy(int x)
{
	for(int m=0;m<=numbertop;m++)
	{
		maptop[x][m]=temnumber[m];
	}
}
void node::debug(date*top)
{
	if(!top)
		return;
	cout<<top->ch;
	debug(top->left);
	debug(top->right);
}
void node::compress()
{
	compress_tree();
	unsigned char temp;
	fstream infile; 
    infile.open("test.txt");/////////////////
    infile >> noskipws;
    infile>>temp;
    while (!infile.eof())
    {
		if(temp>='a'&&temp<='z')
			inputcode(temp-'a');
		else if(temp>='A'&&temp<='Z')
			inputcode(temp-'A'+26);
		else if(temp==',')
			inputcode(52);
		else if(temp=='.')
			inputcode(53);
		else if(temp=='?')
			inputcode(54);
		else if(temp=='!')
			inputcode(55);
		else if(temp=='\"')
			inputcode(56);
		else if(temp=='\'')
			inputcode(57);
		else if(temp==' ')
			inputcode(58);
		else if(temp=='\n')
			inputcode(59);
		infile>>temp;
	}
	if(v.length())
	{
		fout<<v;
    }
	infile.close();
	fout.close();
}
void node::inputcode(int x)
{
	string input;
	int n=0;
	unsigned char out,tmp;
	int i;
	while(maptop[x][n]!='*')
	{
		v.push_back(maptop[x][n]);
		n++;
	}
	if(v.length()>=8)
	{
		for(i=0;i+7<v.length();i+=8)
		{
			out=0;
			for(int j=7;j>=0;j--)
			{
				if('0'==v[i+j])
					tmp=0;
				else
					tmp=1;
				out+=tmp<<(7-j);
			}
			input.push_back(out);
		}
		fout<<input;
		v = v.substr(i, v.length());//修改值
	}
}
void node::compress_tree()
{
	for(int m=0;m<60;m++)
	{
		int n=0;
		if(maptop[m][n]!='*')
		{
			if(storech[m].ch=='\n')
				fout<<'*';
			else if(storech[m].ch==' ')
				fout<<'&';
			else
			fout<<storech[m].ch;
			fout<<storech[m].time;
			fout<<endl;
		}
	}
	fout<<"$"<<endl;//结束符
}
void denode::build()
{
	while(!que.empty())
		que.pop();
	storech=new date[60];
	for(int m=0;m<60;m++)
	{
		if(m<=25)
		storech[m].ch='a'+m;
		else if(m<52)
		storech[m].ch='A'+m-26;
		else if(m==52)
		storech[m].ch=',';
		else if(m==53)
		storech[m].ch='.';
		else if(m==54)
		storech[m].ch='?';
		else if(m==55)
		storech[m].ch='!';
		else if(m==56)
		storech[m].ch='\"';
		else if(m==57)
		storech[m].ch='\'';
		else if(m==58)
		storech[m].ch=' ';
		else if(m==59)
		storech[m].ch='\n';
	}
	unsigned char temp;
	int time;
    infilete.open("out.cxq");
    infilete>>temp;
    while (temp!='$')
    {
    	infilete>>time;
		if(temp>='a'&&temp<='z')
		storech[temp-'a'].time=time;
		else if(temp>='A'&&temp<='Z')
		storech[temp-'A'+26].time=time;
		else if(temp==',')
		storech[52].time=time;
		else if(temp=='.')
		storech[53].time=time;
		else if(temp=='?')
		storech[54].time=time;
		else if(temp=='!')
		storech[55].time=time;
		else if(temp=='\"')
		storech[56].time=time;
		else if(temp=='\'')
		storech[57].time=time;
		else if(temp=='&')
		storech[58].time=time;
		else if(temp=='*')
		storech[59].time=time;
		infilete>>temp;
	}
	sort(storech);
	date *temptop;
	while(!(que.empty()))
	{
		temptop=new date;
		date *pre=new date;
		*pre=que.top();
		que.pop();
		if(que.empty())
		{
			top=pre;
			number=top->time;
			return;
		}
		date *bac=new date;
		*bac=que.top();
		que.pop();
		temptop->time=pre->time+bac->time;
		if(pre->time<=bac->time)
		{
			temptop->left=pre;
			temptop->right=bac;
		}
		else 
		{
			temptop->right=pre;
			temptop->left=bac;
		}
		que.push(*temptop);
	}
	top=temptop;
	number=top->time;
}
void denode::sort(date*top)
{
	for(int m=0;m<60;m++)
	{
		if(top[m].time)
		{
			que.push(top[m]);
			sum++;
		}
	}
}
void denode::debug(date*top)
{
	if(!top)
		return;
	cout<<top->ch;
	debug(top->left);
	debug(top->right);
}
void denode::decompress()
{
	fstream write;
	write.open("copy.txt");
	unsigned char ch;
	int transition;
	//infilete>>ch;
	ch=infilete.get();//读取回车
	infilete >> noskipws;
	string tran;
	date*temhead=top;
	int topm=-1;
	int end=0;
	while(end!=number)
	{
		unsigned char inch;
		ch=infilete.get();
		if(ch=='1'||ch=='0')
		{
			inch=infilete.get();
			if(inch=='1'||inch=='0')
				break;
			else
				infilete.seekg(-1,ios::cur);
		}
		int i=ch;
		for(int j=7;j>=0;j--)//把ch改为二进制
        {
            if(i&(1<<j))
            tran.push_back('1');
            else
            tran.push_back('0');
        }
        int lenth=tran.length();
        for(int m=0;m<lenth-1;m++)
        {
        	if(tran[0]=='1')
        	{
        		temhead=temhead->right;
        		tran = tran.substr(1,tran.length());
        	}
        	else if(tran[0]=='0')
        	{
        		temhead=temhead->left;
        		tran = tran.substr(1,tran.length());
        	}
        	if(!temhead->left&&!temhead->right)
        	{
        		end++;
        		write<<temhead->ch;
        		temhead=top;
        		break;
        	}
        }
	}
	if(end!=number)//处理尾字符
	{
		infilete.seekg(-2,ios::cur);
		while(!infilete.eof())
		{
			ch=infilete.get();
			if(ch==255)
				break;
			tran.push_back(ch);
		}
		while(tran.length()!=1)
		{
			if(tran[0]=='1')
			{
				temhead=temhead->right;
				tran=tran.substr(1,tran.length());
			}
			else if(tran[0]=='0')
			{
				temhead=temhead->left;
				tran=tran.substr(1,tran.length());
			}
			if(!temhead->left&&!temhead->right)
        	{
        		write<<temhead->ch;
        		temhead=top;
        	}
		}
		if(tran[0]=='1')
		temhead=temhead->right;
		else if(tran[0]=='0')
		temhead=temhead->left;
        write<<temhead->ch;
	}
}
void node::inputmap()
{
	fstream ifile;
	ifile.open("code.txt");
	for(int m=0;m<60;m++)
	{
		int n=0;
		if(maptop[m][n]!='*')
		{
			ifile<<storech[m].ch;
		while(maptop[m][n]!='*')
		{
			ifile<<maptop[m][n];
			n++;
		}
		ifile<<endl;
		}
	}
	ifile.close();
}
void node::max_small()
{ 
	fstream copy;
	copy.open("out.cxq");
	fstream pre;
	pre.open("test.txt");
	copy.seekg(0,ios::end); 
	long size1 = copy.tellg(); 
	pre.seekg(0,ios::end);
	long size2 = pre.tellg();
	double temp=1.0*size1/size2;
	copy.close();
	pre.close();
	cout<<"压缩率:"<<temp;
}
