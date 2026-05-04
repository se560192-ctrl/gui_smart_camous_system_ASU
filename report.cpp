#include<string>
#include "building.h"
#include "report.h"

using namespace std;

// define any functions related to generating reports in this file ---> Eman

string generateMonthlyCampusReport(building buildings[], int building_counter, EnergyReading readings[], int reading_counter, Alert alerts[], int alert_counter, string targetMonth) {

    float total_consumption = 0;
    string most_efficient_building = "N/A";
    string least_efficient_building = "N/A";

    float min_consumption = 0;
    float max_consumption = 0;
    bool first_record = true;

    for (int i = 0; i < reading_counter; i++) {
        if (readings[i].month == targetMonth) {
            total_consumption += readings[i].consumption_value;

            // بنجيب اسم المبنى من مصفوفة الـ buildings باستخدام الـ BuildingID
            string currentBuildingName = "Unknown";
            for(int j = 0; j < building_counter; j++) {
                if(buildings[j].ID == readings[i].BuildingID) { // تأكدي إن المتغير اسمه ID أو حسب ما هو في building.h
                    currentBuildingName = buildings[j].Name;
                    break;
                }
            }

            if (first_record) {
                min_consumption = readings[i].consumption_value;
                max_consumption = readings[i].consumption_value;
                most_efficient_building = currentBuildingName;
                least_efficient_building = currentBuildingName;
                first_record = false;
            } else {
                if (readings[i].consumption_value < min_consumption) {
                    min_consumption = readings[i].consumption_value;
                    most_efficient_building = currentBuildingName;
                }
                if (readings[i].consumption_value > max_consumption) {
                    max_consumption = readings[i].consumption_value;
                    least_efficient_building = currentBuildingName;
                }
            }
        }
    }

    // باقي الكود (حساب التنبيهات وتجميع الـ report) زي ما هو...
    int unresolved = 0, resolved = 0;
    for (int i = 0; i < alert_counter; i++) {
        if (alerts[i].month == targetMonth) {
            if (alerts[i].status == "Resolved") resolved++;
            else unresolved++;
        }
    }

    string report = "📊 --- REPORT FOR " + targetMonth + " ---\n\n";
    if (first_record) {
        report += "⚠️ No data found for this month.\n";
    } else {
        report += "• Total Campus Consumption: " + to_string(total_consumption) + " kWh\n";
        report += "🏆 Most Efficient Building: " + most_efficient_building + "\n";
        report += "⚠️ Least Efficient Building: " + least_efficient_building + "\n";
        report += "-----------------------------\n";
        report += "• Unresolved Alerts: " + to_string(unresolved) + "\n";
        report += "• Resolved Alerts: " + to_string(resolved) + "\n";
    }

    return report;
}