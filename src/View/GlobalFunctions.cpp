#include "GlobalFunctions.h"
#include <string>
#include "QString"
#include <cmath>
#include <QTableView>
#include <QHeaderView>
#include "Model/User.h"

QString roundDouble(double number)
{
	double intPart;
	return std::modf(number, &intPart) == 0.0 ?
		QString::number(number) :
		QString::number(number, 'f', 2);
}

QString priceToString(double price) { return roundDouble(price) + " " + User::company().currency.c_str(); }

QString formatDoubleWithDecimal(const double& price) //adding the dot in case of integer
{
	return QString::number(price, 'f', 2);
}

void setTableViewDefaults(QTableView* view)
{
	view->verticalHeader()->setHidden(true);
	view->verticalHeader()->setDefaultSectionSize(20);
	view->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	view->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	view->horizontalHeader()->setStretchLastSection(true);
	view->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
	view->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
}


