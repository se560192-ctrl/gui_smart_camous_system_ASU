#include<string>
#include "building.h"
#include "alert.h"
#include <QMessageBox>
using namespace std;
// define function to calculate efficiency score --> sondus
void calculateEfficiencyScore(building buildings[], int building_counter,EnergyReading readings[],int reading_counter,string targetmonth )
{
    for(int i=0;i<building_counter;i++){
        float cons_for_month=0.0;
        for (int j = 0; j < reading_counter; j++) {
            if (readings[j].BuildingID == buildings[i].ID && readings[j].month == targetmonth) {
                cons_for_month = readings[j].consumption_value;
                break;
            }
        }
        if (buildings[i].Monthly_Limit > 0) {
            buildings[i].Efficiency_Score = ((buildings[i].Monthly_Limit -cons_for_month )
                                             / buildings[i].Monthly_Limit) * 100.0;
        } else {
            buildings[i].Efficiency_Score = 0; // لو مفيش قراءة للشهر ده
        }

    }
}

//define function to add new building ---> basmala
void AddBuildingGUI(building buildings[], int& building_counter, int id, string name, string type, float limit)
{
    // نفس الشرط بتاعك بالظبط
    if (building_counter < 10) {

        // 1. التأكد من الـ ID (نفس الـ Loop)
        for (int i = 0; i < building_counter; i++) {
            if (id == buildings[i].ID) {
                QMessageBox::critical(nullptr, "Error", "A building with this ID already exists!");
                return; // بنخرج عشان اليوزر يعدل الرقم ويدوس تاني
            }
        }

        // 2. التأكد من الاسم (نفس الـ Loop)
        for (int i = 0; i < building_counter; i++) {
            if (name == buildings[i].Name) {
                QMessageBox::critical(nullptr, "Error", "A building with this name already exists!");
                return;
            }
        }

        // 3. التخزين (نفس الطريقة)
        buildings[building_counter].ID = id;
        buildings[building_counter].Name = name;
        buildings[building_counter].Type = type;
        buildings[building_counter].Monthly_Limit = limit;
        buildings[building_counter].Total_consumption = 0.0;
        buildings[building_counter].Efficiency_Score = 100.0;

        building_counter++;

        QMessageBox::information(nullptr, "Success", "Building added successfully!");
    }
    else {
        QMessageBox::warning(nullptr, "Limit Reached", "Building limit reached! Cannot add more buildings.");
    }
}
// define function to display building information ---> basmala
// فانكشن بتدور على المبنى
int findBuildingIndex(building buildings[], int building_counter, int id, string name) {
    for (int i = 0; i < building_counter; i++) {
        if (buildings[i].ID == id && buildings[i].Name == name) {
            return i; // لقيناه!
        }
    }
    return -1; // مش موجود
}
