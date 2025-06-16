#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>

enum class CategoryType {
    FRUITS_VEGETABLES,
    DAIRY,
    MEAT_FISH,
    BAKERY,
    BEVERAGES,
    HOUSEHOLD,
    PERSONAL_CARE,
    OTHER
};

class Category {
private:
    CategoryType type;
    std::string name;
    std::string description;

public:
    Category(CategoryType type, const std::string& name, const std::string& description = "");

    CategoryType getType() const;
    std::string getName() const;
    std::string getDescription() const;

    void setName(const std::string& name);
    void setDescription(const std::string& description);

    bool operator==(const Category& other) const;
    bool operator!=(const Category& other) const;
};

#endif