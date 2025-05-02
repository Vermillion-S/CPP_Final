#include "employee.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Default Constructor
Employee::Employee()
{
    ID_NO = 0;
    Name = "Default Employee";
    password = "1234"; // default password
    payrate = 0.0;
    clock_in_time = 0.0;
    hours_worked = 0.0;
}

// OverLoaded Constructor
Employee::Employee(int id, string name, string Password, float salary, float Hours_worked)
{
    ID_NO = id;
    Name = name;
    password = Password;
    payrate = salary;
    clock_in_time = 0.0;
    hours_worked = Hours_worked;

}
// Return ID NUMBer
int Employee::get_ID_NO()
{
    return ID_NO;
}
// Returns Employee Name
string Employee::get_name()
{
    return Name;
}
// Sets Employee Name
void Employee::set_name(string name)
{
    Name = name;
}
// Returns Pay rate /hr
float Employee::get_payrate()
{
    return payrate;
}
// Returns Clock in Time hrs from 00:00
float Employee::get_clock_in_time()
{
    return clock_in_time;
}
// Sets The Payrate
void Employee::set_payrate(float salary)
{
    payrate = salary;
}
// Returns Hours Worked
float Employee::get_hours_worked()
{
    return hours_worked;
}
// Sets The Hours Worked
void Employee::set_hours_worked(float hours)
{
    hours_worked = hours;
}
// Sets The clock in time
void Employee::clock_in(float time)
{
    clock_in_time = time;
}
// Clocks out
void Employee::clock_out(float time)
{
    // Sets Hours worked from the difference
    // Between the Clock out and Clock in times
    hours_worked += time - clock_in_time;
    // Resets Clock IN time
    clock_in_time = 0.0;
}
//Changes user Password
void Employee::change_password()
{
    // Initialize user INput
    string password_attempt;
    cout << "Enter old password(Type X to Exit): ";
    // Takes User input
    cin >> password_attempt;
    if (password_attempt == "X" || password_attempt == "x") // Loop on Failure
    {
        // Breaks on Blank input
        cout << "Exiting..." << endl;
        
    } else if (password_attempt == password) {
        // INput New Password
        string new_password;
        cout << "Enter new password: ";
        cin >> new_password;

        if (new_password != password) {
            password = new_password;
            cout << "Password changed successfully." << endl;
        } else if (new_password == password) {
            // Prevents Setting Password To What it once was
            cout << "New password cannot be same as old password." << endl;
            change_password();
        }
    } else if (password_attempt != password) {
        cout << "Incorrect password." << endl;
        change_password();
    }
}
// Returns Employee Password
string Employee::get_password()
{
    return password;
}
// Sets Employee ID number
void Employee::set_ID_NO(int id)
{
    ID_NO = id;
}
