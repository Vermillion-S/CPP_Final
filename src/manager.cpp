#include "manager.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

// Default Constructor
Manager::Manager(): Employee()
{
    Name = "Test_Admin";
    Admin_username = "Admin";
    Admin_password = "1234"; // default password
    store_account_balance = 0.0;
}

// Overloaded Constructor
Manager::Manager(float balance)
{
    Name = "Test_Admin";
    store_account_balance = balance;
    Admin_username = "Admin";
    Admin_password = "1234"; // default password
}

// Returns Username
string Manager::get_username()
{
    return Admin_username;
}

// Returns Password
string Manager::get_password()
{
    return Admin_password;
}

// Shows Inventory
void Manager::view_inventory(vector<Ingredient> &Inventory)
{
    // Loops through the INventory Database
    // Displays Ingredient Info
    for (auto Ing : Inventory)
    {
        cout <<"======================" << endl;
        cout << "Name: " << Ing.getname() << endl;
        cout << "Purchase Price: " << Ing.get_salesprice() << endl;
        cout << "Inventory Quantity: " << Ing.getinventory_quantity() << endl;
    }
    cout <<"======================" << endl;
}

void Manager::view_menu(vector<Item> &Item_Board, vector<Meal> &Meals)
{
    // Loops through the Items and Meals Database
    // Displays Item Info
    for (auto Item : Item_Board)
    {
        cout <<"======================" << endl;
        cout << "Name: " << Item.getname() << endl;
        cout << "Price: " << Item.getprice() << endl;
        cout << "Ingredients: " << endl;
        // Displays Ingredients Included in the Items
        for (auto Ing : Item.getingredients())
        {
            cout << "   |-" << Ing.getname() << endl;
        }
    }
    cout <<"======================" << endl;

    // Displays Meal Info
    for (auto Meal : Meals)
    {
        cout <<"======================" << endl;
        cout << "Deal Code: " << Meal.getdeal_code() << endl;
        cout << "Price: " << Meal.getprice() << endl;
        cout << "Items: " << endl;
        // Dispays Items included in the meal
        for (auto Item : Meal.getitems())
        {
            cout << "   |-" << Item.getname() << endl;
        }
    }
    cout <<"======================" << endl;
}

// Diplays Order History
void Manager::view_order_history(vector<Order> &OrderHistory)
{
    // Loops through Order Database
    // Displays order INfo
    for (auto Order : OrderHistory)
    {
        cout <<"======================" << endl;
        cout << "Order Number: " << Order.get_order_num() << endl;
        cout << "Order Status: " << Order.get_order_status() << endl;
        cout << "Total Price: " << Order.get_total_price() << endl;
        cout << "Items: " << endl;
        // Dispays Items included in the Order
        for (auto Item : Order.get_items())
        {
            cout << "   |-" << Item.getname() << endl;
        }
    }
    cout <<"======================" << endl;
}

// Displays Employee Records
void Manager::view_employees_records(vector<Employee> &Employees)
{
    // Loops Through Employee Database
    // Displays Info
    for (auto Employee : Employees)
    {
        cout <<"======================" << endl;
        cout << "ID: " << Employee.get_ID_NO() << endl;
        cout << "Name: " << Employee.get_name() << endl;
        cout << "Pay Rate: " << Employee.get_payrate() << endl;
        cout << "Hours Worked: " << Employee.get_hours_worked() << endl;
    }
    cout <<"======================" << endl;
}

// Adds a new Employee to the Employee Database
// This exists as a Function in the Manager Class for Security Reasons
void Manager::add_employee(vector<Employee> &Employees)
{
    // New Employee Object
    Employee new_employee;

    //Initialize Variables
    int id = Employees.back().get_ID_NO() + 1; // Set Id to the Last in the database
    string name;
    float salary;

    // Take User INput
    cout << "Enter Employee Name: ";
    cin >> name;
    // Validate Input
    if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Invalid input. Please try again." << endl;
            add_employee(Employees);
        }
    // Take User INput
    cout << "Enter Employee Salary: ";
    cin >> salary;
    // Validate Input
    if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Invalid input. Please try again." << endl;
            add_employee(Employees);
        }
    
    // Set data based on variables
    new_employee.set_ID_NO(id);
    new_employee.set_name(name);
    new_employee.set_payrate(salary);

    //Add the employee to the vector
    Employees.push_back(new_employee);
    cout << "Employee added successfully." << endl;
}

// Purchases Ingredients and Adds it to the Inventory
void Manager::purchase_ingredient(vector<Ingredient> &Inventory)
{
    // Initialize Input Variables
    string name;
    int purchase_volume;

    // Take User Input for the chosen Ingredient
    cout << "Enter Ingredient Name: ";
    cin >> name;
    // Loop over The INventory Database
    for (int i = 0; i < Inventory.size(); i++)
    {
        // Determines if Ingredient Exists
        if (Inventory[i].getname() == name)
        {
            // Take User input for Purchase Volume
            cout << "Current Inventory: " << Inventory[i].getinventory_quantity() << endl;
            cout << "Enter How much: " << Inventory[i].getname() << " to purchase: ";
            cin >> purchase_volume;
            // Validate Input
            if (cin.fail())
                {
                    cin.clear();
                    cin.ignore();
                    cout << "Invalid input. Please try again." << endl;
                    
                    purchase_ingredient(Inventory);
                }
            //Check if the store has enough funds to purchase the ingredients
            if (Inventory[i].get_purchaseprice() * purchase_volume > store_account_balance)
            {
                cout << "Not enough funds to purchase ingredient." << endl;
            }
            //modify ingredient inventory count to the vector
            Inventory[i].addinventory(purchase_volume);
            cout << "New Inventory: " << Inventory[i].getinventory_quantity() << endl;
            //Update the store account balance
            store_account_balance -= Inventory[i].get_purchaseprice() * purchase_volume;
            cout << "Ingredient purchased successfully." << endl;
            return;
        }else {cout << "Ingredient not found." << endl;}
    }
}

// Function For Paying employees
void Manager::rollout_payroll(vector<Employee> &Employees)
{
    // Initialize Counter Variable
    float funds_needed;
    // Loop through Employee Database
    for (auto employee : Employees)
    {
        // Pay = Pay/Hr * Hrs Worked
        funds_needed += employee.get_payrate() * employee.get_hours_worked();
    }
    // Throw an error if there is not enough funds
    if (funds_needed > store_account_balance)
    {
        cout << "Not enough funds to rollout payroll." << endl;
        return;
    }else if (funds_needed <= store_account_balance) // If there is enough money...
    {
        // Update store balance
        store_account_balance -= funds_needed;
        // Reset Hours worked
        for (int i = 0; i < Employees.size(); i++)
        {
            Employees[i].set_hours_worked(0.0);
        }
        cout << "Payroll rolled out successfully." << endl;
    }
}

// Update Store Balance (For Completing Orders)
void Manager::add_balalnce(float amount)
{
    store_account_balance += amount;
    cout << "Store account balance updated successfully." << endl;
    cout << "New Store Account Balance: " << store_account_balance << endl;
}