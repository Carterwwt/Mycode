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
		T->data=e;T->lchild=NULL;
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


BiTNode* FindNode( BiTree Ta,i) //����������������е�i����㡣
{
	//��������
}





int main()   //������
{
	BiTree  T=NULL;
	int i,n,e;
	scanf("%d",&n);//���ɶ���������Ta
	for(i=0;i<n;i++){
		scanf("%d",&e);
		InsertBiTree(T,e);
	}
    //ǰ���С��������������
	PreOrderTraverse(T,PrintElement);
	printf("\n");
	InOrderTraverse(T,PrintElement);
	printf("\n");
	PostOrderTraverse(T,PrintElement);
	printf("\n");

    scanf("%d",&i);
}//main
