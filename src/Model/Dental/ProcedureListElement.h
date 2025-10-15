#pragma once
#include "Model/Dental/Procedure.h"

struct ProcedureListElement
{
	Procedure::Type type;
	std::string code;
	std::string name;
	bool favourite = false;
	double price = 0;
	std::string diagnosis;
};
