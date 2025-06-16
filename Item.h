

#ifndef LISTA_SPESA_ITEM_H
#define LISTA_SPESA_ITEM_H
#include <string>
#include <memory>
#include "Category.h"

class Item {
private:
    static int nextId;
    int id;
    std::string name;
    int quantity;
    bool purchased;
    std::shared_ptr<Category> category;
    std::string notes;

public:
    Item(const std::string& name, int quantity = 1,
         std::shared_ptr<Category> category = nullptr,
         const std::string& notes = "");

    int getId() const;
    std::string getName() const;
    int getQuantity() const;
    bool isPurchased() const;
    std::shared_ptr<Category> getCategory() const;
    std::string getNotes() const;

    void setName(const std::string& name);
    void setQuantity(int quantity);
    void setPurchased(bool purchased);
    void setCategory(std::shared_ptr<Category> category);
    void setNotes(const std::string& notes);

    bool operator==(const Item& other) const;
    bool operator!=(const Item& other) const;
};


#endif
