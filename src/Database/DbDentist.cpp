#include "DbDentist.h"
#include "Database.h"

std::optional<Dentist> DbDentist::get(long long rowId, const std::string& pass)
{
    std::optional<Dentist> result;

    std::string query =
        "SELECT fname, lname, pass FROM dentist "
        "WHERE rowid = ? "
        "AND (pass = ? OR pass = '')";

    Db db(query);

    db.bind(1, rowId);
    db.bind(2, pass);


    while(db.hasRows())
    {
        Dentist dentist;

        dentist.rowID = rowId;
        dentist.fname = db.asString(0);
        dentist.lname = db.asString(1);
        dentist.pass = db.asString(2);

        result = dentist;
    }

    return result;
}

std::optional<Dentist> DbDentist::get(long long rowid)
{
    std::optional<Dentist> result;

    std::string query =
        "SELECT fname, lname, pass FROM dentist "
        "WHERE rowid = ?";

    Db db(query);

    db.bind(1, rowid);

    while (db.hasRows())
    {
        Dentist dentist;

        dentist.rowID = rowid;
        dentist.fname = db.asString(0);
        dentist.lname = db.asString(1);
        dentist.pass = db.asString(2);

        result = dentist;
    }

    return result;

}

bool DbDentist::removeDentist(long long dentist_rowid)
{
    Db db("DELETE FROM dentist WHERE rowid=?");
    db.bind(1, dentist_rowid);
    return db.execute();
}

long long DbDentist::getDoctorAutoLoginRowid()
{
    Db db("SELECT rowid FROM dentist WHERE auto_login=1");

    while (db.hasRows()) {
        return db.asRowId(0);
    }

    return 0;
}

bool DbDentist::setAutoLogin(long long rowid, bool remember)
{
    std::string query = "UPDATE dentist SET auto_login=? WHERE rowid=?";

    Db db(query);
    db.bind(1, remember);
    db.bind(2, rowid);

    return db.execute();
}

bool DbDentist::update(const Dentist& dentist)
{
   Db db;

   db.newStatement(
       "UPDATE dentist SET "
       "fname=?,"
       "lname=?,"
       "pass=? "
       "WHERE rowid=?"
   );

   db.bind(1, dentist.fname);
   db.bind(2, dentist.lname);
   db.bind(3, dentist.pass);
   db.bind(4, dentist.rowID);

   if(!db.execute()) return false;

   return true;
}

long long DbDentist::insert(const Dentist& dentist)
{
    Db db(
        "INSERT INTO dentist (fname, lname, pass) "
        "VALUES(?,?,?)"
    );

    db.bind(1, dentist.fname);
    db.bind(2, dentist.lname);
    db.bind(3, dentist.pass);

    if (db.execute()) {
        return db.lastInsertedRowID();
    };

    return 0;
}

std::vector<Dentist> DbDentist::getList()
{
    std::vector<Dentist> result;

    std::string query = "SELECT rowid, fname, lname, pass FROM dentist";

    for (Db db(query); db.hasRows();)
    {
        result.push_back(Dentist{
            .rowID = db.asRowId(0),
            .fname = db.asString(1),
            .lname = db.asString(2),
            .pass = db.asString(3)
        });
    }

    return result;
}

bool DbDentist::updateFavouriteProcedures(const std::vector<std::string>& procedureCodes, long long dentist_rowid)
{
    Db db;
    db.newStatement("DELETE FROM favourite_code WHERE dentist_rowid=?");
    db.bind(1, dentist_rowid);
    db.execute();

    for (auto& code : procedureCodes) {
        db.newStatement("INSERT INTO favourite_code (procedure_code, dentist_rowid) VALUES (?,?)");
        db.bind(1, code);
        db.bind(2, dentist_rowid);

        if (!db.execute()) {
            return false;
        }
    }

    return true;
}

std::set<std::string> DbDentist::getFavouriteProcedures(long long dentistRowid)
{
    Db db;

    db.newStatement("SELECT procedure_code FROM favourite_code WHERE dentist_rowid=?");

    db.bind(1, dentistRowid);

    std::set<std::string> result;

    while (db.hasRows()) {
        result.insert(db.asString(0));
    }

    return result;
}
