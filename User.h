#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include "ShoppingList.h"
#include "Observer.h"

class User : public Observer<ShoppingListInfo> {
private:
    static int nextId;
    int id;
    std::string username;
    std::string email;
    std::vector<std::shared_ptr<ShoppingList>> ownedLists;
    std::vector<std::shared_ptr<ShoppingList>> sharedLists;

public:
    User(const std::string& username, const std::string& email);
    ~User() override = default;

    int getId() const;
    std::string getUsername() const;
    std::string getEmail() const;
    std::vector<std::shared_ptr<ShoppingList>> getOwnedLists() const;
    std::vector<std::shared_ptr<ShoppingList>> getSharedLists() const;
    std::vector<std::shared_ptr<ShoppingList>> getAllLists() const;

    void setUsername(const std::string& username);
    void setEmail(const std::string& email);

    std::shared_ptr<ShoppingList> createList(const std::string& name);
    bool deleteList(int listId);
    void shareList(std::shared_ptr<ShoppingList> list, std::shared_ptr<User> user);
    void joinSharedList(std::shared_ptr<ShoppingList> list);
    void leaveSharedList(int listId);

    std::shared_ptr<ShoppingList> findList(int listId) const;
    std::shared_ptr<ShoppingList> findListByName(const std::string& name) const;

    // Observer pattern implementation
    void update(const ShoppingListInfo& info) override;

    bool operator==(const User& other) const;
    bool operator!=(const User& other) const;
};

#endif