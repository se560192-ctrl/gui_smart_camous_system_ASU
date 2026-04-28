#include<iostream>
#include<string>
#include "building.h"
#include "alert.h"
#include "reading.h"
#include "admin.h"
using namespace std;
// define function to calculate efficiency score --> sondus
void calculateEfficiencyScore(building buildings[],int building_counter) {
	for (int i = 0; i < building_counter; i++) {
		if (buildings[i].Monthly_Limit > 0) {

			buildings[i].Efficiency_Score = ((buildings[i].Monthly_Limit - buildings[i].Total_consumption) / buildings[i].Monthly_Limit) * 100;
		}
		else {
			buildings[i].Efficiency_Score = 0;
		}
	}
	cout << "Efficiency score updated successfully" << endl;

}

//define function to add new building ---> basmala
void AddBuilding(building &buildings,int &building_counter)
{
	int id;
	string name;
	string type;
	float monthly_limit;
	cout << "Enter building ID: ";
	cin >> id;
	cout << "Enter building name: ";
	cin.ignore(); // Ignore the newline character left in the input buffer 
	getline(cin, name);
	cout << "Enter building type: ";
	getline(cin, type);
	cout << "Enter monthly limit: ";
	cin >> monthly_limit;
	buildings.ID = id;
	buildings.Name = name;
	buildings.type = type;
	buildings.Monthly_Limit = monthly_limit;
	buildings.Total_consumption = 0.0; // Initialize total consumption to 0
	buildings.Efficiency_Score = 100.0; // Initialize efficiency score to 100
	building_counter++; // Increment the building counter
	cout << "Building added successfully!" << endl;
	
}
// define function to display building information ---> basmala
void displayBuildingInfo(building buildings[], int building_counter) {
	int id;
	cout << "Enter building ID: ";
	cin >> id;
	cin.ignore();
	string building_name;
	getline(cin, building_name);
	for (int i = 0; i < building_counter; i++) {
		if (buildings[i].ID == id && buildings[i].Name == building_name) {
			cout << "Building ID: " << buildings[i].ID << endl;
			cout << "Building Name: " << buildings[i].Name << endl;
			cout << "Building Type: " << buildings[i].type << endl;
			cout << "Monthly Limit: " << buildings[i].Monthly_Limit << " kWh" << endl;
			cout << "Total Consumption: " << buildings[i].Total_consumption << " kWh" << endl;
			cout << "Efficiency Score: " << buildings[i].Efficiency_Score << "%" << endl;
			cout << "-----------------------------" << endl;
			return;
		}
	}
}
