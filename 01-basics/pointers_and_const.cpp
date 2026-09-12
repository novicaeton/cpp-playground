#include <iostream>

using std::cout;

int main()
{
    int age = 42;
    int otherAge = 50;

    // Pointer to const data
    const int* ptrToConst = &age;

    // Const pointer to data
    int* const constPtr = &age;

    // Const pointer to const data
    const int* const constPtrToConst = &age;

    cout << "age: " << age << '\n';
    cout << "*ptrToConst: " << *ptrToConst << '\n';
    cout << "*constPtr: " << *constPtr << '\n';
    cout << "*constPtrToConst: " << *constPtrToConst << '\n';

    // Cannot modify age through ptrToConst
    // *ptrToConst = 50;

    // Can modify age through constPtr
    *constPtr = 50;

    // Cannot redirect constPtr to another object
    // constPtr = &otherAge;

    // Cannot modify age through constPtrToConst
    // *constPtrToConst = 60;

    // Cannot redirect constPtrToConst
    // constPtrToConst = &otherAge;

    cout << "age after *constPtr = 50: " << age << '\n';

    return 0;
}