#include "Category.h"

// Base Category implementation
Category::Category(const std::string& name, const std::string& description)
        : name(name), description(description) {}

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
    return name == other.name && getType() == other.getType();
}

bool Category::operator!=(const Category& other) const {
    return !(*this == other);
}

// FoodCategory implementation
FoodCategory::FoodCategory(const std::string& name, const std::string& description)
        : Category(name, description) {}

std::string FoodCategory::getType() const {
    return "Food";
}

// HouseholdCategory implementation
HouseholdCategory::HouseholdCategory(const std::string& name, const std::string& description)
        : Category(name, description) {}

std::string HouseholdCategory::getType() const {
    return "Household";
}