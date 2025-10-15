#include "User.h"

#include "Database/DbDentist.h"
#include <unordered_map>

static Dentist s_doctor;
static Company s_company;

std::unordered_map<long long, std::string> s_names;

void User::loadDentistList()
{
    s_names.clear();

    for (auto &d : DbDentist::getList())
    {
        s_names.insert({ d.rowID, d.getFullName() });
    }
}

bool User::isValid()
{
    return s_doctor.rowID != 0;
}

const Dentist& User::dentist()
{
    return s_doctor;
}

const Company& User::company()
{
    return s_company;
}

void User::setCurrentDentist(const Dentist& dentist)
{
    s_doctor = dentist;
}

void User::setCurrentCompany(const Company& company)
{
    s_company = company;
}

void User::resetUser()
{
    s_doctor = Dentist();
}

bool User::isCurrentUser(long long rowid)
{
    return rowid == s_doctor.rowID;
}

std::string User::getNameFromRowid(long long rowid)
{
    if (s_names.count(rowid)) return s_names[rowid];

    return "???";
}
