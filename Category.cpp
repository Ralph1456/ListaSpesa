#include "Category.h"

Category::Category(CategoryType type, const std::string& name, const std::string& description)
        : type(type), name(name), description(description) {}

CategoryType Category::getType() const {
    return type;
}

std::string Category::getName() const {
    return name;
}

std::string Category::getDescription() const {
    return description;
}

void Category::setName(const std::string& name) {
    this->name = name;
}

void Category::setDescription(const std::string& description) {
    this->description = description;
}

bool Category::operator==(const Category& other) const {
    return type == other.type && name == other.name;
}

bool Category::operator!=(const Category& other) const {
    return !(*this == other);
}