#pragma once
#include "CommonValidators.h"

class IbanValidator : public Validator
{
public:
	bool validateInput(const std::string& text) override;
};

class BICValidator : public Validator
{
public:
	bool validateInput(const std::string& text) override;
};