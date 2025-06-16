#include "Item.h"

int Item::nextId = 1;

Item::Item(const std::string& name, int quantity,
           std::shared_ptr<Category> category, const std::string& notes)
        : id(nextId++), name(name), quantity(quantity), purchased(false),
          category(category), notes(notes) {}

int Item::getId() const {
    return id;
}

std::string Item::getName() const {
    return name;
}

int Item::getQuantity() const {
    return quantity;
}

bool Item::isPurchased() const {
    return purchased;
}

std::shared_ptr<Category> Item::getCategory() const {
    return category;
}

std::string Item::getNotes() const {
    return notes;
}

void Item::setName(const std::string& name) {
    this->name = name;
}

void Item::setQuantity(int quantity) {
    if (quantity > 0) {
        this->quantity = quantity;
    }
}

void Item::setPurchased(bool purchased) {
    this->purchased = purchased;
}

void Item::setCategory(std::shared_ptr<Category> category) {
    this->category = category;
}

void Item::setNotes(const std::string& notes) {
    this->notes = notes;
}

bool Item::operator==(const Item& other) const {
    return id == other.id;
}

bool Item::operator!=(const Item& other) const {
    return !(*this == other);
}