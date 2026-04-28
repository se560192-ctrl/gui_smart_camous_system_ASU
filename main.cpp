#include "my_project.h"
#include <QApplication>
#include "filehandling.h" // 1. لازم تضمنيه هنا

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 2. تعاريف المصفوفات والعدادات (لازم تكون هنا عشان تتبعت للفانكشن)
    building buildings[100];
    int building_counter = 0;
    EnergyReading Readings[100];
    int reading_counter = 0;
    Alert alerts[100];
    int alert_counter = 0;
    Admin admins[100];
    int current_admin_numbers = 0;

    // 3. نادي على اللود هنا (دي أهم خطوة في حياتنا دلوقتي)
    loadFiles(buildings, building_counter, Readings, reading_counter, alerts, alert_counter, admins, current_admin_numbers);

    my_project w;
    w.show();
    return a.exec();
}