#include"stdio.h"
#include"stdlib.h"
#include"math.h"
#include"string.h"
#include"malloc.h"

inline void Swap(char& a, char& b)
{// ����a��b
    char temp = a;
    a = b;
    b = temp;
}

void Perm(char list[], int k, int m)
{ //����list [k��m ]���������з�ʽ
    int i;
    if (k == m) {//���һ�����з�ʽ
        for (i = 0; i <= m; i++)
            putchar(list[i]);
        putchar('\n');
    }
    else // list[k��m ]�ж�����з�ʽ
        // �ݹ�ز�����Щ���з�ʽ
        for (i=k; i <= m; i++) {
            Swap (list[k], list[i]);
            Perm (list, k+1, m);
            Swap (list [k], list [i]);
        }
}

int main()
{
    char s[]="123";
    Perm(s, 0, 2);
    return 0;
}
