#include <stdio.h>
#include <math.h>
int bj(char temp,char pre);
void input(char type,int topnum,char *ch,int*num);
int main(void)
{
    int k,flag=0;
    int op[20];
    int num[20]={0},n,h;//n:opÕ»µÄ¶¥¸Ç
    int kuh[20];
    int dg=-1;//kuhµÄ¶¥¸Ç
    char ch[20],temp;
    int topnum,topch;
    topch=topnum=-1;
    while(temp=getchar())
    {
        n=-1;
        while(temp>='0'&&temp<='9')
        {
            flag=1;
            op[++n]=temp-'0';
            temp=getchar();
        }
        if(flag)
        {
            topnum++;
            num[topnum]=0;
            flag=0;
        }
        for(k=n;k>=0;k--)
        {
            num[topnum]+=op[k]*pow(10,n-k);
        }
        if(!(temp>='0'&&temp<='9'))
        {
            if(temp=='('||temp==')')
            {
                if(temp=='(')
                {
                    ch[++topch]=temp;
                    kuh[++dg]=topch;
                }
                else
                {
                    while(topch!=kuh[dg])
                    {
                        input(ch[topch],topnum,ch,num);
                        topch--;
                    }
                    topch--;
                    topnum--;
                    dg--;
                }
            }
            else if(temp!='\n'&&topch>=0&&bj(temp,ch[topch]))
            {
                input(ch[topch],topnum,ch,num);
                topnum--;
                ch[topch]=temp;
            }
            else if(temp=='\n')
            {
                while(topch!=-1)
                {
                    input(ch[topch],topnum,ch,num);
                    topnum--;
                    topch--;
                }
                break;
            }
            else
            {
                ch[++topch]=temp;
            }
        }
    }
    printf("%d",num[0]);
    return 0;
}
int bj(char temp,char pre)
{
    if(pre=='('||pre==')')
        return 0;
    if(temp=='+'||temp=='-')
    {
        return 1;
    }
    if(temp=='*'||temp=='/')
    {
        if(pre=='*'||pre=='/')
            return 1;
        else
            return 0;
    }
}
void input(char type,int topnum,char *ch,int*num)
{
    switch(type)
    {
        case '+':num[topnum-1]=num[topnum-1]+num[topnum];
                 break;
        case '-':num[topnum-1]=num[topnum-1]-num[topnum];
                 break;
        case '*':num[topnum-1]=num[topnum-1]*num[topnum];
                 break;
        case '/':num[topnum-1]=num[topnum-1]/num[topnum];
                 break;
        default:break;
    }
}

