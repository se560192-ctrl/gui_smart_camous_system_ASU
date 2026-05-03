#include "my_project.h"
#include "ui_my_project.h"
#include <QMessageBox>
#include <QThread>
#include <QCloseEvent>
#include "building.h"
#include "reading.h"
#include "alert.h"
#include "filehandling.h"
#include "report.h"
my_project::my_project(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::my_project)
{
    ui->setupUi(this);
   loadFiles(buildings, building_counter, readings, reading_counter, alerts, alert_counter, admins, current_admin_numbers);


    // هنا بنخليه يبدا من صفحة ال welcome
   ui->stackedWidget->setCurrentIndex(WELCOME_PAGE);

}

my_project::~my_project()
{
    delete ui;
}

void my_project::on_monitoring_btn_clicked()
{ //هنا بنقله login page
 ui->stackedWidget->setCurrentIndex(login_page);
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
        ui->stackedWidget->setCurrentIndex(MAIN_MENU); // هنا بنقله لل main menu
    } else {
        ui->valid_massage->setText("Invalid Username or Password!");
        ui->valid_massage->setStyleSheet("color: red;");
    }
}





void my_project::on_newadmin_btn_clicked()
{// هنا بنقله sign up page
    ui->stackedWidget->setCurrentIndex(SIGNUP_PAGE);
}




void my_project::on_confirm_botton_clicked()
{

    string u = ui->new_userLine->text().toStdString();
    string p = ui->new_passwordLine->text().toStdString();

    QString user = ui->new_userLine->text().trimmed();
    QString pass = ui->new_passwordLine->text().trimmed();

    if (user.isEmpty() || pass.isEmpty()) {
        QMessageBox::warning(this, "Login Failed", "Username or Password cannot be empty! ⚠️");
        return;
    }

    // بنادي الفانكشن وبشوف هترجع إيه
    bool success = admin_signup(admins, current_admin_numbers, u, p);

    if (success) {
        // لو نجح، سيف وطلع رسالة وانقله
        QMessageBox::information(this, "Success", "Admin added successfully!");
        ui->stackedWidget->setCurrentIndex(login_page);// هنا هنقله للوجبن فانكشن علشان يدخل البيانات
    } else {
        // لو فشل (يعني العداد وصل لـ 5)
        QMessageBox::warning(this, "Error", "Sorry! Admin database is full (Max 5 admins).");
        // مش هننقله للصفحة التانية، هيفضل مكانه عشان يشوف الغلط فين
    }

}

// ADD NEW ENERGY READING PROGRESS
void my_project::on_new_energy_reading_btn_clicked()
{
     ui->stackedWidget->setCurrentIndex(Building_VALIDATION);
}


void my_project::on_CON_N_ID_ANER_clicked() // BUILDING VALIDATION
{
    int inputID = ui->BID_ANER->text().toInt();
    string inputName = ui->BNAME_ANER->text().toStdString();

    bool building_found = false;

    // هندور على ال BUILDING في ال ARRAY
    for (int i = 0; i < building_counter; i++) {
        if (buildings[i].ID == inputID && buildings[i].Name == inputName) {
            building_found = true;
            break;
        }
    }

    // 3. اتخاذ قرار بناءً على النتيجة
    if (building_found) {
        // لو المبنى موجود بيدخل يدخل قراءة
        ui->stackedWidget->setCurrentIndex(ADD_READING_DATA);
    }
    else {
        // لو ملقاش المبنى
        QMessageBox::critical(this, "Error", "Building not found! Please check the ID and Name.");
    }
}


void my_project::on_BACK_MENU_clicked()
{
     ui->stackedWidget->setCurrentIndex(MAIN_MENU);
}


void my_project::on_CONFIRM_NER_clicked() // ADD NEW READING AFTER FINDING BUILDING
{
    if (ui->READING_MONTH->text().isEmpty() || ui->READING_VALUE->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Month and Reading Value cannot be empty! ⚠️");
        return;
    }
        // نسحبة من نفس المكان بتاع اول مرة
        int id = ui->BID_ANER->text().toInt();
        string name = ui->BNAME_ANER->text().toStdString();

        // نكمل سحب بيانات الشهر والقيمة
        string month = ui->READING_MONTH->text().toStdString();
        float val = ui->READING_VALUE->text().toFloat();

        // نعمل كول للفانكشن
       bool hasAlert = AddEnergyReading(buildings, building_counter, readings, reading_counter,
                         alerts, alert_counter, numberOfUnresolvedAlerts,
                         id, name, month, val);
        // بعد سطر AddEnergyReading...

       if (hasAlert) {
           float buildingLimit = 0;

           // بندور على المبنى في الـ Array عشان نجيب الليميت بتاعه
           for (int j = 0; j < building_counter; j++) {
               if (buildings[j].ID == id) {
                   buildingLimit = buildings[j].Monthly_Limit;
                   break;
               }
           }

           float overUsage = val - buildingLimit; // هنا الـ 300 هتتحسب صح

           QMessageBox::critical(this, "⚠️ ALERT!",
                                 QString("Warning! Building %1 has exceeded its limit!\n\n"
                                         "Current Reading: %2\n"
                                         "Monthly Limit: %3\n"
                                         "Over-consumption Amount: %4")
                                     .arg(QString::fromStdString(name))
                                     .arg(val)
                                     .arg(buildingLimit)
                                     .arg(overUsage));
       } // ده قوس نهاية الـ if (hasAlert) اللي في سطر 179
else {
    // الرسالة دي هتظهر لو القراءة سليمة (أقل من الليميت)
    QMessageBox::information(this, "Reading Added",
                             QString("Energy reading for %1 has been recorded successfully! ✅")
                                 .arg(QString::fromStdString(name)));
}
} // ده قوس نهاية الـ on_CONFIRM_NER_clicked


void my_project::on_BACK_MENU_ANER2_clicked()
{
    ui->stackedWidget->setCurrentIndex(MAIN_MENU);
}


void my_project::on_display_information_btn_clicked()
{
ui->stackedWidget->setCurrentIndex(BUILDING_MENU);
}


void my_project::on_Add_building_confirm_clicked()
{
    if (ui->id_input->text().isEmpty() || ui->name_input->text().isEmpty() ||
        ui->type_input->text().isEmpty() || ui->limit_input->text().isEmpty())
    {
        QMessageBox::warning(this, "Input Error", "All fields are required to add a new building! ⚠️");
        return; // اخرج وم تكملش إضافة
    }
    // سحب البيانات من الشاشة
    int id = ui->id_input->text().toInt();
    string name = ui->name_input->text().toStdString();
    string type = ui->type_input->text().toStdString();
    float limit = ui->limit_input->text().toFloat();

    // نداء الفانكشن الشبيهة بكودك القديم
    AddBuildingGUI(buildings, building_counter, id, name, type, limit);
}


void my_project::on_Add_new_building_btn_clicked()
{
ui->stackedWidget->setCurrentIndex(Add_new_building);
}


void my_project::on_Back_ANB_clicked()
{
     ui->stackedWidget->setCurrentIndex(MAIN_MENU);
}


void my_project::on_display_BI_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(Display_building_info1);
}


void my_project::on_BACK_DBI_clicked()
{
     ui->stackedWidget->setCurrentIndex(MAIN_MENU);
}


void my_project::on_Search_building_clicked()
{
    int id = ui->search_id->text().toInt();
    string name = ui->search_name->text().toStdString();

    // 2. الكول للوجيك (الفانكشن اللي في building.cpp)
    int index = findBuildingIndex(buildings, building_counter, id, name);

    // 3. التنفيذ بناءً على اللوجيك
    if (index != -1) {
        // لو موجود، املأ البيانات وانقل الصفحة
        ui->label_id->setText(QString::number(buildings[index].ID));
        ui->label_name->setText(QString::fromStdString(buildings[index].Name));
        ui->label_type->setText(QString::fromStdString(buildings[index].type));
        ui->label_limit->setText(QString::number(buildings[index].Monthly_Limit));
        ui->label_consumption->setText(QString::number(buildings[index].Total_consumption));
        ui->label_score->setText(QString::number(buildings[index].Efficiency_Score) + "%");

         ui->stackedWidget->setCurrentIndex(Display_building_info2);
    }
    else {
        // لو مش موجود
        QMessageBox::warning(this, "Not Found", "Building not found!");
    }
}



// calculate efficiency score progress



void my_project::on_calculate_effieciancy_score_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(CALC_EFFICIENCY_PAGE);
}


void my_project::on_START_CALCULATION_BTN_clicked()
{

        // 1. تصفير البروجرس بار في البداية
        ui->progressBar_calc->setValue(0);

        // 2. نداء الفانكشن الاصلية وبعد ما تخلص يعمل سيف علشان يسمع في الملف بتاع الفايل هاندلينج
        calculateEfficiencyScore(buildings, building_counter);


        // 3. حركة وهمية علشان البروجرس بار يتملي واحده واحده واليوزر يشوفه
        for(int i = 0; i <= 100; i++) {
            ui->progressBar_calc->setValue(i);
            // السطر ده علشان يشتغل ببطئ
            QThread::msleep(20);
            // السطر ده علشان ميهنجش
            QCoreApplication::processEvents();
        }

        // 4. تحديث الـ Status Label
        ui->CALC_LABEL->setText("Last calculated: Just now (Success ✅)");
        ui->CALC_LABEL->setStyleSheet("color: #2e7d32; font-style: italic;");

        // 5. رسالة التأكيد النهائية
        QMessageBox::information(this, "Success", "Calculate Efficiency Score Completed Successfully!");

}


void my_project::on_BACK_CALC_clicked()
{
     ui->stackedWidget->setCurrentIndex(MAIN_MENU);
}


// logout progress



void my_project::on_log_out_btn_clicked()
{
    // 1. رسالة تأكيد (عشان اليوزر ميتلخبطش ويخرج بالغلط)
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Logout", "Are you sure you want to logout?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        // لو ايوة هنرجعو لل لوجين بيدج تاني
        ui->stackedWidget->setCurrentIndex(login_page);

        // هنمسح اي حاجة كانت موجودة في اللاينز بتاعت اللوجين علشان الخصوصية
        ui->user_input->clear();
        ui->password_input->clear();
    }
}
// GENERATE ALERT PROGRESS

void my_project::on_generate_alerts_btn_clicked()
{
    alert_counter = 0;
    numberOfUnresolvedAlerts = 0;

    int created = 0;

    for (int i = 0; i < reading_counter; i++) {
        for (int j = 0; j < building_counter; j++) {
            if (readings[i].BuildingID == buildings[j].ID) {

                // 2. شيكي بس على الاستهلاك
                if (readings[i].consumption_value > buildings[j].Monthly_Limit) {
                    if (alert_counter < 100) {
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
                        created++;
                    }
                }
            }
        }
    }


    if (created > 0) {
        QMessageBox::information(this, "Success", QString("Done! %1 alerts generated.").arg(created));
    } else {
        QMessageBox::information(this, "System Scan", "No over-consumption found.");
    }
}
// VIEW UNRESOLVED ALERTS PROGRESS

void my_project::on_view_unresolverd_alerts_clicked()
{

        QStringList result; // الشنطة اللي هنجمع فيها الكلام

        // 1. مناداة الفانكشن بتاعتك
        displayOverconsumption(alerts, alert_counter, result);

        // 2. عرض النتيجة في الـ List Widget اللي في Screenshot 2026-04-30 193302.png
        ui->listWidget_alerts->clear();
        ui->listWidget_alerts->addItems(result);
 ui->stackedWidget->setCurrentIndex(view_unresolved_alerts);
}


void my_project::on_BACK_VURA_clicked()
{
    ui->stackedWidget->setCurrentIndex(MAIN_MENU);

}


void my_project::on_resolve_alert_btn_clicked()
{
    // 1. نتأكد إن اليوزر اختار سطر فعلاً من اللستة
    if (!ui->listWidget_alerts->currentItem()) {
        QMessageBox::warning(this, "Selection Required", "Please select an alert from the list first! 🖱️");
        return;
    }

    // 2. نجيب النص اللي مكتوب في السطر اللي اختاره
    QString selectedText = ui->listWidget_alerts->currentItem()->text();

    // 3. حركة ذكية: نطلع الـ ID من النص
    // لو النص شكله "Alert ID: 5 | ..." إحنا عايزين رقم 5
    // أسهل طريقة لو إنتي مثبتة التنسيق هي استخدام الـ QRegularExpression أو التقطيع
    // بس عشان منتعقدش، هفترض إنك هتاخدي أول رقم يقابلك في السطر:

    int alertID = selectedText.section('#', 1, 1).section('\n', 0, 0).toInt();
    // ملاحظة: الـ section دي بتعتمد على شكل النص اللي إنتي كتبتيه في الـ View
    // لو النص عندك بيبدأ بـ "Alert ID: 1"، استخدمي التقسيم المناسب له.

    // 4. نادي الـ Logic
    int res = resolveAlert(alertID, alerts, alert_counter, numberOfResolvedAlerts, numberOfUnresolvedAlerts);

    if (res == 1) {
        QMessageBox::information(this, "Success", "Alert #" + QString::number(alertID) + " has been resolved! ✅");
        numberOfResolvedAlerts++;
        numberOfUnresolvedAlerts--;
        // 5. تحديث اللستة فوراً عشان السطر يختفي أو يتغير حالته
        on_view_unresolverd_alerts_clicked();
    }
}
// generate monthly report progress

void my_project::on_generate_montly_report_btn_clicked()
{
    numberOfResolvedAlerts = 0;
    numberOfUnresolvedAlerts = 0;

    for (int i = 0; i < alert_counter; i++) {
        if (alerts[i].status == "Resolved")
            numberOfResolvedAlerts++;
        else if (alerts[i].status == "Unresolved")
            numberOfUnresolvedAlerts++;
    }
        // 1. حساب القيم باستخدام الفانكشنز اللي عدلناها
        float totalConsumption = calculateTotalCampusConsumption(buildings, building_counter);
        QString mostEfficient = QString::fromStdString(getMostEfficientBuilding(buildings, building_counter));
        QString leastEfficient = QString::fromStdString(getLeastEfficientBuilding(buildings, building_counter));

        // 2. تجهيز النص بتنسيق احترافي
        QString reportText = QString(
                                 "📊 --- MONTHLY CAMPUS REPORT ---\n\n"
                                 "⚡ Total Campus Consumption: %1 kWh\n"
                                 "🏆 Most Efficient Building: %2\n"
                                 "⚠️ Least Efficient Building: %3\n\n"
                                 "------------------------------------------\n"
                                 "🚨 Unresolved Alerts: %4\n"
                                 "✅ Resolved Alerts: %5\n"
                                 )
                                 .arg(totalConsumption)
                                 .arg(mostEfficient)
                                 .arg(leastEfficient)
                                 .arg(numberOfUnresolvedAlerts)
                                 .arg(numberOfResolvedAlerts);

        // 3. عرض التقرير في MessageBox
        QMessageBox msgBox;
        msgBox.setWindowTitle("Campus Energy Report");
        msgBox.setText(reportText);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setStyleSheet("QLabel{ min-width: 300px; font-size: 14px; }"); // تظبيط حجم الخط
        msgBox.exec();

}


void my_project::on_BACK_FROM_DISPLAY_clicked()
{
     ui->stackedWidget->setCurrentIndex(MAIN_MENU);
}

void my_project::closeEvent(QCloseEvent *event) {
    // نستخدم المتغيرات اللي متعرفة جوه الكلاس (الأسماء اللي بالأسود في الصورة اللي فاتت)
    saveData(buildings, building_counter, readings, reading_counter, alerts, alert_counter, admins, current_admin_numbers);

    event->accept();
}