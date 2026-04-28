#include "my_project.h"
#include "ui_my_project.h"
#include <QMessageBox>
#include "building.h"
#include "reading.h"
#include "alert.h"
#include "filehandling.h"
extern building buildings[];
extern int building_counter;
extern EnergyReading Readings[];
extern int reading_counter;
extern Alert alerts[];
extern int alert_counter;
extern int numberOfUnresolvedAlerts;
extern int numberOfResolvedAlerts;

my_project::my_project(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::my_project)
{
    ui->setupUi(this);
   loadFiles(buildings, building_counter, Readings, reading_counter, alerts, alert_counter, admins, current_admin_numbers);


    // بنخلي البرنامج يبدأ بصفحة الـ Login (رقم 1)
    ui->stackedWidget->setCurrentIndex(1);
}

my_project::~my_project()
{
    delete ui;
}

void my_project::on_monitoring_btn_clicked()
{
   ui->welcome_label->setText("SYSTEM INITIALIZED & READY.");
    ui->description_label->setText("fetching consumption data from faculty databases...");
   ui->monitoring_btn->hide();

}


void my_project::on_login_btn_clicked()
{
    QString user = ui->user_input->text();
    QString pass = ui->password_input->text();

    // 1. نسحب البيانات من الشاشة
    string u = ui->user_input->text().toStdString();
    string p = ui->password_input->text().toStdString();

    // 2.  ننادي هنا الفانكشن بتاعت ال admin login
    bool found = Admin_login(admins, current_admin_numbers, u, p);

    // 3. ناخد النتيجة ونقرر هنعمل إيه في الشاشة
    if (found) {
        ui->stackedWidget->setCurrentIndex(0); // انقل للـ Dashboard
    } else {
        ui->valid_massage->setText("Invalid Username or Password!");
        ui->valid_massage->setStyleSheet("color: red;");
    }
}





void my_project::on_newadmin_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}




void my_project::on_confirm_botton_clicked()
{

    string u = ui->new_userLine->text().toStdString();
    string p = ui->new_passwordLine->text().toStdString();

    // بنادي الفانكشن وبشوف هترجع إيه
    bool success = admin_signup(admins, current_admin_numbers, u, p);

    if (success) {
        // لو نجح، سيف وطلع رسالة وانقله
       saveData(buildings, building_counter, Readings, reading_counter, alerts, alert_counter, admins, current_admin_numbers);
        QMessageBox::information(this, "Success", "Admin added successfully!");
        ui->stackedWidget->setCurrentIndex(1);
    } else {
        // لو فشل (يعني العداد وصل لـ 5)
        QMessageBox::warning(this, "Error", "Sorry! Admin database is full (Max 5 admins).");
        // مش هننقله للصفحة التانية، هيفضل مكانه عشان يشوف الغلط فين
    }

}

