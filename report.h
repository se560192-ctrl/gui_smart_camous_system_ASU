#pragma once
#include <string>
using namespace std;

// Eman declare any functions or structs related to generating reports in this file
// if you want a reference how to write in this file 
// you can check the other header files in this project like building.h, alert.h, reading.h, admin.h
// write functions definitions in report.cpp


//declare function to generate monthly campus report---> Eman
void generateMonthlyCampusReport(building buildings[], int building_counter, int numberOfUnresolvedAlerts , int numberOfResolvedAlerts);

//declare function to calculate Total Campus Consumption--> Eman
void calculateTotalCampusConsumption(building buildings[], int building_counter);

//declare function to find the most efficient building--> Eman
void findMostEfficientBuilding(building buildings[], int building_counter);

//declare function to find the least efficient building--> Eman
void findLeastEfficientBuilding(building buildings[], int building_counter);

