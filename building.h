#pragma once
#include <string>
using namespace std;
// محطيناش الانكلود ريدنج دوت اتش علشان ال ال سيركولار ديبندانسي
struct EnergyReading;

struct building
{
    int ID;
    string Name;
    string Type;
    float Monthly_Limit;
    float Total_consumption;
    float Efficiency_Score;
};

// 2. تعديل سطر الفانكشن (بنكتب كلمة struct قبل اسم النوع)
void calculateEfficiencyScore(building buildings[], int building_counter, struct EnergyReading readings[], int reading_counter, string targetmonth);

void AddBuildingGUI(building buildings[], int& building_counter, int id, string name, string type, float limit);
int findBuildingIndex(building buildings[], int counter, int searchID, string searchName);