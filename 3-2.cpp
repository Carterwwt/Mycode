#include"stdio.h"
#include"stdlib.h"
#include"iostream"
#define MAXSTRLEN 255
#define TRUE 1
#define FALSE 0
#define OK  1
#define ERROR  0
#define INFEASLBLE  -1
#define OVERFLOW  -2
typedef unsigned char SString[MAXSTRLEN+1];

void get_next(SString T,int next[])
{// �㷨4.7
// ��ģʽ��T��next����ֵ����������next
    int i=1,j=0;
    next[1]=0;
    while(i<T[0])// T[0]���ڴ洢�ַ������ַ�����
    {
        if(j==0||T[i]==T[j])
        {
            ++i;++j;
            if(T[i]!=T[j])
                next[i]=j;
            else
                next[i]=next[j];
        }
        else j=next[j];
    }
}

int Index_KMP(SString S,SString T,int pos)
{
// �㷨4.6
// ����ģʽ��T��next������T������S�е�pos���ַ�֮���λ��
// KMP�㷨��   ���У�T�ǿգ�1<=pos<=StrLength(S)
    int i=pos,j=1;
    //printf("%d %d\n",i,j);
    int next[MAXSTRLEN];
    get_next(T,next);
    while(i<=S[0]&&j<=T[0])// T[0]���ڴ洢�ַ������ַ�����
    {
        if(j==0||S[i]==T[j])
        {
            i++;
            j++;
            //printf("%d %d\n",i,j);
        }
        else j=next[j];//ģʽ�������ƶ�
    }
    //printf("%d %d\n",i,j);
    if(j>T[0]) return i-T[0];
    else return 0;
}

int main()
{
    SString S,T;
    int n,i,j;
    char ch;
    int pos;
    scanf("%d",&n);
    ch=getchar();
    for(i=1;i<=n;i++)
    {
        ch=getchar();
        for(j=1;j<=MAXSTRLEN&&(ch!='\n');j++)
        {
            S[j]=ch;
            ch=getchar();
        }
        S[0]=j-1;// S[0]���ڴ洢�ַ������ַ�����
        /*get_next(S,next);
        printf("NEXT S is:");
        for(j=1;j<=S[0];j++)
            printf("%d",next[j]);
        printf("\n");*/

        ch=getchar();
        for(j=1;j<=MAXSTRLEN&&(ch!='\n');j++)//¼��ģʽ��
        {
            T[j]=ch;
            ch=getchar();
        }
        T[0]=j-1;// T[0]���ڴ洢ģʽ�����ַ�����
        pos=Index_KMP(S,T,1);
        printf("%d\n",pos);
    }
    return 0;
}









