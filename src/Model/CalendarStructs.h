#pragma once
#include <string>
#include <QDateTime>

struct Patient;

struct CalendarEvent
{
	CalendarEvent(const Patient& p);
	CalendarEvent() {}
	long long rowid{ 0 };
	std::string summary;
	std::string description;
	QDateTime start;
	QDateTime end;
	
	long long patient_rowid{ 0 };
};
