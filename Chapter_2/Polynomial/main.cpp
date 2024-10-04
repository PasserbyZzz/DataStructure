#include <iostream>
#include "polynomial.h"
using namespace std;

int main()
{
	Type stop_flag;
	getStop(stop_flag);  //读入停止标志对

	Polynomial<Type> L1(stop_flag), L2(stop_flag), L3(stop_flag);

    L1.getPoly(); //读入第一个多项式
    L2.getPoly(); //读入第二个多项式

    L3.addPoly(L1,L2); //L3 = L1 +L2
   	L3.dispPloy(); //显示多项式L3的内容
    
	return 0;
} 
