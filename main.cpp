#include <iostream>
#include <memory>
#include "User.h"
#include "Item.h"
#include "Category.h"
#include "ShoppingList.h"

void printSeparator(const std::string& title) {
    std::cout << "\n=== " << title << " ===\n";
}

void printList(const std::shared_ptr<ShoppingList>& list) {
    std::cout << "Lista: " << list->getName() << " (ID: " << list->getId() << ")\n";
    std::cout << "Articoli totali: " << list->getTotalItems() << "\n";
    std::cout << "Acquistati: " << list->getPurchasedItemsCount() << "\n";
    std::cout << "Da acquistare: " << list->getRemainingItems() << "\n";

    auto items = list->getItems();
    for (const auto& item : items) {
        std::cout << "  - " << item->getName()
                  << " (Qt: " << item->getQuantity() << ")"
                  << (item->isPurchased() ? " [ACQUISTATO]" : " [DA ACQUISTARE]");
        if (item->getCategory()) {
            std::cout << " - Categoria: " << item->getCategory()->getName()
                      << " (" << item->getCategory()->getType() << ")";
        }
        std::cout << "\n";
    }
}

int main() {
    printSeparator("Demo Shopping List App - New Category System");

    // Create categories using inheritance
    auto foodCategory = std::make_shared<FoodCategory>("Alimentari", "Prodotti alimentari");
    auto householdCategory = std::make_shared<HouseholdCategory>("Casa", "Prodotti per la casa");

    // Create users
    auto user1 = std::make_shared<User>("Mario", "mario@email.com");
    auto user2 = std::make_shared<User>("Anna", "anna@email.com");

    printSeparator("Creazione Liste e Articoli");


    auto groceryList = user1->createList("Spesa Settimanale");


    auto apple = std::make_shared<Item>("Mele", 2, foodCategory, "Bio preferibilmente");
    auto milk = std::make_shared<Item>("Latte", 1, foodCategory);
    auto chicken = std::make_shared<Item>("Pollo", 1, foodCategory, "Petto di pollo");
    auto detergent = std::make_shared<Item>("Detersivo", 1, householdCategory, "Per i piatti");

    groceryList->addItem(apple);
    groceryList->addItem(milk);
    groceryList->addItem(chicken);
    groceryList->addItem(detergent);

    printList(groceryList);

    printSeparator("Condivisione Lista");

    user1->shareList(groceryList, user2);
    std::cout << "Lista condivisa con " << user2->getUsername() << "\n";

    printSeparator("Acquisti - Observer Pattern in Azione");

    std::cout << "Acquistando alcuni articoli...\n";
    groceryList->markItemPurchased(apple->getId(), true);
    groceryList->markItemPurchased(milk->getId(), true);

    printSeparator("Stato Finale Lista");
    printList(groceryList);

    printSeparator("Filtri e Ricerche");

    auto purchasedItems = groceryList->getPurchasedItems();
    std::cout << "Articoli acquistati (" << purchasedItems.size() << "):\n";
    for (const auto &item: purchasedItems) {
        std::cout << "  - " << item->getName() << "\n";
    }

    auto unpurchasedItems = groceryList->getUnpurchasedItems();
    std::cout << "Articoli da acquistare (" << unpurchasedItems.size() << "):\n";
    for (const auto &item: unpurchasedItems) {
        std::cout << "  - " << item->getName() << "\n";
    }

    // Filter by category type
    auto foodItems = groceryList->getItemsByCategory(foodCategory);
    std::cout << "Articoli nella categoria 'Alimentari' (" << foodItems.size() << "):\n";
    for (const auto &item: foodItems) {
        std::cout << "  - " << item->getName() << "\n";
    }

    printSeparator("Creazione Seconda Lista");

    auto quickList = user2->createList("Spesa Veloce");
    auto bread = std::make_shared<Item>("Pane", 1, foodCategory, "Integrale");
    auto soap = std::make_shared<Item>("Sapone", 1, householdCategory);

    quickList->addItem(bread);
    quickList->addItem(soap);

    printList(quickList);

    printSeparator("Riepilogo Utenti");

    std::cout << "Utente: " << user1->getUsername() << "\n";
    std::cout << "  Liste possedute: " << user1->getOwnedLists().size() << "\n";
    std::cout << "  Liste condivise: " << user1->getSharedLists().size() << "\n";
    std::cout << "  Totale liste: " << user1->getAllLists().size() << "\n";

    std::cout << "Utente: " << user2->getUsername() << "\n";
    std::cout << "  Liste possedute: " << user2->getOwnedLists().size() << "\n";
    std::cout << "  Liste condivise: " << user2->getSharedLists().size() << "\n";
    std::cout << "  Totale liste: " << user2->getAllLists().size() << "\n";



    return 0;
}