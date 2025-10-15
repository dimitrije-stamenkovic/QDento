#pragma once

#include <string>
#include <vector>
#include <optional>
#include "Model/UserStructs.h"

struct PerioStatus;
class ToothContainer;
struct Procedure;
struct DetailsSummary;
struct Invoice;
struct NhifData;
struct HISProcedureResult;

namespace Parser
{
	std::string write(const PerioStatus& status);
	std::string write(const ToothContainer& status);
	std::string write(const Invoice& inv);
	std::string write(const ToothContainer& status);

	void parse(const std::string& jsonString, DetailsSummary& summary);
	void parse(const std::string& jsonString, PerioStatus& status);
	void parse(const std::string& jsonString, ToothContainer& status);
	void parse(const std::string& jsonString, Invoice& invoice);

	std::string parseDiagnosis(const std::string& jsonProcedureString);

};