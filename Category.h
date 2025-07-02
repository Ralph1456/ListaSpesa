
#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>


class Category {
protected:
    std::string name;
    std::string description;

public:
    Category(const std::string& name, const std::string& description = "");
    virtual ~Category() = default;

    virtual std::string getName() const;
    virtual std::string getDescription() const;
    virtual std::string getType() const = 0;

   virtual void setName(const std::string& name);
    virtual void setDescription(const std::string& description);

    bool operator==(const Category& other) const;
    bool operator!=(const Category& other) const;
};


class FoodCategory : public Category {
public:
    FoodCategory(const std::string& name, const std::string& description = "");
    std::string getType() const override;
};

class HouseholdCategory : public Category {
public:
    HouseholdCategory(const std::string& name, const std::string& description = "");
    std::string getType() const override;
};

#endif