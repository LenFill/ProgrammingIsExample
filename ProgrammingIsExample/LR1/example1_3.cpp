//Написать программу, которая меняет местами значения двух переменных.
//В качестве параметра использовать int, int* и int&.
// 
//
/*
#include <iostream>
using namespace std;
int main()
{
	int a = 2, b = 5;
	void obmen1(int, int);
	void obmen2(int*, int*);
	void obmen3(int&, int&);
	cout << "before the exchange: a= " << a << " b= " << b << endl;
	// вызов obmen1(int, int);
	obmen1(a, b);
	cout << "after the exchange 1: a= " << a << " b= " << b << endl;
	// вызов obmen2(int, int);
	obmen2(&a, &b);
	cout << "after the exchange 2: a= " << a << " b= " << b << endl;
	// вызов obmen3(int, int);
	obmen3(a, b);
	cout << "after the exchange 3: a= " << a << " b= " << b << endl;
}
void obmen1(int a, int b) {
	int temp = a;
	a = b;
	b = temp;	
}
void obmen2(int* a, int* b) {
int temp = *a;
	*a = *b;
	*b = temp;	
}
void obmen3(int& x, int& y) {
	int temp = x;
	x = y;
	y = temp;
}*/