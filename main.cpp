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
            std::cout << " - Categoria: " << item->getCategory()->getName();
        }
        std::cout << "\n";
    }
}

int main() {
    printSeparator("Demo Shopping List App");


    auto categoryFruits = std::make_shared<Category>(CategoryType::FRUITS_VEGETABLES, "Frutta e Verdura");
    auto categoryDairy = std::make_shared<Category>(CategoryType::DAIRY, "Latticini");
    auto categoryMeat = std::make_shared<Category>(CategoryType::MEAT_FISH, "Carne e Pesce");


    auto user1 = std::make_shared<User>("Mario", "mario@email.com");
    auto user2 = std::make_shared<User>("Anna", "anna@email.com");

    printSeparator("Creazione Liste e Articoli");


    auto groceryList = user1->createList("Spesa Settimanale");


    auto apple = std::make_shared<Item>("Mele", 2, categoryFruits, "Bio preferibilmente");
    auto milk = std::make_shared<Item>("Latte", 1, categoryDairy);
    auto chicken = std::make_shared<Item>("Pollo", 1, categoryMeat, "Petto di pollo");
    auto tomatoes = std::make_shared<Item>("Pomodori", 1, categoryFruits);

    groceryList->addItem(apple);
    groceryList->addItem(milk);
    groceryList->addItem(chicken);
    groceryList->addItem(tomatoes);

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


    auto fruitsItems = groceryList->getItemsByCategory(categoryFruits);
    std::cout << "Articoli nella categoria 'Frutta e Verdura' (" << fruitsItems.size() << "):\n";
    for (const auto &item: fruitsItems) {
        std::cout << "  - " << item->getName() << "\n";
    }

    printSeparator("Creazione Seconda Lista");


    auto quickList = user2->createList("Spesa Veloce");
    auto bread = std::make_shared<Item>("Pane", 1, nullptr, "Integrale");
    auto water = std::make_shared<Item>("Acqua", 6);

    quickList->addItem(bread);
    quickList->addItem(water);

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

    printSeparator("Fine Demo");

    return 0;
}