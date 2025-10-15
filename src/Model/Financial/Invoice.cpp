#include "Invoice.h"

#include "Model/User.h"
#include "Model/FreeFunctions.h"
#include "BusinessOperation.h"
#include <QObject>

Invoice::Invoice(const Patient& p) :
    type(FinancialDocType::Invoice),
	recipient(p)
	
{}

Invoice::Invoice(const Recipient& r) :
    type (FinancialDocType::Invoice),
	recipient(r)
{
}

std::optional<MainDocument> Invoice::mainDocument() const
{
	if (type == FinancialDocType::Invoice)	return {};

	return m_mainDocument;
}

void Invoice::setMainDocumentData(long long num, Date date)
{
	m_mainDocument.number = num;
	m_mainDocument.date = date;
}

std::string Invoice::title() const
{
	std::string titles[] = { QObject::tr("Invoice").toStdString(), QObject::tr("Debit Note").toStdString(), QObject::tr("Credit Note").toStdString() };

	return titles[static_cast<int>(type)];
}

Issuer Invoice::issuer() const
{
	return Issuer();
}

std::string Invoice::getInvoiceNumber() const
{
	return FreeFn::leadZeroes(number, 10);
}

void Invoice::removeOperation(int idx)
{
	businessOperations.erase(businessOperations.begin() + idx);
}

void Invoice::addOperation(const BusinessOperation& op)
{
	businessOperations.push_back(op);
}

void Invoice::editOperation(const BusinessOperation& op, int idx)
{
	businessOperations[idx] = op;
}

double Invoice::amount() const
{
	double result = 0;

	for (auto& operation : businessOperations)
	{
		result += operation.value_price();
	}

    return result;
}

double Invoice::VATamount() const
{
    if(!VAT) return 0;

    return amount()*VAT/100;
}
