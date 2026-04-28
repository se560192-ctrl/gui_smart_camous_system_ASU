#include<iostream>
#include<string>
#include "building.h"
#include"reading.h"
#include "alert.h"
#include "admin.h"
using namespace std;
// define function to add new energy reading --> basmala
void AddEnergyReading(building buildings[], int& building_counter, EnergyReading readings[], int& reading_counter,Alert alerts[],int &alert_counter,int &numberOfUnresolvedAlerts) {
	do {
		cout << "select building ID: ";
		int id;
		cin >> id;
		cout << "select building name: ";
		string name;
		cin.ignore(); // Ignore the newline character left in the input buffer
		getline(cin, name);
		bool building_found = false;

		for (int i = 0; i < building_counter; i++) {
			if (buildings[i].ID == id && buildings[i].Name == name) {
				building_found = true;
				break;
			}
		}

		if (!building_found) {
			cout << "Building not found!" << endl;
			cout << "Do you want to add this building? (y/n): ";
			char choice;
			cin >> choice;
			if (choice == 'y' || choice == 'Y') {
				AddBuilding(buildings[building_counter], building_counter);
			}
		}
		else {
			cout << "Enter month: ";
			string month;
			cin >> month;
			cout << "Enter consumption value: ";
			float consumption_value;
			cin >> consumption_value;

			// Add the new reading
			readings[reading_counter].ReadingID = reading_counter + 1;
			readings[reading_counter].BuildingID = id;
			readings[reading_counter].month = month;
			readings[reading_counter].consumption_value = consumption_value;
			reading_counter++;

			// Update building's total consumption
			for (int i = 0; i < building_counter; i++) {
				if (buildings[i].ID == id && buildings[i].Name == name) {
					if (consumption_value > buildings[i].Monthly_Limit) {
						generate_alert_for_over_usage(consumption_value, buildings[i].Monthly_Limit, buildings[i].Name, buildings[i].ID, month, alerts, alert_counter, numberOfUnresolvedAlerts);
					}
					buildings[i].Total_consumption += consumption_value;
					break;
				}
			}

			cout << "Energy reading added successfully!" << endl;
			cout << "Do you want to update efficiency score? (y/n): ";
			char update_choice;
			cin >> update_choice;
			if (update_choice == 'y' || update_choice == 'Y') {
				calculateEfficiencyScore(buildings, building_counter);
			}
		}
		cout << "Do you want to add another energy reading? (y/n): ";
		char continue_choice;
		cin >> continue_choice;
		if (continue_choice == 'n' || continue_choice == 'N') {
			break;
		}
	} while (true);
}
