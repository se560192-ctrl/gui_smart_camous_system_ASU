#ifndef MY_PROJECT_H
#define MY_PROJECT_H

#include <QWidget>
#include "admin.h"
#include "building.h"
#include "alert.h"
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

private slots:

    void on_monitoring_btn_clicked();

    void on_login_btn_clicked();

    void on_newadmin_btn_clicked();



    void on_confirm_botton_clicked();

private:
    Ui::my_project *ui;
    Admin admins[5];
    int current_admin_numbers = 0;
};
#endif // MY_PROJECT_H
