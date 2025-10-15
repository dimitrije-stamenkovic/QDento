#pragma once
#include <optional>

#include "Model/Dental/Procedure.h"

class ProcedureEditDialog;

class ProcedureEditorPresenter
{

	//NotEmptyValidator not_emptyValidator;
	ProcedureEditDialog* view;
	std::optional<Procedure> result;

	//not present in the view, so state should be saved:
	std::string name;
	std::string code;
	Procedure::Type type = Procedure::Type::General;
	ToothIndex m_tooth_index;

public:
	ProcedureEditorPresenter(const Procedure& p);
	std::optional<Procedure> openDialog();
	void setView(ProcedureEditDialog* view);
	void okPressed();
};

