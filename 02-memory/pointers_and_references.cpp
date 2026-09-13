/*
* ================================================================================
 * LESSON: POINTERS & REFERENCES IN MODERN C++
 * [EN] Memory management fundamentals, address manipulation, and passing semantics.
 * [SRB] Osnove upravljanja memorijom, manipulacija adresama i semantika prenošenja.
 * ================================================================================
 *
 * [EN] KEY CONCEPTS FROM THE LESSON:
 * 1. What is a Pointer?
 *    - A variable that holds a memory address of another variable.
 *    - Size is fixed depending on architecture: 8 bytes (64-bit) or 4 bytes (32-bit).
 *    - Address operator `&`: Retrieves the memory location of a variable.
 *    - Dereference operator `*`: Accesses/modifies the value stored at the address.
 * 2. What is a Reference?
 *    - An alias for an existing variable. It MUST be initialized when declared and CANNOT be reassigned to point to another variable.
 *    - Syntactically cleaner than pointers (no need for explicit `*` or `&` inside function bodies).
 * 3. Passing Semantics (Interview Classic):
 *    - Pass-by-Value: Creates a full copy. Expensive for large structures.
 *    - Pass-by-Pointer: Passes address. Allows nullptr/optional semantics and reassignment.
 *    - Pass-by-Const-Reference (`const T&`): ZERO copy overhead + guarantees input immutability. Preferred default in low-latency C++.
 *
 * [SRB] KLJUČNI KONCEPTI IZ LEKCIJE:
 * 1. Šta je Pokazivač (Pointer)?
 *    - Promenljiva koja drži memorijsku adresu druge promenljive.
 *    - Veličina je fiksna u zavisnosti od arhitekture: 8 bajtova (64-bit) ili 4 bajta (32-bit).
 *    - Operators adrese `&`: Dobija memorijsku lokaciju promenljive.
 *    - Dereferencirajući operator `*`: Pristupa/menja vrednost na datoj adresi.
 * 2. Šta je Referenca (Reference)?
 *    - Alias (drugo ime) za već postojeću promenljivu. MORA se inicijalizovati pri deklaraciji i NE MOŽE se preusmeriti na drugu promenljivu.
 *    - Sintaksno čistija od pokazivača (nema potrebe za eksplicitnim `*` ili `&` u telu funkcije).
 * 3. Semantike prenošenja u funkcije (Klasično pitanje za intervju):
 *    - Pass-by-Value: Pravi kompletnu kopiju. Skupo za velike objekte.
 *    - Pass-by-Pointer: Prenosi adresu. Dozvoljava nullptr/opcione parametre i ponovno usmeravanje.
 *    - Pass-by-Const-Reference (`const T&`): NULA overhead-a pri kopiranju + garantuje neizmenjivost. Najčešći izbor u low-latency C++-u.
 */
#include <iostream>
#include <string>

struct HeavyData {
    std::string name;
    int payload[1000]{}; // Large structure to demonstrate copy overhead / Velika struktura za demonstraciju kopiranja
};

// [EN] Pass-by-Value: Creates a full deep copy (Slow)
// [SRB] Pass-by-Value: Pravi potpunu duboku kopiju (Sporo)
static void ProcessByValue(HeavyData data) {
    data.name = "Modified Inside Value";
}

// [EN] Pass-by-Pointer: Passes address. Requires nullptr check.
// [SRB] Pass-by-Pointer: Prenosi adresu. Zahteva proveru na nullptr.
static void ProcessByPointer(HeavyData* data) {
    if (data != nullptr) {
        data->name = "Modified Inside Pointer"; // Same as (*data).name
    }
}

// [EN] Pass-by-Reference: Passes alias. Cannot be null. Clean syntax.
// [SRB] Pass-by-Reference: Prenosi alias. Ne može biti null. Čista sintaksa.
static void ProcessByReference(HeavyData& data) {
    data.name = "Modified Inside Reference";
}

// [EN] Pass-by-Const-Reference: Zero copy + Immutable guarantee (Best practice for low-latency read-only operations)
// [SRB] Pass-by-Const-Reference: Nula kopiranja + garancija neizmenjivosti (Najbolja praksa za read-only operacije)
static void PrintData(const HeavyData& data) {
    std::cout << "[Read Only] Data Name: " << data.name << '\n';
    // data.name = "Test"; // [EN] Compile Error! / [SRB] Greška pri kompajliranju!
}
int main() {
    std::cout << "=== 1. POINTER BASICS / OSNOVE POKAZIVAČA ===\n";
    {
        int var = 42;
        int* ptr = &var; // ptr holds the address of var / ptr drži adresu od var

        std::cout << "var value: " << var << '\n';
        std::cout << "var address (&var): " << &var << '\n';
        std::cout << "ptr value (holds address): " << ptr << '\n';
        std::cout << "Dereferenced ptr (*ptr): " << *ptr << '\n';
        std::cout << "Pointer size in memory: " << sizeof(ptr) << " bytes\n\n";

        // Modifying var through pointer / Izmena var preko pokazivača
        *ptr = 99;
        std::cout << "Updated var through *ptr: " << var << "\n\n";
    }

    std::cout << "=== 2. REFERENCE BASICS / OSNOVE REFERENCI ===\n";
    {
        int original = 100;
        int& ref = original; // ref is an alias for original / ref je alias za original

        std::cout << "original: " << original << " | ref: " << ref << '\n';
        ref = 200;
        std::cout << "After modifying ref -> original is now: " << original << '\n';
        std::cout << "Address of original: " << &original << " | Address of ref: " << &ref << " (Identical!)\n\n";
    }

    std::cout << "=== 3. FUNCTION PASSING COMPARISON / POREĐENJE PRENOŠENJA U FUNKCIJE ===\n";
    {
        HeavyData myData;
        myData.name = "Initial Name";

        // 1. Value
        ProcessByValue(myData);
        std::cout << "After ProcessByValue: " << myData.name << " (Unchanged due to value copy)\n";

        // 2. Pointer
        ProcessByPointer(&myData);
        std::cout << "After ProcessByPointer: " << myData.name << " (Changed directly)\n";

        // 3. Reference
        ProcessByReference(myData);
        std::cout << "After ProcessByReference: " << myData.name << " (Changed directly)\n";

        // 4. Const Reference
        PrintData(myData);
    }

    return 0;
}