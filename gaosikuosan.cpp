#include<stdio.h>
#include<iostream>
#include<math.h>
using namespace std;
#define e 2.718281828459
#define PI 3.1415926
void qiuxy(char wending ,double x,double &dy,double &dz)
{
    switch(wending)
	{
	   case 'A': dy=0.22*x/(sqrt(1+0.0001*x)), dz=0.2*x; break;
	   case 'B': dy=0.16*x/(sqrt(1+0.0001*x)), dz=0.12*x; break;
	   case 'C': dy=0.11*x/(sqrt(1+0.0001*x)), dz=0.08*x/(sqrt(1+0.0002*x)); break;
	   case 'D': dy=0.08*x/(sqrt(1+0.0001*x)), dz=0.06*x/(sqrt(1+0.0015*x)); break;
	   case 'E': dy=0.06*x/(sqrt(1+0.0001*x)), dz=0.03*x/(1+0.0003*x); break;

	   case 'F': dy=0.04*x/(sqrt(1+0.0001*x)), dz=0.016*x/(1+0.0003*x); break;
	}
}

main()
{
    double c1,c2,x,z,t,p0,H,dx,dy,dz,a,s,k,I,Ts;
	char daqi;
	cout<<"�밴���¸�ʽ���룺"<<endl;
	cout<<"�·��L�����꣨�ף���"<<endl;
	cin>>x;
	cout<<"�ص�������꣨�ף���"<<endl;
    cout<<"0 "<<endl;
    cout<<"�ص��Ǧֱ���꣨�ף���"<<endl;
	cin>>z;
	cout<<"��ɢʱ�䣨�룩��"<<endl;
	cin>>t;
	cout<<"���淴��ϵ����"<<endl;
	cin>>a;
    cout<<"������������ɢ�ٶȣ�m/s����"<<endl;
	cin>>s;
	cin>>s;
	cin>>s;
	cin>>s;
	cin>>s;
	cout<<"���٣�m/s����"<<endl;
	cin>>k;
    cout<<"��ˮǿ�ȣ�����/Сʱ����"<<endl;
	cin>>I;
	cout<<"������˥�����ڣ��죩��"<<endl;
    cin>>Ts;
    cout<<"��ʼŨ�ȣ�ǧ��/�����ף���"<<endl;
	cin>>p0;
	cout<<"��Ч�߶ȣ��ף���"<<endl;
	cin>>H;
	cout<<"�����ȶ��ȵȼ���"<<endl;
	cin>>daqi;
	qiuxy(daqi,x,dy,dz);
	dx=dz;
    c1=p0/(2*PI*(s-k)*dy*dz)*pow(e,-(0.693*x)/(3600*(Ts*24)*(k+s))-(8*e-5*pow(I,0.6)*x)/(k+s))*(pow(e,-((z-H)+(0.01*x/(s-k)))*((z-H)+(0.01*x/(s-k)))/2*dz*dz)+a*pow(e,-(z+H+(0.01*x/(s-k)))*(z+H+(0.01*x/(s-k)))/(2*dz*dz)));
    cout<<"�·��L������������Ũ��= "<<c1<<endl;
	c2=p0/(2*PI*(s-k)*dy*dz)*pow(e,-(0.693*(-x))/(3600*(Ts*24)*(k+s))-(8*e-5*pow(I,0.6)*(-x))/(k+s))*(pow(e,-((z-H)+(0.01*(-x)/(s-k)))*((z-H)+(0.01*(-x)/(s-k)))/2*dz*dz)+a*pow(e,-(z+H+(0.01*(-x)/(s-k)))*(z+H+(0.01*(-x)/(s-k)))/(2*dz*dz)));
    cout<<"�Ϸ��-L������������Ũ��= "<<c2<<endl;
}

//-x*x/(4*dx*t)-y*y/(4*dy*t)
//-(z-H)*(z-H)/(4*dz*t)-a*(z+H)*(z+H)/(4*dz*t)
