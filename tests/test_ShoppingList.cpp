#include <gtest/gtest.h>
#include "ShoppingList.h"
#include "Item.h"
#include "Category.h"
#include <memory>

class ShoppingListTest : public ::testing::Test {
protected:
    void SetUp() override {
        list = std::make_unique<ShoppingList>("Test List");
        category = std::make_shared<Category>(CategoryType::FRUITS_VEGETABLES, "Frutta");
        item1 = std::make_shared<Item>("Mele", 2, category);
        item2 = std::make_shared<Item>("Banane", 3, category);
        item3 = std::make_shared<Item>("Latte", 1, nullptr);
    }

    std::unique_ptr<ShoppingList> list;
    std::shared_ptr<Category> category;
    std::shared_ptr<Item> item1;
    std::shared_ptr<Item> item2;
    std::shared_ptr<Item> item3;
};

TEST_F(ShoppingListTest, Constructor) {
    EXPECT_EQ(list->getName(), "Test List");
    EXPECT_GT(list->getId(), 0);
    EXPECT_EQ(list->getTotalItems(), 0);
    EXPECT_EQ(list->getPurchasedItemsCount(), 0);
    EXPECT_EQ(list->getRemainingItems(), 0);
}

TEST_F(ShoppingListTest, AddItems) {
    list->addItem(item1);
    list->addItem(item2);

    EXPECT_EQ(list->getTotalItems(), 2);
    EXPECT_EQ(list->getRemainingItems(), 2);
    EXPECT_EQ(list->getPurchasedItemsCount(), 0);

}

TEST_F(ShoppingListTest, RemoveItems) {
    list->addItem(item1);
    list->addItem(item2);

    EXPECT_TRUE(list->removeItem(item1->getId()));
    EXPECT_EQ(list->getTotalItems(), 1);
    EXPECT_FALSE(list->removeItem(999)); // Non-existent ID
}

TEST_F(ShoppingListTest, FindItems) {
    list->addItem(item1);
    list->addItem(item2);

    auto found = list->findItem(item1->getId());
    EXPECT_EQ(found, item1);

    auto foundByName = list->findItemByName("Banane");
    EXPECT_EQ(foundByName, item2);

    auto notFound = list->findItem(999);
    EXPECT_EQ(notFound, nullptr);
}

TEST_F(ShoppingListTest, MarkItemsPurchased) {
    list->addItem(item1);
    list->addItem(item2);

    list->markItemPurchased(item1->getId(), true);

    EXPECT_EQ(list->getPurchasedItemsCount(), 1);
    EXPECT_EQ(list->getRemainingItems(), 1);
    EXPECT_TRUE(item1->isPurchased());
    EXPECT_FALSE(item2->isPurchased());
}

TEST_F(ShoppingListTest, GetItemsByCategory) {
    list->addItem(item1);
    list->addItem(item2);
    list->addItem(item3);

    auto fruitsItems = list->getItemsByCategory(category);
    EXPECT_EQ(fruitsItems.size(), 2);

    auto otherCategory = std::make_shared<Category>(CategoryType::DAIRY, "Latticini");
    auto otherItems = list->getItemsByCategory(otherCategory);
    EXPECT_EQ(otherItems.size(), 0);
}

TEST_F(ShoppingListTest, GetPurchasedAndUnpurchasedItems) {
    list->addItem(item1);
    list->addItem(item2);
    list->addItem(item3);

    item1->setPurchased(true);
    item2->setPurchased(false);
    item3->setPurchased(true);

    auto purchased = list->getPurchasedItems();
    auto unpurchased = list->getUnpurchasedItems();

    EXPECT_EQ(purchased.size(), 2);
    EXPECT_EQ(unpurchased.size(), 1);
    EXPECT_EQ(unpurchased[0], item2);
}

TEST_F(ShoppingListTest, ClearItems) {
    list->addItem(item1);
    list->addItem(item2);
    item1->setPurchased(true);

    list->clearPurchasedItems();
    EXPECT_EQ(list->getTotalItems(), 1);
    EXPECT_EQ(list->findItem(item2->getId()), item2);

    list->clearAllItems();
    EXPECT_EQ(list->getTotalItems(), 0);
}

TEST_F(ShoppingListTest, SetName) {
    list->setName("New Name");
    EXPECT_EQ(list->getName(), "New Name");
}

TEST_F(ShoppingListTest, EqualityOperators) {
    ShoppingList list2("Another List");
    EXPECT_NE(*list, list2);
    EXPECT_TRUE(*list == *list);
}

TEST_F(ShoppingListTest, AddNullItem) {
    list->addItem(nullptr);
    EXPECT_EQ(list->getTotalItems(), 0);
}