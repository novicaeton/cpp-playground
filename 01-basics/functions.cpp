#include <iostream>

using std::cout;

static int add(const int a, const int b)
{
    return a + b;
}

int main()
{
    const int result = add(10, 20);

    cout << "Result: " << result << '\n';

    return 0;
}