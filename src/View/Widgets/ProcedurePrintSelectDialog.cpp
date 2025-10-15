#include "ProcedurePrintSelectDialog.h"
#include <QPainter>
#include "View/CommonIcon.h"

void ProcedurePrintSelectDialog::paintEvent(QPaintEvent*)
{
	QPainter painter(this);

	painter.fillRect(rect(), Qt::white);
}

ProcedurePrintSelectDialog::ProcedurePrintSelectDialog(const std::vector<Procedure>& procedures, QWidget* parent)
	: QDialog(parent), model(procedures)
{
	ui.setupUi(this);
	setModal(true);
    setWindowTitle(tr("Select Procedures"));

	ui.tableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
	ui.tableView->setSelectionMode(QAbstractItemView::SelectionMode::NoSelection);
	ui.tableView->setModel(&this->model);

	ui.tableView->setFocusPolicy(Qt::NoFocus);
	ui.tableView->setColumnWidth(0, 110);
	ui.tableView->setColumnWidth(1, 200);
    ui.tableView->setColumnWidth(2, 80);
	ui.tableView->setColumnWidth(3, 80);
	ui.tableView->verticalHeader()->setDefaultSectionSize(20);
	ui.tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	ui.tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	ui.tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
	ui.tableView->setShowGrid(false);
	ui.tableView->verticalHeader()->hide();

	if (procedures.empty()) {
		ui.tableView->hide();
		adjustSize();
	}

    connect(ui.okButton, &QPushButton::pressed, this, [=, this]
		{
			auto select = ui.tableView->selectionModel()->selectedIndexes();

			m_selectedRows = model.selectedRows();

			accept();

		});
}

const std::vector<int> ProcedurePrintSelectDialog::selectedProcedures() const
{
	return m_selectedRows;
}

ProcedurePrintSelectDialog::~ProcedurePrintSelectDialog()
{
}
