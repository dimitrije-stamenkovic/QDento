#pragma once
#include "Model/Date.h"
#include "Model/Dental/ToothIndex.h"

struct DetailsSummary
{
    Date date;
    std::string procedureDiagnosis;
    std::string procedureName;
    int tooth;
    int code;
    double price{ 0 };
    std::string LPK;
};
