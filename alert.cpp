#include<string>
#include <QStringList>
#include "building.h"
#include "alert.h"
#include "reading.h"
using namespace std;
// define function to check limit  ---> amal
void check_alert_generate(building buildings[], int building_counter, EnergyReading readings[], int reading_counter, Alert alerts[], int& alert_counter, int& numberOfUnresolvedAlerts) {

    for (int i = 0; i < reading_counter; i++) {
        for (int j = 0; j < building_counter; j++) {

            // لو الاستهلاك عالي، بننادي الفانكشن التانية وهي اللي تشيك براحتها
            if (readings[i].BuildingID == buildings[j].ID && readings[i].consumption_value > buildings[j].Monthly_Limit) {

                generate_alert_for_over_usage(
                    readings[i].consumption_value,
                    buildings[j].Monthly_Limit,
                    buildings[j].Name,
                    buildings[j].ID,
                    readings[i].month,
                    alerts,
                    alert_counter,
                    numberOfUnresolvedAlerts
                    );
            }
        }
    }
}
// define function to generate alert for over usage
void generate_alert_for_over_usage(float consumption_value, float Monthly_Limit, string building_name, int building_id, string month, Alert alerts[], int& alert_counter, int& numberOfUnresolvedAlerts) {

    float overusage = consumption_value - Monthly_Limit;

    // الـ bool اللي إنتي عايزاه يكون هنا مش في الـ check
    bool alreadyExists = false;
    for (int i = 0; i < alert_counter; i++) {
        if (alerts[i].month == month && alerts[i].BuildingID == building_id && overusage == alerts[i].over_usage_amount) {
            alreadyExists = true;
            break;
        }
    }

    // لو فعلاً مش موجود (يعني alreadyExists لسه false)
    if (!alreadyExists) {
        alerts[alert_counter].AlertID = alert_counter + 1;
        alerts[alert_counter].BuildingID = building_id;
        alerts[alert_counter].over_usage_amount = overusage;
        alerts[alert_counter].month = month;
        alerts[alert_counter].status = "Unresolved";

        alert_counter++;
        numberOfUnresolvedAlerts++;
    }
}

// define function to resolve alert ---> judy
int resolveAlert(int alertID ,Alert alerts[],int alert_counter,int &numberOfResolvedAlerts,int &numberOfUnresolvedAlerts) {
    for (int i = 0; i < alert_counter; i++) {
        if (alerts[i].AlertID == alertID) {
            if (alerts[i].status == "Unresolved") {
                alerts[i].status = "Resolved";
                numberOfResolvedAlerts++;
                numberOfUnresolvedAlerts--;
                return 1; // تم الحل بنجاح
            }
        }
    }
    return 0;
}

// define function to show all unresolved alerts ---> aya
    void displayOverconsumption(Alert alerts[], int alert_counter, QStringList& listToFill)
	{
        bool found = false;
        for (int i = 0; i < alert_counter; i++)
        {
            if (alerts[i].status == "Unresolved")
            {
                // بنجهز السطر اللي هيتعرض في الـ List Widget
                QString row = QString(                      "🚨 ALERT #%1\n"
                                                            "🏢 Building ID: %2\n"
                                                            "📅 Month: %3\n"
                                                            "📉 Excess Amount: %4 Units\n"
                                                            "-----------------------------------")
                                                        .arg(alerts[i].AlertID)
                                                        .arg(alerts[i].BuildingID)
                                                        .arg(QString::fromStdString(alerts[i].month))
                                                        .arg(alerts[i].over_usage_amount);

                listToFill.append(row); // بدل cout << ...
                found = true;
            }
        }
        if (!found)
            listToFill.append("No unresolved alerts found.");
	}
