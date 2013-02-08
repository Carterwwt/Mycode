#include<stdio.h>
#include<malloc.h>
#define ERROR 0
#define OK 1
#define ElemType int

typedef struct LNode
{
 int data;
 struct LNode *next;
}LNode,*LinkList;

int CreateLink_L(LinkList &L,int n){
// ��������n��Ԫ�صĵ�����
  LinkList p,q;
  int i;
  ElemType e;
  L = (LinkList)malloc(sizeof(LNode));
  L->next = NULL;              // �Ƚ���һ����ͷ���ĵ�����
  q = (LinkList)malloc(sizeof(LNode));
  q = L;
  for (i=0; i<n; i++) {
	 scanf("%d", &e);
    p = (LinkList)malloc(sizeof(LNode));  // �����½��
	p->data=e;
	p->next=q->next;
	q->next=p;
	q=q->next;
  }
  return OK;
}

int LoadLink_L(LinkList &L){
// ���������
 LinkList p = L->next;
 if(p==NULL)printf("The List is empty!"); // �����
 else
 {
	 while(p!=NULL)    // �����
	 {
		printf("%d ",p->data);
		p=p->next;    // �����
	 }
 }
 printf("\n");
 return OK;
}

int LinkInsert_L(LinkList &L,int i,ElemType e){
	LNode *p=L,*s;
	int j=0;
	while(p&&j<i-1)
	{
		p=p->next;
		++j;
	}
	if(!p||j>i-1) return ERROR;
	s=(LinkList)malloc(sizeof(LNode));
	s->data=e;s->next=p->next;
	p->next=s;
	return OK;
}

int LinkDelete_L(LinkList &L,int i, ElemType &e){
	LNode *p=L,*q;
	int j=0;
	while(p->next&&j<i-1)
	{
		p=p->next;
		++j;
	}
	if(!(p->next)||j<i-1) return ERROR;
	q=p->next;p->next=q->next;
	e=q->data;
	free(q);
	return OK;
}
void MergeList_L(LinkList &La,LinkList &Lb,LinkList &Lc)
{
	LinkList pa,pb,pc;
	pa=La->next;pb=Lb->next;
	Lc=pc=La;
	while(pa&&pb)
	{
		if(pa->data<=pb->data)
		{
			pc->next=pa;
			pc=pa;
			pa=pa->next;
		}
		else
		{
			pc->next=pb;
			pc=pb;
			pb=pb->next;
		}
	}
	pc->next=pa?pa:pb;
	free(Lb);

}

int main()
{
	LinkList La,Lb,Lc;
	int n;
	scanf("%d",&n);
	CreateLink_L(La,n);
	printf("List A:");
	LoadLink_L(La);
	scanf("%d",&n);
	CreateLink_L(Lb,n);
	printf("List B:");
	LoadLink_L(Lb);
	MergeList_L(La,Lb,Lc);
	printf("List C:");
	LoadLink_L(Lc);
}
