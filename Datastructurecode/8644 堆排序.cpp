#include<stdio.h>

int main()
{ 
	int i,j,k,m,n,sum,t,a[100];
    scanf("%d",&n);
    for(i=1;i<=n;i++)
	{
    scanf("%d",&a[i]);
	}
    i=n;sum=n;
	while(i!=0)
	{ m=sum/2;
	  if(sum%2!=0)
	  {
		  for(j=m;j>0;j--)   //�Ӻ��濪ʼ����
		  { 
	         if(a[2*j]>a[j]&&a[2*j+1]>a[j])
			 {
			if(a[2*j]>=a[2*j+1]) {t=a[j];a[j]=a[2*j];a[2*j]=t;}
			else {t=a[j];a[j]=a[2*j+1];a[2*j+1]=t;}
			 }
		    else if(a[2*j]>a[j]) {t=a[j];a[j]=a[2*j];a[2*j]=t;}
			else if(a[2*j+1]>a[j]) {t=a[j];a[j]=a[2*j+1];a[2*j+1]=t;}
		  }
		  for(j=1;j<=m;j++)   //�ٴ�ǰ��ȷ����������Ƿ����
		  {
		  if(a[2*j]>a[j]&&a[2*j+1]>a[j])
			 {
			if(a[2*j]>=a[2*j+1]) {t=a[j];a[j]=a[2*j];a[2*j]=t;}
			else {t=a[j];a[j]=a[2*j+1];a[2*j+1]=t;}
			 }
		    else if(a[2*j]>a[j]) {t=a[j];a[j]=a[2*j];a[2*j]=t;}
			else if(a[2*j+1]>a[j]) {t=a[j];a[j]=a[2*j+1];a[2*j+1]=t;}
		  }
	  }
       else   //ż������ʱ���м��Ǹ���һ��û���Һ���
	   { if(a[m]<a[2*m]) {t=a[m];a[m]=a[2*m];a[2*m]=t;}  
	     for(j=m-1;j>0;j--)   //�Ӻ��濪ʼ����
		  { 
	         if(a[2*j]>a[j]&&a[2*j+1]>a[j])
			 {
			if(a[2*j]>=a[2*j+1]) {t=a[j];a[j]=a[2*j];a[2*j]=t;}
			else {t=a[j];a[j]=a[2*j+1];a[2*j+1]=t;}
			 }
		    else if(a[2*j]>a[j]) {t=a[j];a[j]=a[2*j];a[2*j]=t;}
			else if(a[2*j+1]>a[j]) {t=a[j];a[j]=a[2*j+1];a[2*j+1]=t;}
		  }
		  for(j=1;j<m;j++)   //�ٴ�ǰ��ȷ����������Ƿ����
		  {
		  if(a[2*j]>a[j]&&a[2*j+1]>a[j])
			 {
			if(a[2*j]>=a[2*j+1]) {t=a[j];a[j]=a[2*j];a[2*j]=t;}
			else {t=a[j];a[j]=a[2*j+1];a[2*j+1]=t;}
			 }
		    else if(a[2*j]>a[j]) {t=a[j];a[j]=a[2*j];a[2*j]=t;}
			else if(a[2*j+1]>a[j]) {t=a[j];a[j]=a[2*j+1];a[2*j+1]=t;}
		  }
		  if(a[m]<a[2*m]) {t=a[m];a[m]=a[2*m];a[2*m]=t;}
	   }
	   for(k=1;k<=n;k++)
	   {printf("%d ",a[k]);}
	   printf("\n");
	   t=a[1];
	   a[1]=a[sum];
	   a[sum]=t;
	   sum--;
	   i--;
	   
	}
	return 0;
}
