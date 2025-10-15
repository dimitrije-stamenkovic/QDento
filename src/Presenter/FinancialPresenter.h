#pragma once
#include "Presenter/TabInstance.h"
#include "Model/Financial/Invoice.h"
#include "Model/Dental/DentalVisit.h"
#include "Model/Patient.h"

class FinancialView;
class TabView;

class FinancialPresenter : public TabInstance
{
	FinancialView* view;

	// Inherited via TabInstance
public:

	Invoice m_invoice;

	FinancialPresenter(TabView* tabView, std::shared_ptr<Patient> patient, const std::vector<Procedure>& procedures = {});
	FinancialPresenter(TabView* tabView, long long rowId);
	FinancialPresenter(TabView* tabView, const Recipient& r);

	void addOperation();
	void editOperation(int idx);
	void removeOperation(int idx);

	void print();

	void dateChanged(Date date);
	void taxEventDateChanged(Date date);
	void paymentTypeChanged(PaymentType type);
	void docTypeChanged(int index);
	void mainDocumentChanged(long long num, Date date);
	void editRecipient();
	void editIssuer();
	void invoiceNumberChanged(long long number);
    void vatChanged(bool isVat);

	long long rowID() const override;
	bool save() override;
	void setDataToView() override;
	bool isNew() override;

	TabName getTabName() override;
};

