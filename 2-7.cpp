#include<malloc.h>
#include<stdio.h>
#define OK 1
#define ERROR 0
typedef int Status; // Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK��
typedef int QElemType;
#define MAXQSIZE 100 // �����г���(����ѭ�����У������г���Ҫ��1)

typedef struct
{
    QElemType *base; // ��ʼ���Ķ�̬����洢�ռ�
    int front; // ͷָ��,�����в���,ָ�����ͷԪ��
    int rear; // βָ��,�����в���,ָ�����βԪ�ص���һ��λ��
 }SqQueue;

Status InitQueue(SqQueue &Q)
{
// ����һ���ն���Q���ö���Ԥ�����СΪMAXQSIZE
// �벹ȫ����
    Q.base=(QElemType*)malloc(MAXQSIZE*sizeof(QElemType));
    if(!Q.base) return ERROR;
    Q.front=Q.rear=0;
    return OK;
}

Status EnQueue(SqQueue &Q,QElemType e)
{
// ����Ԫ��eΪQ���µĶ�βԪ��
// �벹ȫ����
    if((Q.rear+1)%MAXQSIZE==Q.front) return ERROR;
    Q.base[Q.rear]=e;
    Q.rear=(Q.rear+1)%MAXQSIZE;
    return OK;
}

Status DeQueue(SqQueue &Q, QElemType &e)
{
// �����в���, ��ɾ��Q�Ķ�ͷԪ��, ��e������ֵ, ������OK; ���򷵻�ERROR
// �벹ȫ����
    if(Q.rear==Q.front) return ERROR;
    e=Q.base[Q.front];
    Q.front=(Q.front+1)%MAXQSIZE;
    return OK;
}

Status GetHead(SqQueue Q, QElemType &e)
{
// �����в��գ�����e���ض�ͷԪ�أ�������OK�����򷵻�ERROR
// �벹ȫ����
    if(Q.rear==Q.front) return ERROR;
    e=Q.base[Q.front];
    return OK;
}

int QueueLength(SqQueue Q)
{
// ����Q��Ԫ�ظ���
    return (Q.rear-Q.front+MAXQSIZE)%MAXQSIZE;
}

Status QueueTraverse(SqQueue Q)
{
// �����в��գ���Ӷ�ͷ����β���������������Ԫ�أ�������OK�����򷵻�ERROR.
	int i;
	i=Q.front;
	if(Q.rear==Q.front)printf("The Queue is Empty!");  //�����
	else{
		printf("The Queue is: ");
		while(i!=Q.rear)     //�����
		{
			printf("%d ",Q.base[i]);   //�����
			i =(i+1)%MAXQSIZE;   //�����
		}
	}
	printf("\n");
	return OK;
}

int main()
{
    int i,a,p,q,e,r;
    SqQueue S;
    float t,s=0;
    InitQueue(S);
    scanf("%d",&a);
    getchar();
    for(i=1;i<=a*2;i++)
    {
        scanf ("%d",&e);getchar();
        EnQueue(S,e);
    }
    p=S.base[S.front];
    while (S.rear>S.front)
    {
        q=p+S.base[S.front+1];
        DeQueue(S,e);
        DeQueue(S,e);
        if (S.front==S.rear) break;
        r=q-S.base[S.front];
        if(r<0)
        {
            r=0;
            p=S.base[S.front];
            continue;
        }
        s=s+r;
        p=q;
    }
    t=s/a;
    printf("%.2f\n",t);
    return OK;
}
