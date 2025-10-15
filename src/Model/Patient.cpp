#include "Patient.h"

int Patient::getAge(const Date& currentDate) const
{
	int age = currentDate.year - birth.year;

	if ((currentDate.month == birth.month && currentDate.day < birth.day)  || 
		birth.month > currentDate.month) 
		age--;

	return std::max(-1, age);
}

std::string Patient::firstLastName() const
{
	std::string fullName = firstName;

	if (lastName.size() && firstName.size()) {
		fullName += " ";
	}

	fullName += lastName;

	return fullName;
}

Patient::~Patient()
{

}
