#ifndef Ingredient_h
#define Ingredient_h
#include <iostream>
#include <string>

using namespace std;

// Definition for the Ingredient Class

class Ingredient
{
private:
    // Ingredient Variables
    string name;
    float purchase_price;
    float sales_price;
    int inventory_quantity;
public:
    // Constructors
    Ingredient();
    Ingredient(string name, float purchase, float price, int inventory_quantity);
    
    // Functions
    string getname();
    float get_purchaseprice();
    float get_salesprice();
    int getinventory_quantity();
    void setname(string name);
    void setprice(float price);
    void addinventory(int quantity);
    void removeinventory(int quantity);
};

#endif