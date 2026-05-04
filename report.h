#pragma once
#include <string>
#include <iostream>
#include "building.h"
#include "reading.h"
#include "alert.h"
using namespace std;

// Eman declare any functions or structs related to generating reports in this file
// if you want a reference how to write in this file 
// you can check the other header files in this project like building.h, alert.h, reading.h, admin.h
// write functions definitions in report.cpp


// لازم يكون كدة في الـ .h
string generateMonthlyCampusReport(building buildings[], int building_counter, EnergyReading readings[], int reading_counter, Alert alerts[], int alert_counter, string targetMonth);