#pragma once

#include "Presenter/ProcedureListPresenter.h"
#include "Model/UserStructs.h"
#include <vector>

class SettingsDialog;

class SettingsMainPresenter
{
	std::vector<Dentist> m_dentists;

	SettingsDialog* view{nullptr};

	ProcedureListPresenter procedure_list;

public:

	SettingsMainPresenter();

	void setView(SettingsDialog* view);
	void addDentist();
	void removeDentist(int idx);
	void okPressed();
	bool applyChanges();
	void sqlCommandExec(const std::string& sql);
    void practiceTabFocused(); //need to refresh the dentist list
	void addProcedureElement();
	void editProcedureElement(int row);
	void removeProcedureElement(int row);
	void favClicked(int row);

};
