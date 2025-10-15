#include "BusinessOperation.h"
#include "Model/Dental/Procedure.h"
#include "Model/User.h"

BusinessOperation::BusinessOperation(const std::string& code, const std::string& name, double price, int quantity) :
	activity_code(code),
	activity_name(name),
	unit_price(price),
	quantity(quantity)
{
}

BusinessOperation::BusinessOperation(const Procedure& p) :
	activity_code(p.code),
	activity_name(p.name),
	unit_price(p.price),
	quantity(1)
{
}

bool BusinessOperation::operator == (const BusinessOperation& other) const
{
	return (activity_code == other.activity_code) &&
		(activity_name == other.activity_name) &&
		(unit_price == other.unit_price);
}

void BusinessOperation::addQuantity(int q)
{
	quantity += q;
}
