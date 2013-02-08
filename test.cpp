/*************************************************************
*  �ļ�����Producer_Consumer.cpp
*  �������ڣ�2011.11.11
*  ��   �ߣ�ꐵ���
*  ʹ���ߣ�������̼�������ϵͳʵ����
*  ��   �ܣ���P��V������������ߣ����������⣨windows�汾��
*  ��   ����) 1�������ߣ���������
*            2) ��������С��
*            3) �������csArray
*                  �ź�����hFull
*                  �ź�����hEmpty
*
*
**************************************************************/
#include "stdafx.h"
#include "stdio.h"
#include <windows.h>
#define FILE_LOG
#ifdef FILE_LOG
FILE * cfileLog;
#endif

//����������СΪ
int array[5];
//��¼�������ݵĸ���
int pointer;
//��¼ȡ�õ����ݵ�λ��
int pointerget;
//�����������ݺ�
int sum;
//�ٽ�������
CRITICAL_SECTION csArray;
//���������Full�ź���
HANDLE hFull;
//���������Empty�ź���
HANDLE hEmpty;

//�����ߺ���
DWORD WINAPI Producer(LPVOID lpParam)
{
    int i = 0;
    pointer = 0;
    while( i < 100 )
    {
        WaitForSingleObject(hEmpty,INFINITE);
        EnterCriticalSection( &csArray);
        array[(pointer++)%5] = i + 1;
        printf("new data: %5d\n",i + 1);
#ifdef FILE_LOG
        char DebugString[100];
        int StringLong;
        sprintf(DebugString,"new data: %5d\n",i + 1);
        StringLong = strlen(DebugString);
        fwrite(DebugString,1,StringLong,cfileLog);
#endif
        LeaveCriticalSection( &csArray);
        ReleaseSemaphore(hFull,1,NULL);
        i++;
    }
    return 0;
}

//�����ߺ���A
DWORD WINAPI ConsumerA(LPVOID lpParam)
{
    while(1)
    {
        WaitForSingleObject(hFull,INFINITE);
        EnterCriticalSection( &csArray);
        sum += array[(pointerget ++ )%5];
        printf("        Consumer A get %5d\n",array[(pointerget -1)%5]);
        if(pointerget == 100)
        {
            printf("The sum is %d",sum);
        }
#ifdef FILE_LOG
        char DebugString[100];
        int StringLong;
        sprintf(DebugString,"Consumer A get %5d\n",array[(pointerget -1)%5]);
        StringLong = strlen(DebugString);
        fwrite(DebugString,1,StringLong,cfileLog);
#endif
        LeaveCriticalSection( &csArray);
        ReleaseSemaphore(hEmpty,1,NULL);
    }
    return 0;
}

//�����ߺ���B
DWORD WINAPI ConsumerB(LPVOID lpParam)
{
    while(1)
    {
        WaitForSingleObject(hFull,INFINITE);
        EnterCriticalSection( &csArray);
        sum += array[(pointerget ++ )%5];
        printf("Consumer B get %5d \n",array[(pointerget -1 )%5]);
        if(pointerget == 100)
        {
            printf("The sum is %d",sum);
        }
#ifdef FILE_LOG
        char DebugString[100];
        int StringLong;
        sprintf(DebugString,"Consumer B get %5d \n",array[(pointerget -1 )%5]);
        StringLong = strlen(DebugString);
        fwrite(DebugString,1,StringLong,cfileLog);
#endif
        LeaveCriticalSection( &csArray);
        ReleaseSemaphore(hEmpty,1,NULL);
    }
    return 0;
}



int main(int argc, char* argv[])
{
    HANDLE hThreadProducer,hThreadConsumerA,hThreadComsumerB;
    sum = 0;
    pointerget = 0;
#ifdef FILE_LOG
    cfileLog = fopen("������_��������־.txt","w");
#endif
    InitializeCriticalSection( &csArray);
    hFull  = CreateSemaphore(NULL, 0, 5, NULL);
    hEmpty = CreateSemaphore(NULL, 5, 5, NULL);
    hThreadProducer  = CreateThread(NULL, 0, Producer,  NULL, 0, NULL);
    hThreadConsumerA = CreateThread(NULL, 0, ConsumerA, NULL, 0, NULL);
    hThreadComsumerB = CreateThread(NULL, 0, ConsumerB, NULL, 0, NULL);
    getchar();
    fclose(cfileLog);
    return 0;
}
