#pragma once
#include <string>
using namespace std;
// declare building struct
struct building
{
	int ID;
	string Name;
	string type;
	float Monthly_Limit;
	float Total_consumption;
	float Efficiency_Score;

};
// declare function to calculate efficiency score --> sondus
void calculateEfficiencyScore(building buildings[], int building_counter);

// declare function to add new building --> basmala
void AddBuilding(building &buildings,int &building_counter);

// declare function to display building information --> basmala
void displayBuildingInfo(building buildings[], int building_counter);
