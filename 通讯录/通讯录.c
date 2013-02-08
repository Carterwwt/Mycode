#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <windows.h>

typedef struct peo    //����ṹ��
{
     char name[20];  //����
     char street[20];//�ֵ�
     char city[20];//����
     char eip[20];//�ʱ�
     char state[20];//����
     char group[20];//Ⱥ��
     struct peo *next;       //����ṹ��ָ��
}PEO,*Link;

 PEO *head;

int ReadData(Link *head) //����ͨѶ¼
{
    FILE *fp;
    PEO *p1,*p2;//����ͷָ�룬βָ��
    if((fp=fopen("people.txt","rb"))==NULL)
    {
        printf("\n****************����һ���µ�ͨѶ¼����ϵͳ******************\n");
        return;
    }
    while(!feof(fp))
    {
        p1=(PEO *)malloc(sizeof(PEO));
        if(p1==NULL)
        {
            printf("����\n");
			fclose(fp);
			return 0;
        }
        if(fread(p1,sizeof(PEO),1,fp)!=1)
        {
            free(p1);
            break;
        }
        if(*head==NULL)
            *head=p2=p1;
        else
        {
            p2->next=p1;
            p2=p1;
        }
    }
    fclose(fp);
    return 1;
}

void initial(PEO *h)              //��ʼ������
{
    h=NULL;                                //��ͷָ�뷵�ص���һ���ڵ�
}
void sort(PEO *h)                 //˳�����
{
    PEO *p,*q,*s;
    char   t[20];                  //������ʱ�������ݵ�����
    p=h;                 //ʹpָ��ͷָ��
    while(p)                   //����pʱ����s->q->p˳���ȡ
    {
        s=p;
        q=p->next;
        while(q)                  //����qʱ���Ƚ�s,p�Ƿ���ͬ
        {
            if(strcmp(q->name,s->name)<=0)  //����ͬ����qָ������ݸ���s
                s=q;
            q=q->next;
        }
        if(s!=p)                         //��p������һ���ڵ㣬��s��p����ͬʱ
        {
            strcpy(t,p->name);                 //�����¶�s��ֵ
            strcpy(p->name,s->name);
            strcpy(s->name,t);
        }
        p=p->next;
    }
}
PEO *enter(PEO *h)     //��Ӻ�������
{
    PEO *p,*p0;
    p=p0=(PEO *)malloc(sizeof(PEO));
    printf("��������Ҫ��ӵ��˵�����,�ֵ�,����,�ʱ�,���ң�Ⱥ��:\n");
    scanf("%s%s%s%s%s%s",p->name,p->street,p->city,p->eip,p->state,p->group);
    p->next=NULL;
    if(h==NULL)
    {
        h=p;
        printf("��ӳɹ�!\n");
        return h;
    }
    p0=h;
    if(strcmp(p0->name,p->name)>0)//�ж�����������Ƿ���ͬ
    {
        p->next=h;
        h=p;
        printf("��ӳɹ�!\n");
        return h;
    }
    while(p0->next!=NULL&&strcmp(p0->next->name,p->name)<0)
        p0=p0->next;
    if(p0->next==NULL)
    {
        p0->next=p;
        printf("��ӳɹ�!\n");
        return h;
    }
    else if(!strcmp(p0->next->name,p->name))
    {
        printf("��¼�Ѵ���!\n");
        free(p);
        return h;
    }
    else
    {
        p->next=p0->next;
        p0->next=p;
        printf("��ӳɹ�!\n");
        return h;
    }
}
void display(PEO *ptr)
{
    if(ptr==NULL)
    {
        printf("û�м�¼!\n");
        return ;
    }
    printf("������������£�\n");
    printf("    ����      �ֵ�      ����      �ʱ�      ����      Ⱥ��\n");
    while(ptr!=NULL)
    {
        printf("%6s%10s%10s%10s%10s%10s\n",ptr->name,ptr->street,ptr->city,ptr->eip,ptr->state,ptr->group);
        ptr=ptr->next;
    }
    printf("\n");
}


void data2(PEO *p,char find[])  //������༶���ҵĽ����������groupsearch(PEO *h)����
{
    if(strcmp(p->group,find)==0)        //�ж��Ƿ���ҪѰ�ҵ�Ⱥ�����Ǻ�
    {
        printf("Ⱥ���������£�\n");
        printf("    ����      �ֵ�      ����      �ʱ�      ����      Ⱥ��\n");
        printf("%6s%10s%10s%10s%10s%10s\n",p->name,p->street,p->city,p->eip,p->state,p->group);
    }
    else  p=p->next;      //�����Ǻϣ�ָ��ָ����һ���ڵ�����ж�
}//data2

void menu4()  //����˵��������Ʒ�
{
        printf("================================================================================");
}//menu4

PEO *Locate(PEO *h,char find[],char match[]) //����ƥ�亯������,�ú������ڶ�λ�����з���Ҫ��Ľڵ㣬�����ظ�ָ��
{
    PEO *r;                //����ڵ�ָ��r
    if(strcmp(match,"group")==0)                //��Ⱥ���ѯ
    {
        r=h;                //��ʼ��r,ָ���һ���ڵ�
        while(r!=NULL)                //r�ǿ�
        {
                if(strcmp(r->group,find)==0)                //��ѯ�ɹ�
                        return r;
                r=r->next;                //�ڵ����
        }
    }
    return 0;
}

void groupsearch(PEO *h)                //��ѯ��������
{
    char temp;                //���嵥�ַ�temp
    char find[20];              //�����ַ���find[]
    int n=0;
    PEO *p,*p0;                //����ڵ�p,p0
    if(h==NULL)
    {
        printf("\n\a�Բ���,����Ϣ�ɲ�ѯ!\n");
        return;
    }
    else
    {
        printf("\n��������Ҫ��ѯ��Ⱥ��:");
        scanf("%s",find);
        p=Locate(h,find,"group");   //����Locate ��������Ⱥ�������в���ƥ��
    }//else if
    if(p)
    {
        printf("\n                    ==============>��ѯ���<==============\n");
        menu4();
        while(p)
        {
            p0=p;
            data2(p0,find);                //�����Ⱥ�������ҵĽ��

            p=p->next;                //�ڵ����
            if((strcmp(find,p0->group)==0))    //�����ظ�Ⱥ����ʱ��n��1
                n++;
        }//while
        printf("��Ⱥ����  %d ����ϵ�ˡ� \n",n);
        menu4();
    }//if
    else    printf("\n\a�Բ���,����Ϣ�ɲ�ѯ!\n");
}

PEO *delet(PEO *h)
{
    char s[20];
    PEO *p,*p0;
    if(h==NULL)
    {
        printf("û�м�¼!\n");
        return h;
    }
    printf("��������Ҫɾ���˵�������\n");
    scanf("%s",s);
    p0=h;
    if(!strcmp(p0->name,s))
    {
        h=p0->next;
        free(p0);
        printf("ɾ���ɹ�!\n");
        return h;
    }
    p=p0->next;
    while(p!=NULL)
    {
        if(!strcmp(p->name,s))
        {
            p0->next=p->next;
            free(p);
            printf("ɾ���ɹ�!\n");
            return h;
        }
        p0=p;
        p=p->next;
    }
    printf("û�д��˵ļ�¼!\n");
    return h;
}
int save(PEO *head)
{
    PEO *p;
    FILE *fp;
    if((fp=fopen("people.txt","wb"))==NULL)
    {
        printf("\n�򲻿��ļ�!\n");
        return;
    }
    p = head;
    while(p!=NULL)
    {
        if(fwrite(p,sizeof(PEO),1,fp)!=1)
		{
			printf("д�����ݳ���\n");
			fclose(fp);
			return 0;
		}
		p=p->next;
    }
    fclose(fp);
	return 1;
}
void search(PEO *h)
{
    char s[20];
    PEO *ptr;
    ptr=h;
    if(ptr==NULL)
    {
        printf("û�м�¼!\n");
        return ;
    }
    printf("��������Ҫ�����˵�������\n");
    scanf("%s",s);
    for( ;ptr!=NULL;ptr=ptr->next)
    {
        if(!strcmp(ptr->name,s))
        {
            printf("����������£�\n");
            printf("    ����      �ֵ�      ����      �ʱ�      ����\n");
            printf("%6s%10s%10s%10s%10s\n",ptr->name,ptr->street,ptr->city,ptr->eip,ptr->state);
            return ;
        }
    }
    Beep(1060,500);//i
    Beep(784,500);//5
    Beep(523,500);//1
    printf("���޴���!\n");
}

void Free(Link *head)//�ͷ���Դ
{
	Link p = *head;
	while(p!=NULL)
	{
		*head = (*head)->next;
		free(p);
		p =* head;
	}
	*head = NULL;
}

void main()
{
    int k;
    char s[20],c[20]={'1'};
    char p[20];
    Link head = NULL;
    printf("Welcome to CY's NOTEBOOK!\n");
    printf("Please enter you password:\n");
    gets(p);
    printf("\n Please wait...\n");
    Sleep(1000);
    system("cls");
    if(!strcmp("Chen Yi",p))
    {
        printf("\n\n Welcome!\n");
        printf(" []             *   *    *                 @              *                 *   ");
        printf("\n");
        printf(" []          *             *               @                *              *    ");
        printf("\n");
        printf(" []         *               *              @                  *          *      ");
        printf("\n");
        printf(" []         *                              @                    *      *       ");
        printf("\n");
        printf(" []         *                              @                        *          ");
        printf("\n");
        printf(" []          *                             @                        *           ");
        printf("\n");
        printf(" []            *           *               @                        *           ");
        printf("\n");
        printf(" []               *  *  *                  @                        *           ");
        ReadData(&head);
        do
        {
            printf("�����ѯ�밴1����Ӽ�¼�밴2,ɾ����¼�밴3,��ʾȫ���밴4,�����¼�밴5,������Ϣ��ѯ�밴6,�˳�ϵͳ�밴0\n");
            scanf("%d",&k);
            while(k!=1&&k!=2&&k!=3&&k!=4&&k!=5&&k!=6&&k!=0)
            {
                printf("�����������������1��6!\n");
                scanf("%d",&k);
            }
            switch(k)
            {
                case 1:
                    do
                    {
                        groupsearch(head);//��ѰȺ����Ϣ
                        printf("������ѯ�밴1,���������˳���ѯ!\n");
                        scanf("%s",s);
                    }while(!strcmp(s,c));
                    break;
                case 2:
                    do
                    {
                        sort(head);
                        head=enter(head);//��Ӹ�����Ϣ
                        printf("��������밴1,���������˳����!\n");
                        scanf("%s",s);
                    }while(!strcmp(s,c));
                    break;
                case 3:
                    do
                    {
                        sort(head);
                        head=delet(head);//ɾ��������Ϣ
                        printf("����ɾ���밴1,���������˳�ɾ��!\n");
                        scanf("%s",s);
                    }while(!strcmp(s,c));
                    break;
                case 4:sort(head);display(head);break;
                case 5:sort(head);save(head);printf("����ɹ�");break;//���������Ϣ
                case 6:sort(head);search(head);break;//��ѯ������Ϣ
                case 0:Free(&head);return;
            }
        }while(1);
    }
    else printf("�������ϵͳ���Զ��˳���");
    Beep(1060,500);//i
    Beep(784,500);//5
    Beep(523,500);//1
}
