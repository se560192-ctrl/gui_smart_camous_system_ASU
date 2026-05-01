#include<string>
#include "building.h"
#include "report.h"
using namespace std;

// define any functions related to generating reports in this file ---> Eman

// تعديل بسيط: نخلي الفانكشن ترجع float بدل void
float calculateTotalCampusConsumption(building buildings[], int building_counter) {
    float total = 0.0;
    for (int i = 0; i < building_counter; i++) {
        total += buildings[i].Total_consumption;
    }
    return total;
}

// تعديل: ترجع اسم المبنى الأكثر كفاءة
string getMostEfficientBuilding(building buildings[], int building_counter) {
    float most_score = buildings[0].Efficiency_Score;
    string most_name = buildings[0].Name;
    for (int i = 1; i < building_counter; i++) {
        if (buildings[i].Efficiency_Score > most_score) {
            most_score = buildings[i].Efficiency_Score;
            most_name = buildings[i].Name;
        }
    }
    return most_name;
}

// تعديل: ترجع اسم المبنى الأقل كفاءة
string getLeastEfficientBuilding(building buildings[], int building_counter) {
    float least_score = buildings[0].Efficiency_Score;
    string least_name = buildings[0].Name;
    for (int i = 1; i < building_counter; i++) {
        if (buildings[i].Efficiency_Score < least_score) {
            least_score = buildings[i].Efficiency_Score;
            least_name = buildings[i].Name;
        }
    }
    return least_name;
}