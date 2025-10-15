#pragma once
#include <set>
#include <string>

namespace DbDiagnosis
{
	std::set<std::string> getDiagnosisList(bool includeProcedureList = false);
	void setDiagnosisList(const std::set<std::string>& diagnoss);
}