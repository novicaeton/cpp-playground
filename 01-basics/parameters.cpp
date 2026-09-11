#include <iostream>

using std::cout;

void byValue(int value)
{
    value++;
}

static void byReference(int& value)
{
    value++;
}

static void byConstReference(const int& value)
{
    cout << "const reference: " << value << '\n';
}

static void byPointer(int* value)
{
    (*value)++;
}

int main()
{
    // compile-time const
    constexpr int a = 10;
    int b = 10;
    constexpr int c = 10;
    int d = 10;

    byValue(a);
    byReference(b);
    byConstReference(c);
    byPointer(&d);

    cout << "a: " << a << '\n';
    cout << "b: " << b << '\n';
    cout << "c: " << c << '\n';
    cout << "d: " << d << '\n';

    /*
        int&        → can modify the original value
        const int&  → cannot modify the original value
        int*        → can modify the value through the pointer
        const int*  → cannot modify the value through the pointer
    */

    return 0;
}