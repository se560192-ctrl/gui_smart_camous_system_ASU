#pragma once
#include "building.h"
#include "alert.h"
#include "reading.h"
#include "admin.h"
using namespace std;


void loadFiles(building buildings[], int &building_counter, EnergyReading Readings[], int &reading_counter, Alert alerts[], int &alert_counter, Admin admins[], int &current_admin_numbers);

void saveData(building buildings[], int &building_counter, EnergyReading Readings[], int &reading_counter, Alert alerts[], int &alert_counter, Admin admins[], int &current_admin_numbers);


