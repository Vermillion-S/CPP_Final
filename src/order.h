#ifndef order_h
#define order_h
#include <iostream>
#include <string>
#include <vector>
#include "Item.h"
#include "meal.h"

using namespace std;

// Definition for the ORDER Class

class Order
{
    private:
        // Variables
        vector<Item> items;
        float total_price;
        int order_num;
        string order_status;
        
    public:
        // Constructors
        Order();
        Order(int order_num, string order_status, float total_price, vector<Item> items);

        // Functions
        void add_item(Item Item);
        void remove_last_item();
        void set_total_price(float price);
        void add_meal(Meal meal);
        float get_total_price();
        void print_order();
        void clear_order();
        void set_order_num(int);
        void set_order_status(string status);
        string get_order_status();
        int get_order_num();
        vector<Item> get_items();
        void complete_order(vector<Ingredient>&);
};

#endif