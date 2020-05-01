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
  explicit Food(const Location& given_loc, const FoodType& given_type);

  Location GetLocation() const;
  Location SetLocation(const Location& given_loc);

  FoodType GetFoodType() const;
  FoodType SetFoodType(const FoodType& given_type);

 private:
  Location loc;
  FoodType food_type;
};
}

#endif  // FINALPROJECT_FOOD_H
