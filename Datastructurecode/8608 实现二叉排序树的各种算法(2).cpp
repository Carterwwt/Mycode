#include "stdio.h"
#include "malloc.h"
#define OK  1
#define ERROR  0
#define STACK_INIT_SIZE 100 // ջ�洢�ռ��ʼ������
#define STACKINCREMENT 10   // ջ�洢�ռ��������
#define MAXQSIZE 100        // ������󳤶�

typedef int  Status;        //��������
typedef int  ElemType;      //���Ԫ������

typedef struct BiTNode      //���ڵ�ṹ
{
  ElemType data;
  struct BiTNode *lchild,*rchild;
} BiTNode,*BiTree;

struct SqStack              //ջ�ڵ�ṹ
{
     BiTree *base;          //���Ԫ��������BiTree�����Դ洢������ָ��
     BiTree *top;
     int stacksize;
};

typedef struct              //ջ�ڵ�ṹ
{
   BiTree *base;            //���Ԫ��������BiTree�����Դ洢������ָ��
   int front;
   int rear;
 }SqQueue;


//================================ջ�Ļ�������============================

Status InitStack(SqStack &S)             // ����һ����ջS����ջԤ�����СΪSTACK_INIT_SIZE
{
    S.base=(BiTree*)malloc(STACK_INIT_SIZE*sizeof(BiTree));
    if(!S.base) return ERROR;
    S.top=S.base;
    S.stacksize=STACK_INIT_SIZE;
    return OK;
}

Status Push(SqStack &S,BiTree e)         // ��ջS�в���Ԫ��eΪ�µ�ջ��Ԫ��
{
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

Status Pop(SqStack &S,BiTree &e)         // ��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR
{
    if(S.top==S.base) return ERROR;
    e=*--S.top;
    return OK;
}

Status StackEmpty(SqStack &S)            // ��ջ�գ�������OK�����򷵻�ERROR
{
    if(S.top==S.base) return OK;
    return ERROR;
}

//================================ѭ�����л�������=========================

Status InitQueue(SqQueue &Q)             // ����һ���ն���Q���ö���Ԥ�����СΪMAXQSIZE
{
    Q.base=(BiTree*)malloc(MAXQSIZE*sizeof(BiTree));
    if(!Q.base) return ERROR;
    Q.front=Q.rear=0;
    return OK;
}

Status EnQueue(SqQueue &Q,BiTree e)         // ����Ԫ��eΪQ���µĶ�βԪ��
{

    if((Q.rear+1)%MAXQSIZE==Q.front) return ERROR;
    Q.base[Q.rear]=e;
    Q.rear=(Q.rear+1)%MAXQSIZE;
    return OK;
}

Status DeQueue(SqQueue &Q, BiTree &e)       // �����в���, ��ɾ��Q�Ķ�ͷԪ��, ��e������ֵ, ������OK; ���򷵻�ERROR
{
    if(Q.front==Q.rear) return ERROR;
    e=Q.base[Q.front];
    Q.front=(Q.front+1)%MAXQSIZE;
    return OK;
}

Status GetHead(SqQueue Q, BiTree &e)         // �����в��գ�����e���ض�ͷԪ�أ�������OK�����򷵻�ERROR
{
    if(Q.front==Q.rear) return ERROR;
    e=Q.base[Q.front];
    return OK;
}

Status QueueEmpty(SqQueue &Q)                // �����п�, ����OK; ���򷵻�ERROR
{
    if(Q.front==Q.rear) return OK;
    return ERROR;
}

//================================���Ļ�������============================

Status Insert(BiTree &T,ElemType ins);      //���뺯������

Status CreateBiTree(BiTree &T)               //����
{
    ElemType ch;
    int n;
    scanf("%d",&n);
    if (n==0) {T = NULL;return OK;}       //�������Ϊ0������Ϊ�����������Ƚ������ĸ��ڵ�
    else
    {
        scanf("%d",&ch);
        if (!(T = (BiTNode *)malloc(sizeof(BiTNode)))) return ERROR;
        T->data=ch;T->lchild=NULL;T->rchild=NULL;                    //����ʼ��
    }
    for(;n>1;n--)                         //����ʣ���n-1�����
    {
        scanf("%d",&ch);
        Insert(T,ch);
    }
    return OK;
}

Status PrintElement( ElemType e )           // ���Ԫ��e��ֵ
{
    printf("%d ", e );
    return OK;
}

Status PreOrderTraverse(BiTree T)           //�ݹ�ķ������������������
{
   if(T)
   {
       if(PrintElement(T->data))
          if(PreOrderTraverse(T->lchild))
            if(PreOrderTraverse(T->rchild))
                return OK;
       return ERROR;
   }else return OK;
}

Status InOrderTraverse( BiTree T )          //�ݹ�ķ������������������
{
   if(T)
   {
       if(InOrderTraverse(T->lchild))
          if(PrintElement(T->data))
            if(InOrderTraverse(T->rchild))
                return OK;
       return ERROR;
   }else return OK;

}

Status PostOrderTraverse( BiTree T)         //�ݹ�ķ����������ĺ�������
{
   if(T)
   {
        if(PostOrderTraverse(T->lchild))
          if(PostOrderTraverse(T->rchild))
            if(PrintElement(T->data))
       return OK;
       return ERROR;
   }else return OK;

}

Status judge(BiTree T,ElemType a)           //���������Ƿ���Ԫ��a
{
    if(T)
    {
        if(a==T->data||judge(T->lchild,a)||judge(T->rchild,a))   //�õݹ�ķ������������н����a���бȽ�ֻҪ��һ����ȣ��򷵻�1
            return OK;
        else                                                      //���򷵻ؼ�
            return ERROR;
   }else return ERROR;                      //������Ϊ�գ����ؼ�
}

Status Insert(BiTree &T,ElemType ins)       //�����в�����ins
{
    BiTNode *Uf,*U,*V;
    U=T;
    if (!(V=(BiTNode *)malloc(sizeof(BiTNode)))) return ERROR;      //�����½�㲢��ʼ��
        V->data=ins;V->lchild=NULL;V->rchild=NULL;
    while(U!=NULL)          //������U��Ϊ�� �������ж�U������½��ֵ�Ĵ�С�����½�������U�����Һ��ӽ��бȽ�
    {
        if(V->data<U->data)
            {Uf=U;U=U->lchild;}
        else
            {Uf=U;U=U->rchild;}
    }
    if(V->data<Uf->data)    //��U������Ϊ�ղ����½ڵ��UС������½ڵ������ΪU������
        Uf->lchild=V;
    else                    //��U���Һ���Ϊ�ղ����½ڵ��U������½ڵ������ΪU���Һ���
        Uf->rchild=V;
    return OK;
}

Status NRInOrderTraverse(BiTree T)      //�ǵݹ����������
{
    BiTree p;
    SqStack S;
    InitStack(S);                       //��������ջ
    p=T;
    while(p||!StackEmpty(S))
    {
        if(p){Push(S,p);p=p->lchild;}   //��p��Ϊ������ջ����pָ��p��������
        else
        {
            Pop(S,p);                  //��pΪ���򵯳�p�ĸ��׽�㲢�������ʱpָ��p�Ѿ���ջ�ĸ��׽��
            PrintElement(p->data);
            p=p->rchild;                //��pָ��p��������������һ�ֵ��ж�
        }
    }
    return OK;

}

Status LevelOrderTraverse( BiTree T)    //��α���
{
    BiTree p;
    SqQueue Q;
    InitQueue(Q);                   //������α����ĸ�������
    p=T;
    EnQueue(Q,p);                  //����ͷ������
    while(p->lchild||p->rchild||!QueueEmpty(Q))
    {
        if(p->lchild) EnQueue(Q,p->lchild);     //��p����������Ϊ�������
        if(p->rchild) EnQueue(Q,p->rchild);     //��p����������Ϊ�������
        DeQueue(Q,p);                           //p���Ӳ����p����ֵ
        PrintElement(p->data);
        GetHead(Q,p);                           //��pָ����е�ͷ��������һ�ֵ��ж�
    }
}

Status TurnC( BiTree T)                 //������T����������
{
    BiTree rc;                          //rcΪ�м���������Խ�������������ָ�뷽��
    rc=T->rchild;
    T->rchild=T->lchild;
    T->lchild=rc;
    return OK;
}

Status TurnT( BiTree T)               //ת����
{
   if(T)
   {
       if(TurnC(T))              //ת����T����������
          if(TurnT(T->lchild))    //�õݹ�ķ�ʽ��������������ת������������������
            if(TurnT(T->rchild))
                return OK;
       return ERROR;
   }else return OK;
}

Status leaf(BiTree T,int &l)                          //Ҷ�ӽ��ͳ��
{
    if(T)
    {
        if(T->lchild==NULL&&T->rchild==NULL) l++;     //�����T����������Ϊ�գ����ж�ΪҶ�ӽ�㣬Ҷ�ӽ����l��һ
        leaf(T->lchild,l);                            //�ݱ�����������Ҷ�ӽ����������l������ֵ
        leaf(T->rchild,l);
    }else return ERROR;
}

Status deep(BiTree T,int &d,int d2)                   //������ȼ���
{
    if(T)
    {
        d2++;                       //��d2��Ǹ�������ȣ�������d����d2�����ֵ����dΪ������ȡ�
        if(d2>d) d=d2;
        deep(T->lchild,d,d2);       //�ݹ����������������
        deep(T->rchild,d,d2);
    }else return ERROR;             //��TΪ�գ�ֱ�ӷ��ظ��׽��
}

int main()   //������
{
    BiTree T;
    ElemType a,b,ins;
    int l=0,d=0,d2=0;
    if(!CreateBiTree(T))return ERROR;               //���������ʧ��ֱ�ӽ�������
    scanf("%d",&a);          //��������ҽ��
    scanf("%d",&b);
    scanf("%d",&ins);        //�����������
    PreOrderTraverse(T);     //ǰ�к������
    printf("\n");
    InOrderTraverse(T);
    printf("\n");
    PostOrderTraverse(T);
    printf("\n");
    printf("%d\n%d\n",judge(T,a),judge(T,b));   //���Ҳ�������
    Insert(T,ins);          //�����½��
    PreOrderTraverse(T);    //�����ǰ�к������
    printf("\n");
    InOrderTraverse(T);
    printf("\n");
    PostOrderTraverse(T);
    printf("\n");
    NRInOrderTraverse(T);   //�ǵݹ��������
    printf("\n");
    LevelOrderTraverse(T);  //��α���
    printf("\n");
    TurnT(T);               // ��һ��ת��
    PreOrderTraverse(T);    //ת����ǰ�к������
    printf("\n");
    InOrderTraverse(T);
    printf("\n");
    PostOrderTraverse(T);
    printf("\n");
    TurnT(T);               //�ڶ���ת��
    PreOrderTraverse(T);    //ת����ǰ�к������
    printf("\n");
    InOrderTraverse(T);
    printf("\n");
    PostOrderTraverse(T);
    deep(T,d,d2);            //�����d������d2Ϊ��ʱ����
    printf("\n%d",d);
    leaf(T,l);               //��Ҷ�ӽ����l
    printf("\n%d",l);
    return OK;
}
