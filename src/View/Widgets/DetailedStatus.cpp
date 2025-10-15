#include "DetailedStatus.h"

#include <QIcon>
#include <QPainter>
#include <QCursor>

#include "Presenter/DetailedStatusPresenter.h"
#include <QRadioButton>

DetailedStatus::DetailedStatus(DetailedStatusPresenter& presenter) : presenter(presenter)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	setWindowFlags(Qt::Window);
	setWindowTitle(tr("Notes and Procedures"));

	connect(ui.tabWidget, &QTabWidget::currentChanged, this, [&](int index) { if (index == 1) ui.notesEdit->setFocus();});
    connect(ui.okButton, &QPushButton::clicked, this, [&] {presenter.okPressed(); close(); });
    connect(ui.cancelButton, &QPushButton::clicked, this, [=, this] { close(); });
	
    presenter.setView(this);

	ui.notesEdit->setFocus();
}


void DetailedStatus::setNotes(const std::string& notes)
{
	ui.notesEdit->setText(notes.c_str());
}

void DetailedStatus::focusNotes(bool focus)
{
	ui.tabWidget->setCurrentIndex(focus ? 1 : 0);
}


std::string DetailedStatus::getNotes(){ return ui.notesEdit->getText(); }


void DetailedStatus::setHistoryData(const std::vector<Procedure>& history)
{
	m_historyModel.setProcedures(history);
	ui.tableView->setModel(&m_historyModel);

	ui.tableView->horizontalHeader()->setHighlightSections(false);

	ui.tableView->verticalHeader()->setVisible(false);

	ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	
	ui.tableView->verticalHeader()->setDefaultSectionSize(25);
	ui.tableView->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	
	ui.tableView->hideColumn(0);
	ui.tableView->setColumnWidth(1, 90);
	ui.tableView->setColumnWidth(2, 90);
	ui.tableView->setColumnWidth(3, 150);
	ui.tableView->setColumnWidth(4, 50);
	ui.tableView->setColumnWidth(5, 150);
	ui.tableView->setColumnWidth(6, 70);
	ui.tableView->setColumnWidth(7, 100);
	ui.tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	ui.tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	ui.tableView->horizontalHeader()->setSectionResizeMode(8, QHeaderView::Stretch);
	ui.tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

DetailedStatus::~DetailedStatus()
{

}
