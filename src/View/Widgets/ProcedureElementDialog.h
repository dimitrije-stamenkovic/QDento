#pragma once

#include <QDialog>
#include "ui_ProcedureElementDialog.h"
#include "Model/Dental/ProcedureListElement.h"
#include "Model/Validators/CommonValidators.h"
#include <optional>
#include <set>

class ProcedureElementDialog : public QDialog
{
	Q_OBJECT

	std::optional<ProcedureListElement> m_result;
	NotEmptyValidator not_empty_validator;
	std::set<std::string> m_existing_codes;

public:
	ProcedureElementDialog(const std::set<std::string>& existing_codes, std::optional<ProcedureListElement> e = {});
	std::optional<ProcedureListElement> getResult() { return m_result;}
	~ProcedureElementDialog();

private:
	Ui::ProcedureElementDialogClass ui;
};

