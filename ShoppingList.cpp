#include "ShoppingList.h"

int ShoppingList::nextId = 1;

ShoppingList::ShoppingList(const std::string& name)
        : id(nextId++), name(name) {}

void ShoppingList::notifyChange() {
    ShoppingListInfo info{name, getTotalItems(), getPurchasedItemsCount(), getRemainingItems()};
    notifyObservers(info);
}

int ShoppingList::getId() const {
    return id;
}

std::string ShoppingList::getName() const {
    return name;
}

std::vector<std::shared_ptr<Item>> ShoppingList::getItems() const {
    return items;
}

int ShoppingList::getTotalItems() const {
    return static_cast<int>(items.size());
}

int ShoppingList::getPurchasedItemsCount() const {
    return static_cast<int>(std::count_if(items.begin(), items.end(),
                                          [](const std::shared_ptr<Item>& item) { return item->isPurchased(); }));
}

int ShoppingList::getRemainingItems() const {
    return getTotalItems() - getPurchasedItemsCount();
}

void ShoppingList::setName(const std::string& name) {
    this->name = name;
    notifyChange();
}

void ShoppingList::addItem(std::shared_ptr<Item> item) {
    if (item) {
        items.push_back(item);
        notifyChange();
    }
}

bool ShoppingList::removeItem(int itemId) {
    auto it = std::find_if(items.begin(), items.end(),
                           [itemId](const std::shared_ptr<Item>& item) {
                               return item->getId() == itemId;
                           });

    if (it != items.end()) {
        items.erase(it);
        notifyChange();
        return true;
    }
    return false;
}

std::shared_ptr<Item> ShoppingList::findItem(int itemId) const {
    auto it = std::find_if(items.begin(), items.end(),
                           [itemId](const std::shared_ptr<Item>& item) {
                               return item->getId() == itemId;
                           });

    return (it != items.end()) ? *it : nullptr;
}

std::shared_ptr<Item> ShoppingList::findItemByName(const std::string& name) const {
    auto it = std::find_if(items.begin(), items.end(),
                           [&name](const std::shared_ptr<Item>& item) {
                               return item->getName() == name;
                           });

    return (it != items.end()) ? *it : nullptr;
}

void ShoppingList::markItemPurchased(int itemId, bool purchased) {
    auto item = findItem(itemId);
    if (item) {
        item->setPurchased(purchased);
        notifyChange();
    }
}

void ShoppingList::clearPurchasedItems() {
    items.erase(std::remove_if(items.begin(), items.end(),
                               [](const std::shared_ptr<Item>& item) { return item->isPurchased(); }),
                items.end());
    notifyChange();
}

void ShoppingList::clearAllItems() {
    items.clear();
    notifyChange();
}

std::vector<std::shared_ptr<Item>> ShoppingList::getItemsByCategory(std::shared_ptr<Category> category) const {
    std::vector<std::shared_ptr<Item>> result;
    std::copy_if(items.begin(), items.end(), std::back_inserter(result),
                 [category](const std::shared_ptr<Item>& item) {
                     return item->getCategory() && *(item->getCategory()) == *category;
                 });
    return result;
}

std::vector<std::shared_ptr<Item>> ShoppingList::getPurchasedItems() const {
    std::vector<std::shared_ptr<Item>> result;
    std::copy_if(items.begin(), items.end(), std::back_inserter(result),
                 [](const std::shared_ptr<Item>& item) { return item->isPurchased(); });
    return result;
}

std::vector<std::shared_ptr<Item>> ShoppingList::getUnpurchasedItems() const {
    std::vector<std::shared_ptr<Item>> result;
    std::copy_if(items.begin(), items.end(), std::back_inserter(result),
                 [](const std::shared_ptr<Item>& item) { return !item->isPurchased(); });
    return result;
}

bool ShoppingList::operator==(const ShoppingList& other) const {
    return id == other.id;
}

bool ShoppingList::operator!=(const ShoppingList& other) const {
    return !(*this == other);
}