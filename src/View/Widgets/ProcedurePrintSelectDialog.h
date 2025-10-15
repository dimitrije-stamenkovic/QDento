#pragma once

#include <QDialog>
#include "ui_ProcedurePrintSelectDialog.h"
#include <vector>
#include <optional>
#include "Model/Dental/Procedure.h"
#include "View/TableModels/ProcedureSelectModel.h"
#include <QRadioButton>

class ProcedurePrintSelectDialog : public QDialog
{
	Q_OBJECT

	std::vector<int> m_selectedRows;
	ProcedureSelectModel model;

	void paintEvent(QPaintEvent* e) override;

public:
	ProcedurePrintSelectDialog(const std::vector<Procedure>& procedures, QWidget* parent = Q_NULLPTR);
	
	const std::vector<int> selectedProcedures() const;

	~ProcedurePrintSelectDialog();


private:
	Ui::ProcedurePrintSelectDialog ui;
};
