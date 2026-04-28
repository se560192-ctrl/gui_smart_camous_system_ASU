#include<iostream>
#include<string>
#include "building.h"
#include "alert.h"
#include "reading.h"
#include "admin.h"
#include <QMessageBox>
using namespace std;
//define function to validate admin login ---> sama

int Number_of_Admins = 5;
bool Admin_login(Admin admins[], int &current_admin_numbers, string inputUser_name, string inputPassword) {
    QMessageBox::information(nullptr, "Debug", "Current Admins in Memory: " + QString::number(current_admin_numbers));
        for (int i = 0; i < current_admin_numbers; i++) {
			if (admins[i].user_name == inputUser_name && admins[i].password == inputPassword)
				return true;
	}
	return false;
}


bool admin_signup(Admin admins[], int& current_admin_numbers, string newuser, string newpass) {
    if (current_admin_numbers < 5) {
        admins[current_admin_numbers].Admin_ID = current_admin_numbers + 1;
        admins[current_admin_numbers].user_name = newuser;
        admins[current_admin_numbers].password = newpass;
        current_admin_numbers++;
        return true; // تمت الإضافة بنجاح
    }
    return false; // الداتابيز مليانة!
}