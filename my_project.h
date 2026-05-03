#ifndef MY_PROJECT_H
#define MY_PROJECT_H

#include <QWidget>
#include "admin.h"
#include "building.h"
#include "alert.h"
#include "reading.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class my_project;
}
QT_END_NAMESPACE

class my_project : public QWidget
{
    Q_OBJECT

public:
    explicit my_project(QWidget *parent = nullptr);
    ~my_project() override;
    enum Pages {
        WELCOME_PAGE = 0,
        BUILDING_MENU = 1,      // صفحة المنيو في ال add & display building information
        MAIN_MENU =5,          // المنيو الرئيسية
        login_page = 7,        // صفحة اللوجين
        SIGNUP_PAGE = 8,        // صفحة الساين أب
        Building_VALIDATION = 9, // صفحة التأكد من المبنى (Page 1)
        ADD_READING_DATA =10,        // صفحة إدخال القراءة (Page 2)
        Add_new_building=4,
        Display_building_info1=2,
        Display_building_info2=3,
        CALC_EFFICIENCY_PAGE=6,
        view_unresolved_alerts=11,

    };

private slots:

    void on_monitoring_btn_clicked();

    void on_login_btn_clicked();

    void on_newadmin_btn_clicked();



    void on_confirm_botton_clicked();

    void on_new_energy_reading_btn_clicked();

    void on_CON_N_ID_ANER_clicked();

    void on_BACK_MENU_clicked();

    void on_CONFIRM_NER_clicked();

    void on_BACK_MENU_ANER2_clicked();

    void on_display_information_btn_clicked();

    void on_Add_building_confirm_clicked();

    void on_Add_new_building_btn_clicked();

    void on_Back_ANB_clicked();

    void on_display_BI_btn_clicked();

    void on_BACK_DBI_clicked();

    void on_Search_building_clicked();

    void on_START_CALCULATION_BTN_clicked();

    void on_BACK_CALC_clicked();

    void on_calculate_effieciancy_score_btn_clicked();

    void on_log_out_btn_clicked();

    void on_generate_alerts_btn_clicked();

    void on_view_unresolverd_alerts_clicked();

    void on_BACK_VURA_clicked();

    void on_resolve_alert_btn_clicked();

    void on_generate_montly_report_btn_clicked();

    void on_BACK_FROM_DISPLAY_clicked();

private:
    Ui::my_project *ui;
    Admin admins[5];
    int current_admin_numbers = 0;
    // --- ضيفي دول هنا ---
    building buildings[10];      // مصفوفة المباني
    int building_counter = 0;    // عداد المباني

    EnergyReading readings[30];  // مصفوفة القراءات
    int reading_counter = 0;     // عداد القراءات

    Alert alerts[20];            // مصفوفة التنبيهات
    int alert_counter = 0;       // عداد التنبيهات
    int numberOfResolvedAlerts = 0;
    int numberOfUnresolvedAlerts = 0; // عداد التنبيهات غير المحلولة

    // المتغيرات اللي كنا بنقول عليها عشان "تسمع" بين الزراير
    int saved_building_id = -1;
    string saved_building_name = "";

protected:
void closeEvent(QCloseEvent *event) override;
};
#endif // MY_PROJECT_H
