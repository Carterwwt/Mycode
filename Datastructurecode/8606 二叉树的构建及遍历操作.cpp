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

typedef struct BiTNode
{
  ElemType data;
  struct BiTNode *lchild,*rchild;//���Һ���ָ��
} BiTNode,*BiTree;

Status CreateBiTree(BiTree &T)
{  // �㷨6.4
  // �������������������н���ֵ��һ���ַ�������#���ַ���ʾ������
  // ������������ʾ�Ķ�����T��
  char ch;
  scanf("%c",&ch);
  if (ch=='#') T = NULL;
  else {
    if (!(T = (BiTNode *)malloc(sizeof(BiTNode)))) return ERROR;
    T->data=ch;// ���ɸ����
    CreateBiTree(T->lchild);    // ����������
    CreateBiTree(T->rchild);  // ����������
  }
  return OK;
} // CreateBiTree


Status PrintElement( ElemType e )
{  // ���Ԫ��e��ֵ
printf("%c", e );
return OK;
}// PrintElement


Status PreOrderTraverse(BiTree T)
{
   // ǰ�����������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit��
   //��ȫ����,���ö�����
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
     // �������������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit��
    //��ȫ����,���ö�����
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
     // �������������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit��
     //��ȫ����,���ö�����
   if(T)
   {
        if(PostOrderTraverse(T->lchild))
          if(PostOrderTraverse(T->rchild))
            if(PrintElement(T->data))
       return OK;
       return ERROR;
   }else return OK;

} // PostOrderTraverse



int main()   //������
{
    BiTree T;
    if(!CreateBiTree(T))
        return ERROR;
    else
    {
        PreOrderTraverse(T);
        printf("\n");
        InOrderTraverse(T);
        printf("\n");
        PostOrderTraverse(T);
    }
    return OK;
}//main
