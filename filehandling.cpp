#include<iostream>
#include<fstream>
#include "building.h"
#include "alert.h"
#include "reading.h"
#include "admin.h"
#include "filehandling.h"
#include <QMessageBox>
using namespace std;

void loadFiles(building buildings[], int &building_counter, EnergyReading Readings[], int &reading_counter, Alert alerts[], int &alert_counter, Admin admins[], int &current_admin_numbers) {
    ifstream read("campusData.txt");

    if (!read.is_open()) {
        // لو ملقاش الفايل، هنخلي العدادات بـ 0 ونخرج بسلام
        building_counter = 0;
        reading_counter = 0;
        alert_counter = 0;
        current_admin_numbers = 0;
        return;
    }
    read >> current_admin_numbers;
    for (int i = 0; i < current_admin_numbers; i++) {
        read >> admins[i].Admin_ID;
        read >> ws;
        getline(read, admins[i].user_name);
        read >> admins[i].password;
    }
    read >> building_counter;
    for (int i = 0; i < building_counter; i++) {
        read >> buildings[i].ID;
        read >> ws;
        getline(read, buildings[i].Name);
        getline(read, buildings[i].type);
        read >> buildings[i].Monthly_Limit >> buildings[i].Total_consumption >> buildings[i].Efficiency_Score;
    }

    read >> reading_counter;
    for (int i = 0; i < reading_counter; i++) {
        read >> Readings[i].ReadingID >> Readings[i].BuildingID >> Readings[i].month >> Readings[i].consumption_value;
    }

    read >> alert_counter;
    for (int i = 0; i < alert_counter; i++) {
        read >> alerts[i].AlertID >> alerts[i].BuildingID >> alerts[i].month >> alerts[i].over_usage_amount >> alerts[i].status;
    }


    read.close();
}

void saveData(building buildings[], int &building_counter, EnergyReading Readings[], int &reading_counter, Alert alerts[], int &alert_counter, Admin admins[], int &current_admin_numbers){
    ofstream saveFile("campusData.txt");
    if (saveFile) {//Check if this file was opened
        saveFile << current_admin_numbers << endl;
        for (int i = 0; i < current_admin_numbers; i++) {
            saveFile << admins[i].Admin_ID << endl;
            saveFile << admins[i].user_name << endl;
            saveFile << admins[i].password << endl;
        }

saveFile << building_counter << endl;
            for (int i = 0; i < building_counter; i++) {
                saveFile << buildings[i].ID << endl;;
                saveFile << buildings[i].Name << endl;
                saveFile << buildings[i].type << endl;
                saveFile << buildings[i].Monthly_Limit << " " << buildings[i].Total_consumption << " " << buildings[i].Efficiency_Score << endl;

            }
saveFile <<  reading_counter << endl;
            for (int i = 0; i < reading_counter; i++) {
                saveFile << Readings[i].ReadingID << " " << Readings[i].BuildingID << " " << Readings[i].month << " " << Readings[i].consumption_value << endl;
            }
saveFile << alert_counter << endl;
            for (int i = 0; i < alert_counter; i++) {
                saveFile << alerts[i].AlertID << " " << alerts[i].BuildingID << " " << alerts[i].month << " " << alerts[i].over_usage_amount << " " << alerts[i].status << endl;
            }
            saveFile.close();
    }
    else {
        cout << " This file does not exist " << endl;
    }
}
