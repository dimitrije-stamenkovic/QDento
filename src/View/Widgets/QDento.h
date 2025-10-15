#pragma once

#include <QtWidgets/QMainWindow>
#include <QPainter>

#include "ui_QDento.h"

class TabView;

class QDento : public QMainWindow
{
    Q_OBJECT

    void paintEvent(QPaintEvent* event) override;
    void closeEvent(QCloseEvent* event) override;

public:
    QDento(QWidget *parent = Q_NULLPTR);
    TabView* tabView();
    void setUserLabel(const std::string& doctorName, const std::string& practiceName);
    void exitProgram();
    bool initialized();
    void disableButtons(bool saveDisabled);
    void setNotificationIcon(int activeNotifCount);

    ~QDento();

    bool m_loggedIn = false;

private:
    Ui::DinoDentClass ui;
};
