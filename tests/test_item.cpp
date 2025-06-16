#include <gtest/gtest.h>
#include "Item.h"
#include "Category.h"

class ItemTest : public ::testing::Test {
protected:
    void SetUp() override {
        category = std::make_shared<Category>(CategoryType::FRUITS_VEGETABLES, "Frutta");
        item = std::make_unique<Item>("Mele", 3, category, "Bio");
    }

    std::shared_ptr<Category> category;
    std::unique_ptr<Item> item;
};

TEST_F(ItemTest, Constructor) {
EXPECT_EQ(item->getName(), "Mele");
EXPECT_EQ(item->getQuantity(), 3);
EXPECT_FALSE(item->isPurchased());
EXPECT_EQ(item->getCategory(), category);
EXPECT_EQ(item->getNotes(), "Bio");
EXPECT_GT(item->getId(), 0);
}

TEST_F(ItemTest, DefaultConstructor) {
Item defaultItem("Pane");
EXPECT_EQ(defaultItem.getName(), "Pane");
EXPECT_EQ(defaultItem.getQuantity(), 1);
EXPECT_FALSE(defaultItem.isPurchased());
EXPECT_EQ(defaultItem.getCategory(), nullptr);
EXPECT_EQ(defaultItem.getNotes(), "");
}

TEST_F(ItemTest, SettersAndGetters) {
item->setName("Pere");
item->setQuantity(5);
item->setPurchased(true);
item->setNotes("Mature");

EXPECT_EQ(item->getName(), "Pere");
EXPECT_EQ(item->getQuantity(), 5);
EXPECT_TRUE(item->isPurchased());
EXPECT_EQ(item->getNotes(), "Mature");
}

TEST_F(ItemTest, InvalidQuantity) {
int originalQuantity = item->getQuantity();
item->setQuantity(-1);
EXPECT_EQ(item->getQuantity(), originalQuantity);

item->setQuantity(0);
EXPECT_EQ(item->getQuantity(), originalQuantity);
}

TEST_F(ItemTest, UniqueIds) {
Item item1("Item1");
Item item2("Item2");
EXPECT_NE(item1.getId(), item2.getId());
}

TEST_F(ItemTest, EqualityOperators) {
Item item2("Diverse", 1, nullptr, "");
EXPECT_NE(*item, item2);
EXPECT_TRUE(*item == *item);
}

TEST_F(ItemTest, CategoryAssignment) {
auto newCategory = std::make_shared<Category>(CategoryType::DAIRY, "Latticini");
item->setCategory(newCategory);
EXPECT_EQ(item->getCategory(), newCategory);

item->setCategory(nullptr);
EXPECT_EQ(item->getCategory(), nullptr);
}

