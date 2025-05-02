#ifndef Item_h
#define Item_h
#include <iostream>
#include <string>
#include <vector>
#include "Ingredient.h"

using namespace std;

// Definition for the Item Class

class Item
{
private:
    // Item Variables
    string name;
    float price;
    vector<Ingredient> ingredients;
public:
    // Constructors
    Item();
    Item(string name, float price = 0.0, vector<Ingredient> default_ingredients = {});

    // Functions
    string getname();
    float getprice();
    void setname(string name);
    void setprice(float price);
    void add_ingredients(Ingredient ingredient);
    void remove_ingredients(Ingredient ingredient);
    vector<Ingredient> getingredients();
    
};

#endif