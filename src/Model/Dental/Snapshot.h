#pragma once
#include <string>
#include <vector>

#include "Model/Date.h"
#include "Model/Dental/ToothContainer.h"
#include "Model/Dental/Procedure.h"

struct Procedure;

struct Snapshot {

	Snapshot(const Procedure& p, const ToothContainer& t);
	Snapshot(const ToothContainer& t, Date& date);
	Snapshot() {};

	Date date;
	std::string procedure_name;
	std::string procedure_diagnosis;
	std::string procedure_note;
	ToothContainer teeth;
	std::vector<int> affected_teeth;

};
