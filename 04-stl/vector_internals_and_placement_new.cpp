/*
 * ================================================================================
 * LESSON: STD::VECTOR INTERNALS, CAPACITY & PLACEMENT NEW IN C++
 * [EN] Memory growth strategy, size vs capacity, and object construction via placement new.
 * [SRB] Strategija rasta memorije, veličina vs kapacitet i konstrukcija objekata preko placement new.
 * ================================================================================
 *
 * [EN] KEY CONCEPTS:
 * 1. Internal Structure of std::vector:
 *    - Managed via 3 raw pointers: `begin` (start of array), `end` (last active element), and `capacity_end` (end of allocated heap memory).
 * 2. Size vs Capacity:
 *    - `size()`: Number of currently constructed objects.
 *    - `capacity()`: Total number of objects the current allocated memory can hold before reallocation.
 * 3. Growth Factor & Dynamic Reallocation:
 *    - When `size == capacity`, vector allocates a new block (usually 1.5x or 2x larger), moves/copies old elements, and frees old memory.
 *    - Reallocation invalidates existing pointers/iterators and causes latency spikes!
 * 4. Placement New:
 *    - Constructs an object at an *already allocated* specific memory address: `new (ptr) Object(args)`.
 *    - Eliminates extra copy/move allocations. Basis of `emplace_back()`.
 *
 * [SRB] KLJUČNI KONCEPTI:
 * 1. Unutrašnja struktura std::vector-a:
 *    - Kontroliše se preko 3 sirova pokazivača: `begin` (početak niza), `end` (kraj aktivnih elemenata) i `capacity_end` (kraj alocirane Heap memorije).
 * 2. Veličina (Size) naspram Kapaciteta (Capacity):
 *    - `size()`: Broj trenutno konstruisanih objekata.
 *    - `capacity()`: Ukupan broj objekata koje alocirana memorija može primiti pre realkacije.
 * 3. Faktor rasta i dinamička realokacija:
 *    - Kada je `size == capacity`, vector alocira novi blok (obično 1.5x ili 2x veći), premešta/kopira stare elemente i oslobađa staru memoriju.
 *    - Realokacija poništava postojeće pokazivače/iteratore i uzrokuje kašnjenja (latency spikes)!
 * 4. Placement New:
 *    - Konstruiše objekat na *već alociranoj* konkretnoj memorijskoj adresi: `new (ptr) Object(args)`.
 *    - Eliminiše nepotrebno kopiranje/premeštanje. Osnova za `emplace_back()`.
 */

#include <iostream>
#include <vector>
#include <cstdlib> // std::malloc, std::free
#include <new>     // placement new support

class Item {
public:
    int id;

    Item(int i) : id(i) {
        std::cout << "  [Constructed] Item ID: " << id << '\n';
    }

    ~Item() {
        std::cout << "  [Destroyed] Item ID: " << id << '\n';
    }
};

void DemonstrateCapacityGrowth() {
    std::cout << "=== 1. STD::VECTOR CAPACITY GROWTH / RAST KAPACITETA ===\n";

    std::vector<int> vec;
    std::cout << "Initial size: " << vec.size() << " | Capacity: " << vec.capacity() << '\n';

    // Demonstrating growth jumps / Demonstracija skokova kapaciteta
    for (int i = 1; i <= 5; ++i) {
        vec.push_back(i);
        std::cout << "Pushed " << i << " -> Size: " << vec.size()
                  << " | Capacity: " << vec.capacity() << '\n';
    }

    // Optimization fix for low-latency: reserve() / Optimizacija: reserve()
    std::cout << "\nUsing reserve(100) to prevent reallocations:\n";
    std::vector<int> optimizedVec;
    optimizedVec.reserve(100); // Pre-allocates memory on Heap / Unapred alocira memoriju na Heap-u
    std::cout << "After reserve(100) -> Size: " << optimizedVec.size()
              << " | Capacity: " << optimizedVec.capacity() << "\n\n";
}

void DemonstratePlacementNew() {
    std::cout << "=== 2. PLACEMENT NEW DEMONSTRATION ===\n";

    // Step 1: Allocate raw uninitialized memory (Heap)
    // Korak 1: Alokacija sirove neinicijalizovane memorije
    void* rawMemory = std::malloc(sizeof(Item) * 2);
    std::cout << "Raw memory allocated at address: " << rawMemory << '\n';

    // Cast raw memory to Item pointer / Konverzija u Item pokazivač
    Item* itemBuffer = static_cast<Item*>(rawMemory);

    // Step 2: Use Placement New to construct objects directly in allocated memory
    // Korak 2: Korišćenje Placement New-a za konstrukciju objekata direktno na datoj adresi
    std::cout << "Constructing Item 1 via placement new...\n";
    new (&itemBuffer[0]) Item(101); // Placement new on index 0

    std::cout << "Constructing Item 2 via placement new...\n";
    new (&itemBuffer[1]) Item(102); // Placement new on index 1

    // Step 3: Explicit Destructor Call (Mandatory when using placement new!)
    // Korak 3: Eksplicitno pozivanje destruktora (Obavezno kod placement new-a!)
    std::cout << "\nDestroying items explicitly...\n";
    itemBuffer[0].~Item();
    itemBuffer[1].~Item();

    // Step 4: Free raw memory / Korak 4: Oslobađanje sirove memorije
    std::free(rawMemory);
    std::cout << "Raw memory freed successfully.\n";
}

int main() {
    DemonstrateCapacityGrowth();
    DemonstratePlacementNew();
    return 0;
}