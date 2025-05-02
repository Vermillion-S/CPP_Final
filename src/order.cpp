#include "order.h"
#include "meal.h"
#include "Item.h"
#include "Ingredient.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;


// Default Constructor
Order::Order()
{
    order_num = 0;
    order_status = "Pending";
    items = {};
    total_price = 0.0;
}

// Overloaded COnstructor
Order::Order(int Order_num, string Order_status, float Total_price, vector<Item> Items)
{
    order_num = Order_num;
    order_status = Order_status;
    total_price = Total_price;
    items = Items;
}

// Adds Item to the order
void Order::add_item(Item item)
{
    // Push to vector
    items.push_back(item);
    // Add to total price
    total_price += item.getprice();
}
// Removes the last item from the items vector
void Order::remove_last_item()
{
    // Subtracts from total price
    total_price -= items.back().getprice();
    // Remove the item
    items.pop_back();
    cout << "Successfully Removed Last Item" << endl;
}
// Changes Total Price
void Order::set_total_price(float price)
{
    total_price = price;
}
// Changes Order Number
void Order::set_order_num(int num)
{   
    order_num = num;
}
// Adds a meal to Order
void Order::add_meal(Meal meal)
{
    // Iterate Through the items and add them to the order List
    for (int i = 0; i < meal.getitems().size(); i++)
    {
        items.push_back(meal.getitems()[i]);
    }
    // Add the Meals Price instead of the individual items
    total_price += meal.getprice();
}

// Returns Orde Price
float Order::get_total_price()
{
    return total_price;
}

//
void Order::print_order()
{
    cout << "Order Number: " << order_num << endl;
    cout << "Order Status: " << order_status << endl;
    cout << "Items:" << endl;
    for (int i = 0; i < items.size(); i++)
    {
        cout << items[i].getname() << " - $" << items[i].getprice() << endl;
    }
    cout << "Total Price: $" << total_price << endl;
}
// Resets the order
void Order::clear_order()
{
    items.clear();
    total_price = 0.0;
}
// Sets the ORder Status
void Order::set_order_status(string status)
{
    order_status = status;
}

// Retrieves the order status
string Order::get_order_status()
{
    return order_status;
}

// Returns Order Number
int Order::get_order_num()
{
    return order_num;
}

// Returns Item Vector
vector<Item> Order::get_items()
{
    return items;
}

// Completes Pending Orders
void Order::complete_order(vector<Ingredient> &Inventory)
{
    // Updates Order Status
    order_status = "Completed";
    
    //update ingredient inventory
    // Iterate Through Items
    for (int i = 0; i < items.size(); i++)
    {
        // Iterate Through Item Ingredients
        for (int j = 0; j < items[i].getingredients().size(); j++)
        {
            // Iterate Through inventory
            for (int k = 0; k < Inventory.size(); k++)
            {
                // Remove Ingredients found in the completed Order From the inventory Database
                if (items[i].getingredients()[j].getname() == Inventory[k].getname())
                {
                    Inventory[k].removeinventory(1);
                }
            }
            
            
        }
    }
}