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

 PEO *creat()                       //����ͨѶ¼
{
    FILE *fp;

    PEO *p1=NULL,*p2=NULL,*temp=NULL;

              //����ͷָ�룬βָ��
    if((fp=fopen("people.txt","rb+"))==NULL)
    {
           printf("\n****************����һ���µ�ͨѶ¼����ϵͳ******************\n");
           return;
    }
    head=(PEO *)malloc(sizeof(PEO));
    head->next=NULL;
    temp=p2=head;
    while(! feof(fp))                            //ѭ����ȡ
    {
        p1=(PEO *)malloc(sizeof(PEO));
        temp=p2;
        p2->next=p1;
        p2=p1;
        fread(p1,sizeof(PEO),1,fp);
    }
    temp->next=NULL;
    fclose(fp);
    return head;
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
    p=(PEO *)malloc(sizeof(PEO));
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
void display(PEO *h)
{
    PEO *ptr;
    if(h==NULL)
    {
        printf("û�м�¼!\n");
        return ;
    }
    printf("������������£�\n");
    printf("    ����      �ֵ�      ����      �ʱ�      ����      Ⱥ��\n");
    for(ptr=h;ptr!=NULL;ptr=ptr->next)
    printf("%6s%10s%10s%10s%10s%10s\n",ptr->name,ptr->street,ptr->city,ptr->eip,ptr->state,ptr->group);
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
void save()
{
    PEO *p=NULL;
    PEO *p0=NULL;
    FILE *fp;
    if(head==NULL)
    {
        printf("\n��¼Ϊ�գ�\n");
        Sleep(1000);
        return;
    }
    else
    {
        p=head->next;
        if((fp=fopen("people.txt","wb+"))==NULL)
        {
            printf("\n�򲻿��ļ�!\n");
            return;
        }
        while(p!=NULL)                              //������Ϣ
        {
            fwrite(p,sizeof(PEO),1,fp);
            p0=p;
            p=p->next;
        }
        printf("�������!");
        fclose(fp);
        //*****�ͷ�����ռ�*****
        for(;head->next!=NULL;)
        {
            p=head->next;
            head->next=head->next->next;
            free(p);
        }
        free(head);
    }
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

void main()
{
    int k;
    char s[20],c[20]={'1'};
    char p[20];
    printf("Welcome to CY's NOTEBOOK!\n");
    printf("Please enter you password:\n");
    gets(p);
    printf("\n Please wait...\n");
    Sleep(1000);
    system("cls");
    if(!strcmp("chenyi",p))
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
        head=creat();
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
                case 0:return;
            }
        }while(1);
    }
    else printf("error!");
    Beep(1060,500);//i
    Beep(784,500);//5
    Beep(523,500);//1
}
