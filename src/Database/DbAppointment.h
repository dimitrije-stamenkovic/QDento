#pragma once
#include "Model/CalendarStructs.h"

class QDate;

namespace DbAppointment
{
	long long insert(const CalendarEvent& e, long long dentist_rowid);
	void update(const CalendarEvent& e);
	void remove(long long rowid);
	std::vector<CalendarEvent> get(const QDate& from, const QDate& to, long long dentist_rowid);
}