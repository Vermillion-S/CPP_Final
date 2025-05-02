#ifndef employee_h
#define employee_h
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Definition FOr the EMployee Class
class Employee
{
    protected:
        // Variables shared with child classes
        int ID_NO;
        string Name;
        string password;
    private:
        // Employee Variables
        float payrate;
        float clock_in_time;
        float hours_worked;
    public:
        //Constructor
        Employee();
        // Constructor
        Employee(int id, string name, string password, float salary, float Hours_worked);

        // Functions
        float get_payrate();
        void set_payrate(float salary);
        float get_hours_worked();
        void set_hours_worked(float hours);
        void clock_in(float time);
        float get_clock_in_time();
        void clock_out(float time);
        int get_ID_NO();
        void set_ID_NO(int id);
        string get_password();
        string get_name();
        void set_name(string name);
        void change_password();
};

#endif