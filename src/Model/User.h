#pragma once

#include "UserStructs.h"

namespace User
{
	void loadDentistList();

	bool isValid();
	const Dentist& dentist();
	const Company& company();
	void setCurrentDentist(const Dentist& dentist);
	void setCurrentCompany(const Company& company);
	void resetUser();
    bool isCurrentUser(long long rowid);
	std::string getNameFromRowid(long long rowid);

	inline bool ADA_num = false;
};

