/*
 * ================================================================================
 * LESSON: STATIC ARRAYS IN MODERN C++ (std::array)
 * [EN] Zero-allocation stack arrays, cache locality, and C-array wrapper mechanics.
 * [SRB] Statički nizovi na steku bez alokacije, cache lokalnost i mehanika C-niz omotača.
 * ================================================================================
 *
 * [EN] KEY CONCEPTS FROM THE LESSON:
 * 1. What is std::array?
 *    - A thin wrapper around a C-style fixed-size array `T[N]`.
 *    - Allocation lives directly on the STACK (Zero heap allocation, zero GC overhead).
 *    - Size `N` MUST be a compile-time constant.
 * 2. Why prefer std::array over raw C-arrays (`T arr[N]`)?
 *    - Knows its own size via `.size()`.
 *    - Does NOT implicitly decay to a raw pointer when passed into functions (retains value semantics).
 *    - Provides bound-checked access via `.at(index)` and fast access via `operator[]`.
 *    - Compatible with STL algorithms (`std::sort`, `std::find`, etc.).
 * 3. Performance & Low-Latency Impact:
 *    - 100% Cache Locality (elements stored contiguously on the Stack).
 *    - Zero pointer indirection (unlike `std::vector` which holds a heap pointer).
 *
 * [SRB] KLJUČNI KONCEPTI IZ LEKCIJE:
 * 1. Šta je std::array?
 *    - Tani omotač (thin wrapper) oko C-stil niza fiksne veličine `T[N]`.
 *    - Alokacija ide direktno na STEK (Nula alokacije na Heap-u, nula GC pauza).
 *    - Veličina `N` MORA biti poznata u vreme kompajliranja (compile-time konstanta).
 * 2. Zašto birati std::array umesto C-stil niza (`T arr[N]`)?
 *    - Zna svoju veličinu preko `.size()`.
 *    - Ne degradira automatski u sirovi pokazivač pri slanju u funkciju (zadržava semantiku vrednosti).
 *    - Pruža proveru granica preko `.at(index)` i brz pristup preko `operator[]`.
 *    - Potpuno kompatibilan sa STL algoritmima (`std::sort`, `std::find`).
 * 3. Uticaj na performanse (Low-Latency):
 *    - 100% Cache Lokalnost (elementi su poređani sukcesivno na steku).
 *    - Nula indirektnog pristupa preko pokazivača (za razliku od `std::vector`-a koji drži pokazivač ka Heap-u).
 */

#include <iostream>
#include <array>
#include <algorithm> // std::sort

// [EN] Pass by Const Reference to avoid copying the entire stack block
// [SRB] Prenošenje preko Const Reference da se izbegne kopiranje celog bloka sa steka
template <size_t N>
void PrintArray(const std::array<int, N>& arr) {
    std::cout << "Array contents (size " << arr.size() << "): [ ";
    for (const auto& elem : arr) {
        std::cout << elem << " ";
    }
    std::cout << "]\n";
}

int main() {
    std::cout << "=== 1. CREATION & STACK ALLOCATION / KREIRANJE I STEK ALOKACIJA ===\n";
    
    // Compile-time size definition / Definicija veličine u vreme kompajliranja
    constexpr size_t ARRAY_SIZE = 5;
    std::array<int, ARRAY_SIZE> data = { 40, 10, 50, 20, 30 };

    std::cout << "Size of std::array object in memory: " << sizeof(data) << " bytes\n";
    std::cout << "Size of underlying elements (5 * 4 bytes): " << 5 * sizeof(int) << " bytes\n";
    std::cout << "(Proves std::array has ZERO memory overhead over raw C-arrays!)\n\n";

    std::cout << "=== 2. ELEMENT ACCESS / PRISTUP ELEMENTIMA ===\n";
    std::cout << "Fast unsafe access (data[0]): " << data[0] << '\n';
    std::cout << "Safe bound-checked access (data.at(2)): " << data.at(2) << '\n';
    
    // Direct pointer to raw memory for C-API compatibility / Direktan pokazivač na sirovu memoriju
    int* rawPtr = data.data();
    std::cout << "Raw memory address (.data()): " << rawPtr << "\n\n";

    try {
        // Un-commenting this will throw std::out_of_range exception:
        // std::cout << data.at(10);
    } catch (const std::out_of_range& e) {
        std::cout << "Caught exception: " << e.what() << '\n';
    }

    std::cout << "=== 3. STL ALGORITHMS INTEGRATION / INTEGRACIJA SA STL ALGORITMIMA ===\n";
    std::cout << "Before sort: ";
    PrintArray(data);

    // Sorting std::array in-place / Sortiranje na llicu mesta
    std::sort(data.begin(), data.end());

    std::cout << "After sort:  ";
    PrintArray(data);

    return 0;
}