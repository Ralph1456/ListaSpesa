#include "User.h"
#include <iostream>

int User::nextId = 1;

User::User(const std::string& username, const std::string& email)
        : id(nextId++), username(username), email(email) {}

int User::getId() const {
    return id;
}

std::string User::getUsername() const {
    return username;
}

std::string User::getEmail() const {
    return email;
}

std::vector<std::shared_ptr<ShoppingList>> User::getOwnedLists() const {
    return ownedLists;
}

std::vector<std::shared_ptr<ShoppingList>> User::getSharedLists() const {
    return sharedLists;
}

std::vector<std::shared_ptr<ShoppingList>> User::getAllLists() const {
    std::vector<std::shared_ptr<ShoppingList>> allLists = ownedLists;
    allLists.insert(allLists.end(), sharedLists.begin(), sharedLists.end());
    return allLists;
}

void User::setUsername(const std::string& username) {
    this->username = username;
}

void User::setEmail(const std::string& email) {
    this->email = email;
}

std::shared_ptr<ShoppingList> User::createList(const std::string& name) {
    auto list = std::make_shared<ShoppingList>(name);
    auto selfPtr = std::shared_ptr<User>(this, [](User*) {});
    list->addObserver(selfPtr);
    ownedLists.push_back(list);
    return list;
}

bool User::deleteList(int listId) {
    auto it = std::find_if(ownedLists.begin(), ownedLists.end(),
                           [listId](const std::shared_ptr<ShoppingList>& list) {
                               return list->getId() == listId;
                           });

    if (it != ownedLists.end()) {
        ownedLists.erase(it);
        return true;
    }
    return false;
}

void User::shareList(std::shared_ptr<ShoppingList> list, std::shared_ptr<User> user) {
    if (list && user) {
        user->joinSharedList(list);
    }
}

void User::joinSharedList(std::shared_ptr<ShoppingList> list) {
    if (list) {
        auto it = std::find(sharedLists.begin(), sharedLists.end(), list);
        if (it == sharedLists.end()) {
            sharedLists.push_back(list);
            auto selfPtr = std::shared_ptr<User>(this, [](User*) {});
            list->addObserver(selfPtr);
        }
    }
}

void User::leaveSharedList(int listId) {
    auto it = std::find_if(sharedLists.begin(), sharedLists.end(),
                           [listId](const std::shared_ptr<ShoppingList>& list) {
                               return list->getId() == listId;
                           });

    if (it != sharedLists.end()) {
        auto selfPtr = std::shared_ptr<User>(this, [](User*) {}); // Non-owning shared_ptr
        (*it)->removeObserver(selfPtr);
        sharedLists.erase(it);
    }
}

std::shared_ptr<ShoppingList> User::findList(int listId) const {
    auto allLists = getAllLists();
    auto it = std::find_if(allLists.begin(), allLists.end(),
                           [listId](const std::shared_ptr<ShoppingList>& list) {
                               return list->getId() == listId;
                           });

    return (it != allLists.end()) ? *it : nullptr;
}

std::shared_ptr<ShoppingList> User::findListByName(const std::string& name) const {
    auto allLists = getAllLists();
    auto it = std::find_if(allLists.begin(), allLists.end(),
                           [&name](const std::shared_ptr<ShoppingList>& list) {
                               return list->getName() == name;
                           });

    return (it != allLists.end()) ? *it : nullptr;
}

void User::update(const ShoppingListInfo& info) {
    std::cout << "[User " << username << "] Lista '" << info.listName
              << "' aggiornata: " << info.remainingItems << "/"
              << info.totalItems << " articoli da acquistare\n";
}

bool User::operator==(const User& other) const {
    return id == other.id;
}

bool User::operator!=(const User& other) const {
    return !(*this == other);
}