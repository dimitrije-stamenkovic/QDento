#pragma once

#include <unordered_set>
#include <vector>
#include "Model/Dental/DentalVisit.h"

namespace DbDentalVisit
{
    DentalVisit getNewDoc(long long patientRowId);
    DentalVisit get(long long rowid);

    long long insert(const DentalVisit& v, long long patientRowId); //returns the rowId of the new instered row
    void remove(long long rowid);
    void update(const DentalVisit& v);

    int getNewNumber(Date date);
};

