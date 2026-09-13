/*
 * ================================================================================
 * LESSON: CONST CORRECTNESS IN MODERN C++
 * [EN] Const variables, const pointers, and const member functions.
 * [SRB] Konstante promenljive, konstanti pokazivači i konstante metode klasa.
 * ================================================================================
 *
 * [EN] KEY CONCEPTS (from The Cherno's "CONST in C++"):
 * 1. Read pointers backwards:
 *    - `const int* a`  ==> "a is a pointer to an int that is CONSTANT." (Data cannot change)
 *    - `int* const a`  ==> "a is a CONSTANT pointer to an int." (Pointer address cannot change)
 *    - `const int* const a` ==> "a is a CONSTANT pointer to a CONSTANT int."
 * 2. Const Member Functions:
 *    - Appending `const` after a function declaration (e.g. `int GetX() const`) means
 *      the method promises NOT to modify any class member variables.
 *    - Const instances of a class can ONLY call const member functions.
 *
 * [SRB] KLJUČNI KONCEPTI (iz The Cherno videa "CONST in C++"):
 * 1. Čitanje pokazivača unazad:
 *    - `const int* a`  ==> "a je pokazivač na int koji je KONSTANTAN." (Vrednost se ne menja)
 *    - `int* const a`  ==> "a je KONSTANTAN pokazivač na int." (Adresa se ne menja)
 *    - `const int* const a` ==> "a je KONSTANTAN pokazivač na KONSTANTNI int."
 * 2. Konstantne metode klasa:
 *    - Dodavanje `const` na kraj metode (npr. `int GetX() const`) garantuje da metoda
 *      neće menjati članove klase.
 *    - Konstantne instance klase mogu pozivati ISKLJUČIVO `const` metode.
 */

#include <iostream>

class Entity {
private:
    int m_X{ 0 };
    int m_Y{ 0 };
    mutable int m_DebugCount{ 0 }; // 'mutable' allows modification even in const methods

public:
    Entity(int x, int y) : m_X(x), m_Y(y) {}

    // Const method: Guaranteeing it will not modify m_X or m_Y
    int GetX() const {
        m_DebugCount++; // Allowed because of 'mutable'
        return m_X;
    }

    void SetX(int x) {
        m_X = x;
    }
};

void PrintEntity(const Entity& e) {
    // Passes by const reference to avoid copy and prevent modification
    std::cout << "Entity X: " << e.GetX() << '\n';
}

int main() {
    std::cout << "=== 1. CONST POINTER DEMO ===\n";
    int value = 5;
    int otherValue = 10;

    // Pointer to const data / Pokazivač na konstantne podatke
    const int* ptr1 = &value;
    // *ptr1 = 6; // ERROR: Cannot modify value!
    ptr1 = &otherValue; // OK: Can change memory address

    // Const pointer / Konstantan pokazivač
    int* const ptr2 = &value;
    *ptr2 = 6; // OK: Can modify value
    // ptr2 = &otherValue; // ERROR: Cannot change address!

    std::cout << "Updated value: " << value << "\n\n";

    std::cout << "=== 2. CONST CLASS METHODS ===\n";
    Entity e(10, 20);
    PrintEntity(e);

    return 0;
}