#include "ProcedureCreator.h"
#include <set>
#include "Model/User.h"
#include "View/ModalDialogBuilder.h"
#include "View/SubWidgets/ProcedureInput.h"
#include <QObject>

ProcedureCreator::ProcedureCreator(const std::vector<const Tooth*>& selectedTeeth)
	: m_selectedTeeth(selectedTeeth)
{
	auto tooth = m_selectedTeeth.size() ? m_selectedTeeth.at(0) : nullptr;

	for (auto i = 0; i < static_cast<int>(Procedure::Type::MaxCount); i++) {

		diag_map[Procedure::Type(i)] = getDiagnosis(tooth, Procedure::Type(i));
	}
}

void ProcedureCreator::setProcedure(const ProcedureListElement& e)
{
	this->current_element = e;

	if (e.name.empty()) {
		view->setErrorMsg(QObject::tr("Select a procedure").toStdString());
		return;
	}

	auto scope = Procedure::getScope(e.type);

	if (scope == Procedure::Scope::SingleTooth && m_selectedTeeth.empty()) 
	{
		view->setErrorMsg(QObject::tr("To add this procedure you must select at least one tooth").toStdString());
		return;
	}

	//setting common data
	ProcedureInput::CommonData commonData;

	commonData.diagnosis = e.diagnosis.size() ? e.diagnosis : diag_map[e.type];

	commonData.price = e.price;

	//setting parameter data

	if (Procedure::getScope(e.type) == Procedure::Scope::AllOrNone) {
		view->setParameterData();
	}
	else if (e.type == Procedure::Type::Restoration) {
		view->setParameterData(false, autoSurfaces(*m_selectedTeeth[0]));
	}
	else if (e.type == Procedure::Type::RemoveRestoration) {

		auto rData = autoSurfaces(*m_selectedTeeth[0]);

		if (m_selectedTeeth.at(0)->hasStatus(Dental::Post)) {
			rData.post = true;
		}

		view->setParameterData(false, autoSurfaces(*m_selectedTeeth[0]));

	}
	else if (Procedure::getScope(e.type) == Procedure::Scope::SingleTooth) {
		view->setParameterData(false);
	}
	else if (Procedure::getScope(e.type) == Procedure::Scope::Range) {

		bool allowSingleRange =
			e.type == Procedure::Type::RemoveCrownOrBridge
			|| e.type == Procedure::Type::Denture;

		view->setParameterData(autoRange(m_selectedTeeth, e.type), allowSingleRange);
	}
	else if (e.type == Procedure::Type::Crown) {
		view->setParameterData(false, autoRange(m_selectedTeeth, e.type), true);
	}

    view->setCommonData(commonData);
}

std::vector<Procedure> ProcedureCreator::getProcedures()
{
	std::vector<Procedure> result;

	if (current_element.code.empty()) return result;

	auto err = view->isValid();

	if (err.size()) {
		ModalDialogBuilder::showMessage(err);
		return {};
	}

	Procedure procedure;

	procedure.code = current_element.code;
	procedure.name = current_element.name;
	procedure.price = current_element.price;
	procedure.type = current_element.type;

	auto data = view->getResult();

	procedure.dentist_rowid = User::dentist().rowID;
	procedure.diagnosis = data.diagnosis;
	procedure.notes = data.notes;
	procedure.price = data.price;
	bool supernumeral = false;

	//range
	if (std::holds_alternative<ConstructionRange>(data.parameters)) {
		procedure.affectedTeeth = std::get<ConstructionRange>(data.parameters);
		return { procedure };
	}

	if (Procedure::getScope(current_element.type) == Procedure::Scope::AllOrNone) {
		return { procedure };
	}


	//restoration
	if (std::holds_alternative<std::pair<bool, RestorationData>>(data.parameters)) {
		
		auto& pair = std::get<std::pair<bool, RestorationData>>(data.parameters);
		supernumeral = pair.first;
		procedure.param = pair.second;
	}
	//tooth specific
	else if (std::holds_alternative<bool>(data.parameters)) {
		supernumeral = std::get<bool>(data.parameters);

	}
	
	//return separate procedures
	for (auto t : m_selectedTeeth)
	{
		auto index = t->toothIndex();
		index.supernumeral = supernumeral;
		procedure.affectedTeeth = index;
		result.push_back(procedure);
	}

	return result;
}

std::string ProcedureCreator::getDiagnosis(const Tooth* tooth, Procedure::Type type)
{
	using namespace Dental;
	std::array<std::string, Status::StatusCount> icdSimple{};
	
	icdSimple[Caries] = QObject::tr("Caries").toStdString();
	icdSimple[NonCariesLesion] = tooth && tooth->hasStatus(NonCariesLesion, 0) ? QObject::tr("Tooth erosion").toStdString() : QObject::tr("Tooth abrasion").toStdString();
	icdSimple[Pulpitis] = QObject::tr("Pulpitis").toStdString();
	icdSimple[ApicalLesion] = QObject::tr("Chronic apical periodontitis").toStdString();
	icdSimple[Necrosis] = QObject::tr("Necrosis of pulp").toStdString();
	icdSimple[DefectiveRestoration] = QObject::tr("Defective restoration").toStdString();
	icdSimple[Periodontitis] = QObject::tr("Periodontitis").toStdString();
	icdSimple[Resorption] = QObject::tr("Pathological resorption").toStdString();
	icdSimple[Fracture] = QObject::tr("Tooth fracture").toStdString();
	icdSimple[Root] = QObject::tr("Retained dental root").toStdString();
	icdSimple[Mobility] = QObject::tr("Dislocation of a tooth").toStdString();
	icdSimple[Temporary] = QObject::tr("Exfoliation").toStdString();
	icdSimple[Impacted] = QObject::tr("Impacted tooth").toStdString();
	icdSimple[Denture] = QObject::tr("Presence of dental prosthetic device").toStdString();
	icdSimple[Missing] = QObject::tr("Loss of teeth due to accident, extraction or local periodontal disease").toStdString();
	icdSimple[HasSupernumeral] = QObject::tr("Supernumerary tooth").toStdString();
	icdSimple[Calculus] = QObject::tr("Deposits on teeth").toStdString();
	icdSimple[RootCanal] = "";

	std::vector<Status> statusSearch;

	std::string icd;
	std::string description;

	switch (type)
	{
	case Procedure::Type::General:
	case Procedure::Type::Post:
	case Procedure::Type::ToothNonSpecific:
		break;
	case Procedure::Type::Depuratio:
	case Procedure::Type::DepuratioTooth: 
		icd = icdSimple[Calculus];
		statusSearch = {Periodontitis, Calculus, Mobility };
		break;
	case Procedure::Type::DenturePair:
	case Procedure::Type::Denture:
	case Procedure::Type::Implant:
	case Procedure::Type::Bridge:	icd = icdSimple[Missing];
		break;

	case Procedure::Type::Restoration:
		icd = "";
		statusSearch = { Fracture, Caries, NonCariesLesion, DefectiveRestoration, Necrosis, Pulpitis, ApicalLesion, Root };
		break;
	case Procedure::Type::RemoveRestoration:
		statusSearch = { Pulpitis, ApicalLesion, Fracture, Caries, Periodontitis };
		break;
	case Procedure::Type::Extraction:

		icdSimple[Implant] = QObject::tr("Infection and inflammatory reaction due to implants").toStdString();

        if (tooth && tooth->hasStatus(Root) && tooth->hasStatus(Impacted)) {
			icdSimple[Root] = QObject::tr("Retained dental root").toStdString();
			icdSimple[Impacted] = QObject::tr("Impacted tooth").toStdString();
		}

		icd = QObject::tr("Anomalies of tooth position").toStdString(); //assume ortho reason
        statusSearch = { Implant, Impacted, HasSupernumeral, ApicalLesion, Root, Periodontitis, Mobility, Fracture, Pulpitis, Necrosis, Resorption, Temporary, Caries };
		break;

	case Procedure::Type::Endodontic:
		statusSearch = { Pulpitis, ApicalLesion, Necrosis, Resorption, Root, Fracture, Periodontitis, RootCanal };
		break;

	case Procedure::Type::RemovePost:
		statusSearch = { ApicalLesion, Root, Fracture, RootCanal };
		break;

	case Procedure::Type::PostCore:
		statusSearch = { Root, Fracture };
		break;

	case Procedure::Type::PostCrown:
		statusSearch = { ApicalLesion, Root, Fracture, RootCanal };
		break;
		
	case Procedure::Type::Crown:
		icd = "";
		icdSimple[Implant] = QObject::tr("Presence of tooth-root and mandibular implants").toStdString();
		statusSearch = {Implant, Fracture, RootCanal};
		break;
	case Procedure::Type::RemoveCrownOrBridge:
		statusSearch = { Pulpitis, ApicalLesion, Root, Fracture, Periodontitis, RootCanal };
		break;

	case Procedure::Type::MultipleExtraction:
		break;
	}

	for (auto s : statusSearch) {

		if (tooth == nullptr) break;

		if (tooth->hasStatus(s)) {
			
			icd = icdSimple[s];
/*
			if (s == RootCanal) {
				description = "K04.99";
			}
*/
			break;
		}
	}

	return icd;
}

RestorationData ProcedureCreator::autoSurfaces(const Tooth& tooth)
{
	using namespace Dental;

	RestorationData result;

	auto& surfaces = result.surfaces;

	for (int i = 0; i < 6; i++)
	{
		surfaces[i] = tooth.hasStatus(Caries, i) || tooth.hasStatus(DefectiveRestoration, i) || tooth.hasStatus(NonCariesLesion, i);
	}

	if (tooth[Root])
	{
		surfaces = { 1, 1, 1, 1, 1, 1 };

		if (!tooth[Post]) {
			result.post = true;
		}
	}

	if (tooth[RootCanal])
	{
		if (tooth.type() == Frontal)
		{
			surfaces[Surface::Lingual] = true;
		}
		else surfaces[Surface::Occlusal] = true;
	}

	if (tooth[Fracture])
	{
		if (tooth.type() == Frontal)
		{
			surfaces[Surface::Occlusal] = true;
		}
		else surfaces[Surface::Lingual] = true;
	}
	else if (tooth[Restoration] && !tooth[Caries])
	{
		for (int i = 0; i < 6; i++)
		{
			if (tooth.hasStatus(Restoration, i))
				surfaces[i] = true;
		}
	}

	return result;
}

ConstructionRange ProcedureCreator::autoRange(const std::vector<const Tooth*> selectedTeeth, Procedure::Type type)
{

	if (!selectedTeeth.size()) {

		if (type == Procedure::Type::Denture) {
			return ConstructionRange{ 1, 14 };
		}

		return { 0, 1 };
	}

	if (selectedTeeth.size() == 1)
	{
		return { selectedTeeth[0]->index(), selectedTeeth[0]->index() };
	}

	int begin = selectedTeeth[0]->index(); //if multiple teeth are selected, the range is calculated to be valid
	int end = selectedTeeth.back()->index(); //doesn't matter if the first and last teeth are on different jaws

	if (begin < 16 && end > 15) { end = 15; }

	return { begin, end };
}


void ProcedureCreator::setView(ProcedureInput* view)
{
	this->view = view;
}

void ProcedureCreator::diagnosisChanged(int idx)
{
	//diag_map[m_code.type()] = idx;
}
