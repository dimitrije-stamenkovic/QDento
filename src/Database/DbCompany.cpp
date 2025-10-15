#include "DbCompany.h"
#include "Database.h"
#include "Model/Parser.h"

Company DbCompany::getInvoiceData()
{
    std::string query = "SELECT name, identifier, address, vat, currency, bank, iban, bic FROM company";

    Company company;

    Db db;

    db.newStatement(query);

    while (db.hasRows())
    {
        company.name = db.asString(0);
        company.identifier = db.asString(1);
        company.address = db.asString(2);
        company.vat = db.asInt(3);
        company.currency = db.asString(4);
        company.bank = db.asString(5);
        company.iban = db.asString(6);
        company.bic = db.asString(7);

    }

    return company;
}

bool DbCompany::updateInvoiceData(const Company& company)
{

    Db db(
        "UPDATE company SET "
        "name=?,"
        "identifier=?,"
        "address=?,"
        "vat=?,"
        "currency=?,"
        "bank=?, "
        "iban=?, "
        "bic=? "
    );

    db.bind(1, company.name);
    db.bind(2, company.identifier);
    db.bind(3, company.address);
    db.bind(4, company.vat);
    db.bind(5, company.currency);
    db.bind(6, company.bank);
    db.bind(7, company.iban);
    db.bind(8, company.bic);

    return db.execute();

}

bool DbCompany::insertInvoiceData(const Company& company)
{
    Db db(
        "INSERT INTO company "
        "(name, identifier, address, vat, currency, bank, iban, bic) "
        "VALUES(?,?,?,?,?,?,?,?)"
    );

    db.bind(1, company.name);
    db.bind(2, company.identifier);
    db.bind(3, company.address);
    db.bind(4, company.vat);
    db.bind(5, company.currency);
    db.bind(6, company.bank);
    db.bind(7, company.iban);
    db.bind(8, company.bic);

    return db.execute();
}

bool DbCompany::noInvoiceData()
{
    Db db("SELECT COUNT(*) FROM company");

    db.showErrorDialog(true);

    while (db.hasRows()) {
        return !db.asInt(0);
    }

    return true;
}
