#include "DbDiagnosis.h"
#include "Database/Database.h"

std::set<std::string> DbDiagnosis::getDiagnosisList(bool includeProcedureList)
{
    Db db;

    db.newStatement("SELECT description FROM diagnosis");

    std::set<std::string> result;

    while (db.hasRows()) 
    {
        result.insert(db.asString(0));
    }

    if (!includeProcedureList) return result;

    db.newStatement("SELECT diagnosis FROM procedure_list");

    while (db.hasRows()) 
    {
        auto diag = db.asString(0);

        if (!diag.empty()) result.insert(diag);
    }

    return result;
}

void DbDiagnosis::setDiagnosisList(const std::set<std::string>& diagnoses)
{
    Db db;

    db.execute("DELETE FROM diagnosis");

    for (const auto& d : diagnoses) 
    {
        db.newStatement("INSERT INTO diagnosis (description) VALUES (?)");

        db.bind(1, d);

        db.execute();
    }
}