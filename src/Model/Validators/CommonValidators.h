#pragma once
#include "AbstractValidator.h"

class NotEmptyValidator : public Validator
{
	static const std::string couldntBeEmpty;

public:
	NotEmptyValidator();
	bool validateInput(const std::string& text) override;
};

class DigitsOnlyValidator : public Validator
{

public:
	bool validateInput(const std::string& text) override;
};

template<int minimum>
class MinimumLengthValidator : public Validator
{

	inline static const std::string mustBeAtLeast = 
		"The field should contain at least " + std::to_string(minimum) + " symbols";
public:
	bool validateInput(const std::string& text) override
	{
		_errorMsg = &mustBeAtLeast;

		return (text.length() >= minimum);
	};
};

template<int exact>
class ExactLengthValidator : public Validator
{
	inline static const std::string mustBeExactly =
		"The field should contain exactly " + std::to_string(exact) + " symbols";

public:
	bool validateInput(const std::string& text) override
	{
		_errorMsg = &mustBeExactly;

		return (text.length() == exact);
	};
};