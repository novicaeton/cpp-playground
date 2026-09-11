#include <iostream>

using std::cout;

static void increment(int& value)
{
    value++;
}

static void print(const int& value)
{
    cout << "Value: " << value << '\n';
}

int main()
{
    int age = 42;

    // A reference is another name for an existing variable
    int& ref = age;

    cout << "age: " << age << '\n';
    cout << "ref: " << ref << '\n';

    // A reference and the original variable refer to the same object
    ref = 50;

    cout << "age after ref = 50: " << age << '\n';
    cout << "ref after ref = 50: " << ref << '\n';

    // Pass by reference allows the function to modify the original variable
    increment(age);

    cout << "age after increment: " << age << '\n';

    // A const reference provides read-only access
    print(age);

    // ref is an alias to age, so it prints the same value
    print(ref);

    return 0;
}