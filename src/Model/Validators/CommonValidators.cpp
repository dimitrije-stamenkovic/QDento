#include "CommonValidators.h"

const std::string NotEmptyValidator::couldntBeEmpty{ "The field is mandatory" };

NotEmptyValidator::NotEmptyValidator()
{
    _errorMsg = &couldntBeEmpty;
}

bool NotEmptyValidator::validateInput(const std::string& text)
{
    return text.size() > 0;
}

const std::string mustBeNumber{ "The field should contain only digits" };

bool DigitsOnlyValidator::validateInput(const std::string& text)
{
    _errorMsg = &mustBeNumber;

    for (char c : text)
    {
        if (!std::isdigit(static_cast<unsigned char>(c)))
        {
            return false;
        }
    }

    return true;
}
