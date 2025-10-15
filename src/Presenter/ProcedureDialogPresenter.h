#pragma once

#include "Model/Dental/ToothUtils.h"
#include "ProcedureCreator.h"
#include "Presenter/ProcedureListPresenter.h"

struct DentalVisit;
class ProcedureDialog;

class ProcedureDialogPresenter
{
	std::vector<const Tooth*> selectedTeeth;

	const DentalVisit& dental_visit;

	ProcedureCreator procedure_creator;
	ProcedureListPresenter list_presenter;
	ProcedureDialog* view;

	std::vector<Procedure> result;

public:

	ProcedureDialogPresenter
	(
		const DentalVisit& ambSheet,
		const std::vector<const Tooth*>& selectedTeeth
	);

	void setView(ProcedureDialog* view);
	void setCode(int idx);
	void formAccepted();
	void favClicked(int idx) { list_presenter.favClicked(idx); }
	std::vector<Procedure> openDialog();

	~ProcedureDialogPresenter();

};