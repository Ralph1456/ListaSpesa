cmake_minimum_required(VERSION 3.16)
project(ShoppingList)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(shopping_list_app
        main.cpp
        Category.cpp
        Item.cpp
        ShoppingList.cpp
        User.cpp
)


add_library(ShoppingListLib STATIC
        Category.cpp
        Item.cpp
        ShoppingList.cpp
        User.cpp
        Category.h
        Item.h
        ShoppingList.h
        User.h
        Observer.h
)


target_include_directories(ShoppingListLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
