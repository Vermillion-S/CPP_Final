#ifndef manager_h
#define manager_h
#include <iostream>
#include <string>
#include <vector>
#include "employee.h"
#include "Ingredient.h"

using namespace std;

// Definition of the Manager Class

// Child of the Employee Class
class Manager : public Employee
{
    private:
        // Variables
        string Admin_username;
        string Admin_password;
        float store_account_balance;
    public:
        // Constructors
        Manager();
        Manager(float balance);

        // Functions
        string get_username();
        string get_password();
        void add_employee(vector<Employee> &Employees);
        void view_employees_records(vector<Employee> &Employees);
        void view_order_history(vector<Order> &OrderHistory);
        void view_inventory(vector<Ingredient> &Inventory);
        void view_menu(vector<Item> &Item_Board, vector<Meal> &Meals);
        void purchase_ingredient(vector<Ingredient> &Inventory);
        void rollout_payroll(vector<Employee> &Employees);
        void add_balalnce(float amount);
};

#endif