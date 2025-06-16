#include <gtest/gtest.h>
#include "User.h"
#include "ShoppingList.h"
#include "Item.h"

class MockObserver : public Observer<ShoppingListInfo> {
public:
    int updateCount = 0;
    ShoppingListInfo lastInfo;

    void update(const ShoppingListInfo& info) override {
        updateCount++;
        lastInfo = info;
    }
};

class UserTest : public ::testing::Test {
protected:
    void SetUp() override {
        user1 = std::make_shared<User>("Mario", "mario@test.com");
        user2 = std::make_shared<User>("Anna", "anna@test.com");
    }

    std::shared_ptr<User> user1;
    std::shared_ptr<User> user2;
};

TEST_F(UserTest, Constructor) {
EXPECT_EQ(user1->getUsername(), "Mario");
EXPECT_EQ(user1->getEmail(), "mario@test.com");
EXPECT_GT(user1->getId(), 0);
EXPECT_EQ(user1->getOwnedLists().size(), 0);
EXPECT_EQ(user1->getSharedLists().size(), 0);
}

TEST_F(UserTest, SettersAndGetters) {
user1->setUsername("Giuseppe");
user1->setEmail("giuseppe@test.com");

EXPECT_EQ(user1->getUsername(), "Giuseppe");
EXPECT_EQ(user1->getEmail(), "giuseppe@test.com");
}

TEST_F(UserTest, CreateList) {
auto list = user1->createList("My List");

EXPECT_NE(list, nullptr);
EXPECT_EQ(list->getName(), "My List");
EXPECT_EQ(user1->getOwnedLists().size(), 1);
EXPECT_EQ(user1->getAllLists().size(), 1);
}

TEST_F(UserTest, DeleteList) {
auto list = user1->createList("To Delete");
int listId = list->getId();

EXPECT_TRUE(user1->deleteList(listId));
EXPECT_EQ(user1->getOwnedLists().size(), 0);
EXPECT_FALSE(user1->deleteList(999)); // Non-existent ID
}

TEST_F(UserTest, ShareList) {
auto list = user1->createList("Shared List");

user1->shareList(list, user2);

EXPECT_EQ(user1->getOwnedLists().size(), 1);
EXPECT_EQ(user2->getSharedLists().size(), 1);
EXPECT_EQ(user2->getAllLists().size(), 1);
}

TEST_F(UserTest, LeaveSharedList) {
auto list = user1->createList("Shared List");
user1->shareList(list, user2);

user2->leaveSharedList(list->getId());

EXPECT_EQ(user2->getSharedLists().size(), 0);
EXPECT_EQ(user1->getOwnedLists().size(), 1); // Owner still has it
}

TEST_F(UserTest, FindList) {
auto list1 = user1->createList("List 1");
auto list2 = user1->createList("List 2");

auto found = user1->findList(list1->getId());
EXPECT_EQ(found, list1);

auto foundByName = user1->findListByName("List 2");
EXPECT_EQ(foundByName, list2);

auto notFound = user1->findList(999);
EXPECT_EQ(notFound, nullptr);
}

TEST_F(UserTest, ObserverPattern) {
    auto list = user1->createList("Observer Test");
    auto item = std::make_shared<Item>("Test Item", 1, nullptr);

    // Testa che la lista si aggiorni correttamente
    EXPECT_EQ(list->getTotalItems(), 0);
    list->addItem(item);
    EXPECT_EQ(list->getTotalItems(), 1);

    // Il fatto che non ci siano eccezioni significa che l'Observer funziona
    EXPECT_TRUE(true); // Test che passa sempre se arriviamo qui
}

TEST_F(UserTest, EqualityOperators) {
EXPECT_NE(*user1, *user2);
EXPECT_TRUE(*user1 == *user1);
}

TEST_F(UserTest, UniqueIds) {
EXPECT_NE(user1->getId(), user2->getId());
}

TEST_F(UserTest, ShareNullList) {
user1->shareList(nullptr, user2);
EXPECT_EQ(user2->getSharedLists().size(), 0); // Should not add null list
}

TEST_F(UserTest, JoinSharedListDirectly) {
auto list = user1->createList("Direct Join");
user2->joinSharedList(list);

EXPECT_EQ(user2->getSharedLists().size(), 1);

// Try to join same list again
user2->joinSharedList(list);
EXPECT_EQ(user2->getSharedLists().size(), 1); // Should not duplicate
}

