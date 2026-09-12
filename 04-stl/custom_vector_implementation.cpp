/*
 * [EN] KEY CONCEPTS FROM THE LESSON:
 * 1. Custom Vector Architecture:
 *    - Manages a raw pointer to a heap-allocated buffer (T* m_Data), current size, and capacity.
 * 2. Dynamic Memory Growth (Reallocation):
 *    - When m_Size reaches m_Capacity, a new larger buffer is allocated (e.g. 2x growth strategy).
 *    - Existing elements are moved to the new location, and the old memory block is freed.
 * 3. Constructing Elements In-Place (emplace_back):
 *    - Uses variadic templates (Args&&...) and placement new / move semantics to build objects directly inside memory.
 * 4. Subscript Operator & Memory Management:
 *    - Implements operator[] for direct $O(1)$ array access.
 *    - Destructor ensures proper deletion of allocated heap memory.
 *
 * [SRB] KLJUČNI KONCEPTI IZ LEKCIJE:
 * 1. Arhitektura sopstvenog vektora:
 *    - Upravlja sirovim pokazivačem na bafer na Heap-u (T* m_Data), trenutnom veličinom i kapacitetom.
 * 2. Dinamičko proširenje memorije (Re-alokacija):
 *    - Kada m_Size dostigne m_Capacity, alocira se novi veći bafer (npr. strategija udvostručavanja kapaciteta).
 *    - Postojeći elementi se pomeraju na novu lokaciju, a stari blok memorije se oslobađa.
 *    - U Low-Latency sistemima ovo je ključno razumeti jer re-alokacija nosi vremenski overhead.
 * 3. Konstrukcija objekata u samoj memoriji (emplace_back):
 *    - Koristi variadic template-e (Args&&...) i move semantiku za direktnu konstrukciju unutar alociranog bafera.
 * 4. Operatori pristupa i upravljanje memorijom:
 *    - Implementira operator[] za direktan $O(1)$ pristup elementima.
 *    - Destruktor osigurava pravilno oslobađanje alocirane memorije na Heap-u.
 */

#include <iostream>
#include <utility>

template <typename T>
class Vector {
private:
    T* m_Data = nullptr;
    size_t m_Size = 0;
    size_t m_Capacity = 0;

    // [EN] Internal function to reallocate memory when capacity is full
    // [SRB] Interna funkcija za re-alokaciju memorije kada se kapacitet popuni
    void ReAlloc(size_t newCapacity) {
        // [EN] 1. Allocate new block of memory on the Heap
        // [SRB] 1. Alociraj novi blok memorije na Heap-u
        T* newBlock = new T[newCapacity];

        // [EN] 2. Move existing elements if new size is smaller than old size
        // [SRB] 2. Pomeri postojeće elemente u novi blok
        if (newCapacity < m_Size) {
            m_Size = newCapacity;
        }

        for (size_t i = 0; i < m_Size; i++) {
            newBlock[i] = std::move(m_Data[i]);
        }

        // [EN] 3. Delete old memory block and reassign pointers
        // [SRB] 3. Obriši stari blok memorije i preusmeri pokazivač
        delete[] m_Data;
        m_Data = newBlock;
        m_Capacity = newCapacity;
    }

public:
    Vector() {
        // [EN] Initial allocation for 2 elements
        // [SRB] Inicijalna alokacija za 2 elementa
        ReAlloc(2);
    }

    ~Vector() {
        // [EN] Clean up heap memory
        // [SRB] Oslobodi memoriju sa Heap-a
        delete[] m_Data;
    }

    // [EN] Push element by copying
    // [SRB] Dodaj element kopiranjem
    void PushBack(const T& element) {
        if (m_Size >= m_Capacity) {
            ReAlloc(m_Capacity + m_Capacity / 2); // [EN] Grow capacity by 1.5x / [SRB] Povećaj kapacitet za 1.5x
        }

        m_Data[m_Size] = element;
        m_Size++;
    }

    // [EN] Push element by moving (rvalue reference)
    // [SRB] Dodaj element pomeranjem (rvalue referenca)
    void PushBack(T&& element) {
        if (m_Size >= m_Capacity) {
            ReAlloc(m_Capacity + m_Capacity / 2);
        }

        m_Data[m_Size] = std::move(element);
        m_Size++;
    }

    // [EN] Construct object directly in vector memory (EmplaceBack)
    // [SRB] Konstruiši objekat direktno u memoriji vektora (EmplaceBack)
    template <typename... Args>
    T& EmplaceBack(Args&&... args) {
        if (m_Size >= m_Capacity) {
            ReAlloc(m_Capacity + m_Capacity / 2);
        }

        m_Data[m_Size] = T(std::forward<Args>(args)...);
        return m_Data[m_Size++];
    }

    // [EN] Array subscript operator (non-const)
    // [SRB] Operator [] za pristup elementu (non-const)
    T& operator[](size_t index) {
        return m_Data[index];
    }

    // [EN] Array subscript operator (const)
    // [SRB] Operator [] za pristup elementu (const)
    const T& operator[](size_t index) const {
        return m_Data[index];
    }

    size_t Size() const { return m_Size; }
    size_t Capacity() const { return m_Capacity; }
};

struct Vector3 {
    float x = 0, y = 0, z = 0;

    Vector3() = default;
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vector3(const Vector3& other)
        : x(other.x), y(other.y), z(other.z) {
        std::cout << "[EN] Copied Vector3! / [SRB] Kopiran Vector3!\n";
    }

    Vector3(Vector3&& other) noexcept
        : x(other.x), y(other.y), z(other.z) {
        std::cout << "[EN] Moved Vector3! / [SRB] Pomeren Vector3!\n";
    }

    Vector3& operator=(const Vector3& other) {
        std::cout << "[EN] Copy Assigned Vector3! / [SRB] Copy dodela Vector3!\n";
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }

    Vector3& operator=(Vector3&& other) noexcept {
        std::cout << "[EN] Move Assigned Vector3! / [SRB] Move dodela Vector3!\n";
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }
};

int main() {
    std::cout << "=== CUSTOM VECTOR DEMO ===\n";

    Vector<Vector3> vector;

    std::cout << "\n--- Adding elements with EmplaceBack ---\n";
    vector.EmplaceBack(1.0f, 2.0f, 3.0f);
    vector.EmplaceBack(4.0f, 5.0f, 6.0f);
    vector.EmplaceBack(7.0f, 8.0f, 9.0f); // [EN] Triggers ReAlloc! / [SRB] Pokreće ReAlloc!

    std::cout << "\n--- Vector contents / Sadržaj vektora ---\n";
    for (size_t i = 0; i < vector.Size(); i++) {
        std::cout << "Element " << i << ": "
                  << vector[i].x << ", " << vector[i].y << ", " << vector[i].z << '\n';
    }

    std::cout << "\n[EN] Final Size: " << vector.Size() << " | Capacity: " << vector.Capacity() << '\n';
    std::cout << "[SRB] Konačna veličina: " << vector.Size() << " | Kapacitet: " << vector.Capacity() << '\n';

    return 0;
}