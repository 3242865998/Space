#include "mathdynamiclibrary.h"
#include <iostream>
int main()
{
    std::cout<<"1+1="<<add(1,1)<<std::endl;
    Calculator cal;
    std::cout<<"2*5="<<cal.multiply(2,5)<<std::endl;
    std::cout<<"9-5="<<cal.subtract(9,5)<<std::endl;
    return 0;
}