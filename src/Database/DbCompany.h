#pragma once
#include <vector>
#include <set>
#include "Model/UserStructs.h"

namespace DbCompany
{
	Company getInvoiceData();
	bool updateInvoiceData(const Company& company);
	bool insertInvoiceData(const Company& company);
	bool noInvoiceData();
}
