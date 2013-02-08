#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define Null 0
#define LEN sizeof(struct student)
typedef struct student

{ long number;

  char name[25];

  char sex;

  float score; 

  struct student *next;
}STU;
  int n;
  struct student *creat(void)
  {
	  STU *head;
	  STU *p1,*p2;
	  p1=p2=(struct student*)malloc(LEN);
	  p1->next=NULL;
	  scanf("%ld",&p1->number);
	  if(p1->number==0) return head; 
      head=p1;
	  scanf("%s",p1->name);getchar();
	  scanf("%c%f",&p1->sex,&p1->score);
	  while(p1->number!=0)
	  {
		   p1=(struct student *)malloc(LEN);
           p1->next=Null;
		   scanf("%ld",&p1->number);
            if(p1->number==0) return head;
		   scanf("%s",p1->name);getchar();
		   scanf("%c%f",&p1->sex,&p1->score);
		   
		   p2->next=p1;
		   p2=p1;

		  
	  }
	  
	  return head;
  }
  void gather(struct student *head)
  {
	  STU *p;
	  int Fnum=0,Wnum=0;
	  int s1,s2,t,temp;
	  p=head;
	  while(p!=Null)
	  {
		  if(p->sex=='F') Fnum++;
		  else Wnum++;
		  p=p->next;
	  };
	  s1=Fnum;
	  s2=Wnum;
	  if(s1<s2)
	  {
		  temp=s1;
		  s1=s2;
		  s2=temp;
	  }
	  printf("%d %d",s1,s2);
	  
	  while(s2!=0)
	  {printf("iddd");
		  t=s1%s2;
		  s1=s2;
		  s2=t;
	  }
	  if(s2>0)
	  {
	   s1=Fnum/s1;
	   s2=Wnum/s1;
	  }
	  printf("��Ů������Ϊ:%d:%d",s1,s2);
  }
  void find(struct student *head,long number)
  {
	  STU *p;
	  p=head;
	  while(p->number!=number&&p->next!=Null)
		  p=p->next;
	  if(p->number==number)
	  {
		  printf("���ҵ�ѧ����Ϣ���£�");
		  printf("ѧ��:%ld\n����:%s\n�Ա�:%c\n���Ƴɼ�:%f\n",p->number,p->name,p->sex,p->score);
	  }
	  else printf("�޴�ѧ����Ϣ.");
  }
  void print(struct student *head)
  {
	  STU *p;
	  p=head;
	  while(p!=NULL)
	  {
		  printf("ѧ��:%ld   ����:%s   �Ա�:%c   ���Ƴɼ�:%f\n",p->number,p->name,p->sex,p->score);
		  p=p->next;
	  }
  }
  struct student *del(struct student *head,long number)
  {
	  STU *p1,*p2;
      if(head==NULL)
	  {
	    printf("��ѧ����Ϣ\n");
		return NULL;
	  }
	  p1=head;
	 
	  while(number!=p1->number&&p1->next!=NULL)
	  {p2=p1;p1=p1->next;}
	  if(number==p1->number)
	  {
		  if(head==p1) head=p1->next;
		  else p2->next=p1->next;
	  }
	  else printf("�޴�ѧ��ѧ�ţ�ɾ�����ɹ�.\n");
	  n=n-1;
	  return head;
  }

  void main()
  {
	  STU *head,*p;
	  FILE *fp;
	  long number;
	  printf("������ѧ����Ϣ(������0ʱ��������):\n");
	  head=creat();
	  print(head);
      gather(head);
	  printf("��������Ҫ���ҵ�ѧ��ѧ��:");
	  scanf("%ld",&number);
	  find(head,number);
	  printf("��ѧ����Ϣ����:\n");
	  print(head);
	  printf("\n");
	  printf("����������ɾ����ѧ��ѧ��(����0��ֹͣ����):\n");
	  scanf("%ld",&number);
	  while(number!=0)
	  {
		  head=del(head,number);
		  print(head);
		  printf("����������ɾ����ѧ��ѧ��(����0��ֹͣ����):\n");
		  scanf("%ld",&number);
	  }
	 
	  if(head!=NULL)
	  { p=head;
	  if((fp=fopen("d","w"))==Null)
	  { 
		  printf("can't open this file!");
		  exit(0);
	  }
	  do
	  {
		 if((fprintf(fp," %ld %s %c %f",p->number,p->name,p->sex,p->score))<=0)
			 printf("error!");
		  p=p->next;
	  }while(p!=Null);
	  fclose(fp);
	  }
}