#pragma once

#include <optional>
#include "Model/Financial/Recipient.h"
#include "Model/Validators/CommonValidators.h"

class RecipientEditView;

class RecipientPresenter
{

	RecipientEditView* view{ nullptr };

	std::optional<Recipient> result;

	NotEmptyValidator notEmpty_validator;

public:

	RecipientPresenter();
	RecipientPresenter(const Recipient& recipient);

	void idValidInput();

	void setRecipientEditView(RecipientEditView* view);

	void okPressed();

	std::optional<Recipient> openDialog();
};