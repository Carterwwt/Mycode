#include"malloc.h" /* malloc()�� */
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


int Search_Bin(SSTable &ST,ElemType key)
{
    int low=1,hight,mid;
    hight=ST.length;
    while(low<=hight)
    {
        mid=(low+hight)/2;
        if(ST.elem[mid]==key) return mid;
        else if(ST.elem[mid]>key) hight=mid-1;
        else low=mid+1;
    }
    return 0;
}

main()
{
	SSTable ST;
	int loc,key;
	int n;
	scanf("%d",&n);
	Creat_Seq(ST,n);
	scanf("%d",&key);
	loc = Search_Bin(ST,key);
	if(loc!=0)
		printf("The element position is %d.\n",loc-1);
	else
		printf("The element is not exist.\n");
}
