#include "stdio.h"
#include "malloc.h"
#define TRUE 1
#define FALSE 0
#define OK  1
#define ERROR  0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int  Status;

typedef char  ElemType;
typedef struct BiTNode{
	ElemType data;
	struct BiTNode *lchild,*rchild;//���Һ���ָ��
} BiTNode,*BiTree;

Status CreateBiTree(BiTree &T) {  // �㷨6.4
  // �������������������н���ֵ��һ���ַ�������#���ַ���ʾ������
  // ������������ʾ�Ķ�����T��
  char ch;
  scanf("%c",&ch);
  if (ch=='#') T = NULL;
  else {
    if (!(T = (BiTNode *)malloc(sizeof(BiTNode)))) return ERROR;
    T->data=ch; // ���ɸ����
    CreateBiTree(T->lchild); // ����������
    CreateBiTree(T->rchild); // ����������
  }
  return OK;
} // CreateBiTree


Status PrintElement( ElemType e ) {  // ���Ԫ��e��ֵ
printf("%c", e );
return OK;
}// PrintElement


Status PreOrderTraverse( BiTree T, Status(*Visit)(ElemType) ) {
   // ǰ�����������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit��
   //��ȫ����,���ö�����
  if(T==NULL)  return 0;
	Visit( T->data );
	PreOrderTraverse(T->lchild,Visit);
	PreOrderTraverse(T->rchild,Visit);
	return OK;

} // PreOrderTraverse

Status InOrderTraverse( BiTree T, Status(*Visit)(ElemType) ) {
     // �������������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit��
    //��ȫ����,���ö�����
    if(T==NULL)  return 0;
	InOrderTraverse(T->lchild,Visit);
	Visit(T->data);
	InOrderTraverse(T->rchild,Visit);
	return 1;


} // InOrderTraverse

Status PostOrderTraverse( BiTree T, Status(*Visit)(ElemType) ) {
     // �������������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit��
     //��ȫ����,���ö�����
    if(T==NULL)  return 0;
	PostOrderTraverse(T->lchild,Visit);
	PostOrderTraverse(T->rchild,Visit);
	Visit(T->data);
	return 1;

} // PostOrderTraverse



int main()   //������
{
	BiTree  T=NULL;
	CreateBiTree(T);//���ɶ���������Ta
    //ǰ���С��������������
	PreOrderTraverse(T,PrintElement);
	printf("\n");
	InOrderTraverse(T,PrintElement);
	printf("\n");
	PostOrderTraverse(T,PrintElement);
	printf("\n");
	return 0;
}//main
