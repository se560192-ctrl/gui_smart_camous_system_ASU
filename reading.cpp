#include<string>
#include "building.h"
#include"reading.h"
#include "alert.h"
using namespace std;
// define function to add new energy reading --> basmala
bool AddEnergyReading(building buildings[], int& building_counter, EnergyReading readings[], int& reading_counter, Alert alerts[], int& alert_counter, int& unresolved, int id, string name, string month, float val)
{
    bool alertGenerated = false;

    if (reading_counter < 30) {
        // 1. تسجيل القراءة الجديدة في أري القراءات
        readings[reading_counter].ReadingID = reading_counter + 1;
        readings[reading_counter].BuildingID = id;
        readings[reading_counter].month = month;
        readings[reading_counter].consumption_value = val;
        reading_counter++; // زودي العداد عشان الحفظ يشتغل صح

        // 2. البحث عن المبنى عشان نحدث بياناته ونشيك على الليميت
        for (int i = 0; i < building_counter; i++) {
            if (buildings[i].ID == id) {

                // تحديث إجمالي استهلاك المبنى (مطلوب في ورقة المشروع)
                buildings[i].Total_consumption += val;

                // 3. مقارنة القراءة الحالية بالليميت (المنطق اللي إنتي عايزاه)
                if (val > buildings[i].Monthly_Limit) {
                    if (alert_counter < 20) {
                        generate_alert_for_over_usage(val, buildings[i].Monthly_Limit,
                                                      buildings[i].Name, id, month,
                                                      alerts, alert_counter, unresolved);
                        alertGenerated = true;
                    }
                }

                break; // لقينا المبنى وخلصنا شغلنا، نخرج من اللوب
            }
        }
    }

    return alertGenerated;
}
