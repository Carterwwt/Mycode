#include<malloc.h>
#include<stdio.h>
#define OK 1
#define ERROR 0
#define STACK_INIT_SIZE 100 // �洢�ռ��ʼ������
#define STACKINCREMENT 10 // �洢�ռ��������

typedef int SElemType; // ����ջԪ������
typedef int Status; // Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK��

struct SqStack
{
     SElemType *base; // ��ջ����֮ǰ������֮��base��ֵΪNULL
     SElemType *top; // ջ��ָ��
     int stacksize; // ��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ
}; // ˳��ջ

Status InitStack(SqStack &S)
{
// ����һ����ջS����ջԤ�����СΪSTACK_INIT_SIZE
// �벹ȫ����
    S.base=(SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    if(!S.base) return ERROR;
    S.top=S.base;
    S.stacksize=STACK_INIT_SIZE;
    return OK;
}

Status Push(SqStack &S,SElemType e)
{
// ��ջS�в���Ԫ��eΪ�µ�ջ��Ԫ��
// �벹ȫ����
    if((S.top-S.base)>=S.stacksize)
    {
        S.base=(SElemType*)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(SElemType));
        if(!S.base) return ERROR;
            S.top=S.base+S.stacksize;
        S.stacksize+=STACKINCREMENT;
    }
    *S.top++=e;
    return OK;
}

Status Pop(SqStack &S,SElemType &e)
{
// ��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR
// �벹ȫ����
    if(S.top==S.base) return ERROR;
    e=*--S.top;
    return OK;
}

Status GetTop(SqStack S)
{
// ��ջ���գ�����e����S��ջ��Ԫ�أ�������OK�����򷵻�ERROR
// �벹ȫ����
    Status e;
    if(S.top==S.base) return ERROR;
     e=*(S.top-1);
    return e;
}

int StackLength(SqStack S)
{
// ����ջS��Ԫ�ظ���
// �벹ȫ����
    int i;
    i=S.top-S.base;
    return i;
}

Status StackTraverse(SqStack S)
{
// ��ջ����ջ���������ջ�е�ÿ��Ԫ��
	SElemType *p = (SElemType *)malloc(sizeof(SElemType));
	p =  S.top;        //�����
	if(p==S.base) printf("The Stack is Empty!"); //�����
	else
	{
		//printf("The Stack is: ");
		p--;
		while(p>=S.base)            //�����
		{
			printf("%d ",*p);
			p--;               //�����
		}
	}
	printf("\n");
	return OK;
}

Status In(SElemType &c)
{

    if(c=='+'||c=='-'||c=='*'||c=='/'||c=='('||c==')')
        return OK;
    else
        return ERROR;
}

Status Operate(SElemType a,SElemType theta,SElemType b)
{
    switch(theta)
    {
        case '+': return a+b;
        case '-': return a-b;
        case '*': return a*b;
        case '/': return a/b;
    }
}

int precede(int a,int b)
{
	if(a=='('&&b==')')
		return '=';
	if(b=='#'||b==')'||a==')')
		return '>';
	if(a=='#'||b=='('||a=='(')
		return '<';
	if(a=='*'||a=='/'||b=='+'||b=='-')
		return '>';
	else
		return '<';
}

int main()
{
     SElemType a,b,c,x,theta;
     SqStack OPTR,OPND;
     InitStack(OPTR);InitStack(OPND);
     Push(OPTR,'#');
     c=getchar();
     while(c!='='||GetTop(OPTR)!='#')
     {

         if(!In(c))
		 {
            c=c-'0';
			Push(OPND,c);
			c=getchar();
		 }
        else
            switch(precede(GetTop(OPTR),c))
            {
                case '<':Push(OPTR,c);c=getchar();break;
                case '=':Pop(OPTR,x); c=getchar();break;
                case '>':Pop(OPTR,theta);
                         Pop(OPND,b);Pop(OPND,a);
                         Push(OPND,Operate(a,theta,b));
                         break;
            }
     }
     StackTraverse(OPND);
     printf("%d",GetTop(OPND));
     return 0;
}
