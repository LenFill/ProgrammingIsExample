//Выполнить программу, иллюстрирующую разные операции с указателями.
//Повторить эксперемент для разныз типов данных 

#define PR(x) printf("x=%u, *x=%lf, &x=%u\n",x,*x,&x)
#include <stdio.h>
#include <iostream>
using namespace std;
void main(void)
{
	double mas[] = { 100.123, 200.456, 300.789 };
	double *ptr1, *ptr2;
	ptr1 = mas;
	ptr2 = &mas[2];
	PR(ptr1);
	ptr1++;
	PR(ptr1);
	PR(ptr2);
	++ptr2;
	printf("ptr2-ptr1 = %u\n", ptr2 - ptr1);
}