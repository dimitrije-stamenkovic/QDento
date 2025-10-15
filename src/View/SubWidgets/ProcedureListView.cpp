#include "ProcedureListView.h"

#include <QKeyEvent>

ProcedureListView::ProcedureListView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.searchEdit->installEventFilter(this);

	proxyModel.setSourceModel(&model);
	proxyModel.setFilterKeyColumn(3);

	auto& table = ui.tableView;

	table->setModel(&proxyModel);
	table->setMouseTracking(true);

	table->setColumnWidth(0, 30);
	table->hideColumn(1);
    table->setColumnWidth(2, 100);
	table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeMode::Stretch);
	table->horizontalHeader()->setHighlightSections(false);
	table->verticalHeader()->setVisible(false);
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setSelectionMode(QAbstractItemView::SingleSelection);


	table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
	table->verticalHeader()->hide();

	auto favDelagete = new FavButtonDelegate();
	table->setItemDelegateForColumn(0, favDelagete);

	connect(favDelagete, &FavButtonDelegate::updateRequested, this, [&] {
		ui.tableView->viewport()->update();
	});

	connect(favDelagete, &FavButtonDelegate::favouriteClicked, this, [&](int rowIdx) {

		emit favouritesClicked(proxyModel.index(rowIdx, 0).data().toInt());

		refresh();

	});

	connect(ui.tableView, &QTableView::doubleClicked, this, [&](const QModelIndex& index) {
		
		if (!index.isValid()) return;

		int idx = proxyModel.index(index.row(), 0).data().toInt();

		emit codeDoubleClicked(idx);

	});

	connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, this, [&] {

		current_index = table->selectionModel()->currentIndex().row();

		if (current_index == -1) {
			emit codeSelected(-1);
			ui.tableView->clearSelection(); //because of bug when reseting the model
			return;
		}

		emit codeSelected(proxyModel.index(current_index, 0).data().toInt());
	});


	connect(ui.searchEdit, &QLineEdit::textChanged, this, [=, this](const QString& text)
	{
			s_search = text;
			proxyModel.setFilterRegularExpression(QRegularExpression(s_search, QRegularExpression::CaseInsensitiveOption));
			ui.tableView->selectRow(current_index);
	});

	
}

int ProcedureListView::currentRow()
{
	QModelIndex index = ui.tableView->selectionModel()->currentIndex();

	if (index.isValid()) {
		return model.index(index.row(), 0).data().toInt();
	}

	return -1;
}

void ProcedureListView::setPresenter(ProcedureListPresenter* p)
{
	presenter = p;

	if (current_section == -1) {
		current_section = presenter->hasFavourites() ? 1 : 0;
	}


	refresh();

	ui.searchEdit->setText(s_search);
	ui.tableView->selectRow(current_index);
}

void ProcedureListView::refresh()
{
	auto list = presenter->getList();

	model.setProcedures(presenter->getList());

	emit codeSelected(-1);
}


bool ProcedureListView::eventFilter(QObject* obj, QEvent* e)
{

	if (
		e->type() == QEvent::KeyPress &&
		(static_cast<QKeyEvent*>(e)->key() == Qt::Key_Down ||
			static_cast<QKeyEvent*>(e)->key() == Qt::Key_Up
			)
		)
	{
		int currentRow = ui.tableView->currentIndex().row();

		currentRow +=
			static_cast<QKeyEvent*>(e)->key() == Qt::Key_Up ?
			-1 : 1;

		ui.tableView->selectRow(currentRow);

		return true;

	}

	return QObject::eventFilter(obj, e);
}
