#include "Ingredient.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// INGREDIENT CLASS

// Default Constructor
Ingredient::Ingredient()
{
    name = "Unknown";
    purchase_price = 0.0;
    sales_price = 0.0;
    inventory_quantity = 0;
}

// Overloaded Constructor
Ingredient::Ingredient(string Name, float purchase, float price, int Inventory_quantity)
{
    name = Name;
    purchase_price = purchase;
    sales_price = price;
    inventory_quantity = Inventory_quantity;
}
// Returns Ingredient Name
string Ingredient::getname()
{
    return name;
}

// Returns Purchase Price
float Ingredient::get_purchaseprice()
{
    return purchase_price;
}
// Returns Sales Price
float Ingredient::get_salesprice()
{
    return sales_price;
}

// Returns INventory QUantitiy
int Ingredient::getinventory_quantity()
{
    return inventory_quantity;
}
// Sets INgredient Name
void Ingredient::setname(string name)
{
    name = name;
}
// sets Sales Price
void Ingredient::setprice(float price)
{
    sales_price = price;
}

// Adds to inventory quantity by a specified amount
void Ingredient::addinventory(int quantity)
{
    inventory_quantity += quantity;
}
// Adds to inventory quantity by a specified amount
// Cant Remove Less than zero
void Ingredient::removeinventory(int quantity)
{
    if (quantity > inventory_quantity || quantity < 0)
    {
        cout << "Not enough inventory to remove." << endl;
        return;
    } else if (quantity < 0)
    {
        cout << "Invalid quantity." << endl;
        return;
    }

    inventory_quantity -= quantity;
}