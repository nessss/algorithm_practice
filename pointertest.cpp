#include <iostream>

int main()
{
    int n = 5;
    int *pn = &n;
    int *pn2 = pn;

    std::cout << n << std::endl;
    std::cout << *pn << std::endl;
    std::cout << *pn2 << std::endl;

    int array[] = { 1, 2, 3, 4 };
    int *pa = array;
    int *pa2 = pa;

    std::cout << *pa << std::endl;
    std::cout << *pa2 << std::endl;

    ++pa;

    std::cout << *pa << std::endl;
    std::cout << *pa2 << std::endl;
}
