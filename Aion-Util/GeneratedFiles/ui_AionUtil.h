/********************************************************************************
** Form generated from reading UI file 'AionUtil.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AIONUTIL_H
#define UI_AIONUTIL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AionUtilClass
{
public:
    QWidget *centralWidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QPushButton *pushButton;
    QCheckBox *worldChat_checkBox;
    QWidget *page_2;

    void setupUi(QMainWindow *AionUtilClass)
    {
        if (AionUtilClass->objectName().isEmpty())
            AionUtilClass->setObjectName(QStringLiteral("AionUtilClass"));
        AionUtilClass->resize(600, 400);
        centralWidget = new QWidget(AionUtilClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 601, 401));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        pushButton = new QPushButton(page);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(140, 330, 331, 28));
        worldChat_checkBox = new QCheckBox(page);
        worldChat_checkBox->setObjectName(QStringLiteral("worldChat_checkBox"));
        worldChat_checkBox->setGeometry(QRect(30, 20, 181, 16));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        stackedWidget->addWidget(page_2);
        AionUtilClass->setCentralWidget(centralWidget);

        retranslateUi(AionUtilClass);

        QMetaObject::connectSlotsByName(AionUtilClass);
    } // setupUi

    void retranslateUi(QMainWindow *AionUtilClass)
    {
        AionUtilClass->setWindowTitle(QApplication::translate("AionUtilClass", "AionUtil", nullptr));
        pushButton->setText(QApplication::translate("AionUtilClass", "You are inside of the StackedWidget.", nullptr));
        worldChat_checkBox->setText(QApplication::translate("AionUtilClass", "Disable World chat", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AionUtilClass: public Ui_AionUtilClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AIONUTIL_H
