#include "ProcedureDialog.h"
#include "Presenter/ProcedureDialogPresenter.h"

ProcedureDialog::ProcedureDialog(ProcedureDialogPresenter& presenter, QWidget *parent)
	: QDialog(parent), presenter(presenter), proxyModel(this)
{
	ui.setupUi(this);

	ui.procedureInput->setParamMinHeight(300);

	setModal(true);
	
	setWindowFlags(windowFlags() | Qt::CustomizeWindowHint |
								   Qt::WindowMaximizeButtonHint |
								   Qt::WindowCloseButtonHint);

	setWindowTitle(tr("Add Procedure"));


	connect(ui.procedureListView, &ProcedureListView::codeDoubleClicked, this, [&] { presenter.formAccepted(); });
	connect(ui.procedureListView, &ProcedureListView::codeSelected, this, [&](int idx){ presenter.setCode(idx); });
	connect(ui.procedureListView, &ProcedureListView::favouritesClicked, this, [&](int idx) { presenter.favClicked(idx); });

	connect(ui.cancelButton, &QPushButton::clicked, this, [&] { close(); });
	connect(ui.okButton, &QPushButton::clicked, this, [&] { presenter.formAccepted(); });

    presenter.setView(this);
}

ProcedureDialog::~ProcedureDialog()
{
}

void ProcedureDialog::setSelectionLabel(const std::vector<int>& selectedTeethNum)
{
	QString selectedTeeth;

	selectedTeeth.reserve(15 + selectedTeethNum.size() * 3);

	selectedTeeth.append(tr("Selected Teeth: "));

    for (size_t i = 0; i < selectedTeethNum.size(); i++)
	{
		selectedTeeth.append(QString::number(selectedTeethNum[i]));
		if (i < selectedTeethNum.size() - 1)
		{
			selectedTeeth.append(", ");
		}
	}

	if (!selectedTeethNum.size())
	{
		selectedTeeth.append(tr("None"));
	}

	ui.statusLabel->setText(selectedTeeth);
}

ProcedureListView* ProcedureDialog::procedureList()
{
	return ui.procedureListView;
}

ProcedureInput* ProcedureDialog::procedureInput()
{
	return ui.procedureInput;
}


