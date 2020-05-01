//
// Created by Brianna Zhang on 5/1/20.
//

#ifndef FINALPROJECT_FOOD_H
#define FINALPROJECT_FOOD_H

#include "location.h"

namespace myapp {

class Food {
  enum class FoodType {
    kNormal;
    kSpecial;
    kCherry;
  };

 public:
  Food(const Location& given_loc, const FoodType& given_type);

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
