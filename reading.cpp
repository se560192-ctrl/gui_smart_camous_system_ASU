#include<string>
#include "building.h"
#include"reading.h"
#include "alert.h"
using namespace std;
// define function to add new energy reading --> basmala
void AddEnergyReading(building buildings[], int& building_counter, EnergyReading readings[], int& reading_counter,Alert alerts[],int &alert_counter,int &numberOfUnresolvedAlerts ,int id, string name, string month, float consumption_value)
    {
        if (reading_counter < 30) {
            // --- الكود بتاعك بدأ من هنا ---
            readings[reading_counter].ReadingID = reading_counter + 1;
            readings[reading_counter].BuildingID = id;
            readings[reading_counter].month = month;
            readings[reading_counter].consumption_value = consumption_value;
            reading_counter++;

            // Update building's total consumption
            for (int i = 0; i < building_counter; i++) {
                if (buildings[i].ID == id && buildings[i].Name == name) {
                    // Calculate total consumption for the month
                    float total_consumption_per_month = 0.0;
                    for (int j = 0; j < reading_counter; j++) {
                        if (readings[j].BuildingID == id && readings[j].month == month) {
                            total_consumption_per_month += readings[j].consumption_value;
                        }
                    }

                    // Check monthly limit
                    if (total_consumption_per_month > buildings[i].Monthly_Limit) {
                        if (alert_counter < 20) {
                            generate_alert_for_over_usage(total_consumption_per_month, buildings[i].Monthly_Limit,
                                                          buildings[i].Name, buildings[i].ID, month,
                                                          alerts, alert_counter, numberOfUnresolvedAlerts);
                        }
                        // شيلنا الـ cout وحطينا مكانه منطق الـ Alert اللي إنتي كاتباه
                    }

                    // التحديث اللي سألتي عليه
                    buildings[i].Total_consumption += consumption_value;
                    break;
                }
            }
            // --- الكود بتاعك خلص هنا ---
        }
}
