#pragma once

#include <optional>

#include "Model/Patient.h"

class PatientFormDialog;

struct PatientDialogPresenter
{
	std::optional<Patient> m_patient;

	PatientFormDialog* view;

	std::string dialogTitle;

	//data not present in view:
	long long rowid{ 0 };
	TeethNotes teeth_notes;
	std::string patientNotes;

	Patient getPatientFromView(); //sets the data not present in view

public:
	PatientDialogPresenter(std::string dialogTitle, std::string patientData = "");
	PatientDialogPresenter(const Patient& patient);
	std::optional<Patient> open();

	void searchDbForPatient(const std::string& id);
	void accept();

	void setView(PatientFormDialog* view);
};

