#include"stdio.h"
#include"stdlib.h"
#include"math.h"
#include"string.h"
#include"malloc.h"
int main()
{
    int a[100],i,j=2,k,p,q,length,t,flag=0;
    scanf("%d",&length);
    for(i=0;i<length;i++)
    {
        scanf("%d",&a[i]);
    }
    if(length==1)   printf("%d\n",a[0]);
    else
    {
        while(j<=length)    //�鲢���д�������2��ƽ������
        {
            k=0;
            if(flag<=1)          //��ֹ���һ�����������ѭ����ר�ñ��
            {
                for(i=k;i<length;i=i+j)   //������������
                {
                    if(i+j-1<length)       //���м�����һ�����ĺ��벻����ԭ���鳤��
                    {
                        for(p=i;p<i+j;p++)
                        {
                            for(q=i+j-1;q>p;q--)
                                if(a[p]>=a[q]) {t=a[p];a[p]=a[q];a[q]=t;}
                        }
                        for(p=i;p<i+j;p++)
                            printf("%d ",a[p]);
                    }
                    else              //���м�����һ�����ĺ��볬����ԭ���鳤��
                    {
                        for(p=i;p<length-1;p++)
                        {
                            for(q=length-1;q>p;q--)
                                if(a[p]>=a[q]) {t=a[p];a[p]=a[q];a[q]=t;}
                        }
                        for(p=i;p<length;p++)
                            printf("%d ",a[p]);
                    }
                }

            }
            else break;           //����ѭ��
            j=2*j;
            if(j>=length) {j=length;flag++;}     //���һ�ε�2�η���ǿ��ת����ԭ���鳤��
            printf("\n");
        }
    }
    return 0;
}
