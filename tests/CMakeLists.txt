cmake_minimum_required(VERSION 3.16)

include(FetchContent)


FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
        GIT_SHALLOW TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


enable_testing()


add_executable(run_tests
        test_Category.cpp
        test_item.cpp
        test_ShoppingList.cpp
        test_User.cpp
)


target_link_libraries(run_tests
        PRIVATE
        ShoppingListLib
        gtest_main
)


target_include_directories(run_tests PRIVATE ${CMAKE_SOURCE_DIR})


include(GoogleTest)
gtest_discover_tests(run_tests)