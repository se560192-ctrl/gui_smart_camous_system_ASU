#pragma once
#include <string>
using namespace std;
// declare reading struct
struct Alert;
struct EnergyReading {
	int ReadingID;
	int BuildingID;
	string month;
	float consumption_value;
};

// declare function to add new energy reading --> basmala

void AddEnergyReading(building buildings[], int& building_counter, EnergyReading readings[], int& reading_counter, Alert alerts[], int& alert_counter, int& numberOfUnresolvedAlerts);
