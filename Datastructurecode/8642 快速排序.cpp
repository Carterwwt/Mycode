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

int Partition(SSTable &ST,int low,int high)
{
    ElemType pivotkey;
    ST.elem[0]=ST.elem[low];
    pivotkey=ST.elem[low];
    while(low<high)
    {
        while(low<high&&ST.elem[high]>=pivotkey) --high;
        ST.elem[low]=ST.elem[high];
        while(low<high&&ST.elem[low]<=pivotkey) ++low;
        ST.elem[high]=ST.elem[low];
    }
    ST.elem[low]=ST.elem[0];
    PR(ST);
    return low;
}



void QSort(SSTable &ST,int low,int high)
{
    int pivotloc;
    if(low<high)
    {
        pivotloc=Partition(ST,low,high);
        QSort(ST,low,pivotloc-1);
        QSort(ST,pivotloc+1,high);
    }
}

main()
{
	SSTable ST;
	int loc,key;
	int n;
	scanf("%d",&n);
	Creat_Seq(ST,n);
	QSort(ST,1,n);
}

