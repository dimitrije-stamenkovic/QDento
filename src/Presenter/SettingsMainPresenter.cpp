#include "SettingsMainPresenter.h"
#include "Database/DbCompany.h"
#include "Database/DbDentist.h"
#include "Database/Database.h"
#include "Model/User.h"
#include "View/ModalDialogBuilder.h"
#include "GlobalSettings.h"
#include "Presenter/DoctorDialogPresenter.h"
#include "Model/PlainTable.h"
#include "View/SubWidgets/ProcedureListView.h"
#include "Model/Patient.h"
#include "Database/DbPatient.h"
#include "Database/DbDentalVisit.h"
#include "Database/DbProcedure.h"
#include "View/Widgets/SettingsDialog.h"
#include "View/Widgets/ProcedureElementDialog.h"

SettingsMainPresenter::SettingsMainPresenter() :
	m_dentists(DbDentist::getList())
{}

void SettingsMainPresenter::setView(SettingsDialog* view)
{
	this->view = view;

	auto company = DbCompany::getInvoiceData();
	auto dentist = DbDentist::get(User::dentist().rowID).value(); //quite unsafe lol


	view->setDoctor(dentist);
	view->setCompany(company);
	view->setDentistList(m_dentists);

	view->getProcedureView()->setPresenter(&procedure_list);

	view->getProcedureView()->refresh();
}

void SettingsMainPresenter::okPressed()
{
	if (applyChanges())
	{
		view->close();
	}
}

void SettingsMainPresenter::addDentist()
{
	DentistDialogPresenter p;

	auto dentist = p.open();

	if (!dentist.has_value()) return;

	m_dentists.emplace_back(*dentist);

	view->setDentistList(m_dentists);
}

void SettingsMainPresenter::removeDentist(int idx)
{
	if (idx < 0) return;

	if (User::isCurrentUser(m_dentists[idx].rowID))
	{
		ModalDialogBuilder::showError(QObject::tr("You can't delete the profile which you are using").toStdString());
		return;
	}
	
	if (!ModalDialogBuilder::askDialog(QObject::tr("This action cannot be undone. Are you sure?").toStdString())) return;

	if (!DbDentist::removeDentist(m_dentists[idx].rowID)) {
		return;
	}

	m_dentists.erase(m_dentists.begin() + idx);
	
	view->setDentistList(m_dentists);
}

bool SettingsMainPresenter::applyChanges()
{
	auto company = view->getCompany();

	auto dentist = view->get();

	dentist.rowID = User::dentist().rowID;

	DbCompany::updateInvoiceData(company);

	DbDentist::update(dentist);

	auto useADA = view->isADANumenclature();

	GlobalSettings::setToothNum(view->isADANumenclature());
	User::ADA_num = useADA;
	User::setCurrentDentist(DbDentist::get(dentist.rowID).value());
	User::setCurrentCompany(DbCompany::getInvoiceData());
	User::loadDentistList();

	return true;
}

void SettingsMainPresenter::sqlCommandExec(const std::string& sql)
{
	Db db(sql);

	int columnCount = db.columnCount();

	if (!db.columnCount()) {

		if (!db.execute()) return;

		ModalDialogBuilder::showMessage(
			QObject::tr("Query successful\n Affected rows: ").toStdString() +
			std::to_string(db.rowsAffected())
		);

		return;
	}

	PlainTable table;

	for (int i = 0; i < columnCount; i++) {
		table.addColumn(PlainColumn(db.columnName(i)));
	}

	while (db.hasRows()) {
		for (int i = 0; i < columnCount; i++) {
            table.addCell(i, PlainCell{ db.asString(i) });
		}
	}
	
	view->setSqlTable(table);
}

void SettingsMainPresenter::practiceTabFocused()
{
    view->setDentistList(m_dentists);
}

void SettingsMainPresenter::addProcedureElement()
{
	ProcedureElementDialog d(procedure_list.getUniqueCodes());
	
	d.exec();

	auto result = d.getResult();

	if (!result) return;
	
	procedure_list.addProcedureElement(result.value());

	view->getProcedureView()->refresh();
}

void SettingsMainPresenter::editProcedureElement(int idx) {

	ProcedureElementDialog d(procedure_list.getUniqueCodes(), procedure_list.getList()[idx]);
	d.exec();

	auto result = d.getResult();

	if (!result) return;

	procedure_list.editProcedureElement(result.value(), idx);

	view->getProcedureView()->refresh();
}

void SettingsMainPresenter::removeProcedureElement(int idx)
{
	procedure_list.removeProcedureElement(idx);

	view->getProcedureView()->refresh();
}

void SettingsMainPresenter::favClicked(int idx)
{
	procedure_list.favClicked(idx);

	view->getProcedureView()->refresh();
}