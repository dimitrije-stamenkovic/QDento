#pragma once
#include "Model/UserStructs.h"
#include "Model/Validators/CommonValidators.h"
#include <optional>

class DoctorSettingsDialog;

class DentistDialogPresenter
{
	DoctorSettingsDialog* view{nullptr};

	long long current_rowid{ 0 };

	std::optional<Dentist> result;

	NotEmptyValidator not_emptyValidator;

public:
	DentistDialogPresenter();
	DentistDialogPresenter(const Dentist& dentist);

	void okPressed();

	void setView(DoctorSettingsDialog* view);

	std::optional<Dentist> open();
};

