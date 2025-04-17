#include "mathdynamiclibrary.h"

extern "C" MATH_API int add(int a,int b)
{
    return a+b;
}

int Calculator::multiply(int a,int b)
{
    return a*b;
}

int Calculator::subtract(int a,int b)
{
    return a-b;
}