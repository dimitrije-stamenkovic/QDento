#pragma once

#include <QString>
#include "Model/Dental/Procedure.h"

struct QProcedure
{
	QProcedure(const Procedure& p);
	QString date;
	QString diagnosis;
	QString tooth{};
	QString description;
	QString code;
	QString price;
	QString dentist;
	QString notes;
};

