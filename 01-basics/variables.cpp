#include <iostream>
#include <string>

using std::cout;
using std::string;

int main()
{
    int age = 42;
    double price = 19.99;
    bool active = true;
    char grade = 'A';
    string name = "Novica";

    cout << "Name: " << name << '\n';
    cout << "Age: " << age << '\n';
    cout << "Price: " << price << '\n';
    cout << "Active: " << active << '\n';
    cout << "Grade: " << grade << '\n';

    return 0;
}