#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "src\master_reference.cpp"

using namespace std;

// UNIT TEST FOR THE PROJECTS CLASS OBJECTS

// Runs Every Single Class Function

int main()
{
    try
    {
        struct Restaurant 
        {
            vector<Ingredient> Inventory;
            vector<Item> Item_Board;
            vector<Meal> Meals;
            vector<Order> Orders_Record;
            vector<Employee> Employees;
        };

        Restaurant test_struct;


        // Test Ingredient Class
        cout << "==================================" << endl;
        cout << "||  TEST FOR INGREDIENT CLASS   ||" << endl;
        cout << "==================================" << endl;

        auto Lettuce = Ingredient("Lettuce", 0.25, 0.33, 125);
        cout << Lettuce.getname() << endl;
        cout << Lettuce.get_salesprice() << endl;
        cout << Lettuce.get_purchaseprice() << endl;
        cout << Lettuce.getinventory_quantity() << endl;

        Lettuce.setname("New Lettuce");
        Lettuce.setprice(55.55);
        Lettuce.addinventory(1);

        cout << Lettuce.getname() << endl;
        cout << Lettuce.get_salesprice() << endl;
        cout << Lettuce.get_purchaseprice() << endl;
        cout << Lettuce.getinventory_quantity() << endl;

        auto Carrot = Ingredient("Carrot", 0.25, 0.33, 125);

        test_struct.Inventory.push_back(Lettuce);
        test_struct.Inventory.push_back(Carrot);

        // Test Item Class
        cout << "=============================" << endl;
        cout << "||  TEST FOR ITEMS CLASS   ||" << endl;
        cout << "=============================" << endl;

        auto test_item = Item("Test_item", 12.22, {Lettuce});
        cout << test_item.getname() << endl;
        cout << test_item.getprice() << endl;
        for (auto a : test_item.getingredients())
        {
            cout << "   |-" << a.getname() << endl;
        }

        test_struct.Item_Board.push_back(test_item);

        test_item.setname("Practice_name");
        test_item.setprice(14.22);
        test_item.add_ingredients(Carrot);
        test_item.add_ingredients(Carrot);
        test_item.remove_ingredients(Lettuce);

        cout << test_item.getname() << endl;
        cout << test_item.getprice() << endl;
        for (auto a : test_item.getingredients())
        {
            cout << "   |-" << a.getname() << endl;
        }

        test_struct.Item_Board.push_back(test_item);

        // Test Meal Class
        cout << "============================" << endl;
        cout << "||  TEST FOR MEAL CLASS   ||" << endl;
        cout << "============================" << endl;

        auto test_meal = Meal({test_struct.Item_Board[0]}, 5.55, 1);

        cout << test_meal.getdeal_code() << endl;
        cout << test_meal.getprice() << endl;
        cout << test_meal.get_discount() << endl;
        for (auto a : test_meal.getitems())
        {
            cout << "   |-" << a.getname() << endl;
        }

        test_struct.Meals.push_back(test_meal);

        test_meal.setprice(25.55);
        test_meal.add_item(test_struct.Item_Board[1]);
        test_meal.remove_item(test_struct.Item_Board[0]);

        cout << test_meal.getdeal_code() << endl;
        cout << test_meal.getprice() << endl;
        cout << test_meal.get_discount() << endl;

        test_struct.Meals.push_back(test_meal);

        // Test Employee Class
        cout << "===============================" << endl;
        cout << "||  TEST FOR EMPLOYEE CLASS  ||" << endl;
        cout << "===============================" << endl;

        auto test_employee1 = Employee(1, "John Doe", "Cat123", 22.22, 5);
        cout << test_employee1.get_ID_NO() << endl;
        cout << test_employee1.get_name() << endl;
        cout << test_employee1.get_password() << endl;
        cout << test_employee1.get_payrate() << endl;
        cout << test_employee1.get_hours_worked() << endl;
        test_employee1.clock_in(12.22);
        cout << test_employee1.get_clock_in_time() << endl;

        test_struct.Employees.push_back(test_employee1);

        test_employee1.set_ID_NO(2);
        test_employee1.set_name("Jane Doe");
        test_employee1.set_hours_worked(12);
        test_employee1.set_payrate(222);
        
        test_employee1.clock_out(15.12);
        test_employee1.change_password();

        cout << test_employee1.get_ID_NO() << endl;
        cout << test_employee1.get_name() << endl;
        cout << test_employee1.get_password() << endl;
        cout << test_employee1.get_payrate() << endl;
        cout << test_employee1.get_hours_worked() << endl;
        test_employee1.clock_in(12.22);
        cout << test_employee1.get_clock_in_time() << endl;

        test_struct.Employees.push_back(test_employee1);

        // Test Order Class
        cout << "==============================" << endl;
        cout << "||   TEST FOR ORDER CLASS   ||" << endl;
        cout << "==============================" << endl;

        
        auto Order_1 = Order(1,"Pending", 14.22, {test_struct.Item_Board[0],test_struct.Item_Board[1]});
        Order Order_2;
        cout << "ORDER 1" << endl;
        cout << Order_1.get_order_num() << endl;
        cout << Order_1.get_order_status() << endl;
        cout << Order_1.get_total_price() << endl;
        for (auto a : Order_1.get_items())
        {
            cout << "   |-" << a.getname() << endl;
        }
        cout << "ORDER 2" << endl;
        cout << Order_2.get_order_num() << endl;
        cout << Order_2.get_order_status() << endl;
        cout << Order_2.get_total_price() << endl;
        for (auto a : Order_2.get_items())
        {
            cout << "   |-" << a.getname() << endl;
        }

        Order_1.add_item(test_struct.Item_Board[0]);
        Order_1.complete_order(test_struct.Inventory);

        Order_2.add_meal(test_struct.Meals[0]);
        Order_2.set_order_num(2);
        Order_2.set_order_status("Custom Status");
        Order_2.set_total_price(33.33);
        Order_2.remove_last_item();

        auto Order_3 = Order_2;
        
        Order_3.clear_order();

        cout << "ORDER 1" << endl;
        cout << Order_1.get_order_num() << endl;
        cout << Order_1.get_order_status() << endl;
        cout << Order_1.get_total_price() << endl;
        for (auto a : Order_1.get_items())
        {
            cout << "   |-" << a.getname() << endl;
        }
        cout << "ORDER 2" << endl;
        cout << Order_2.get_order_num() << endl;
        cout << Order_2.get_order_status() << endl;
        cout << Order_2.get_total_price() << endl;
        for (auto a : Order_2.get_items())
        {
            cout << "   |-" << a.getname() << endl;
        }

        cout << "ORDER 3" << endl;
        cout << Order_3.get_order_num() << endl;
        cout << Order_3.get_order_status() << endl;
        cout << Order_3.get_total_price() << endl;
        for (auto a : Order_3.get_items())
        {
            cout << "   |-" << a.getname() << endl;
        }

        // Test Manager Class
        cout << "==============================" << endl;
        cout << "||  TEST FOR MANAGER CLASS  ||" << endl;
        cout << "==============================" << endl;
        
        auto manager = Manager(12345);

        manager.get_username();
        manager.get_password();
        
        manager.view_inventory(test_struct.Inventory);
        manager.view_menu(test_struct.Item_Board, test_struct.Meals);
        manager.view_order_history(test_struct.Orders_Record);
        manager.view_employees_records(test_struct.Employees);
        
        manager.add_balalnce(1222);
        manager.add_employee(test_struct.Employees);
        manager.purchase_ingredient(test_struct.Inventory);
        manager.rollout_payroll(test_struct.Employees);

        manager.view_inventory(test_struct.Inventory);
        manager.view_menu(test_struct.Item_Board, test_struct.Meals);
        manager.view_order_history(test_struct.Orders_Record);
        manager.view_employees_records(test_struct.Employees);
    }
    catch(const exception& e)
    {
        // Print exception
        cerr << e.what() << '\n';
    }

    return 0;
}