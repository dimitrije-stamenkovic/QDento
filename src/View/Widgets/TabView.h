#pragma once

#include <QWidget>

#include "View/Widgets/VisitView.h"
#include "View/Widgets/PerioView.h"
#include "View/Widgets/FinancialView.h"
#include "View/uiComponents/PixmapLabel.h"
#include "View/Widgets/WelcomeWidget.h"
#include "View/Widgets/CalendarView.h"
#include "ui_TabView.h"

class TabTitle;

class TabView : public QWidget
{
	Q_OBJECT

	PerioView m_perioView;
	VisitView m_listView;
	FinancialView m_financialView;
	CalendarView m_calendarView;
	WelcomeWidget welcomeScreen{ nullptr };

	void showTabWidget(QWidget* w);

	TabTitle* getTabTitle(int tabId);
	int getTabIndex(int tabId);


public:
	TabView(QWidget *parent = Q_NULLPTR);
	~TabView();

	void requestClose(int tabId);

	// Inherited via ITabView
	void removeAllTabs();
	void newTab(int tabId, const TabName& tabName);
	void focusTab(int tabId);
	void removeCurrentTab();
	void changeTabName(const TabName& tabName, int tabId);

	void removeTab(int tabId);

	std::pair<int, int> getScrollPos();
	void setScrollPos(const std::pair<int, int>& scrollPos);

	void showListView();
    void showPerioView();
	void showFinancialView();
	void showWelcomeScreen();
	void showCalendarView();

	VisitView* listView() { return &m_listView; }
	PerioView* perioView() { return &m_perioView; }
	FinancialView* financialView() { return &m_financialView; }
	CalendarView* calendarView()  { return &m_calendarView; }

signals:
	void closeRequested(int mapIndex);

private:
	Ui::TabView ui;




};
