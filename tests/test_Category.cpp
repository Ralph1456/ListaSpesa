#include <gtest/gtest.h>
#include "Category.h"

class CategoryTest : public ::testing::Test {
protected:
    void SetUp() override {
        foodCategory = std::make_unique<FoodCategory>("Frutta", "Categoria per frutta fresca");
        householdCategory = std::make_unique<HouseholdCategory>("Pulizie", "Prodotti per la pulizia");
    }

    std::unique_ptr<FoodCategory> foodCategory;
    std::unique_ptr<HouseholdCategory> householdCategory;
};

TEST_F(CategoryTest, FoodCategoryConstructor) {
    EXPECT_EQ(foodCategory->getName(), "Frutta");
    EXPECT_EQ(foodCategory->getDescription(), "Categoria per frutta fresca");
    EXPECT_EQ(foodCategory->getType(), "Food");
}

TEST_F(CategoryTest, HouseholdCategoryConstructor) {
    EXPECT_EQ(householdCategory->getName(), "Pulizie");
    EXPECT_EQ(householdCategory->getDescription(), "Prodotti per la pulizia");
    EXPECT_EQ(householdCategory->getType(), "Household");
}

TEST_F(CategoryTest, SettersAndGetters) {
    foodCategory->setName("Verdura");
    foodCategory->setDescription("Categoria per verdure fresche");

    EXPECT_EQ(foodCategory->getName(), "Verdura");
    EXPECT_EQ(foodCategory->getDescription(), "Categoria per verdure fresche");
    EXPECT_EQ(foodCategory->getType(), "Food"); // Type shouldn't change
}

TEST_F(CategoryTest, EqualityOperators) {
    FoodCategory other("Frutta", "Descrizione diversa");
    HouseholdCategory different("Pulizie", "Categoria pulizie");

    EXPECT_TRUE(*foodCategory == other);
    EXPECT_FALSE(*foodCategory != other);
    EXPECT_FALSE(*foodCategory == different);
    EXPECT_TRUE(*foodCategory != different);
}

TEST_F(CategoryTest, EmptyDescription) {
    FoodCategory emptyDesc("Latticini");
    EXPECT_EQ(emptyDesc.getDescription(), "");
    EXPECT_EQ(emptyDesc.getType(), "Food");
}

TEST_F(CategoryTest, Polymorphism) {
    std::unique_ptr<Category> baseFood = std::make_unique<FoodCategory>("Test Food");
    std::unique_ptr<Category> baseHousehold = std::make_unique<HouseholdCategory>("Test Household");

    EXPECT_EQ(baseFood->getType(), "Food");
    EXPECT_EQ(baseHousehold->getType(), "Household");
}