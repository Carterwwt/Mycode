#include"stdio.h"
#include"stdlib.h"
//#include"iostream.h"
#define MAXSTRLEN 255
typedef unsigned char SString[MAXSTRLEN+1];

void get_next(SString T,int next[])
{// �㷨4.7
// ��ģʽ��T��next����ֵ����������next
   // �벹ȫ����
    int i=1,j=0;
    next[1]=0;
    while(i<T[0])// T[0]���ڴ洢�ַ������ַ�����
    {
        if(j==0||T[i]==T[j])
        {
            ++i;++j;next[i]=j;
        }
        else j=next[j];
    }
}

int main()
{
    int next[MAXSTRLEN];
    SString S;
    int n,i,j;
    char ch;
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
        get_next(S,next);
        printf("NEXT J is:");
        for(j=1;j<=S[0];j++)
            printf("%d",next[j]);
        printf("\n");
    }
    return 0;
}
