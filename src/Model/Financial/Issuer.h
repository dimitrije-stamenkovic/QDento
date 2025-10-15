#pragma once
#include <string>
#include <variant>
#include <optional>

struct Company;
struct Dentist;

struct Issuer
{
private:
	Issuer(const Company& user);

public:
	//default construction with current user
	Issuer(); 

	std::string company_name;
	std::string address;
	int vat;

	std::string identifier;
	std::string bank;
	std::string iban;
	std::string bic;



};