/*
 * [EN] KEY CONCEPTS FROM THE LESSON:
 * 1. Smart Pointers Overview:
 *    - Wrappers around raw pointers that automate memory allocation and deallocation on the Heap (RAII).
 *    - Eliminates explicit calls to 'new' and 'delete' and prevents memory leaks.
 * 2. std::unique_ptr:
 *    - Scoped pointer with exclusive ownership (cannot be copied, only moved).
 *    - Zero overhead: Performs exactly like a raw pointer in terms of speed and size.
 *    - Best practice: Preferred choice by default unless shared ownership is explicitly required.
 * 3. std::shared_ptr:
 *    - Shared ownership using Reference Counting (Control Block).
 *    - Memory is deallocated when the last shared_ptr pointing to it is destroyed.
 *    - Overhead: Extra memory allocation for control block and atomic thread-safe reference counts.
 * 4. std::weak_ptr:
 *    - Non-owning reference to an object managed by shared_ptr.
 *    - Does not increment the reference count. Used to break cyclic references.
 *    - Must be converted to shared_ptr via .lock() before accessing the underlying object.
 *
 * [SRB] KLJUČNI KONCEPTI IZ LEKCIJE:
 * 1. Pregled pametnih pokazivača:
 *    - Omotači oko sirovih pokazivača koji automatizuju alokaciju i oslobađanje memorije na Heap-u (RAII).
 *    - Eliminišu eksplicitne pozive 'new' i 'delete' i sprečavaju curenje memorije.
 * 2. std::unique_ptr:
 *    - Pokazivač sa ekskluzivnim vlasništvom (ne može se kopirati, samo pomerati preko std::move).
 *    - Nulti overhead: Ponaša se identično sirovom pokazivaču po brzini i veličini.
 *    - Dobra praksa: Prvi izbor po podrazumevanoj vrednosti osim ako nije neophodno deljeno vlasništvo.
 * 3. std::shared_ptr:
 *    - Deljeno vlasništvo nad resursom pomoću prebrojavanja referenci (Control Block).
 *    - Memorija se oslobađa tek kada se poslednji shared_ptr koji pokazuje na nju uništi.
 *    - Overhead: Dodatna alokacija za kontrolni blok i atomski brojač bezbedan za niti.
 * 4. std::weak_ptr:
 *    - Pokazivač bez vlasništva nad objektom kojim upravlja shared_ptr.
 *    - Ne povećava brojač referenci. Koristi se za razbijanje cikličnih zavisnosti u memoriji.
 *    - Mora se konvertovati u shared_ptr preko .lock() pre pristupa samom objektu.
 */

#include <iostream>
#include <memory>

class Entity {
public:
    Entity() {
        std::cout << "[EN] Entity Created! / [SRB] Entity Kreiran!\n";
    }

    ~Entity() {
        std::cout << "[EN] Entity Destroyed! / [SRB] Entity Uništen!\n";
    }

    void Print() const {
        std::cout << "Hello from Entity!\n";
    }
};

int main() {
    std::cout << "=== 1. UNIQUE POINTER (unique_ptr) ===\n";
    {
        // [EN] Best Practice: Use std::make_unique instead of raw new for exception safety
        // [SRB] Dobra praksa: Koristiti std::make_unique umesto new zbog bezbednosti izuzetaka
        std::unique_ptr<Entity> entity = std::make_unique<Entity>();
        entity->Print();

        // [EN] Copying is DELETED / [SRB] Kopiranje je ZABRANJENO:
        // std::unique_ptr<Entity> eCopy = entity; // Error!

        // [EN] Ownership can be MOVED / [SRB] Vlasništvo se može POMERITI:
        std::unique_ptr<Entity> movedEntity = std::move(entity);
        if (!entity) {
            std::cout << "[EN] 'entity' is now nullptr after std::move!\n";
            std::cout << "[SRB] 'entity' je sada nullptr nakon std::move-a!\n";
        }
    } // [EN] Memory automatically freed here / [SRB] Memorija se automatski oslobađa ovde

    std::cout << "\n=== 2. SHARED POINTER (shared_ptr) ===\n";
    {
        std::shared_ptr<Entity> shared1;
        {
            // [EN] Create shared pointer and allocate control block
            // [SRB] Kreiraj shared pointer i alociraj kontrolni blok
            std::shared_ptr<Entity> shared2 = std::make_shared<Entity>();
            shared1 = shared2; // [EN] Ref count increases to 2 / [SRB] Brojač se povećava na 2

            std::cout << "[EN] Use Count: " << shared1.use_count()
                      << " | [SRB] Brojač referenci: " << shared1.use_count() << '\n';
        } // [EN] shared2 goes out of scope, ref count drops to 1 (Entity NOT destroyed yet)
          // [SRB] shared2 izlazi iz opsega, brojač pada na 1 (Entity JOŠ UVEK nije uništen)

        std::cout << "[EN] Use Count outside inner scope: " << shared1.use_count()
                  << " | [SRB] Brojač van unutrašnjeg opsega: " << shared1.use_count() << '\n';
    } // [EN] shared1 goes out of scope, ref count drops to 0 -> Entity DESTROYED here!
      // [SRB] shared1 izlazi iz opsega, brojač pada na 0 -> Entity se UNIŠTAVA ovde!

    std::cout << "\n=== 3. WEAK POINTER (weak_ptr) ===\n";
    {
        std::weak_ptr<Entity> weak;
        {
            std::shared_ptr<Entity> shared = std::make_shared<Entity>();
            weak = shared; // [EN] Assigning to weak_ptr DOES NOT increment ref count
                           // [SRB] Dodeljivanje weak_ptr-u NE povećava brojač referenci

            std::cout << "[EN] Use Count with weak_ptr: " << shared.use_count()
                      << " | [SRB] Brojač uz weak_ptr: " << shared.use_count() << '\n';

            // [EN] Accessing object via .lock()
            // [SRB] Pristup objektu preko .lock()
            if (std::shared_ptr<Entity> locked = weak.lock()) {
                locked->Print();
            }
        } // [EN] shared goes out of scope -> Entity DESTROYED!
          // [SRB] shared izlazi iz opsega -> Entity UNISŠTEN!

        // [EN] Check if weak_ptr target has been deleted (expired)
        // [SRB] Provera da li je objekat pod weak_ptr obrisan (istekao)
        if (weak.expired()) {
            std::cout << "[EN] weak_ptr is expired! Object no longer exists.\n";
            std::cout << "[SRB] weak_ptr je istekao! Objekat više ne postoji.\n";
        }
    }

    return 0;
}