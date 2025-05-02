#ifndef meal_h
#define meal_h
#include <iostream>
#include <string>
#include <vector>
#include "Item.h"

using namespace std;

// Definition for the MEAL class

class Meal
{
private:
    // variables
    int deal_code;
    float price;
    float deal_price;
    vector<Item> items;
    float meal_discount;
public:
    // Constructors
    Meal();
    Meal(vector<Item> items, float deal_price, int deal_code);

    // Functions
    int getdeal_code();
    float getprice();
    void setprice(float price);
    void add_item(Item item);
    void remove_item(Item item);
    vector<Item> getitems();
    float get_discount();
};

#endif