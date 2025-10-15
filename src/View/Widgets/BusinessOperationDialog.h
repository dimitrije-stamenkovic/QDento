#pragma once

#include <QDialog>
#include "ui_BusinessOperationDialog.h"
#include "Model/Financial/BusinessOperation.h"
#include "Model/Validators/CommonValidators.h"
#include <optional>
#include "Model/Dental/ProcedureListElement.h"

class BuisnessOperationDialog : public QDialog
{
	Q_OBJECT

	std::optional<BusinessOperation> m_operation;

	std::vector<ProcedureListElement> m_procedures;

	NotEmptyValidator notEmptyValidator;

	void paintEvent(QPaintEvent* e) override;

public:
	BuisnessOperationDialog(const std::optional<BusinessOperation>& op = {});

	std::optional<BusinessOperation> getResult() { return m_operation; };

	~BuisnessOperationDialog();

	

private:
	Ui::BusinessOperationDialog ui;
};
