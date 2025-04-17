#ifndef _MATH_DYNAMIC_LIBRARY_H_
#define _MATH_DYNAMIC_LIBRARY_H_

#ifdef MATHLIBRARY_EXPORTS
    #define MATH_API __declspec(dllexport)
#else
    #define MATH_API __declspec(dllimport)
#endif

extern "C" MATH_API int add(int a,int b);

class MATH_API Calculator
{
public:
    static int multiply(int a,int b);
    int subtract(int a,int b);
};

#endif