#pragma once

#include <unordered_map>
#include <set>
#include <optional>
#include <vector>
#include "Model/UserStructs.h"

namespace DbDentist
{
	std::optional<Dentist>get(long long dentist_rowid, const std::string& pass);
	std::optional<Dentist>get(long long dentist_rowid);
	bool removeDentist(long long dentist_rowid);
	long long getDoctorAutoLoginRowid();
	bool setAutoLogin(long long dentist_rowid, bool remember);
	bool update(const Dentist& dentist);
	long long insert(const Dentist& dentist);
	std::vector<Dentist> getList();
	bool updateFavouriteProcedures(const std::vector<std::string>& procedureCodes, long long dentist_rowid);
	std::set<std::string> getFavouriteProcedures(long long dentistRowid);
}
