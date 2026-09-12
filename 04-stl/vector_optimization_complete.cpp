/*
 * [EN] KEY CONCEPTS FROM THE LESSON:
 * 1. What is std::vector?
 *    - A dynamic array that can resize at runtime, unlike standard C-style arrays (int arr[5]).
 *    - Stores elements in a contiguous block of memory on the Heap.
 * 2. Reallocation Overhead (How vector grows):
 *    - When vector capacity is exceeded, it allocates a new larger memory block on the Heap.
 *    - Copies (or moves) existing elements to the new location and frees the old memory.
 *    - In Low-Latency engineering: Reallocation is an expensive operation and should be avoided.
 * 3. Pass by Reference:
 *    - Passing vectors by value (std::vector<T>) creates a full copy of the entire vector.
 *    - Always pass by const reference (const std::vector<T>&) to prevent copying.
 * 4. Optimizations (reserve & emplace_back):
 *    - reserve(N): Pre-allocates memory for N elements to eliminate runtime reallocations.
 *    - emplace_back(...): Constructs objects in-place directly in vector memory, avoiding temporary objects.
 * 5. Move Assignment & vector::erase:
 *    - Erasing elements requires shifting memory using operator=.
 *    - Defining a custom move constructor deletes implicit assignment operators, so operator= must be provided.
 *
 * [SRB] KLJUČNI KONCEPTI IZ LEKCIJE:
 * 1. Šta je std::vector?
 *    - Dinamički niz koji može menjati veličinu u run-time-u, za razliku od C niza (int arr[5]).
 *    - Smešta elemente u kontinualnom bloku memorije na Heap-u.
 * 2. Reallocation Overhead (Kako vektor raste):
 *    - Kada se kapacitet popuni, alocira se novi veći blok memorije na Heap-u.
 *    - Kopiraju se (ili pomeraju) postojeći elementi na novu lokaciju i briše stara memorija.
 *    - U Low-Latency inženjerstvu: Re-alokacija je skupa operacija koju treba izbegavati.
 * 3. Prenošenje po referenci:
 *    - Prenošenje po vrednosti (std::vector<T>) kreira kompletnu kopiju celog vektora.
 *    - Uvek prosleđivati po const referenci (const std::vector<T>&) da se spreči kopiranje.
 * 4. Optimizacije (reserve & emplace_back):
 *    - reserve(N): Unapred alocira memoriju za N elemenata čime se eliminišu re-alokacije.
 *    - emplace_back(...): Konstruiše objekte direktno u memoriji vektora bez privremenih objekata.
 * 5. Move Assignment & vector::erase:
 *    - Brisanje elemenata zahteva pomeranje u memoriji preko operatora dodele (operator=).
 *    - Definisanjem ručnog move konstruktora gube se podrazumevani operatori dodele, pa se operator= mora redefinisati.
 */
#include <iostream>
#include <vector>

struct Vertex {
    float x, y, z;

    // [EN] Constructor
    // [SRB] Konstruktor
    Vertex(float x, float y, float z)
        : x(x), y(y), z(z) {
        std::cout << "Constructed!\n";
    }

    // [EN] Copy Constructor
    // [SRB] Konstruktor kopije
    Vertex(const Vertex& vertex)
        : x(vertex.x), y(vertex.y), z(vertex.z) {
        std::cout << "Copied Vertex!\n";
    }

    // [EN] Move Constructor
    // [SRB] Move konstruktor
    Vertex(Vertex&& vertex) noexcept
        : x(vertex.x), y(vertex.y), z(vertex.z) {
        std::cout << "Moved Vertex!\n";
    }

    // [EN] Move Assignment Operator (Required for std::vector::erase / shift operations)
    // [SRB] Move Operator Dodele (Neophodan za std::vector::erase / pomeranje u memoriji)
    Vertex& operator=(Vertex&& other) noexcept {
        std::cout << "Move Assigned Vertex!\n";
        if (this != &other) {
            x = other.x;
            y = other.y;
            z = other.z;
        }
        return *this;
    }

    // [EN] Destructor
    // [SRB] Destruktor
    ~Vertex() {
        std::cout << "Destroyed Vertex!\n";
    }
};

// [EN] Best practice: Pass by const reference to avoid copying the entire vector
// [SRB] Dobra praksa: Prosleđivanje po const referenci sprečava kopiranje celog vektora
void PrintVertices(const std::vector<Vertex>& vertices) {
    for (const auto& v : vertices) {
        std::cout << v.x << ", " << v.y << ", " << v.z << '\n';
    }
}

int main() {
    std::cout << "=== UNOPTIMIZED APPROACH (Neoptimizovan pristup) ===\n";
    {
        std::vector<Vertex> vertices;

        vertices.push_back(Vertex(1, 2, 3));
        vertices.push_back(Vertex(4, 5, 6));

        std::cout << "--- List of Vertices ---\n";
        PrintVertices(vertices);

        // [EN] Removing element by iterator - O(N) complexity (calls move assignment)
        // [SRB] Uklanjanje elementa preko iteratora - O(N) složenost (poziva move dodelu)
        vertices.erase(vertices.begin() + 1);
    }

    std::cout << "\n=== OPTIMIZED APPROACH (Optimizovan pristup) ===\n";
    {
        std::vector<Vertex> vertices;

        // [EN] 1. Pre-allocate Heap memory for 2 elements (0 re-allocations)
        // [SRB] 1. Unapred alociraj memoriju na Heap-u za 2 elementa (0 re-alokacija)
        vertices.reserve(2);

        // [EN] 2. Construct objects in-place directly inside vector memory
        // [SRB] 2. Konstruiši objekte direktno unutar memorije vektora
        vertices.emplace_back(1, 2, 3);
        vertices.emplace_back(4, 5, 6);

        std::cout << "--- List of Vertices (Optimized) ---\n";
        PrintVertices(vertices);
    }

    return 0;
}