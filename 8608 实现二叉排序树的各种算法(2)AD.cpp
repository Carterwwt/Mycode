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
#define STACK_INIT_SIZE 100 // �洢�ռ��ʼ������
#define STACKINCREMENT 10 // �洢�ռ��������

typedef int  ElemType;
typedef int  Status;//Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK��

typedef struct BiTNode{//���Ľṹ
    ElemType  data;
    struct BiTNode *lchild,*rchild;//���Һ���ָ��
} BiTNode,*BiTree;

typedef BiTree SElemType; // ����ջԪ������

typedef struct{
    SElemType *base; // ��ջ����֮ǰ������֮��base��ֵΪNULL
    SElemType *top; // ջ��ָ��
    int stacksize; // ��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ
}SqStack; // ˳��ջ

Status InitStack(SqStack &S){
// ����һ����ջS����ջԤ�����СΪSTACK_INIT_SIZE
    S.base=(SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if(!S.base) return(ERROR);
    S.top = S.base;
    S.stacksize=STACK_INIT_SIZE;
    return OK;
}

Status Push(SqStack &S,BiTree e){
// ��ջS�в���Ԫ��eΪ�µ�ջ��Ԫ��
    if(S.top-S.base>=S.stacksize)
    {
        S.base=(SElemType*)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(SElemType));
        if(!S.base) return(ERROR);
        S.top=S.base+S.stacksize;
        S.stacksize+=STACKINCREMENT;
    }
    *S.top++=e;
    return OK;
}

Status StackEmpty(SqStack &S){
//  �ж�ջ��
    if(S.top==S.base)
        return TRUE;
    else return FALSE;
}

Status Pop(SqStack &S,SElemType &e){
// ��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR
    if(StackEmpty(S)) return ERROR;
    e=*--S.top;
    return OK;
}

Status SearchBST(BiTree T,int key,BiTree f,BiTree &p){
    //�ڸ�ָ��T��ָ�Ķ������еݹ�ز������С����key������Ԫ�أ������ҳɹ���
    //��ָ��pָ�������Ԫ�ؽ�㣬������TRUE������ָ��pָ�����·���Ϸ��ʵ�
    //���һ����㲢����FALSE��ָ��fָ��T��˫�ף����ʼ����ֵΪNULL
    if (!T)  {p=f;return FALSE;}//���Ҳ��ɹ�
    else if (key==T->data) {p=T;return TRUE;}//���ҳɹ�
    else if (key<T->data)   return SearchBST(T->lchild,key,T,p);//���������м�������
    else  return SearchBST(T->rchild,key,T,p);//���������м�������
}

Status InsertBST(BiTree &T,ElemType e){
    //������������T�в����ڴ�С�ĵ���e������Ԫ��ʱ������e��������TRUE
    //���򷵻�FALSE
    BiTNode *p,*s;
	if(!SearchBST(T,e,NULL,p)){     //���Ҳ��ɹ�
		s = (BiTNode *)malloc(sizeof(BiTNode));//�����½��
		s->data = e;s->lchild = NULL;s->rchild = NULL;
		if(!p) T = s;               //������*sΪ�µĸ����
		else if(e < p->data) p->lchild = s;//������*sΪ����
		else p->rchild = s;//������*sΪ�ҽ��
		return TRUE;
	}
	else return FALSE;//�������йؼ�����ͬ�Ľ�㣬���ٲ���
}

Status CreateBiTree(BiTree &T,int e) {//������
    if (!(T = (BiTNode *)malloc(sizeof(BiTNode)))) return ERROR;
    T->data=e;
    T->lchild=NULL;
    T->rchild=NULL;
    return OK;
}

Status PrintElement( ElemType e ) {//���Ԫ��e��ֵ
    printf("%d ", e );
    return OK;
}// PrintElement

Status PreOrderTraverse( BiTree T, Status(*Visit)(ElemType) ){
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

Status LevelOrderTraverse(BiTree T){
    //�������Ĳ�α���
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

SqStack S;

Status Dif_InOrder( BiTree T){
    //���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú���
    //�������������T�ķǵݹ��㷨����ÿ������Ԫ�ص��ú���Visit
    BiTree p;
    SqStack S;
    InitStack(S);
    p = T;
    while(p||!StackEmpty(S)){
        if(p) {Push(S,p);p = p->lchild;}//��ָ���ջ������������
        else{       //��ָ����ջ�����ʸ���㣬����������
            Pop(S,p);
            printf("%d ",p->data);
            p=p->rchild;
        }//else
    }//While
    return OK;
}

Status PreOrderd(BiTree T){
    //�ݹ�����,�������
    if(T)
    {
        PreOrderd(T->lchild);
        PreOrderd(T->rchild);
    }
    return OK;
}

void changeleaf(BiTree  T){
    //������������
	if(T!=NULL)
	{
        BiTree p;
        p=T->lchild;
        T->lchild=T->rchild;
        T->rchild=p;
        changeleaf(T->lchild);
        changeleaf(T->rchild);
    }
}

int deep(BiTree  T) {
    //�����������
	int deepth,ldeep,rdeep;
	if(!T) deepth=0;
	else
	{
        ldeep=deep(T->lchild);
        rdeep=deep(T->rchild);
        if(ldeep>rdeep) deepth=1+ldeep;
            else    deepth=1+rdeep;
	}
    return deepth;
}

Status leaves(BiTree T,int &m){
    //mΪҶ�ӽ����
    if(!T) return ERROR;
    {
        if(T->lchild==NULL&&T->rchild==NULL) m++;
        else {leaves(T->lchild,m);leaves(T->rchild,m);}
    }
    return OK;
}

int main()
{
    BiTNode *T;
    int n,key0,key1,leavesnum=0,in,d;
    int i,m;
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

    scanf("%d",&key0); m=SearchBST(T,key0,f,p); printf("%d\n",m);//��Ѱ���
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
    Dif_InOrder(T);
    printf("\n");
    LevelOrderTraverse(T);
	printf("\n");

    changeleaf(T);
    PreOrderTraverse(T,PrintElement);
    printf("\n");
    InOrderTraverse(T,PrintElement);
    printf("\n");
    PostOrderTraverse(T,PrintElement);
    printf("\n");

    changeleaf(T);
    PreOrderTraverse(T,PrintElement);
    printf("\n");
    InOrderTraverse(T,PrintElement);
    printf("\n");
    PostOrderTraverse(T,PrintElement);
    printf("\n");

	d=deep(T);
	printf("%d\n",d);
	leaves(T,leavesnum);
	printf("%d\n",leavesnum);
	return 0;
 }

/*Sample Input
7
40 20 60 18 50 56 90
18
35
30

Sample Output
40 20 18 60 50 56 90
18 20 40 50 56 60 90
18 20 56 50 90 60 40
1
0
40 20 18 30 60 50 56 90
18 20 30 40 50 56 60 90
18 30 20 56 50 90 60 40
18 20 30 40 50 56 60 90
40 20 60 18 30 50 90 56
40 60 90 50 56 20 30 18
90 60 56 50 40 30 20 18
90 56 50 60 30 18 20 40
40 20 18 30 60 50 56 90
18 20 30 40 50 56 60 90
18 30 20 56 50 90 60 40
4
4
*/
