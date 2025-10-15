#include "QProcedure.h"

#include "Model/User.h"
#include "Model/Dental/Procedure.h"
#include "View/GlobalFunctions.h"

QProcedure::QProcedure(const Procedure& p) :
	date(QString::fromStdString(p.date.toLocalFormat())),
	code(p.code.c_str()),
	description(p.name.c_str()),
	diagnosis(QString::fromStdString(p.diagnosis)),
	tooth(p.getToothString().c_str()),
	dentist(QString::fromStdString(User::getNameFromRowid(p.dentist_rowid))),
	notes(QString::fromStdString(p.notes)),
	price(priceToString(p.price))
{}
