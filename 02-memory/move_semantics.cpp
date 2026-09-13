/*
 * ================================================================================
 * LESSON: MOVE SEMANTICS & RVALUE REFERENCES IN MODERN C++ (std::move)
 * [EN] Resource theft, avoiding heap reallocations, and pass-by-rvalue semantics.
 * [SRB] Krađa resursa, izbegavanje realokacija na Heap-u i semantika prenošenja rvalue referenci.
 * ================================================================================
 *
 * --------------------------------------------------------------------------------
 * THEORY & CONCEPTS / TEORIJA I KONCEPTI
 * --------------------------------------------------------------------------------
 * [EN] 1. WHAT ARE LVALUE AND RVALUE?
 *    - Lvalue (Left Value): An object that has a recognizable name and an accessible
 *      memory address (you can take its address with `&`). Lives beyond a single expression.
 *      Example: `int x = 10;` (`x` is an lvalue).
 *    - Rvalue (Right Value): A temporary value/object that does NOT have a name or a
 *      persistent memory address. It "dies" immediately after the expression evaluation.
 *      Example: `10`, `x + 5`, or a temporary returned by a function by value.
 *
 * [SRB] 1. ŠTA SU LVALUE I RVALUE?
 *    - Lvalue (Left Value): Objekat koji ima prepoznatljivo ime i trajnu memorijsku
 *      adresu (možeš mu uzeti adresu pomoću `&`). Živi i nakon završetka izraza.
 *      Primer: `int x = 10;` (`x` je lvalue).
 *    - Rvalue (Right Value): Privremena vrednost/objekat koji NEMA ime niti trajnu
 *      memorijsku adresu. "Umire" odmah nakon izvršavanja tog izraza.
 *      Primer: `10`, `x + 5`, ili privremeni objekat koji funkcija vraća po vrednosti.
 *
 * --------------------------------------------------------------------------------
 * [EN] 2. ANALOGY: COPY VS. MOVE
 *    - Copy: Imagine buying brand-new furniture identical to your old furniture and
 *      placing it into a new house. (Requires allocating new Heap memory and copying bytes).
 *    - Move: Taking the existing furniture directly from your old house and putting it
 *      into the new one, leaving the old house empty. (Fast O(1) pointer redirection).
 *
 * [SRB] 2. ANALOGIJA: KOPIRANJE VS. PREMEŠTANJE (MOVE)
 *    - Kopiranje (Copy): Kupovina potpuno novog nameštaja identičnog starom i njegovo
 *      postavljanje u novu kuću. (Zahteva alokaciju nove Heap memorije i kopiranje svake vrednosti).
 *    - Premeštanje (Move): Uzimanje postojećeg nameštaja direktno iz stare kuće i njegovo
 *      prebacivanje u novu, pri čemu stara kuća ostaje prazna. (Brza O(1) operacija preusmeravanja pokazivača).
 *
 * --------------------------------------------------------------------------------
 * [EN] 3. RVALUE REFERENCE (T&&) & std::move
 *    - Rvalue Reference (`T&&`): Introduced in C++11, a type of reference that binds
 *      exclusively to temporary objects (rvalues).
 *    - `std::move`: Does NOT actually move anything at runtime! It is merely a compile-time
 *      static_cast that turns an lvalue into an rvalue (`static_cast<T&&>(var)`), signaling
 *      to the compiler: "You are allowed to steal this object's resources."
 *
 * [SRB] 3. RVALUE REFERENCA (T&&) I std::move
 *    - Rvalue Referenca (`T&&`): Inovacija u C++11 standardu, tip reference koji se vezuje
 *      isključivo za privremene objekte (rvalues).
 *    - `std::move`: U izvršavanju (runtime) zapravo ne pomera ništa! To je samo cast
 *      u vreme kompajliranja koji pretvara lvalue u rvalue (`static_cast<T&&>(var)`),
 *      dajući signal kompajleru: "Smeš da ukradeš resurse iz ovog objekta."
 * ================================================================================
 */
#include <iostream>
#include <utility> // std::move
#include <cstring> // std::memcpy

class DynamicBuffer {
private:
    char* m_Data{ nullptr };
    size_t m_Size{ 0 };

public:
    // 1. Constructor / Konstruktor
    DynamicBuffer(size_t size) : m_Size(size) {
        m_Data = new char[m_Size];
        std::cout << "[Allocated] Buffer size: " << m_Size << " bytes at " << (void*)m_Data << '\n';
    }

    // 2. Destructor / Destruktor
    ~DynamicBuffer() {
        if (m_Data) {
            std::cout << "[Freed] Buffer at " << (void*)m_Data << '\n';
            delete[] m_Data;
        }
    }

    // 3. COPY CONSTRUCTOR (Expensive O(N) allocation)
    // [SRB] Konstruktor kopije: Alocira novu memoriju i kopira sve bajtove
    DynamicBuffer(const DynamicBuffer& other) : m_Size(other.m_Size) {
        std::cout << "[COPY CONSTRUCTOR] Slow heap allocation and copy!\n";
        m_Data = new char[m_Size];
        std::memcpy(m_Data, other.m_Data, m_Size);
    }

    // 4. MOVE CONSTRUCTOR (Fast O(1) pointer transfer)
    // [SRB] Konstruktor premeštanja: Preuzima (krade) pokazivač i poništava izvorni objekat
    DynamicBuffer(DynamicBuffer&& other) noexcept
        : m_Data(other.m_Data), m_Size(other.m_Size) {
        std::cout << "[MOVE CONSTRUCTOR] Fast O(1) pointer transfer!\n";

        // CRITICAL: Leave source object in a valid empty state
        // KLJUČNO: Ostaviti izvorni objekat u validnom praznom stanju
        other.m_Data = nullptr;
        other.m_Size = 0;
    }
};

int main() {
    std::cout << "=== 1. COPY SEMANTICS (Slow) ===\n";
    DynamicBuffer buf1(1024); // Alocira 1KB
    DynamicBuffer buf2 = buf1; // Poziva Copy Constructor (skupo)

    std::cout << "\n=== 2. MOVE SEMANTICS (Fast) ===\n";
    // std::move pretvara 'buf1' (lvalue) u rvalue i omogućava krađu memorije
    DynamicBuffer buf3 = std::move(buf1);

    return 0;
}