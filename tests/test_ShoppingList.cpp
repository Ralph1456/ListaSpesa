#include <gtest/gtest.h>
#include "Item.h"
#include "Category.h"
#include "ShoppingList.h"


class ShoppingListItemTest : public ::testing::Test {
protected:
    void SetUp() override {
        category = std::make_shared<FoodCategory>("Frutta e Verdura", "Frutta");
        item = std::make_unique<Item>("Mele", 3, category, "Bio");
    }

    std::shared_ptr<Category> category;
    std::unique_ptr<Item> item;
};

TEST_F(ShoppingListItemTest, Constructor) {
    EXPECT_EQ(item->getName(), "Mele");
    EXPECT_EQ(item->getQuantity(), 3);
    EXPECT_FALSE(item->isPurchased());
    EXPECT_EQ(item->getCategory(), category);
    EXPECT_EQ(item->getNotes(), "Bio");
    EXPECT_GT(item->getId(), 0);
}

TEST_F(ShoppingListItemTest, DefaultConstructor) {
    Item defaultItem("Pane");
    EXPECT_EQ(defaultItem.getName(), "Pane");
    EXPECT_EQ(defaultItem.getQuantity(), 1);
    EXPECT_FALSE(defaultItem.isPurchased());
    EXPECT_EQ(defaultItem.getCategory(), nullptr);
    EXPECT_EQ(defaultItem.getNotes(), "");
}

TEST_F(ShoppingListItemTest, SettersAndGetters) {
    item->setName("Pere");
    item->setQuantity(5);
    item->setPurchased(true);
    item->setNotes("Mature");

    EXPECT_EQ(item->getName(), "Pere");
    EXPECT_EQ(item->getQuantity(), 5);
    EXPECT_TRUE(item->isPurchased());
    EXPECT_EQ(item->getNotes(), "Mature");
}

TEST_F(ShoppingListItemTest, InvalidQuantity) {
    int originalQuantity = item->getQuantity();
    item->setQuantity(-1);
    EXPECT_EQ(item->getQuantity(), originalQuantity);

    item->setQuantity(0);
    EXPECT_EQ(item->getQuantity(), originalQuantity);
}

TEST_F(ShoppingListItemTest, UniqueIds) {
    Item item1("Item1");
    Item item2("Item2");
    EXPECT_NE(item1.getId(), item2.getId());
}

TEST_F(ShoppingListItemTest, EqualityOperators) {
    Item item2("Diverse", 1, nullptr, "");
    EXPECT_NE(*item, item2);
    EXPECT_TRUE(*item == *item);
}

TEST_F(ShoppingListItemTest, CategoryAssignment) {
    auto newCategory = std::make_shared<HouseholdCategory>("Latticini", "Prodotti caseari");
    item->setCategory(newCategory);
    EXPECT_EQ(item->getCategory(), newCategory);

    item->setCategory(nullptr);
    EXPECT_EQ(item->getCategory(), nullptr);
}


class ShoppingListTest : public ::testing::Test {
protected:
    void SetUp() override {
        shoppingList = std::make_unique<ShoppingList>("Lista della spesa");
        foodCategory = std::make_shared<FoodCategory>("Frutta", "Frutta fresca");
        householdCategory = std::make_shared<HouseholdCategory>("Casa", "Prodotti per la casa");

        item1 = std::make_shared<Item>("Mele", 3, foodCategory, "Bio");
        item2 = std::make_shared<Item>("Pane", 1, foodCategory);
        item3 = std::make_shared<Item>("Detersivo", 1, householdCategory);
    }

    std::unique_ptr<ShoppingList> shoppingList;
    std::shared_ptr<Category> foodCategory;
    std::shared_ptr<Category> householdCategory;
    std::shared_ptr<Item> item1;
    std::shared_ptr<Item> item2;
    std::shared_ptr<Item> item3;
};

TEST_F(ShoppingListTest, Constructor) {
    EXPECT_EQ(shoppingList->getName(), "Lista della spesa");
    EXPECT_GT(shoppingList->getId(), 0);
    EXPECT_EQ(shoppingList->getTotalItems(), 0);
    EXPECT_EQ(shoppingList->getPurchasedItemsCount(), 0);
    EXPECT_EQ(shoppingList->getRemainingItems(), 0);
}

TEST_F(ShoppingListTest, AddItems) {
    shoppingList->addItem(item1);
    shoppingList->addItem(item2);

    EXPECT_EQ(shoppingList->getTotalItems(), 2);
    EXPECT_EQ(shoppingList->getRemainingItems(), 2);
    EXPECT_EQ(shoppingList->getPurchasedItemsCount(), 0);
}

TEST_F(ShoppingListTest, AddNullItem) {
    int originalCount = shoppingList->getTotalItems();
    shoppingList->addItem(nullptr);
    EXPECT_EQ(shoppingList->getTotalItems(), originalCount);
}

TEST_F(ShoppingListTest, FindItem) {
    shoppingList->addItem(item1);
    shoppingList->addItem(item2);

    auto found = shoppingList->findItem(item1->getId());
    EXPECT_EQ(found, item1);

    auto notFound = shoppingList->findItem(9999);
    EXPECT_EQ(notFound, nullptr);
}

TEST_F(ShoppingListTest, FindItemByName) {
    shoppingList->addItem(item1);
    shoppingList->addItem(item2);

    auto found = shoppingList->findItemByName("Mele");
    EXPECT_EQ(found, item1);

    auto notFound = shoppingList->findItemByName("Inesistente");
    EXPECT_EQ(notFound, nullptr);
}

TEST_F(ShoppingListTest, RemoveItem) {
    shoppingList->addItem(item1);
    shoppingList->addItem(item2);

    EXPECT_TRUE(shoppingList->removeItem(item1->getId()));
    EXPECT_EQ(shoppingList->getTotalItems(), 1);

    EXPECT_FALSE(shoppingList->removeItem(9999));
    EXPECT_EQ(shoppingList->getTotalItems(), 1);
}

TEST_F(ShoppingListTest, MarkItemPurchased) {
    shoppingList->addItem(item1);
    shoppingList->addItem(item2);

    shoppingList->markItemPurchased(item1->getId(), true);

    EXPECT_TRUE(item1->isPurchased());
    EXPECT_EQ(shoppingList->getPurchasedItemsCount(), 1);
    EXPECT_EQ(shoppingList->getRemainingItems(), 1);

    shoppingList->markItemPurchased(item1->getId(), false);
    EXPECT_FALSE(item1->isPurchased());
    EXPECT_EQ(shoppingList->getPurchasedItemsCount(), 0);
}

TEST_F(ShoppingListTest, GetItemsByCategory) {
    shoppingList->addItem(item1);
    shoppingList->addItem(item2);
    shoppingList->addItem(item3);

    auto foodItems = shoppingList->getItemsByCategory(foodCategory);
    EXPECT_EQ(foodItems.size(), 2);

    auto householdItems = shoppingList->getItemsByCategory(householdCategory);
    EXPECT_EQ(householdItems.size(), 1);
}

TEST_F(ShoppingListTest, GetPurchasedAndUnpurchasedItems) {
    shoppingList->addItem(item1);
    shoppingList->addItem(item2);
    shoppingList->addItem(item3);

    item1->setPurchased(true);
    item2->setPurchased(false);
    item3->setPurchased(true);

    auto purchased = shoppingList->getPurchasedItems();
    auto unpurchased = shoppingList->getUnpurchasedItems();

    EXPECT_EQ(purchased.size(), 2);
    EXPECT_EQ(unpurchased.size(), 1);
    EXPECT_EQ(unpurchased[0], item2);
}

TEST_F(ShoppingListTest, ClearPurchasedItems) {
    shoppingList->addItem(item1);
    shoppingList->addItem(item2);
    shoppingList->addItem(item3);

    item1->setPurchased(true);
    item3->setPurchased(true);

    shoppingList->clearPurchasedItems();

    EXPECT_EQ(shoppingList->getTotalItems(), 1);
    EXPECT_EQ(shoppingList->getItems()[0], item2);
}

TEST_F(ShoppingListTest, ClearAllItems) {
    shoppingList->addItem(item1);
    shoppingList->addItem(item2);
    shoppingList->addItem(item3);

    shoppingList->clearAllItems();

    EXPECT_EQ(shoppingList->getTotalItems(), 0);
    EXPECT_TRUE(shoppingList->getItems().empty());
}

TEST_F(ShoppingListTest, SetName) {
    shoppingList->setName("Nuova Lista");
    EXPECT_EQ(shoppingList->getName(), "Nuova Lista");
}

TEST_F(ShoppingListTest, UniqueIds) {
    ShoppingList list1("Lista 1");
    ShoppingList list2("Lista 2");
    EXPECT_NE(list1.getId(), list2.getId());
}

TEST_F(ShoppingListTest, EqualityOperators) {
    ShoppingList list2("Altra Lista");
    EXPECT_NE(*shoppingList, list2);
    EXPECT_TRUE(*shoppingList == *shoppingList);
}