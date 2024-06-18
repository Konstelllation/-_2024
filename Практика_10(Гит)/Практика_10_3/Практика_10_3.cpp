#include <iostream>


void swap(int& a, int& b)
{
    
    int temp{ a };

    a = b;
    
    b = temp;
}

int main()
{
    int a{ 6 };
    int b{ 8 };
    swap(a, b);

    if (a == 8 && b == 6)
        std::cout << "It works!\n";
    else
        std::cout << "It's broken!\n";

    return 0;
}