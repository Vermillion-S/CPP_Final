#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
// Found And used the String Stream Library 
// due to the program requiring a way to split strings
#include <sstream>
#include <iomanip>
#include "src\master_reference.cpp"

using namespace std;

//TaxRate
const float TAX_RATE = 1.07;

//Paths to the data files
const string INGREDIENT_FILE = "data\\Ingredient_Inventory.txt";
const string ITEMS_FILE = "data\\official_items.txt";
const string MEAL_FILE = "data\\meals.txt";
const string ORDER_FILE = "data\\Order_history.txt";
const string EMPLOYEE_FILE = "data\\employee_records.txt";

//Data structure to consolidate vector data
struct Restaurant 
{
    vector<Ingredient> Inventory;
    vector<Item> Item_Board;
    vector<Meal> Meals;
    vector<Order> Orders_Record;
    vector<Employee> Employees;
    Manager manager;
};

//Function for getting the line count of a file
int getFileLineCount(string);
//Function for Initiating the Main Menu
void MainMenu(Restaurant &);
//Function for The Manager Menu
void RestaurantManagementMenu(Restaurant &, bool = false);
//Function for The Employee Menu
void OrderMenu(Restaurant &, bool = false, Employee = Employee());
//Function for Managing Existing Order
void OrderPending(Restaurant &);
//Function for Creating NEW orders
void OrderMachine(Restaurant &, Order = Order(), bool = false);

//Function for Validating Inputs
bool input_validation(string, int);

//Instantiate Arrays from the data files
void load_data(vector<Ingredient>&, string);
void load_data(vector<Item>&, string);
void load_data(vector<Meal>&, string);
void load_data(vector<Employee>&, string);
void load_data(vector<Order>&, string);

// Function to save session data to the files
void data_to_file(vector<Ingredient>);
void data_to_file(vector<Employee>);
void data_to_file(vector<Order>);

// Convert HH:MM to hours
float clock_to_hours(string);
bool exists_in(vector<int>, int);

// Initialize Global Databases
vector<Ingredient> Inventory;
vector<Item> Item_Board;
vector<Meal> Meals;
vector<Order> Orders_Record;
vector<Employee> Employees;
// Load data into the inventory vector

int main()
{   
    //Load data from files
    //Must be loaded in this sequence
    load_data(Inventory, INGREDIENT_FILE);
    load_data(Item_Board, ITEMS_FILE);
    load_data(Meals, MEAL_FILE);
    load_data(Orders_Record, ORDER_FILE);
    load_data(Employees, EMPLOYEE_FILE);

    //Instantiating a new Test Admin With an arbitrarily large account balance
    Manager TestAdmin(1000000000.0);

    //Consolidate the data into a Restaurant object
    //This is the main object that will be used to store all the data
    Restaurant Test_Restaurant;
    Test_Restaurant.Inventory = Inventory; 
    Test_Restaurant.Item_Board = Item_Board; 
    Test_Restaurant.Meals = Meals;
    Test_Restaurant.Orders_Record = Orders_Record; 
    Test_Restaurant.Employees = Employees; 
    Test_Restaurant.manager = TestAdmin;
        
    
    // Display the main menu
    MainMenu(Test_Restaurant);    

    //Save Changes to the files
    data_to_file(Test_Restaurant.Inventory);
    data_to_file(Test_Restaurant.Orders_Record);
    data_to_file(Test_Restaurant.Employees);


    return 0;
}

int getFileLineCount(string filename)
{
    //Open the file
    ifstream file(filename);
    //Initialize Variable to retrieve lines
    string line;
    //INitialize count
    int count = 0;
    //While the get line function still runs
    //add to the count
    while (getline(file, line))
    {
        count++;
    }
    //return the count number
    return count;
}

void load_data(vector<Ingredient>& Inventory, string filepath)
{
    //create new File object
    fstream file;
    cout << "Loading data from file: " << filepath << endl;
    //Open the file in read mode
    file.open(filepath, ios::in);
    string line;
    //If the File successfully opens
    if (!file.fail())
    {
        cout<< "File opened successfully." << endl;
        while (file)
        {
            //Initialize variables to collect from String Stream
            string name;
            float purchase_price;
            float sales_price;
            int inventory_quantity;
            getline(file, line);

            //Check if the line is empty; and skip if it is
            if (line.empty()) continue;
            //split line along space delimiter to get name, price and inventory_quantity
            stringstream ss(line);
            //Get the name, price and inventory_quantity from the line
            ss >> name >> purchase_price >> sales_price >> inventory_quantity;
            //Input data into the vector as an ingredient object
            Inventory.push_back(Ingredient(name, purchase_price, sales_price, inventory_quantity));
            //if there is no newline character at the end of the line, break the loop
            if (file.eof()) break;
        }
    } 
    file.close();
}

void load_data(vector<Item>& a, string filepath)
{
    //create new File object
    fstream file;
    cout << "Loading data from file: " << filepath << endl;
    //Open the file in read mode
    file.open(filepath, ios::in);
    string line;
    
    if (!file.fail())
    {
        cout<< "File opened successfully." << endl;
        while (file)
        {
            //Initialize variables to collect from String Stream
            string name;
            float price;
            vector<string> ingredient_names;
            getline(file, line);

            //Check if the line is empty
            if (line.empty()) continue;
            //splite line along space delimiter to get name, price and inventory_quantity
            stringstream ss(line);
            //Get the name and price from the line
            ss >> name >> price;
            //Get the ingredients from the line
            string ingredient_name;
            //
            while (ss >> ingredient_name)
            {
                ingredient_names.push_back(ingredient_name);
            }
            //Create a vector of ingredients from the ingredient names
            vector<Ingredient> ingredients;
            for (auto ingredient_name : ingredient_names)
            {
                //Find the ingredient in the inventory
                //If it exists in the inventory, add it to the Item's Ingredient List
                for (auto ingredient : Inventory)
                {
                    if (ingredient.getname() == ingredient_name)
                    {
                        ingredients.push_back(ingredient);
                        break;
                    }
                }
            }
            //Input data into the vector as an Item object
            a.push_back(Item(name, price, ingredients));
            //if there is no newline character at the end of the line, break the loop
            if (file.eof()) break;
        }
    } 
    file.close();
}

void load_data(vector<Meal>& a, string filepath)
{
    //create new file object
    fstream file;
    cout << "Loading data from file: " << filepath << endl;
    //Open the file in read mode
    file.open(filepath, ios::in);
    string line;
    
    if (!file.fail())
    {
        cout<< "File opened successfully." << endl;
        while (file)
        {
            //Initialize Variables for String Stream object
            int deal_code;
            float deal_price;
            float relative_discount;
            vector<string> item_names;
            getline(file, line);

            //Check if the line is empty
            if (line.empty()) continue;
            //splite line along space delimiter to get name, price and inventory_quantity
            stringstream ss(line);
            //Get the Meal code And Meal Price from the line
            ss >> deal_code >> deal_price;
            //Get the item names from the line
            string item_name;
            while (ss >> item_name)
            {
                item_names.push_back(item_name);
            }
            //Create a vector of Items from the Item names
            vector<Item> Items;
            for (auto item_name : item_names)
            {
                //Find the Item in Official List
                for (auto item : Item_Board)
                {
                    // IF it exists
                    if (item.getname() == item_name)
                    {
                        // Add it to the item vector
                        Items.push_back(item);
                        break;
                    }
                }
            }
            //Input data into the vector as an Meal object
            a.push_back(Meal(Items, deal_price, deal_code));
            //if there is no newline character at the end of the line, break the loop
            if (file.eof()) break;
        }
    } 
    file.close();
}

void load_data(vector<Order>& a, string filepath)
{
    //Create New File
    fstream file;
    cout << "Loading data from file: " << filepath << endl;
    //Open the file in read mode
    file.open(filepath, ios::in);
    string line;
    // if the file Exists
    if (!file.fail())
    {
        cout<< "File opened successfully." << endl;
        while (file)
        {
            // Instantiate Stringstream Variables
            vector<string> item_names;
            float total_price;
            int order_num;
            string order_status;
            getline(file, line);

            //Check if the line is empty
            if (line.empty()) continue;
            //splite line along space delimiter to get name, price and inventory_quantity
            stringstream ss(line);
            //Get the Number, Status, and Price from the line
            ss >> order_num >> order_status >> total_price;
            //Get the item names from the line
            string item_name;
            while (ss >> item_name)
            {
                item_names.push_back(item_name);
            }
            
            //Create a vector of Items from the Item names
            vector<Item> Items;
            for (auto item_name : item_names)
            {
                //Find the Item in Official List
                for (auto item : Item_Board)
                {
                    // IF it exists, add it to the Items vector
                    if (item.getname() == item_name)
                    {
                        Items.push_back(item);
                        break;
                    }
                }
            }

            
            //Input data into the vector as an Order object
            a.push_back(Order(order_num, order_status, total_price, Items));
            //if there is no newline character at the end of the line, break the loop
            if (file.eof()) break;
        }
    } 
    file.close();
}

void load_data(vector<Employee>& a, string filepath)
{
    // Create new file
    fstream file;
    cout << "Loading data from file: " << filepath << endl;
    //Open the file in read mode
    file.open(filepath, ios::in);
    string line;
    // If the File opens
    if (!file.fail())
    {
        cout<< "File opened successfully." << endl;
        while (file)
        {
            // Instatiate String Stream Variables
            int id;
            string name;
            float salary;
            string password;
            float hours_worked;
            getline(file, line);
    
            //Check if the line is empty or is a comment

            if (line.empty()||line[0] == static_cast<char>('/')) continue;
            //splite line along space delimiter to get name, price and inventory_quantity
            stringstream ss(line);
            //Get the ID, Name, Salary, Password, and Hours Worked from the line
            ss >> id >> name >> salary >> password >> hours_worked;
            
            //Input data into the vector as an Employee object
            a.push_back(Employee(id, name, password, salary, hours_worked));
            //if there is no newline character at the end of the line, break the loop
            if (file.eof()) break;
        }
    } 
    file.close();
}

// Function to display the menu
void MainMenu(Restaurant &store)
{
    // Start Loop Controller
    bool session = true;
    // INitiate user input
    int choice;
    do
    {
        // Main Menu Options
        cout << "Welcome to the Restaurant Management System" << endl;
        cout << "1. Manager Restuarant" << endl;
        cout << "2. Start Register" << endl;
        cout << "3. Exit" << endl;
        cout << ">> ";
        // Take User Input
        cin >> choice;
        // Validate User Input
        if (cin.fail())
            {
                cin.clear();
                cin.ignore();
                cout << "Invalid input. Please try again." << endl;
                MainMenu(store);
            }
        // Act Based On Selection
        switch (choice)
        {
            case 1:
                // Start The Manager Menu
                RestaurantManagementMenu(store, false);
                break;
            case 2:
                // Start The Employee Menu
                OrderMenu(store, false, Employee());
                break;
            case 3:
                // End The Loop
                cout << "Exiting..." << endl;
                session = false;
                break;
            default:
                // Exception Catcher
                cout << "Invalid choice. Please try again." << endl;
                MainMenu(store);
        }
    } while (session);
    
    
    
}

// Manager Menu
void RestaurantManagementMenu(Restaurant &store, bool prior_success) 
{
    // Initialize User Input Variables
    string username, password;
    // Set Flag for Successful Login
    bool login_success = false;
    // Skip the Login if you are Already Logged in
    if (!prior_success)
    {
        cout << "Enter Username for " << store.manager.get_name() << "(Test is Admin): ";
        // Get Username
        if (input_validation(store.manager.get_username(), 3))
        {
            cout << "Enter Password (Test is 1234): ";
            // Get Password
            if (input_validation(store.manager.get_password(), 3))
            {
                // Set the login flag on successful login
                login_success = true;
            } else {login_success = false;}
        // Try Again if you fail
        }else {RestaurantManagementMenu(store);}
    }   
    
    // Give access to menu If the login is successful
    // Or if you are already Logged in
    if (login_success || prior_success)
    {
        // Variable For escape case
        const int EXIT_CASE = 8;
        cout << "Welcome " << store.manager.get_name() << endl;
        // Menu Input
        int choice;
        // Menu Choices
        cout << "1. View Inventory" << endl;
        cout << "2. View Menu" << endl;
        cout << "3. View Orders" << endl;
        cout << "4. View Employees" << endl;
        cout << "5. Add Employee" << endl;
        cout << "6. Rollout Payroll" << endl;
        cout << "7. Order Ingredients" << endl;
        cout << "8. Exit" << endl;
        cout << ">> ";
        
        // Take User Input
        cin >> choice;
        //Check if the input is valid
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Invalid input. Please try again." << endl;
            RestaurantManagementMenu(store, true);
        }else // If it Is valid
        {
            // Choose Menu Options based on the choice
            switch (choice)
            {
                case 1:
                    //View Inventory
                    store.manager.view_inventory(store.Inventory);
                    break;
                case 2:
                    //View Items
                    store.manager.view_menu(store.Item_Board, store.Meals);
                    break;
                case 3:
                    //View Orders
                    store.manager.view_order_history(store.Orders_Record);
                    break;
                case 4:
                    //View Employees
                    store.manager.view_employees_records(store.Employees);
                    break;
                case 5:
                    //Add Employee
                    store.manager.add_employee(store.Employees);
                    break;
                case 6:
                    //Rollout Payroll
                    store.manager.rollout_payroll(store.Employees);
                    break;
                case 7:
                    //Order Ingredients
                    store.manager.purchase_ingredient(store.Inventory);
                    break;
                case EXIT_CASE:
                    // Reset Flags
                    login_success = false;
                    prior_success = false;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    // Restart the menu, but already logged in
                    RestaurantManagementMenu(store, true);
            }
            //Loop until the user chooses to exit
            if (choice != EXIT_CASE)
            {
                // Restart the menu, but already logged in
                RestaurantManagementMenu(store, true);
            }
        }
    }
}

// Employee Menu
void OrderMenu(Restaurant &store, bool prior_success, Employee login_account)
{
    // Employee who is managing this session
    Employee active_employee;
    // Determines if you are successfully logged inFalse By default
    bool login_success = prior_success;
    // Skips login if you already are in a session
    if (!prior_success)
    {
        // Choose from a list of existing employees
        int choice; 
        cout << "Employee Login" << endl;
        cout << "==============" << endl;
        for (int i = 0; i < store.Employees.size(); i++)
        {
            cout << store.Employees[i].get_ID_NO() << ") " << store.Employees[i].get_name() << endl;
        }
        // Take User Input
        cout << ">> ";
        cin >> choice;
        // Fail Input if it is outside of range, or in wrong format
        if (cin.fail() || !(choice > 0 && choice <= store.Employees.size()))
        {
            cin.clear();
            cin.ignore();
            cout << "Invalid input. Please try again." << endl;
            OrderMenu(store);
        }
        // Put in the Password for the Chosen employee
        cout << "Enter Password: ";
        if (input_validation(store.Employees[choice - 1].get_password(), 3))
        {
            // Set the Users choice to the Active Employee Variable
            active_employee = store.Employees[choice - 1];
            // Set login flag
            login_success = true;

            // Prompt the User To Clock IN
            string clock_in_time;
            float clock_in_hours;
            cout << "Enter Clock In Time (HH:MM): ";

            //Check if the input is a valid Time
            do {
                cin >> clock_in_time;

                if (cin.fail() || clock_to_hours(clock_in_time) == -1.0)
                {
                    cin.clear();
                    cin.ignore();
                    cout << "Invalid input. Please try again." << endl;
                    cout << "Enter Clock In Time (HH:MM): ";
                }
            } while (clock_to_hours(clock_in_time) == -1.0);

            // Set the User's Clock in Hours
            clock_in_hours = clock_to_hours(clock_in_time);
            active_employee.clock_in(clock_in_hours);
        }
    } else {
        // Set Flags from previous session if it is still continuing
        active_employee = login_account;
        login_success = true;
    }

    // Initialize Menu if Successfully Logged IN
    if (login_success || prior_success)
    {
        // Constant for the Excape Statement
        const int EXIT_CHOICE = 5;
        // Start Menu
        cout << "Welcome " << active_employee.get_name() << endl;
        //Initialize User Input
        int choice;
        cout << "1. View Account Details" << endl;
        cout << "2. Change Password" << endl;
        cout << "3. Manage Pending Orders" << endl;
        cout << "4. Start New Orders" << endl;
        cout << "5. Exit" << endl;
        cout << ">> ";
        // Take User Input
        cin >> choice;
        //Check if the input is valid
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Invalid input. Please try again." << endl;
            OrderMenu(store, true, active_employee);
        }else
        {
            // Start Variable for when the User Clocks out
            //C++ Gets fussy with variable scope if you put them in the switch statement
            string clock_out_time;
            float clock_out_hours;
            switch (choice)
            {
                case 1:
                    //View Account Details
                    cout << "ID: " << active_employee.get_ID_NO() << endl;
                    cout << "Name: " << active_employee.get_name() << endl;
                    cout << "Pay Rate: " << active_employee.get_payrate() << endl;
                    cout << "Hours Worked: " << active_employee.get_hours_worked() << endl;
                    break;
                case 2:
                    //Change Password
                    active_employee.change_password();
                    break;
                case 3:
                    //Manage Pending Orders
                    OrderPending(store);
                    break;
                case 4:
                    // Start A New order
                    OrderMachine(store);
                   break;
                case EXIT_CHOICE:
                    
                    do {
            
                        // Propt The User to Clock out            
                        cout << "You clocked in at " << active_employee.get_clock_in_time() << endl;
                        cout << "Enter Clock In Time (HH:MM): ";
                        cin >> clock_out_time;

                        // Clock Out time Must be Later Than Clock IN time
                        if (cin.fail() || clock_to_hours(clock_out_time) == -1.0 || clock_to_hours(clock_out_time) <= active_employee.get_clock_in_time())
                        {
                            cin.clear();
                            cin.ignore();
                            clock_out_time = -1.0;
                            cout << "Invalid input. Please try again." << endl;
                            cout << "Enter Clock In Time (HH:MM): ";
                        }
                    } while (clock_to_hours(clock_out_time) == -1.0);

                    // Convert input into hours
                    clock_out_hours = clock_to_hours(clock_out_time);
                    // Clock Out
                    active_employee.clock_out(clock_out_hours);

                    // Save Session date to the employees Vector
                    store.Employees[active_employee.get_ID_NO() - 1] = active_employee;

                    // Reset Flags
                    prior_success = false;
                    login_success = false;
                    active_employee = Employee();
                    break;
                default:
                    // Exception Catcher
                    cout << "Invalid choice. Please try again." << endl;
                    OrderMenu(store, true, active_employee);
            }
            //Loop until the user chooses to exit
            //Otherwise, once the user tries to exit the main menu as well, it will recurse back into this menu
            if (choice != EXIT_CHOICE)
            {
                OrderMenu(store, true, active_employee);
            }
        }
    }
}

// Manage Existing Orders
void OrderPending(Restaurant &store)
{
    // list for Opending Order Id's
    vector<int> pending_stack;
    // Count For Pending Orders
    int pending_count = 0;

    // Iterate Through the Order Record to find pending orders
    for (int i; i < store.Orders_Record.size(); i++)
    {
        if (store.Orders_Record[i].get_order_status() == "Pending")
        {
            // Display pending Orders
            cout << "=========================" << endl;
            cout << "Order Number: " << store.Orders_Record[i].get_order_num() << endl;
            cout << "Total Price: " << store.Orders_Record[i].get_total_price() << endl;
            cout << "Items: ";
            for (auto b : store.Orders_Record[i].get_items())
            {
                cout << b.getname() << " ";
            }
            cout << endl;
            // Pust Order ID to pending vector
            pending_stack.push_back(store.Orders_Record[i].get_order_num());
            // Add to Pending COunt
            pending_count += 1;
        }
    }
    // If there is 1+ pending order
    if (pending_count > 0)
    {
        cout << "=========================" << endl;
        cout << "Enter Order Number to Complete: ";
        // Take User Input for Completion
        int order_num;
        cin >> order_num;
        // Validate Input
        if (cin.fail() || order_num < 1 || order_num > store.Orders_Record.size())
        {
            cin.clear();
            cin.ignore();
            cout << "Invalid input. Please try again." << endl;
        } else if (!exists_in(pending_stack, order_num)) 
        {
            // Cancel if the choice does not include a pending order
            cout << "Invalid input. Please try again." << endl;
        }
        else {

            cout << "=========================" << endl;
            // Complete the order
            store.Orders_Record[order_num - 1].complete_order(store.Inventory);
            // Update Store account Balance
            store.manager.add_balalnce(store.Orders_Record[order_num - 1].get_total_price());
            cout << "Order Number: " << store.Orders_Record[order_num - 1].get_order_num() << " has been completed." << endl;
            cout << "=========================" << endl;
            // Remove Order From the Pending Count
            pending_count--;
        }
    } else {cout << "No Pending Orders" << endl;}
}

// Function For Making NEW Orders
void OrderMachine(Restaurant &store, Order current_order, bool session)
{
    // Creates A new order or takes an order from a previous loop
    Order new_order = current_order;
    // Sets the order Number To a unique Integer
    new_order.set_order_num(store.Orders_Record.back().get_order_num() + 1);
    
    // Menu Input
    int choice;
    // USer Menu
    cout << "============================================" << endl;
    cout << "Welcome to the Order Machine" << endl;
    cout << "1. Add Items to Order" << endl;
    cout << "2. Add Meals to Order" << endl;
    cout << "3. Remove Last Item" << endl;
    cout << "4. View Order" << endl;
    cout << "5. Complete Order" << endl;
    cout << "6. Cancel" << endl;
    cout << ">> ";
    // Take Input
    cin >> choice;
    // validate Input
    if (cin.fail())
    {
        cin.clear();
        cin.ignore();
        cout << "Invalid input. Please try again." << endl;
        OrderMachine(store, new_order, true);
    }else 
    {
        switch (choice)
        {
            case 1:
                //Add Item to Order

                // Show Existing Items From the Menu
                cout << "Available Items: " << endl;
                for (int i = 0; i < store.Item_Board.size(); i++)
                {
                    cout << i+1 << ") " << store.Item_Board[i].getname() <<": $"<< store.Item_Board[i].getprice() << endl;
                }
                // User Input For adding an item
                cout << "Choose an Item to add: ";
                int Item_choice;
                cin >> Item_choice;
                // Validate Input
                if (cin.fail() || Item_choice > store.Item_Board.size())
                {
                    cin.clear();
                    cin.ignore();
                    cout << "Invalid input. Please try again." << endl;
                    OrderMachine(store, new_order);
                }else 
                {
                    // Add The Item to Order 
                    new_order.add_item(store.Item_Board[Item_choice-1]);
                }
                OrderMachine(store, new_order);
                break;
            case 2:
                //Add Meal to Order

                // Show Existing Items From the Menu
                cout << "Available Meals: " << endl;
                for (int i = 0; i < store.Meals.size(); i++)
                {
                    cout << "============================================" << endl;
                    cout << "Meal Number: " << store.Meals[i].getdeal_code() << ") " << store.Meals[i].getdeal_code() << endl;
                    for (auto Item : store.Meals[i].getitems())
                    {
                        cout << "   |-" << Item.getname() << endl;
                    }
                    cout << "Price:                         $" << store.Meals[i].getprice() << endl;
                    cout << "\n";
                }
                // Take User Input
                int Meal_choice;
                cin >> Meal_choice;
                // Vidate user Input
                if (cin.fail() || Meal_choice > store.Meals.size())
                {
                    cin.clear();
                    cin.ignore();
                    cout << "Invalid input. Please try again." << endl;
                    OrderMachine(store, new_order);
                }else 
                {
                    // Add Meal To Order
                    new_order.add_meal(store.Meals[Meal_choice-1]);
                }
                OrderMachine(store, new_order);
                break;
            case 3:
                //Remove last item from Order
                new_order.remove_last_item();
                OrderMachine(store, new_order);
                break;
            case 4:
                //View Order
                for (auto Item : new_order.get_items())
                {
                    cout << setprecision(2) << fixed;
                    cout << "============================================" << endl;
                    cout << Item.getname() << "                         " << endl;
                }
                cout << "============================================" << endl;
                cout << "                         " << "      Cost: $" << new_order.get_total_price() << endl;
                cout << "                         " << "       Tax: $" << new_order.get_total_price() * (TAX_RATE-1) << endl;
                cout << "                         " << "Total Cost: $" << new_order.get_total_price() * TAX_RATE << endl;
                OrderMachine(store, new_order); 
                break;
            case 5:
                //Complete Order
                store.Orders_Record.push_back(new_order);
                break;
            case 6:
                // Leave Without Saving
                break;
            default:
                // Exception Catcher
                cout << "Invalid choice. Please try again." << endl;
                OrderMachine(store, new_order);
        }
    }
}

// Determines if an integer Exists in a vector
bool exists_in(vector<int> list, int value)
{
    // Iterates with an algorithm
    auto it = find(list.begin(), list.end(), value);
    // The Iterator being at the end of the vector means it did not find 
    // Return if it was found or not
    if (it != list.end()) {
        return true;
    }else {return false;}
}

// Takes User Input With A variable set of tries || Setting Max Tries to -1 Gives Unlimited Tries
bool input_validation(string expected_input, int max_tries)
{
    // Set Curren amount of tries
    int tries = 0;
    // Variable For User Input
    string input;
    // Loop While failures are less than the amount of available tries
    while (tries < max_tries || max_tries == -1)
    {
        // Take User Input
        cin >> input;
        // Validate User Input
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Invalid input. Please try again." << endl;
            // Bad Input Counts as failure
            // Add to fail count
            tries++;
            continue;
        }
        if (input == expected_input)
        {
            // End Function if the Input Matches
            return true;
        }
        else {
            cout << "Invalid Input\n>> ";
            // Add to fail count
            tries++;
        }
    }

    // End if Max tries are exceeded
    cout << "Too many tries" << endl;
    return false;
};

// Converts a HH:MM format to a float of hours
float clock_to_hours(string clock_in_time)
{
    //Convert String to a stringstream object
    stringstream ss(clock_in_time);
    //Iniitialize the variables
    int hours, minutes;
    char colon = ':';
    //Get the hours and minutes from the stringstream object
    ss >> hours >> colon >> minutes;
    //Check if the input is valid and if the hours and minutes are within the valid range
    if (ss.fail() || colon != ':' || hours < 0 || hours > 23 || minutes < 0 || minutes > 59)
    {
        return -1.0;
    }
    return hours + (minutes / 60.0);   
}

// Plugs data back into its respective file
void data_to_file(vector<Ingredient> Inventory)
{
    // Create New File Object
    fstream file;
    cout << "Saving data to file: " << INGREDIENT_FILE << endl;
    //Open the file in write mode
    file.open(INGREDIENT_FILE, ios::out);
    if (!file.fail())
    {
        cout<< "File opened successfully." << endl;
        //For Every Instance in the Vector
        for (auto a : Inventory)
        {
            // Output to the file in this set format
            file << a.getname() << " " << a.get_purchaseprice() << " " << a.get_salesprice() << " " << a.getinventory_quantity() << endl;
        }
    } 
    // Close the file
    file.close();
    cout << "Data saved successfully." << endl;
}
// Plugs data back into its respective file
void data_to_file(vector<Order> Orders_Record)
{
    // Create new File Object
    fstream file;
    cout << "Saving data to file: " << ORDER_FILE << endl;
    //Open the file in write mode
    file.open(ORDER_FILE, ios::out);
    if (!file.fail())
    {
        cout<< "File opened successfully." << endl;
        //For Every Instance in the Vector
        for (auto a : Orders_Record)
        {
            file << a.get_order_num() << " " << a.get_order_status() << " " << a.get_total_price() << " ";
            // Output to the file in this set format
            for (auto b : a.get_items())
            {
                file << b.getname() << " ";
            }
            file << endl;
        }
    }
    // Close The File
    file.close();
    cout << "Data saved successfully." << endl;
}
// Plugs data back into its respective file
void data_to_file(vector<Employee> Employees)
{
    // Creat New File Object
    fstream file;
    cout << "Saving data to file: " << EMPLOYEE_FILE << endl;
    //Open the file in write mode
    file.open(EMPLOYEE_FILE, ios::out);
    if (!file.fail())
    {
        cout<< "File opened successfully." << endl;
        // Iterate Through The Vector
        for (auto a : Employees)
        {
            // Write Out the Data
            file << a.get_ID_NO() << " " << a.get_name() << " " << a.get_payrate() << " " << a.get_password() << " " << a.get_hours_worked() << endl;
        }
    } 
    file.close();
    cout << "Data saved successfully." << endl;
}