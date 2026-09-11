#include <iostream>

using std::cout;

static void incrementByReference(int& value)
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

    // Changing the reference changes the original variable
    ref = 50;

    cout << "age after ref = 50: " << age << '\n';

    // Pass by reference allows the function to modify the original variable
    incrementByReference(age);

    cout << "age after increment: " << age << '\n';

    // A const reference provides read-only access
    print(age);

    // ref is an alias to age, so it prints the same value
    print(ref);

    return 0;
}