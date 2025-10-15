#include "ProcedureDialogPresenter.h"

#include "View/ModalDialogBuilder.h"

#include "View/Widgets/ProcedureDialog.h"
#include "Model/Date.h"
#include "Model/Dental/DentalVisit.h"
#include "Model/User.h"

ProcedureDialogPresenter::ProcedureDialogPresenter
(
	const DentalVisit& ambSheet,
	const std::vector<const Tooth*>& selectedTeeth
)
	:
    selectedTeeth(selectedTeeth),
	dental_visit(ambSheet),
    procedure_creator(selectedTeeth),
    view(nullptr)
{}

void ProcedureDialogPresenter::setView(ProcedureDialog* view)
{
	this->view = view;

	procedure_creator.setView(view->procedureInput());

	view->procedureList()->setPresenter(&list_presenter);
	
	//setting the label
	std::vector<int> selectedTeethNum;
	selectedTeethNum.reserve(32);

	for (const Tooth* t : selectedTeeth)
		selectedTeethNum.emplace_back(ToothUtils::getToothNumber(t->index(), t->hasStatus(Dental::Temporary)));

	view->setSelectionLabel(selectedTeethNum);

	setCode(-1);
}

void ProcedureDialogPresenter::setCode(int idx)
{
	if (idx == -1) {
		procedure_creator.setProcedure(ProcedureListElement());
		return;
	}

	procedure_creator.setProcedure(list_presenter.getList()[idx]);
}

void ProcedureDialogPresenter::formAccepted()
{

	result = procedure_creator.getProcedures();

	if (result.empty()) return;

	view->close();
}

std::vector<Procedure> ProcedureDialogPresenter::openDialog()
{
	ProcedureDialog d(*this);
	d.exec();
	return result;
}

ProcedureDialogPresenter::~ProcedureDialogPresenter()
{
}
