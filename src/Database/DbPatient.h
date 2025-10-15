#pragma once

#include "Model/Patient.h"
#include <queue>

class Db;

namespace DbPatient
{
    struct PatientRecord {
        std::string summary;
        std::string fname;
        std::string birth;
        std::string color;
        long long rowid;
    };

    long long insert(const Patient& patient);
    bool update(const Patient& patient);
    Patient get(const std::string& patientID);
    Patient get(long long rowid);

    long long getPatientRowid(const std::string& firstName, const std::string& birth);
    long long getPatientRowid(const std::string& id);
    std::vector<PatientRecord> getPatientList();

    TeethNotes getToothNotes(long long patientRowId);
};

