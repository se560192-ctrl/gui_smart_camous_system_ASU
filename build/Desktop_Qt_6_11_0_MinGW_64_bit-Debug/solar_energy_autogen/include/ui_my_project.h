/********************************************************************************
** Form generated from reading UI file 'my_project.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MY_PROJECT_H
#define UI_MY_PROJECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_my_project
{
public:
    QStackedWidget *stackedWidget;
    QWidget *first_page;
    QLabel *welcome_label;
    QLabel *description_label;
    QPushButton *monitoring_btn;
    QWidget *login_page;
    QLineEdit *user_input;
    QLineEdit *password_input;
    QPushButton *login_btn;
    QLabel *login_label;
    QLabel *Important_note;
    QLabel *username_label;
    QLabel *passwordlabel;
    QPushButton *newadmin_btn;
    QLabel *valid_massage;
    QWidget *signUp_page;
    QLabel *signUp_label;
    QLabel *new_userLabel;
    QLabel *new_passLabel;
    QLineEdit *new_userLine;
    QLineEdit *new_passwordLine;
    QPushButton *confirm_botton;
    QLabel *sign_up_massage;

    void setupUi(QWidget *my_project)
    {
        if (my_project->objectName().isEmpty())
            my_project->setObjectName("my_project");
        my_project->resize(800, 600);
        my_project->setCursor(QCursor(Qt::CursorShape::OpenHandCursor));
        stackedWidget = new QStackedWidget(my_project);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(10, 20, 771, 581));
        first_page = new QWidget();
        first_page->setObjectName("first_page");
        welcome_label = new QLabel(first_page);
        welcome_label->setObjectName("welcome_label");
        welcome_label->setGeometry(QRect(0, 20, 751, 101));
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        welcome_label->setFont(font);
        welcome_label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        description_label = new QLabel(first_page);
        description_label->setObjectName("description_label");
        description_label->setGeometry(QRect(190, 110, 501, 81));
        QFont font1;
        font1.setPointSize(14);
        description_label->setFont(font1);
        description_label->setAlignment(Qt::AlignmentFlag::AlignJustify|Qt::AlignmentFlag::AlignVCenter);
        monitoring_btn = new QPushButton(first_page);
        monitoring_btn->setObjectName("monitoring_btn");
        monitoring_btn->setGeometry(QRect(300, 330, 191, 51));
        QFont font2;
        font2.setPointSize(14);
        font2.setBold(true);
        monitoring_btn->setFont(font2);
        stackedWidget->addWidget(first_page);
        login_page = new QWidget();
        login_page->setObjectName("login_page");
        user_input = new QLineEdit(login_page);
        user_input->setObjectName("user_input");
        user_input->setGeometry(QRect(320, 190, 161, 28));
        password_input = new QLineEdit(login_page);
        password_input->setObjectName("password_input");
        password_input->setGeometry(QRect(320, 240, 161, 28));
        password_input->setEchoMode(QLineEdit::EchoMode::Password);
        login_btn = new QPushButton(login_page);
        login_btn->setObjectName("login_btn");
        login_btn->setGeometry(QRect(340, 300, 121, 41));
        login_btn->setFont(font2);
        login_label = new QLabel(login_page);
        login_label->setObjectName("login_label");
        login_label->setGeometry(QRect(190, 40, 361, 71));
        login_label->setFont(font);
        login_label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        Important_note = new QLabel(login_page);
        Important_note->setObjectName("Important_note");
        Important_note->setGeometry(QRect(240, 100, 261, 31));
        QFont font3;
        font3.setPointSize(12);
        Important_note->setFont(font3);
        Important_note->setAlignment(Qt::AlignmentFlag::AlignCenter);
        username_label = new QLabel(login_page);
        username_label->setObjectName("username_label");
        username_label->setGeometry(QRect(120, 180, 171, 41));
        username_label->setFont(font3);
        passwordlabel = new QLabel(login_page);
        passwordlabel->setObjectName("passwordlabel");
        passwordlabel->setGeometry(QRect(120, 240, 151, 31));
        passwordlabel->setFont(font3);
        newadmin_btn = new QPushButton(login_page);
        newadmin_btn->setObjectName("newadmin_btn");
        newadmin_btn->setGeometry(QRect(520, 460, 221, 41));
        newadmin_btn->setFont(font2);
        valid_massage = new QLabel(login_page);
        valid_massage->setObjectName("valid_massage");
        valid_massage->setGeometry(QRect(250, 370, 271, 31));
        stackedWidget->addWidget(login_page);
        signUp_page = new QWidget();
        signUp_page->setObjectName("signUp_page");
        signUp_label = new QLabel(signUp_page);
        signUp_label->setObjectName("signUp_label");
        signUp_label->setGeometry(QRect(90, 40, 611, 51));
        signUp_label->setFont(font);
        signUp_label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        new_userLabel = new QLabel(signUp_page);
        new_userLabel->setObjectName("new_userLabel");
        new_userLabel->setGeometry(QRect(130, 190, 141, 41));
        new_userLabel->setFont(font3);
        new_passLabel = new QLabel(signUp_page);
        new_passLabel->setObjectName("new_passLabel");
        new_passLabel->setGeometry(QRect(130, 270, 141, 31));
        new_passLabel->setFont(font3);
        new_userLine = new QLineEdit(signUp_page);
        new_userLine->setObjectName("new_userLine");
        new_userLine->setGeometry(QRect(340, 200, 181, 28));
        new_passwordLine = new QLineEdit(signUp_page);
        new_passwordLine->setObjectName("new_passwordLine");
        new_passwordLine->setGeometry(QRect(340, 270, 181, 28));
        confirm_botton = new QPushButton(signUp_page);
        confirm_botton->setObjectName("confirm_botton");
        confirm_botton->setGeometry(QRect(340, 340, 171, 51));
        confirm_botton->setFont(font2);
        sign_up_massage = new QLabel(signUp_page);
        sign_up_massage->setObjectName("sign_up_massage");
        sign_up_massage->setGeometry(QRect(340, 420, 171, 20));
        stackedWidget->addWidget(signUp_page);

        retranslateUi(my_project);

        QMetaObject::connectSlotsByName(my_project);
    } // setupUi

    void retranslateUi(QWidget *my_project)
    {
        my_project->setWindowTitle(QCoreApplication::translate("my_project", "my_project", nullptr));
        welcome_label->setText(QCoreApplication::translate("my_project", "welocome to smart energy menitor", nullptr));
        description_label->setText(QCoreApplication::translate("my_project", "Empowering Ain Shams University with \n"
"               Smart Energy Solutions", nullptr));
        monitoring_btn->setText(QCoreApplication::translate("my_project", "start monitoring", nullptr));
        login_btn->setText(QCoreApplication::translate("my_project", "login", nullptr));
        login_label->setText(QCoreApplication::translate("my_project", "Energy menitor login", nullptr));
        Important_note->setText(QCoreApplication::translate("my_project", "Authorized Personnel Only", nullptr));
        username_label->setText(QCoreApplication::translate("my_project", " Enter username :", nullptr));
        passwordlabel->setText(QCoreApplication::translate("my_project", "Enter password :", nullptr));
        newadmin_btn->setText(QCoreApplication::translate("my_project", "create new admin", nullptr));
        valid_massage->setText(QString());
        signUp_label->setText(QCoreApplication::translate("my_project", "create account in energy system monitor", nullptr));
        new_userLabel->setText(QCoreApplication::translate("my_project", "new user name :", nullptr));
        new_passLabel->setText(QCoreApplication::translate("my_project", "new password :", nullptr));
        confirm_botton->setText(QCoreApplication::translate("my_project", "confirm", nullptr));
        sign_up_massage->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class my_project: public Ui_my_project {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MY_PROJECT_H
