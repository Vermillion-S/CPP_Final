#include "meal.h"
#include <iostream>
#include <string>
#include <vector>
#include "Item.h"

using namespace std;

// Default Constructor
Meal::Meal()
{
    deal_price = 0;
    deal_code = 0;
    items = {};
    meal_discount = 0.0;
}

// Overloaded Constructor
Meal::Meal(vector<Item> Items, float Deal_price, int Deal_code)
{
    items = Items;
    deal_price = Deal_price;
    deal_code = Deal_code;
    meal_discount = get_discount();
}


// Returns Meal ID
int Meal::getdeal_code()
{
    return deal_code;
}

// Returns Meal Price
float Meal::getprice()
{
    return deal_price;
}
// Returns Items Vector
vector<Item> Meal::getitems()
{
    return items;
}
// Changes Meal Price
void Meal::setprice(float price)
{
    price = price;
}
// Adds Item To Meal
void Meal::add_item(Item item)
{
    items.push_back(item);
}
// Removes Item From a meal
void Meal::remove_item(Item item)
{
    // Loop over Existing Items in Meal
    for (int i = 0; i < items.size(); i++)
    {
        // Remove First instnace of the item if it exits
        if (items[i].getname() == item.getname())
        {
            items.erase(items.begin() + i);
            return;
        }
    }
    cout << "Item not found." << endl;
}

// Calculates the relative discount of the Meal compared to the original price of the items
float Meal::get_discount()
{
    float original_price = 0.0;
    // Iterates over items
    for (auto item : items)
    {
        // Add item price to the total
        original_price += item.getprice();
    }
    // return the difference between the total price and the actual price
    return (original_price - deal_price);
}