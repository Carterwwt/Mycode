#include "stdio.h"
#include "malloc.h"
#define TRUE 1
#define FALSE 0
#define OK  1
#define ERROR  0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int  Status;

typedef int  ElemType;
typedef struct BiTNode{
    ElemType data;
    struct BiTNode *lchild,*rchild;//���Һ���ָ��
} BiTNode,*BiTree;

Status InsertBiTree(BiTree &T,int e) //�����½��
{
	if(T==NULL){
		T=(BiTNode *)malloc(sizeof(BiTNode));
		T->data=e;
		T->lchild=NULL;
		T->rchild=NULL;
		return 1;
	}
	if(T->data<e)
		InsertBiTree(T->rchild,e);
	else
		InsertBiTree(T->lchild,e);
	return 0;
}



Status PrintElement( ElemType e ) {  // ���Ԫ��e��ֵ
	printf("%d ", e );
	return OK;
}// PrintElement


Status PreOrderTraverse( BiTree T, Status(*Visit)(ElemType) )//ǰ�����������
 {
	if(T==NULL)  return 0;
	Visit( T->data );
	PreOrderTraverse(T->lchild,Visit);
	PreOrderTraverse(T->rchild,Visit);
	return OK;
} // PreOrderTraverse

Status InOrderTraverse( BiTree T, Status(*Visit)(ElemType) ) //�������������
{
	if(T==NULL)  return 0;
	InOrderTraverse(T->lchild,Visit);
	Visit(T->data);
	InOrderTraverse(T->rchild,Visit);
	return 1;
} // InOrderTraverse

Status PostOrderTraverse( BiTree T, Status(*Visit)(ElemType) )//�������������
 {
    if(T==NULL)  return 0;
	PostOrderTraverse(T->lchild,Visit);
	PostOrderTraverse(T->rchild,Visit);
	Visit(T->data);
	return 1;

} // PostOrderTraverse


int  TreeCount( BiTree T)//���Ľ����
{
    static int count=1;
	if(T->lchild==NULL&&T->rchild==NULL) return 1;
    else
    {
        if(T->lchild!=NULL) {count++;TreeCount(T->lchild);}
        if(T->rchild!=NULL) {count++;TreeCount(T->rchild);}
        return count;
    }
}

int main()   //������
{
	BiTree  T=NULL;
	int i,n,e;
	//���ɶ���������T
    scanf("%d",&e);
    while(1)
    {
        if(e==-1) break;
        InsertBiTree(T,e);
        scanf("%d",&e);
    }
    //ǰ���С��������������
	PreOrderTraverse(T,PrintElement);
	printf("\n");
	InOrderTraverse(T,PrintElement);
	printf("\n");
	PostOrderTraverse(T,PrintElement);
	printf("\n");

    n=TreeCount(T);
    printf("%d",n);     //���������



	return 0;//�������
 }//main
