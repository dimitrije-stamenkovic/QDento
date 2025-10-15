#pragma once
#include <string>

struct Patient;
struct Company;

struct Recipient
{
	Recipient() {};

	Recipient(
		const std::string& name,
		const std::string& address,
		const std::string& identifier,
		const std::string& phone
	) : name(name), address(address), identifier(identifier), phone(phone) {}

	//Patient recipient
	Recipient(const Patient& patient);

	std::string name;
	std::string address;
	std::string identifier;
	std::string phone;

};