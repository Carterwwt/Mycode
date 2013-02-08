#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<malloc.h>
#define OK 1
#define ERROR 0
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef int Status; // Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK��
/*�Ĵ������*/
typedef struct
{
	int stacksize;
	char *base;
	char *top;
} Stack;
/*�Ĵ��������������*/
typedef struct
{
	int stacksize;
	int *base;
	int *top;
} Stack2;
/* ----------------- ȫ�ֱ���--------------- */
Stack OPTR;/* ���������ջ*/
Stack2 OPND; /* ���������ջ */
char expr[255] = ""; /* ��ű��ʽ�� */
char *ptr = expr;

Status InitStack(Stack &S)
{
// ����һ����ջS����ջԤ�����СΪSTACK_INIT_SIZE
    S.base=(char *)malloc(STACK_INIT_SIZE * sizeof(char));
    if(!S.base) return(ERROR);
    S.top = S.base;
    S.stacksize=STACK_INIT_SIZE;
    return OK;
}

Status InitStack2(Stack2 &S)
{
// ����һ����ջS����ջԤ�����СΪSTACK_INIT_SIZE
    S.base=(int *)malloc(STACK_INIT_SIZE * sizeof(int));
    if(!S.base) return(ERROR);
    S.top = S.base;
    S.stacksize=STACK_INIT_SIZE;
    return OK;
}

Status Push(Stack &S,char e)
{
// ��ջS�в���Ԫ��eΪ�µ�ջ��Ԫ��
    if(S.top-S.base>=S.stacksize)
    {
        S.base=(char*)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(char));
        if(!S.base) return(ERROR);
        S.top=S.base+S.stacksize;
        S.stacksize+=STACKINCREMENT;
    }
    *S.top++=e;
    return OK;
}

Status Push2(Stack2 &S,int e)
{
// ��ջS�в���Ԫ��eΪ�µ�ջ��Ԫ��
    if(S.top-S.base>=S.stacksize)
    {
        S.base=(int*)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(int));
        if(!S.base) return(ERROR);
        S.top=S.base+S.stacksize;
        S.stacksize+=STACKINCREMENT;
    }
    *S.top++=e;
    return OK;
}

Status Pop(Stack &S,char &e)
{
// ��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR
    if(S.top==S.base) return ERROR;
    e=*--S.top;
    return OK;
}

Status Pop2(Stack2 &S,int &e)
{
// ��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR
    if(S.top==S.base) return ERROR;
    e=*--S.top;
    return OK;
}

char GetTop(Stack s)//��p���������ջs��ջ��Ԫ��
{
	char p=*(s.top-1);
	return p;
}
int GetTop2(Stack2 s) //��p���ز�����ջs��ջ��Ԫ��
{
	int p=*(s.top-1);
	return p;
}

Status In(char ch) //�ж��ַ��Ƿ���������������������1
{
	return(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='('||ch==')'||ch=='=');
}

/* �ж����������Ȩ����������Ȩ�ߵ� */
char Precede(char c1,char c2)
{
	int i=0,j=0;
	static char array[49]={
	'>', '>', '<', '<', '<', '>', '>',
	'>', '>', '<', '<', '<', '>', '>',
	'>', '>', '>', '>', '<', '>', '>',
	'>', '>', '>', '>', '<', '>', '>',
	'<', '<', '<', '<', '<', '#', '!',
	'>', '>', '>', '>', '!', '>', '>',
	'<', '<', '<', '<', '<', '!', '#'};
	switch(c1)
	{
        /* iΪ����array�ĺ�� */
        case '+' : i=0;break;
        case '-' : i=1;break;
        case '*' : i=2;break;
        case '/' : i=3;break;
        case '(' : i=4;break;
        case ')' : i=5;break;
        case '=' : i=6;break;
	}

	switch(c2)
	{
        /* jΪ����array���ݱ� */
        case '+' : j=0;break;
        case '-' : j=1;break;
        case '*' : j=2;break;
        case '/' : j=3;break;
        case '(' : j=4;break;
        case ')' : j=5;break;
        case '=' : j=6;break;
	}
	return (array[7*i+j]); /* ��������� */
}
/*�������� */
int Operate(int a,char theta,int b)
{
	switch(theta)
	{
        case '+' : return (a+b);
        case '-' : return (a-b);
        case '*' : return (a*b);
        case '/' : return (a/b);
	}
	return 0;
}

int num(int n)//���ز������ĳ���
{
    char p[10];
    //itoa(n,p,10);//������ת�����ַ�����
    n=strlen(p);
    return n;
}
int EvaluateExpression()//��Ҫ��������
{
    Stack OPTR;
    Stack2 OPND;
    int a,b,d,x;
    char c;
    int i;
    InitStack(OPTR); /* ��ʼ�������ջ */
	Push(OPTR,'='); /* ��=ѹ�������ջ */
	InitStack2(OPND); /* ��ʼ��������ջ */
	c=getchar();
	x=GetTop(OPTR);
	while(c!='='||GetTop(OPTR)!='=')
	{
        if(In(c))
        {
            switch(Precede(GetTop(OPTR),c))
            {
                case '<':Push(OPTR,c);c=getchar();;break;
                case '#':Pop2(OPTR,x);c=getchar();;break;
                case '>':Pop2(OPTR,theta);Pop2(OPND,b); Pop2(OPND,a);Push2(OPND,Operate(a,theta,b));
                break;
            }
        }
        else if
        {
            i=0;
            while(c>='0'&&c<='9')
            {
                z[i++]=c;
                c=getchar();
            }
            z[i]=0;
            d=atoe(z);
            Push(OPND,d);
        }
        else exit(ERROR);
	}
	return GetTop2(OPND);
}
int main( )
{

	printf("%d", EvaluateExpression());
	return 0;
}
