#include "DbInvoice.h"
#include "Database/Database.h"
#include "Model/User.h"
#include "Model/Parser.h"

long long DbInvoice::insertInvoice(const Invoice& invoice)
{ 
    Db db;

    db.newStatement(
        "INSERT INTO financial (num, type, date, data,"
        "recipient_id, recipient_name, recipient_address, recipient_phone) "
        "VALUES (?,?,?,?,?,?,?,?)"
    );

    db.bind(1, invoice.number);
    db.bind(2, static_cast<int>(invoice.type));
    db.bind(3, invoice.date.to8601());
    db.bind(4, Parser::write(invoice));
    db.bind(5, invoice.recipient.identifier);
    db.bind(6, invoice.recipient.name);
    db.bind(7, invoice.recipient.address);
    db.bind(8, invoice.recipient.phone);

    db.execute();

    return db.lastInsertedRowID();
}

void DbInvoice::updateInvoice(const Invoice& invoice)
{
    Db db(
            "UPDATE financial SET "
            "num=?,"
            "type=?,"
            "date=?,"
            "data=?,"
            "recipient_id=?,"
            "recipient_name=?,"
            "recipient_phone=?,"
            "recipient_address=? "
            "WHERE rowid=?"
    );

    db.bind(1, invoice.number);
    db.bind(2, static_cast<int>(invoice.type));
    db.bind(3, invoice.date.to8601());
    db.bind(4, Parser::write(invoice));
    db.bind(5, invoice.recipient.identifier);
    db.bind(6, invoice.recipient.name);
    db.bind(7, invoice.recipient.phone);
    db.bind(8, invoice.recipient.address);
    db.bind(9, invoice.rowId);

    db.execute();
}


bool DbInvoice::invoiceAlreadyExists(long long number, long long rowid)
{
    std::string query{
        "SELECT num FROM financial WHERE "
        "num =" + std::to_string(number) + " "
        "AND rowid !=" + std::to_string(rowid)
    };

    for (Db db(query); db.hasRows();)
    {
        return true;
    }

    return false;

}

std::optional<Date> DbInvoice::getMainDocDate(long long invoiceNumber, const std::string& recipient_id)
{
    std::string query{
        "SELECT date FROM financial WHERE "
        "num = " + std::to_string(invoiceNumber) + " "
        "AND type = 0 "
        "AND recipient_id = '" + recipient_id + "' "
    };

    for (Db db(query); db.hasRows();)
    {
        return Date(db.asString(0));
    }

    return {};
}

std::optional<MainDocument> DbInvoice::getMainDocument(const std::string& recipient_id, long long currentRowid)
{
    std::string query{
    "SELECT num, date FROM financial WHERE "
    "type = 0 "
    "AND recipient_id = '" + recipient_id + "' "
    "AND rowid !="+std::to_string(currentRowid) + " "
    "ORDER BY num DESC LIMIT 1"
    };

    for (Db db(query); db.hasRows();)
    {
        return MainDocument{
            db.asLongLong(0),
            db.asString(1)
        };
    }

    return {};
}

std::optional<Recipient> DbInvoice::getRecipient(const std::string& identifier)
{
    Db db(
        "SELECT recipient_id, recipient_name, recipient_address, recipient_phone"
        "FROM financial WHERE recipient_id = ? "
        "ORDER BY num DESC LIMIT 1"
    );

    db.bind(1, identifier);

    std::optional<Recipient> result;

    while (db.hasRows())
    {
        result.emplace();
        result->identifier = db.asString(0);
        result->name = db.asString(1);
        result->address = db.asString(2);
        result->phone = db.asString(3);
    }

    return result;
}

Invoice DbInvoice::getInvoice(long long rowId)
{
    std::string query = "SELECT num, type, date, data, "
        "recipient_id, recipient_name, recipient_phone, recipient_address "
        "FROM financial "
        "WHERE rowid = " + std::to_string(rowId);

    Db db(query);

    while (db.hasRows()) {

        long long invNumber = db.asLongLong(0);
        FinancialDocType type = static_cast<FinancialDocType>(db.asInt(1));
        Date invDate = db.asString(2);

        Invoice inv;

        inv.rowId = rowId;
        inv.number = invNumber;
        inv.date = invDate;
        inv.type = type;

        Parser::parse(db.asString(3), inv);
        inv.recipient.identifier = db.asString(4);
        inv.recipient.name = db.asString(5);
        inv.recipient.phone = db.asString(6);
        inv.recipient.address = db.asString(7);

        return inv;
    }

    return Invoice();
}

long long DbInvoice::getNewInvoiceNumber()
{
    long long number = 0;

    Db db(
        "SELECT num FROM financial "
        "ORDER BY rowid DESC, num DESC LIMIT 1"
    );

    while (db.hasRows()) number = db.asLongLong(0);

    return number + 1;
}

std::unordered_set<int> DbInvoice::getExistingNumbers()
{
    std::unordered_set<int> result;

    Db db("SELECT num FROM financial");

    while (db.hasRows()) {
        result.insert(db.asInt(0));
    }

    return result;
}
