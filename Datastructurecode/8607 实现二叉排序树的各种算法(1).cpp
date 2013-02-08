#include "stdio.h"
#include "malloc.h"
#define OK  1
#define ERROR  0
#define STACK_INIT_SIZE 100 // �洢�ռ��ʼ������
#define STACKINCREMENT 10   // �洢�ռ��������
#define MAXQSIZE 100        // �����г���(����ѭ�����У������г���Ҫ��1)

typedef int  Status;
typedef int  ElemType;

typedef struct BiTNode     //���ڵ�ṹ
{
  ElemType data;
  struct BiTNode *lchild,*rchild;//���Һ���ָ��
} BiTNode,*BiTree;

struct SqStack                  //ջ�ڵ�ṹ
{
     BiTree *base; // ��ջ����֮ǰ������֮��base��ֵΪNULL
     BiTree *top;  // ջ��ָ��
     int stacksize;   // ��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ
}; // ˳��ջ

typedef struct
{
   BiTree *base; // ��ʼ���Ķ�̬����洢�ռ�
   int front;       // ͷָ��,�����в���,ָ�����ͷԪ��
   int rear;        // βָ��,�����в���,ָ�����βԪ�ص���һ��λ��
 }SqQueue;


//================================ջ���ֵĺ���============================

Status InitStack(SqStack &S)
{
// ����һ����ջS����ջԤ�����СΪSTACK_INIT_SIZE
    S.base=(BiTree*)malloc(STACK_INIT_SIZE*sizeof(BiTree));
    if(!S.base) return ERROR;
    S.top=S.base;
    S.stacksize=STACK_INIT_SIZE;
    return OK;
}

Status Push(SqStack &S,BiTree e)
{
// ��ջS�в���Ԫ��eΪ�µ�ջ��Ԫ��
    if((S.top-S.base)>=S.stacksize)
    {
        S.base=(BiTree*)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(BiTree));
        if(!S.base) return ERROR;
            S.top=S.base+S.stacksize;
        S.stacksize+=STACKINCREMENT;
    }
    *S.top++=e;
    return OK;

}

Status Pop(SqStack &S,BiTree &e)
{
// ��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR
    if(S.top==S.base) return ERROR;
    e=*--S.top;
    return OK;
}

Status StackEmpty(SqStack &S)
{
// ��ջ�գ�������OK�����򷵻�ERROR
    if(S.top==S.base) return OK;
    return ERROR;
}

//================================ѭ�����в��ֵĺ���=========================

Status InitQueue(SqQueue &Q)
{
// ����һ���ն���Q���ö���Ԥ�����СΪMAXQSIZE
    Q.base=(BiTree*)malloc(MAXQSIZE*sizeof(BiTree));
    if(!Q.base) return ERROR;
    Q.front=Q.rear=0;
    return OK;
}

Status EnQueue(SqQueue &Q,BiTree e)
{
// ����Ԫ��eΪQ���µĶ�βԪ��
    if((Q.rear+1)%MAXQSIZE==Q.front) return ERROR;
    Q.base[Q.rear]=e;
    Q.rear=(Q.rear+1)%MAXQSIZE;
    return OK;
}

Status DeQueue(SqQueue &Q, BiTree &e)
{
// �����в���, ��ɾ��Q�Ķ�ͷԪ��, ��e������ֵ, ������OK; ���򷵻�ERROR
    if(Q.front==Q.rear) return ERROR;
    e=Q.base[Q.front];
    Q.front=(Q.front+1)%MAXQSIZE;
    return OK;
}

Status GetHead(SqQueue Q, BiTree &e)
{
// �����в��գ�����e���ض�ͷԪ�أ�������OK�����򷵻�ERROR
// �벹ȫ����
    if(Q.front==Q.rear) return ERROR;
    e=Q.base[Q.front];
    return OK;
}

Status QueueEmpty(SqQueue &Q)
{
// �����п�, ����OK; ���򷵻�ERROR
    if(Q.front==Q.rear) return OK;
    return ERROR;
}
//================================�����ֵĺ���============================
Status CreateBiTree(BiTree &T)
{
    ElemType ch;
    BiTree Uf,U,V;
    int n,i=0;
    scanf("%d",&n);
    if (n==0) {T = NULL;return OK;}
    else
    {
        scanf("%d",&ch);
        if (!(T = (BiTNode *)malloc(sizeof(BiTNode)))) return ERROR;
        T->data=ch;T->lchild=NULL;T->rchild=NULL;
    }
    for(;n>1;n--)
    {
        U=T;
        scanf("%d",&ch);
        if (!(V=(BiTNode *)malloc(sizeof(BiTNode)))) return ERROR;
        V->data=ch;V->lchild=NULL;V->rchild=NULL;
        while(U!=NULL)
        {
            if(V->data<U->data)
                {Uf=U;U=U->lchild;}
            else
                {Uf=U;U=U->rchild;}
        }
        if(V->data<Uf->data)
            Uf->lchild=V;
        else
            Uf->rchild=V;
    }
    return OK;
} // CreateBiTree


Status PrintElement( ElemType e )
{  // ���Ԫ��e��ֵ
    printf("%d ", e );
    return OK;
}// PrintElement


Status PreOrderTraverse(BiTree T)
{
   if(T)
   {
       if(PrintElement(T->data))
          if(PreOrderTraverse(T->lchild))
            if(PreOrderTraverse(T->rchild))
                return OK;
       return ERROR;
   }else return OK;
} // PreOrderTraverse

Status InOrderTraverse( BiTree T )
{
   if(T)
   {
       if(InOrderTraverse(T->lchild))
          if(PrintElement(T->data))
            if(InOrderTraverse(T->rchild))
                return OK;
       return ERROR;
   }else return OK;

} // InOrderTraverse

Status PostOrderTraverse( BiTree T)
{
   if(T)
   {
        if(PostOrderTraverse(T->lchild))
          if(PostOrderTraverse(T->rchild))
            if(PrintElement(T->data))
       return OK;
       return ERROR;
   }else return OK;

} // PostOrderTraverse

Status judge(BiTree T,ElemType a)
{
    //�жϺ���
    if(T)
    {
        if(a==T->data||judge(T->lchild,a)||judge(T->rchild,a))
            return OK;
        else
            return ERROR;
   }else return ERROR;
}

Status Insert(BiTree &T,ElemType ins)
{
    //���뺯��
    BiTNode *Uf,*U,*V;
    U=T;
    if (!(V=(BiTNode *)malloc(sizeof(BiTNode)))) return ERROR;
        V->data=ins;V->lchild=NULL;V->rchild=NULL;
    while(U!=NULL)
    {
        if(V->data<U->data)
            {Uf=U;U=U->lchild;}
        else
            {Uf=U;U=U->rchild;}
    }
    if(V->data<Uf->data)
        Uf->lchild=V;
    else
        Uf->rchild=V;
    return OK;
}

Status NRInOrderTraverse(BiTree T)
{
    BiTree p;
    SqStack S;
    InitStack(S);
    p=T;
    while(p||!StackEmpty(S))
    {
        if(p){Push(S,p);p=p->lchild;}
        else
        {
            Pop(S,p);
            PrintElement(p->data);
            p=p->rchild;
        }
    }
    return OK;

} // NRInOrderTraverse

Status LevelOrderTraverse( BiTree T)
{
    BiTree p;
    SqQueue Q;
    InitQueue(Q);
    p=T;
    EnQueue(Q,p);
    while(p->lchild||p->rchild||!QueueEmpty(Q))
    {
        if(p->lchild) EnQueue(Q,p->lchild);
        if(p->rchild) EnQueue(Q,p->rchild);
        DeQueue(Q,p);
        PrintElement(p->data);
        GetHead(Q,p);
    }
}



int main()   //������
{
    BiTree T;
    ElemType a,b,ins;
    if(!CreateBiTree(T))return ERROR;
    scanf("%d",&a);
    scanf("%d",&b);
    scanf("%d",&ins);
    PreOrderTraverse(T); //ǰ�к������
    printf("\n");
    InOrderTraverse(T);
    printf("\n");
    PostOrderTraverse(T);
    printf("\n");
    printf("%d\n%d\n",judge(T,a),judge(T,b));
    Insert(T,ins);
    PreOrderTraverse(T); //�����ǰ�к������
    printf("\n");
    InOrderTraverse(T);
    printf("\n");
    PostOrderTraverse(T);
    printf("\n");
    NRInOrderTraverse(T);
    printf("\n");
    LevelOrderTraverse(T);
    return OK;
}//main
