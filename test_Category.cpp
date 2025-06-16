#include <gtest/gtest.h>
#include "Category.h"

class CategoryTest : public ::testing::Test {
protected:
    void SetUp() override {
        category = std::make_unique<Category>(CategoryType::FRUITS_VEGETABLES, "Frutta", "Categoria per frutta fresca");
    }

    std::unique_ptr<Category> category;
};

TEST_F(CategoryTest, Constructor) {
EXPECT_EQ(category->getType(), CategoryType::FRUITS_VEGETABLES);
EXPECT_EQ(category->getName(), "Frutta");
EXPECT_EQ(category->getDescription(), "Categoria per frutta fresca");
}

TEST_F(CategoryTest, SettersAndGetters) {
category->setName("Verdura");
category->setDescription("Categoria per verdure fresche");

EXPECT_EQ(category->getName(), "Verdura");
EXPECT_EQ(category->getDescription(), "Categoria per verdure fresche");
EXPECT_EQ(category->getType(), CategoryType::FRUITS_VEGETABLES); // Type shouldn't change
}

TEST_F(CategoryTest, EqualityOperators) {
Category other(CategoryType::FRUITS_VEGETABLES, "Frutta", "Descrizione diversa");
Category different(CategoryType::DAIRY, "Latticini", "Categoria latticini");

EXPECT_TRUE(*category == other);
EXPECT_FALSE(*category != other);
EXPECT_FALSE(*category == different);
EXPECT_TRUE(*category != different);
}

TEST_F(CategoryTest, EmptyDescription) {
Category emptyDesc(CategoryType::DAIRY, "Latticini");
EXPECT_EQ(emptyDesc.getDescription(), "");
}
