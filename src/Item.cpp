#include "Item.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Default Constructor
Item::Item()
{
    name = "Default Item";
    price = 0;
    ingredients = {};
}
// Constructor with parameters
Item::Item(string Name, float Price, vector<Ingredient> default_ingredients)
{
    name = Name;
    price = Price;
    ingredients = default_ingredients;
}
// Returns Item Name
string Item::getname()
{
    return name;
}
// Returns Item price
float Item::getprice()
{
    return price;
}
// Returns a vector of The Item's INgredients
vector<Ingredient> Item::getingredients()
{
    return ingredients;
}
// Changes Item Name
void Item::setname(string Name)
{
    name = Name;
}
// Changes Item Price
void Item::setprice(float Price)
{
    price = Price;
}
// Adds ingredient to the item
void Item::add_ingredients(Ingredient ingredient)
{
    ingredients.push_back(ingredient);
}
// Removes Ingredient From the Item
void Item::remove_ingredients(Ingredient ingredient)
{
    // Iterate Through Item's Ingredient List
    for (int i = 0; i < ingredients.size(); i++)
    {
        // Remove The first instance of that ingredient if it exists
        if (ingredients[i].getname() == ingredient.getname())
        {
            ingredients.erase(ingredients.begin() + i);
            return;
        }
    }
    cout << "Ingredient not found." << endl;
}
