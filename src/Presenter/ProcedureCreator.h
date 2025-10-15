#pragma once

#include <map>
#include <vector>

#include "Model/Dental/Procedure.h"
#include "Model/Dental/ProcedureListElement.h"
#include "Model/Dental/Tooth.h"
#include "Model/Validators/CommonValidators.h"

class ProcedureInput;

class ProcedureCreator
{

	ProcedureInput* view{ nullptr };

	ProcedureListElement current_element;

	std::map<Procedure::Type, std::string> diag_map;

	const std::vector<const Tooth*> m_selectedTeeth;

	NotEmptyValidator notEmpty_validator;
	std::string getDiagnosis(const Tooth* tooth, Procedure::Type type);
	RestorationData autoSurfaces(const Tooth& tooth);
	ConstructionRange autoRange(const std::vector<const Tooth*> m_selectedTeeth, Procedure::Type type);	

public:
	ProcedureCreator(const std::vector<const Tooth*>& selectedTeeth);

	void setView(ProcedureInput* view);

	void diagnosisChanged(int idx);

	void setProcedure(const ProcedureListElement& e);

	std::vector<Procedure> getProcedures();
	
};

