/*
 * [EN] KEY CONCEPTS FROM THE LESSON:
 * 1. What is std::vector?
 *    - Dynamic array that can resize at runtime, unlike standard C arrays (int arr[5]).
 *    - Stores elements in a contiguous block of memory on the Heap.
 * 2. How std::vector grows (Reallocation Overhead):
 *    - When capacity is exceeded, it allocates a new, larger memory block on the Heap.
 *    - Copies (or moves) all existing elements to the new location and frees the old block.
 *    - Low-Latency Engineering Note: Reallocation is an expensive operation.
 * 3. Passing to functions (Pass by Reference):
 *    - Passing by value (void func(std::vector<Vertex> v)) creates a complete copy of the vector.
 *    - Best practice in C++: Always pass by const reference (void func(const std::vector<Vertex>& v)).
 *
 * [SRB] KLJUČNI KONCEPTI IZ LEKCIJE:
 * 1. Šta je std::vector?
 *    - Dinamički niz koji može redefinisati svoju veličinu u run-time-u, za razliku od C niza (int arr[5]).
 *    - Smešta elemente u kontinualnom bloku memorije na Heap-u.
 * 2. Kako std::vector raste (Reallocation Overhead):
 *    - Kada se kapacitet popuni, alocira novi veći blok memorije na Heap-u.
 *    - Kopira (ili pomera) sve postojeće elemente na novu lokaciju i briše stari blok.
 *    - Inženjerska napomena za Low-Latency: Ova re-alokacija je skupa operacija.
 * 3. Prenošenje u funkcije (Pass by Reference):
 *    - Prenošenje po vrednosti (std::vector<Vertex> v) stvara kompletnu kopiju celog vektora.
 *    - Pravilan način u C++-u: Uvek prosleđivati po const referenci (const std::vector<Vertex>& v).
 */

#include <iostream>
#include <vector>

struct Vertex {
    float x, y, z;

    // [EN] Constructor
    // [SRB] Konstruktor
    Vertex(float x, float y, float z)
        : x(x), y(y), z(z) {}

    // [EN] Copy Constructor - tracked to observe unnecessary memory copying
    // [SRB] Konstruktor kopije - prati se da bismo uočili nepotrebno kopiranje u memoriji
    Vertex(const Vertex& vertex)
        : x(vertex.x), y(vertex.y), z(vertex.z) {
        std::cout << "Copied Vertex!\n";
    }

    // [EN] Default Copy Assignment Operator (Required for std::vector::erase)
    // [SRB] Podrazumevani operator dodele (Neophodan za std::vector::erase)
    Vertex& operator=(const Vertex&) = default;
};

// [EN] Best practice: Pass by const reference to avoid copying the entire vector
// [SRB] Dobra praksa: Prosleđivanje po const referenci sprečava kopiranje celog vektora
void PrintVertices(const std::vector<Vertex>& vertices) {
    for (const auto& v : vertices) {
        std::cout << v.x << ", " << v.y << ", " << v.z << '\n';
    }
}

int main() {
    // [EN] Dynamic array initialization on the Heap
    // [SRB] Inicijalizacija dinamičkog niza na Heap-u
    std::vector<Vertex> vertices;

    // [EN] Adding elements (triggers allocation + copy if capacity is exceeded)
    // [SRB] Dodavanje elemenata (izaziva alokaciju i kopiranje ako je kapacitet premašen)
    vertices.push_back(Vertex(1, 2, 3));
    vertices.push_back(Vertex(4, 5, 6));

    std::cout << "--- List of Vertices ---\n";
    PrintVertices(vertices);

    // [EN] Removing element by iterator - O(N) complexity due to memory shift
    // [SRB] Uklanjanje elementa preko iteratora - O(N) složenost zbog pomeranja memorije
    vertices.erase(vertices.begin() + 1);

    // [EN] Clear all elements (capacity remains unchanged)
    // [SRB] Čišćenje svih elemenata (kapacitet ostaje nepromenjen)
    // vertices.clear();

    return 0;
}