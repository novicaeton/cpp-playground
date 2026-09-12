/*
 * [EN] KEY CONCEPTS FROM THE LESSON:
 * 1. What is a Raw Array?
 *    - A contiguous block of memory storing elements of the same type.
 *    - Memory overhead is zero; element access via [] is O(1).
 * 2. Stack vs. Heap Allocation:
 *    - Stack: `int arr[5];` - Fixed size at compile-time, ultra-fast allocation, automatically cleaned up.
 *    - Heap: `int* arr = new int[5];` - Dynamic lifetime, must be manually freed with `delete[]`.
 * 3. Pointer Arithmetic & Memory Layout:
 *    - Elements are stored sequentially in memory (e.g., 4 bytes apart for 32-bit integers).
 *    - Expression `*(arr + i)` is strictly equivalent to `arr[i]`.
 * 4. Pointer Decay & Array Size:
 *    - Passing a raw array to a function decays it into a raw pointer (loses size information).
 *    - Use `sizeof(arr) / sizeof(type)` on Stack arrays, or prefer std::array / std::vector.
 *
 * [SRB] KLJUČNI KONCEPTI IZ LEKCIJE:
 * 1. Šta je sirovi niz (Raw Array)?
 *    - Kontinualni (neprekinuti) blok memorije koji drži elemente istog tipa.
 *    - Nema memorijskog overhead-a; pristup elementu preko [] je O(1).
 * 2. Alokacija na Stack-u naspram Heap-a:
 *    - Stack: `int arr[5];` - Fiksna veličina u compile-time-u, ekstremno brza alokacija, automatski se čisti.
 *    - Heap: `int* arr = new int[5];` - Dinamički životni vek, mora se ručno osloboditi preko `delete[]`.
 * 3. Pokazivačka aritmetika i raspored u memoriji:
 *    - Elementi su poređani sekvencijalno u memoriji (npr. razmak od 4 bajta za 32-bitne celobrojne tipove).
 *    - Izraz `*(arr + i)` je potpuno identičan sintaksi `arr[i]`.
 * 4. Pointer Decay i veličina niza:
 *    - Prenošenje sirovog niza u funkciju ga degradira u običan pokazivač (gubi se informacija o veličini).
 *    - Koristite `sizeof(arr) / sizeof(tip)` za nizove na Stack-u, ili u modernom C++-u prednost dajte std::array / std::vector.
 */

#include <iostream>
#include <array>

// [EN] Function demonstrates pointer decay (array loses size info)
// [SRB] Funkcija demonstrira "pointer decay" (niz gubi informaciju o veličini)
void PrintRawArray(const int* array, size_t count) {
    std::cout << "--- Raw Array Memory Dump ---\n";
    for (size_t i = 0; i < count; i++) {
        // [EN] Memory address of each contiguous element
        // [SRB] Memorijska adresa svakog sukcesivnog elementa
        std::cout << "Element [" << i << "] at address: " << (array + i)
                  << " | Value: " << *(array + i) << '\n';
    }
}

int main() {
    std::cout << "=== 1. STACK ALLOCATED ARRAY ===\n";
    {
        // [EN] Stack allocation (Fixed size, continuous memory block)
        // [SRB] Alokacija na Stack-u (Fiksna veličina, neprekinuti blok memorije)
        int example[5] = { 10, 20, 30, 40, 50 };

        // [EN] Calculate size of array on stack
        // [SRB] Izračunavanje veličine niza sa Stack-a
        size_t count = sizeof(example) / sizeof(int);
        std::cout << "[EN] Stack Array Size: " << count << " elements (" << sizeof(example) << " bytes)\n";
        std::cout << "[SRB] Veličina Stack niza: " << count << " elemenata (" << sizeof(example) << " bajtova)\n\n";

        PrintRawArray(example, count);
    }

    std::cout << "\n=== 2. HEAP ALLOCATED ARRAY ===\n";
    {
        // [EN] Heap allocation (Dynamic memory, lifetime controlled by programmer)
        // [SRB] Alokacija na Heap-u (Dinamička memorija, programer kontroliše životni vek)
        int* heapExample = new int[5];

        for (int i = 0; i < 5; i++) {
            heapExample[i] = (i + 1) * 100;
        }

        PrintRawArray(heapExample, 5);

        // [EN] CRITICAL: Always clean up Heap allocated arrays with delete[]
        // [SRB] KLJUČNO: Uvek oslobodite niz alociran na Heap-u koristeći delete[]
        delete[] heapExample;
        std::cout << "\n[EN] Heap memory freed with delete[]\n";
        std::cout << "[SRB] Memorija na Heap-u oslobođena sa delete[]\n";
    }

    std::cout << "\n=== 3. POINTER ARITHMETIC DEMO ===\n";
    {
        int arr[3] = { 5, 15, 25 };
        int* ptr = arr; // [EN] Points to first element / [SRB] Pokazuje na prvi element

        std::cout << "ptr[1] value: " << ptr[1] << '\n';
        std::cout << "*(ptr + 1) value: " << *(ptr + 1) << '\n';

        // [EN] Cast to byte pointer to inspect byte offset manually
        // [SRB] Konverzija u bajt pokazivač radi ručnog uvida u bajtne pomake
        char* bytePtr = (char*)arr;
        int* secondElement = (int*)(bytePtr + sizeof(int)); // Shift by 4 bytes
        std::cout << "Accessing 2nd element via 4-byte offset: " << *secondElement << '\n';
    }

    return 0;
}