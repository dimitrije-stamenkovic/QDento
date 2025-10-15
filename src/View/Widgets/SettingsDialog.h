#pragma once

#include <QDialog>
#include "ui_SettingsDialog.h"

#include "Presenter/SettingsMainPresenter.h"

#include "View/TableModels/PlainTableModel.h"
#include "Model/UserStructs.h"
#include "Model/Validators/FinancialValidator.h"
#include "Model/Validators/CommonValidators.h"

class SettingsDialog : public QDialog
{
	Q_OBJECT

	SettingsMainPresenter presenter;

	NotEmptyValidator not_empty_validator;
	IbanValidator iban_validator;
	BICValidator bic_validator;

	PlainTableModel sql_table_model;
    QString getDentistName(const Dentist& entity);

public:

	enum SettingsTab { GENERAL, DENTIST, PRACTICE, COMPANY, PROCEDURES, DIAGNOSIS, SQL };

	SettingsDialog(QDialog *parent = Q_NULLPTR);

    void setAdminPriv(bool admin);

	ProcedureListView* getProcedureView();
	void setSqlTable(const PlainTable& table);
	void setCompany(const Company& company);
	void setDoctor(const Dentist& dentist);
	void setDentistList(const std::vector<Dentist>& doctors);
	Company getCompany();
	Dentist get();
	void replaceCurrentItem(const Dentist& d);
	bool allFieldsAreValid();
	void focusTab(SettingsTab t);
	bool isADANumenclature();
	~SettingsDialog();

private:
	Ui::SettingsDialog ui;


};
