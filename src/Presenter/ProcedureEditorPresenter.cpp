#include "ProcedureEditorPresenter.h"

#include "Model/Dental/Procedure.h"
#include "Model/User.h"
#include "View/ModalDialogBuilder.h"
#include "View/SubWidgets/ProcedureInput.h"
#include "View/Widgets/ProcedureEditDialog.h"

ProcedureEditorPresenter::ProcedureEditorPresenter(const Procedure& p)
	:
	view(nullptr)
{

	result.emplace(Procedure());
	
	//parameters not set to view
	code = p.code;
	name = p.name;
	type = p.type;
	m_tooth_index = p.getToothIndex();

	//parameters which are set to view
	result->diagnosis = p.diagnosis;
	result->param = p.param;
	result->notes = p.notes;
	result->affectedTeeth = p.affectedTeeth;
	result->price = p.price;
}

std::optional<Procedure> ProcedureEditorPresenter::openDialog()
{
	ProcedureEditDialog d(*this);

	d.exec();

	return result;
}

void ProcedureEditorPresenter::setView(ProcedureEditDialog* view)
{
	this->view = view;

	ProcedureInput::CommonData data;

	data.diagnosis = result->diagnosis;

	data.notes = result->notes;

	auto inputView = view->procedureInput();

	inputView->setCommonData(
		ProcedureInput::CommonData{
			result->diagnosis,
			result->notes,
			result->price
	});

	switch (result->getScope(type)) {

	case Procedure::Scope::AllOrNone:
		inputView->setParameterData();
		break;

	case Procedure::Scope::SingleTooth:
		{
		std::holds_alternative<RestorationData>(result->param) ?
			inputView->setParameterData(
				result->getToothIndex().supernumeral,
				std::get<RestorationData>(result->param)
			)
			:
			inputView->setParameterData(result->getToothIndex().supernumeral);
		}
		break;

		case Procedure::Scope::Range:
		{
			bool allowSingleRange =
				type == Procedure::Type::RemoveCrownOrBridge
				|| type == Procedure::Type::Denture;

			inputView->setParameterData(
				std::get<ConstructionRange>(result->affectedTeeth),
                allowSingleRange
			);
		}
	}

	result.reset();
}

void ProcedureEditorPresenter::okPressed()
{
	auto validationResult = view->procedureInput()->isValid();

	if (validationResult.size()) {
		ModalDialogBuilder::showMessage(validationResult);
		return;
	}

	auto data = view->procedureInput()->getResult();

	//procedure creator:
	result.emplace(Procedure{});

	result->code = code;
	result->name = name;
	result->type = type;
	result->notes = data.notes;
	result->diagnosis = data.diagnosis;
	result->dentist_rowid = User::dentist().rowID;
	result->price = data.price;

	//range
	if (std::holds_alternative<ConstructionRange>(data.parameters)) {
		result->affectedTeeth = std::get<ConstructionRange>(data.parameters);
	}

	//restoration
	else if (std::holds_alternative<std::pair<bool, RestorationData>>(data.parameters)) {

		auto pair = std::get<std::pair<bool, RestorationData >>(data.parameters);
		result->param = pair.second;
		m_tooth_index.supernumeral = pair.first;
		result->affectedTeeth = m_tooth_index;
	}
	//tooth specific
	else if (std::holds_alternative<bool>(data.parameters)) {
		m_tooth_index.supernumeral = std::get<bool>(data.parameters);
		result->affectedTeeth = m_tooth_index;
	}

	view->close();
}

