#include <iostream>

using std::cout;

int main()
{
    int age = 42;

    // Reference: another name for the same variable
    // A reference is another name, or alias, for an existing object.
    int& ref = age;

    // Pointer: stores the address of a variable
    int* ptr = &age;
    int* ptr2 = nullptr, not_pt3;
    int* ptr3;

    cout << "age: " << age << '\n';
    cout << "ref: " << ref << '\n';
    cout << "ptr: " << ptr << '\n';
    cout << "*ptr: " << *ptr << '\n';

    // Modify the original value through the reference
    ref = 50;

    cout << "age after ref = 50: " << age << '\n';

    // Modify the original value through the pointer
    *ptr = 60;

    cout << "age after *ptr = 60: " << age << '\n';

    // Print a null pointer
    cout << "*ptr2: " << ptr2 << '\n';

    // Print the value of an uninitialized int - undefined behavior
    cout << "not_pt3: " << not_pt3 << '\n';

    // Print the uninitialized pointer - undefined behavior
    cout << "ptr3: " << ptr3 << '\n';

    // Dereference the uninitialized pointer - undefined behavior
    cout << "*ptr3: " << *ptr3 << '\n';

    return 0;
}