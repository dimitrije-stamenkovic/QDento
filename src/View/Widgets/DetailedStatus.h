#pragma once

#include <QDialog>
#include  <QVBoxLayout>
#include "ui_DetailedStatus.h"

#include "View/TableModels/ProcedureTableModel.h"
#include <QTextEdit>

class DetailedStatusPresenter;

class DetailedStatus final: public QDialog
{
	Q_OBJECT

    DetailedStatusPresenter& presenter;

	ProcedureTableModel m_historyModel;

public:
    DetailedStatus(DetailedStatusPresenter& presenter);

	void setNotes(const std::string& notes);
	void focusNotes(bool focus);
	std::string getNotes();
	void setHistoryData(const std::vector<Procedure>& history);

	~DetailedStatus();

private:
	Ui::DetailedStatus ui;


};
