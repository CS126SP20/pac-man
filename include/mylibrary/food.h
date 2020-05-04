//
// Created by Brianna Zhang on 5/1/20.
//

#ifndef FINALPROJECT_FOOD_H
#define FINALPROJECT_FOOD_H

#include "location.h"
#include "food_type.h"

namespace myapp {

class Food {
 public:
  // Constructor
  explicit Food(const Location& given_loc, const FoodType& given_type);

  // Getter for the location of the food
  Location GetLocation() const;

  // Getter for the type of the food
  FoodType GetFoodType() const;

 private:
  Location loc;
  FoodType food_type;
};
}

#endif  // FINALPROJECT_FOOD_H
