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
void AddBuildingGUI(building buildings[], int& building_counter, int id, string name, string type, float limit);
// function do validation building
int findBuildingIndex(building buildings[], int counter, int searchID, string searchName);