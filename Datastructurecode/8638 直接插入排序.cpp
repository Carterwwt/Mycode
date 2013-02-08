#include"malloc.h"
#include"stdio.h"
#include"stdlib.h"

typedef int ElemType;
typedef struct /*��̬���ұ��˳��洢�ṹ */
{
	ElemType *elem; /* ����Ԫ�ش洢�ռ��ַ������ʱ��ʵ�ʳ��ȷ��䣬0�ŵ�Ԫ���� */
	int length; /* ���� */
}SSTable;

void Creat_Seq(SSTable &ST,int n)
{ /* �������: ����һ����n������Ԫ�صľ�̬˳����ұ�ST(������������r) */
	int i,temp;
	ST.elem=(ElemType *)malloc((n+1) * sizeof(ElemType)); /* ��̬����n������Ԫ�ؿռ�(0�ŵ�Ԫ����) */
	if(!(ST).elem)
	{
		printf("ERROR\n");
		exit(0);
	} /*�ڴ����ʧ�ܽ�������*/
	for(i=1;i<=n;i++)
	{
		scanf("%d",&temp);
		*(ST.elem+i)=temp; /* ���θ�ֵ��ST */
	}
	ST.length=n;
}

int PR(SSTable &ST)
{
    int i;
    for(i=1;i<=ST.length;i++)
    printf("%d ",ST.elem[i]);
    printf("\n");
}

void InserSort(SSTable &ST)
{
    int i,j;
    for(i=2;i<=ST.length;i++)
    {
        if(ST.elem[i]<ST.elem[i-1])
        {
            ST.elem[0]=ST.elem[i];
            ST.elem[i]=ST.elem[i-1];
            for(j=i-2;ST.elem[0]<ST.elem[j];j--)
            ST.elem[j+1]=ST.elem[j];
            ST.elem[j+1]=ST.elem[0];
        }
        PR(ST);
    }
}

main()
{
	SSTable ST;
	int loc,key;
	int n;
	scanf("%d",&n);
	Creat_Seq(ST,n);
	InserSort(ST);

}
