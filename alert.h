#pragma once
#include <string>
#include "building.h"
#include "reading.h"
#include <Qstring>
using namespace std;

struct Alert {
    int AlertID;
    int BuildingID;
    string month;
    float over_usage_amount;
    string status;
};

// تأكدي إن الترتيب هنا هو اللي هتستخدميه تحت
void generate_alert_for_over_usage(float consumption_value, float Monthly_Limit, string building_name, int building_id, string month, Alert alerts[], int& alert_counter, int& numberOfUnresolvedAlerts);

void check_alert_generate(building buildings[], int& building_counter, EnergyReading readings[], int reading_counter, Alert alerts[], int& alert_counter, int& numberOfUnresolvedAlerts);

// declare function to resolve alert ---> judy
int resolveAlert(int alertID , Alert alerts[], int alert_counter, int& numberOfResolvedAlerts, int& numberOfUnresolvedAlerts);


// declare function to show all unresolved alerts ---> aya
void displayOverconsumption(Alert alerts[], int alert_counter, QStringList& listToFill);
