#pragma once
#include <string>
using namespace std;
// declare admin struct
struct Admin {
	int Admin_ID;
	string user_name;
	string password;
};
// declare function to validate admin login ---> sama
bool Admin_login(Admin admins[], int &current_admin_numbers, string inputUser_name, string inputPassword);
bool admin_signup(Admin admins[], int& current_admin_numbers, string newuser, string newpass);

// declare function to sign up new admin ---> sama



