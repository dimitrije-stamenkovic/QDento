#pragma once

class ILoginView;

#include <optional>
#include "Model/UserStructs.h"
#include "Database/DbDentist.h"

class LoginView;

class LoginPresenter
{

	std::vector<Dentist> m_users;
	LoginView* view{ nullptr };
	bool loginSuccessful{ false };
	int m_currentIndex = -1;

public:

	LoginPresenter();

	bool successful();
	void setView(LoginView* view);
	void userIdxChanged(int idx);
	void okPressed(const std::string& pass, bool remember);
	void login(long long rowid);
};

