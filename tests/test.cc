// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cinder/Rand.h>

#include <mylibrary/direction.h>
#include <mylibrary/engine.h>
#include <mylibrary/filemanager.h>
#include <mylibrary/location.h>
#include <mylibrary/map.h>
#include <mylibrary/pacman.h>

/* DIRECTION TESTS */


/* ENGINE TESTS */


/* FILE MANAGER TESTS */


/* MAP TESTS */


/* PACMAN TESTS */

TEST_CASE("Copy constructor and operator", "[constructor][copy][operator]") {
  SECTION("Copying empty list") {
    LinkedList<int> list;
    LinkedList<int> list_copy(list);

    REQUIRE(list_copy.empty());

    LinkedList<int> copy_of_copy = list_copy;
    REQUIRE(copy_of_copy.empty());
  }

  SECTION("Copying non-empty list") {
    std::vector<int> data{ 1, 2, 3, 4, 5 };
    LinkedList<int> list(data);
    LinkedList<int> list_copy(list);

    std::cout << "List: " << list << std::endl;
    std::cout << "List deep copy: " << list_copy << std::endl;
    REQUIRE(list_copy.size() == 5);

    LinkedList<int> copy_of_copy = list_copy;
    std:: cout << "Copy of the copy: " << copy_of_copy << std::endl;
    REQUIRE(copy_of_copy.size() == 5);
  }
}
