#include <stdio.h>
#include <stdlib.h>

struct Country//�����Ϣ�ṹ��
{
	char counnum[5];
	char counname[21];
	int population;
	int family;//depositor�����
	float relief;//�ȼý�
	struct Country *next;
};

typedef struct Country *Lcountry;

//��������
int CreateData(Lcountry *head)
{
	Lcountry s,p;
	int i,num;

	printf("�������:");
	scanf("%d",&num);
	if(num < 1)
	{
		printf("�������Ϸ�\n");
		return 0;
	}

	//¼������
	for(i=1;i<=num;i++)
	{
		if((s=(Lcountry)malloc(sizeof(struct Country)))==NULL)
		{
			printf("�ڴ��������\n");
			return 0;
		}

		printf("����counnum counname population family relief,�м��ÿո����\n");
		if(scanf("%s%s%d%d%f",s->counnum,s->counname,&s->population,&s->family,&s->relief)!=5)
		{
			printf("¼����������\n");
			return 0;
		}
		s->next=NULL;

		if(i==1)
		{
			*head=p=s;
		}
		else
		{
			p->next=s;
			p=s;
		}
	}

	return 1;
}

//д������
int WriteData(Lcountry head)
{
	FILE *fp;
	Lcountry p;

	if((fp=fopen("test.txt","wb"))==NULL)//������ֻд��ʽ��
	{
		printf("���ļ�����\n");
		return 0;
	}

	p=head;
	while(p!=NULL)
	{
		if(fwrite(p,sizeof(struct Country),1,fp)!=1)
		{
			printf("д�����ݳ���\n");
			fclose(fp);
			return 0;
		}
		p=p->next;
	}

	fclose(fp);//�ر��ļ�
	return 1;
}

//��������
int ReadData(Lcountry *head)
{
	Lcountry s,p;
	FILE *fp;
	if((fp=fopen("test.txt","rb"))==NULL)//������ֻ����ʽ��
	{
		printf("���ļ�����\n");
		return 0;
	}
	while(!feof(fp))//�ļ�����ĩβ
	{
		if((s=(Lcountry)malloc(sizeof(struct Country)))==NULL)
		{
			printf("�ڴ��������\n");
			fclose(fp);
			return 0;
		}
		//��ôд����ô��ȡ
		if(fread(s,sizeof(struct Country),1,fp)!=1)//����ĩβ���߳���,����ѭ��
		{
			free(s);
			break;
		}
		if(*head==NULL)
			*head=p=s;
		else
		{
			p->next=s;
			p=s;
		}
	}
	fclose(fp);//�ر��ļ�
	return 1;
}

//��ʾ����
void Print(Lcountry p)
{
	printf("counnum \t counname \t population \t family \t relief\n");
	while(p!=NULL)
	{
		printf("%s\t\t%s\t\t%d\t\t%d\t\t%0.1f\n",p->counnum,p->counname,p->population,p->family,p->relief);
		p=p->next;
	}
}
//�ͷ���Դ
void Free(Lcountry *head)
{
	Lcountry p=*head;
	while(p!=NULL)
	{
		*head=(*head)->next;
		free(p);
		p=*head;
	}
	*head=NULL;
}

int main(void)
{
	Lcountry head=NULL;

	//��������
	if(CreateData(&head)!=1)
		return 1;

	//��ʾ����
	Print(head);

	//д������
	if(WriteData(head)!=1)
		return 1;

	//�ͷ���Դ
	Free(&head);
	printf("д�����\n");

	printf("\n��ȡ����...\n");
	//��������
	if(ReadData(&head)!=1)
		return 1;

	//��ʾ����
	Print(head);

	//�ͷ���Դ
	Free(&head);
	return 0;
}
