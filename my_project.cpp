#include "my_project.h"
#include "ui_my_project.h"
#include <QMessageBox>
#include <QThread>
#include <QCloseEvent>
#include <QInputDialog>
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


   //----------------------------GO TO WELCOME PAGE------------------------

   ui->stackedWidget->setCurrentIndex(WELCOME_PAGE);

}

my_project::~my_project()
{
    delete ui;
}
   //---------------------START OF LOGIN PROCES-------------------------

void my_project::on_monitoring_btn_clicked()
{
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
        ui->user_input->clear();
        ui->password_input->clear();
        ui->stackedWidget->setCurrentIndex(MAIN_MENU); // هنا بنقله لل main menu
    } else {
        ui->valid_massage->setText("Invalid Username or Password!");
        ui->valid_massage->setStyleSheet("color: red;");
    }
}


   // -----------START OF ADD NEW ADMIN PROCES---------------


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
        ui->new_userLine->clear();
        ui->new_passwordLine->clear();
        ui->stackedWidget->setCurrentIndex(login_page);// هنا هنقله للوجبن فانكشن علشان يدخل البيانات
    } else {
        // لو فشل (يعني العداد وصل لـ 5)
        QMessageBox::warning(this, "Error", "Sorry! Admin database is full (Max 5 admins).");
        // مش هننقله للصفحة التانية، هيفضل مكانه عشان يشوف الغلط فين
    }

}

//----------------------- END OF SIGN UP & LOGIN PROCESES------------------------------



// --------------START OF DISPLAY & ADD BUILDING INFORMATION-----------------------

void my_project::on_display_information_btn_clicked() // الي موجود في ال MAIN MENU
{
    ui->stackedWidget->setCurrentIndex(BUILDING_MENU);
}


// ****START OF ADD NEW BUILDING PROCESS******


void my_project::on_Add_new_building_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(Add_new_building);
}


void my_project::on_Add_building_confirm_clicked()
{
    if (ui->id_input->text().isEmpty() || ui->name_input->text().isEmpty() ||
        ui->type_input->text().isEmpty() || ui->limit_input->text().isEmpty()) {
        QMessageBox::warning(this,
                             "Input Error",
                             "All fields are required to add a new building! ⚠️");
        return; // اخرج وم تكملش إضافة
    }
    QRegularExpression letters("^[A-Za-z0-9_ ]+$");

    if (!letters.match(ui->name_input->text()).hasMatch())
    {
        QMessageBox::warning(this,
                             "Invalid Name",
                             "Name must contain letters only!");
        return;
    }

    if (!letters.match(ui->type_input->text()).hasMatch())
    {
        QMessageBox::warning(this,
                             "Invalid Type",
                             "Type must contain letters only!");
        return;
    }

    bool ok;
    ui->id_input->text().toInt(&ok);
    if (!ok)
    {
        QMessageBox::warning(this,
                             "Invalid ID",
                             "ID must be numbers only!");
        return;
    }

    ui->limit_input->text().toFloat(&ok);
    if (!ok)
    {
        QMessageBox::warning(this,
                             "Invalid Limit",
                             "Limit must be a valid number!");
        return;
    }
    // سحب البيانات من الشاشة
    int id = ui->id_input->text().toInt();
    string name = ui->name_input->text().toStdString();
    string type = ui->type_input->text().toStdString();
    float limit = ui->limit_input->text().toFloat();

    // نداء الفانكشن الشبيهة بكودك القديم
    AddBuildingGUI(buildings, building_counter, id, name, type, limit);
    ui->id_input->clear();
    ui->name_input->clear();
    ui->type_input->clear();
    ui->limit_input->clear();
}
void my_project::on_Back_ANB_clicked()
{
    ui->stackedWidget->setCurrentIndex(MAIN_MENU);
}

//******END OF ADD NEW BUILDING PROCES********


//******START OF DISPLAY BUILDING INFORMATION******

void my_project::on_display_BI_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(Display_building_info1);
}


void my_project::on_BACK_DBI_clicked()
{
    ui->search_id->clear();
    ui->search_name->clear();
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
        ui->label_type->setText(QString::fromStdString(buildings[index].Type));
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

//******END OF DISPLAY BUILDING INFORMATION PROCES********


// --------------END OF DISPLAY & ADD BUILDING INFORMATION-----------------------



 // --------------------START OF ADD NEW ENERGY READING PROCESES----------------------
void my_project::on_new_energy_reading_btn_clicked()
{
     ui->stackedWidget->setCurrentIndex(Building_VALIDATION);
}


void my_project::on_CON_N_ID_ANER_clicked() // BUILDING VALIDATION
{
    if (ui->BID_ANER->text().isEmpty() ||
        ui->BNAME_ANER->text().isEmpty())
    {
        QMessageBox::warning(this,
                             "Input Error",
                             "ID and Name are required!");
        return;
    }

    bool ok;
    int inputID = ui->BID_ANER->text().toInt(&ok);
    if (!ok)
    {
        QMessageBox::warning(this,
                             "Invalid ID",
                             "ID must be numbers only!");
        return;
    }
    QRegularExpression letters("^[A-Za-z0-9_ ]+$");

    if (!letters.match(ui->BNAME_ANER->text()).hasMatch())
    {
        QMessageBox::warning(this,
                             "Invalid Name",
                             "Name must contain letters only!");
        return;
    }
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
        //  ui->BID_ANER->clear();
        //  ui->BNAME_ANER->clear();
        ui->stackedWidget->setCurrentIndex(ADD_READING_DATA);


    } else {
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
    QString monthQ = ui->READING_MONTH->text();
    QRegularExpression monthRx("^[A-Za-z ]+$");

    if (!monthRx.match(monthQ).hasMatch())
    {
        QMessageBox::warning(this,
                             "Invalid Month",
                             "Month must be added in letters");
        return;
    }

    string month = monthQ.toStdString();
    bool ok;
    float val = ui->READING_VALUE->text().toFloat(&ok);

    if (!ok)
    {
        QMessageBox::warning(this,
                             "Invalid Value",
                             "Reading must be a valid number!");
        return;
    }
    int check_id = ui->BID_ANER->text().toInt();
    string check_month = ui->READING_MONTH->text().toStdString();
    for (int i = 0; i < reading_counter; i++) {
        if (readings[i].BuildingID == check_id && readings[i].month == check_month) {
            QMessageBox::warning(this, "Duplicate Reading", "This building already has a reading for this month!");
            return;
        }
    }

    // نعمل كول للفانكشن
    bool hasAlert = AddEnergyReading(buildings,
                                     building_counter,
                                     readings,
                                     reading_counter,
                                     alerts,
                                     alert_counter,
                                     numberOfUnresolvedAlerts,
                                     id,
                                     name,
                                     month,
                                     val);
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

        QMessageBox::critical(this,
                              "⚠️ ALERT!",
                              QString("Warning! Building %1 has exceeded its limit!\n\n"
                                      "Current Reading: %2\n"
                                      "Monthly Limit: %3\n"
                                      "Over-consumption Amount: %4")
                                  .arg(QString::fromStdString(name))
                                  .arg(val)
                                  .arg(buildingLimit)
                                  .arg(overUsage));
        ui->READING_MONTH->clear();
        ui->READING_VALUE->clear();
        ui->BID_ANER->clear();
        ui->BNAME_ANER->clear();
    } // ده قوس نهاية الـ if (hasAlert) اللي في سطر 179
    else {
        // الرسالة دي هتظهر لو القراءة سليمة (أقل من الليميت)
        QMessageBox::information(this,
                                 "Reading Added",
                                 QString("Energy reading for %1 has been recorded successfully! ✅")
                                     .arg(QString::fromStdString(name)));
        ui->READING_MONTH->clear();
        ui->READING_VALUE->clear();
        ui->BID_ANER->clear();
        ui->BNAME_ANER->clear();
    }
} // ده قوس نهاية الـ on_CONFIRM_NER_clicked

void my_project::on_BACK_MENU_ANER2_clicked()
{
    ui->stackedWidget->setCurrentIndex(MAIN_MENU);
}

// ------------------END OF ADD NEW ENERGY READING PROCES---------------------------



//-----------START GENERATE ALERT PROCES-------------

void my_project::on_generate_alerts_btn_clicked()
{
    // 1. نادي الفانكشن اللي بتعمل مسح شامل وتضيف الجديد
    check_alert_generate(buildings,
                         building_counter,
                         readings,
                         reading_counter,
                         alerts,
                         alert_counter,
                         numberOfUnresolvedAlerts);

    // 2. نحسب عدد الـ Resolved (الحسابي)
    // بما إننا عندنا الإجمالي وعندنا الـ Unresolved، يبقى الفرق هو الـ Resolved
    int resolvedCount =0;
    int unresolvedcount=0;
    for(int i=0;i<alert_counter;i++){
        if(alerts[i].status=="Unresolved")unresolvedcount++;
        else resolvedCount++;
    }

    // 3. نجهز رسالة التقرير الشامل
    QString report = "📊 --- System Alerts Report --- 📊\n\n";
    report += "✅ Total Alerts in System: " + QString::number(alert_counter) + "\n";
    report += "🔴 Unresolved Alerts: " + QString::number(unresolvedcount) + "\n";
    report += "🟢 Resolved Alerts: " + QString::number(resolvedCount) + "\n\n";

    // 4. لو فيه تنبيهات، نعرض الـ IDs بتاعتها (أو آخر IDs لو العدد كبير)
    if (alert_counter > 0) {
        report += "🆔 Alert IDs currently active: ";
        for (int i = 0; i < alert_counter; i++) {
            report += QString::number(alerts[i].AlertID);
            if (i < alert_counter - 1)
                report += ", "; // فاصل بين الأرقام
        }
    } else {
        report += "No alerts have been generated yet.";
    }

    // 5. إظهار البوكس النهائي لليوزر
    QMessageBox::information(this, "Audit & Statistics", report);
}
//----------------END OF GENERATE ALERT PROCES-----------------



// --------------START OF VIEW UNRESOLVED ALERTS PROCES---------------

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

//-------------------END OF VIEW UNRESOLVED PROCES-----------------


// ----------------START OF RESOLVE ALERT PROCESS---------------------
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
//--------------------- END OF RESOLVE ALERT PROCESS---------------------




//--------------------START OF CALCULATE EFFIECIENCY PROCESS----------------



void my_project::on_calculate_effieciancy_score_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(CALC_EFFICIENCY_PAGE);
}


void my_project::on_START_CALCULATION_BTN_clicked()
{
    // 1. تصفير البروجرس بار في البداية
    bool ok;
    QString targetMonth = QInputDialog::getText(this, "Calculate Efficiency",
                                                "Enter Month Name:", QLineEdit::Normal,
                                                "", &ok);

    if (!ok || targetMonth.isEmpty()) return;
    string monthStr = targetMonth.toStdString();
    ui->progressBar_calc->setValue(0);

    // 2. نداء الفانكشن الاصلية وبعد ما تخلص يعمل سيف علشان يسمع في الملف بتاع الفايل هاندلينج
    calculateEfficiencyScore(buildings, building_counter,readings,reading_counter,monthStr);

    // 3. حركة وهمية علشان البروجرس بار يتملي واحده واحده واليوزر يشوفه
    for (int i = 0; i <= 100; i++) {
        ui->progressBar_calc->setValue(i);
        // السطر ده علشان يشتغل ببطئ
        QThread::msleep(20);
        // السطر ده علشان ميهنجش
        QCoreApplication::processEvents();
    }

    // 4. تحديث الـ Status Label
    ui->CALC_LABEL->setText("Last calculated: " + targetMonth + " (Success ✅)");
    ui->CALC_LABEL->setStyleSheet("color: #2e7d32; font-style: italic;");

    // 5. رسالة التأكيد النهائية
    QMessageBox::information(this, "Success", "Efficiency Score for " + targetMonth + " Completed Successfully!");
}


void my_project::on_BACK_CALC_clicked()
{
    // 1. تصفير الـ ProgressBar
    ui->progressBar_calc->setValue(0);

    // 2. مسح رسالة النجاح الخضراء
    ui->CALC_LABEL->clear();
     ui->stackedWidget->setCurrentIndex(MAIN_MENU);
}
//-----------------END OF CALCULATE EFFICIENCY PROCESS---------------------------





//--------------START OF GENERATE MONTHLY REPORT PROCES--------------------

void my_project::on_generate_montly_report_btn_clicked()
{
        // 1. نطلب الشهر من اليوزر
        bool isMonthEntered; // غيرنا الاسم هنا
        QString targetMonth = QInputDialog::getText(this, "Monthly Report", "Enter Month Name:", QLineEdit::Normal, "", &isMonthEntered);

        // بنشيك لو اليوزر دخل قيمة وداس موافق فعلاً
        if (isMonthEntered && !targetMonth.isEmpty()) {

            // 2. ننادي الفانكشن بتاعتك باللوجيك الجديد
            string monthStr = targetMonth.toStdString();
            string finalReport = generateMonthlyCampusReport(buildings, building_counter, readings, reading_counter, alerts, alert_counter, monthStr);

            // 3. نعرض النتيجة في الـ Message Box
            QMessageBox::information(this, "Campus Report", QString::fromStdString(finalReport));
        }

}



void my_project::on_BACK_FROM_DISPLAY_clicked()
{
     ui->stackedWidget->setCurrentIndex(MAIN_MENU);
}
//----------------END OF GENERATE MONTHLY REPORT PROCES----------------



//-----------------START OF LOGOUT PROCES---------------------



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

//-------------------END OF LOG OUT PROCES---------------------------


//-------------------SAVE DATA OF ALL PROJECT-----------------------
void my_project::closeEvent(QCloseEvent *event) {
    // نستخدم المتغيرات اللي متعرفة جوه الكلاس (الأسماء اللي بالأسود في الصورة اللي فاتت)
    saveData(buildings, building_counter, readings, reading_counter, alerts, alert_counter, admins, current_admin_numbers);

    event->accept();
}