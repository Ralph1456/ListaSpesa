#ifndef SHOPPING_LIST_H
#define SHOPPING_LIST_H

#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include "Item.h"
#include "Observer.h"

struct ShoppingListInfo {
    std::string listName;
    int totalItems;
    int purchasedItems;
    int remainingItems;
};

class ShoppingList : public Subject<ShoppingListInfo> {
private:
    static int nextId;
    int id;
    std::string name;
    std::vector<std::shared_ptr<Item>> items;

    void notifyChange();

public:
    ShoppingList(const std::string& name);

    int getId() const;
    std::string getName() const;
    std::vector<std::shared_ptr<Item>> getItems() const;
    int getTotalItems() const;
    int getPurchasedItemsCount() const;
    int getRemainingItems() const;

    void setName(const std::string& name);

    void addItem(std::shared_ptr<Item> item);
    bool removeItem(int itemId);
    std::shared_ptr<Item> findItem(int itemId) const;
    std::shared_ptr<Item> findItemByName(const std::string& name) const;

    void markItemPurchased(int itemId, bool purchased = true);
    void clearPurchasedItems();
    void clearAllItems();

    std::vector<std::shared_ptr<Item>> getItemsByCategory(std::shared_ptr<Category> category) const;
    std::vector<std::shared_ptr<Item>> getPurchasedItems() const;
    std::vector<std::shared_ptr<Item>> getUnpurchasedItems() const;

    bool operator==(const ShoppingList& other) const;
    bool operator!=(const ShoppingList& other) const;
};
#endif