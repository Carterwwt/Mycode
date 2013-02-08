#include"stdio.h"
#include"stdlib.h"
#include"math.h"
#include"string.h"
#include"malloc.h"

#define TRUE 1
#define FALSE 0
#define OK  1
#define ERROR  0
#define INFEASIBLE -1

#define MAXQSIZE 100
#define Elemtype int

typedef int  Status;
typedef int  ElemType;

typedef struct BiTNode{//���Ľṹ
    int  data;
    struct BiTNode *lchild,*rchild;//���Һ���ָ��
} BiTNode,*BiTree;

Status CreateBiTree(BiTree &T,int e){ //������
    if(!(T = (BiTNode *)malloc(sizeof(BiTNode)))) return ERROR;
    T->data=e;
    T->lchild=NULL;
    T->rchild=NULL;
    return OK;
}

Status PrintElement( ElemType e ) {//���Ԫ��e��ֵ
    printf("%d ", e );
    return OK;
}// PrintElement

Status PreOrderTraverse( BiTree T, Status(*PrintElement)(ElemType) ){
   // ǰ�����������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit
    if(T==NULL)  return 0;
	Visit(T->data );
	PreOrderTraverse(T->lchild,Visit);
	PreOrderTraverse(T->rchild,Visit);
	return OK;
} // PreOrderTraverse

Status InOrderTraverse( BiTree T, Status(*Visit)(ElemType) ){
     // �������������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit��
    if(T==NULL)  return 0;
	InOrderTraverse(T->lchild,Visit);
	Visit(T->data);
	InOrderTraverse(T->rchild,Visit);
	return OK;
} // InOrderTraverse

Status PostOrderTraverse( BiTree T, Status(*Visit)(ElemType) ) {
     // �������������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit��
    if(T==NULL)  return 0;
	PostOrderTraverse(T->lchild,Visit);
	PostOrderTraverse(T->rchild,Visit);
	Visit(T->data);
	return OK;
} // PostOrderTraverse

Status LevelOrderTraverse(BiTree T)  //��α���
{ //�������Ĳ�α���
    BiTree Queue[MAXQSIZE],p;
    int front=0,rear=0;
    if(T)
    {
        Queue[rear++]=T;
        while(front!=rear)
        {
            p=Queue[front++];
            printf("%d ",p->data);
            if(p->lchild!=NULL) Queue[rear++]=p->lchild;
            if(p->rchild!=NULL) Queue[rear++]=p->rchild;
        }
    }
    return OK;
} // LevelOrderTraverse

Status SearchBST(BiTree T,int key,BiTree f,BiTree &p){
    if (!T)
    {
        p = f;
        return FALSE;
    }
    else
        if(key==T->data)
        {
            p = T;
            return TRUE;
        }
        else
            if(key < T->data)  return SearchBST(T->lchild,key,T,p);
            else  return SearchBST(T->rchild,key,T,p);
}

Status InsertBST(BiTree &T, Elemtype e)
{
	BiTNode *p,*s;
	if(!SearchBST(T,e,NULL,p))
	{
		s = (BiTNode *)malloc(sizeof(BiTNode));//�����½��
		s->data = e;
		s->lchild = NULL;
		s->rchild = NULL;
		if(!p)  T = s;
            else
                if(e < p->data) p->lchild = s;
                    else p->rchild = s;
		return TRUE;
	}
	else return FALSE;
}

int main()
{
    BiTNode *T;
    int n,i,key,key1,m,in;
    BiTree p,f;
    scanf("%d",&n);
    int *a;
    a=(int*)malloc(sizeof(int)*n);
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);
    CreateBiTree(T,a[0]);
    for(i=1;i<n;i++)
    {
        SearchBST(T,a[i],f,p);
        InsertBST(T,a[i]);
    }
    PreOrderTraverse(T,PrintElement);
    printf("\n");
    InOrderTraverse(T,PrintElement);
    printf("\n");
    PostOrderTraverse(T,PrintElement);
    printf("\n");
    scanf("%d",&key); m=SearchBST(T,key,f,p); printf("%d\n",m);//��Ѱ���
    scanf("%d",&key1);m=SearchBST(T,key1,f,p);printf("%d\n",m);
    scanf("%d",&in);
    SearchBST(T,in,f,p);
    InsertBST(T,in);//������
    PreOrderTraverse(T,PrintElement);
    printf("\n");
    InOrderTraverse(T,PrintElement);
    printf("\n");
    PostOrderTraverse(T,PrintElement);
    printf("\n");
    InOrderTraverse(T,PrintElement);
    printf("\n");
    LevelOrderTraverse(T);
    return 0;
}
