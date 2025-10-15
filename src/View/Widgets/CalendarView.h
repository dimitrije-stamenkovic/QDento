#pragma once

#include <QWidget>
#include "ui_CalendarView.h"
#include "Model/CalendarStructs.h"
#include <QDate>

class CalendarPresenter;
class CalendarWidget;

class CalendarView : public QWidget
{
    Q_OBJECT

    CalendarPresenter* presenter{ nullptr };

    CalendarWidget* calendarWidget{ nullptr };

    void initTable();

    void paintEvent(QPaintEvent* event) override;

    void showCalendarWidget();

public:
    CalendarView(QWidget *parent = nullptr);
    void setCalendarPresenter(CalendarPresenter* p);
    void setEventList(const std::vector<CalendarEvent>& list, const CalendarEvent& clipboard);
    void updateWeekView(QDate from, QDate to, int currentDayColumn);
    ~CalendarView();

private:
    Ui::CalendarView ui;
};
