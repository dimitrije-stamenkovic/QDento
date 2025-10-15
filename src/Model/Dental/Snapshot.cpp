#include "Snapshot.h"
#include "Model/Dental/Procedure.h"

Snapshot::Snapshot(const Procedure& p, const ToothContainer& t) :
	date(p.date),
	procedure_name(p.name),
	procedure_diagnosis(p.diagnosis),
	procedure_note(p.notes),
	teeth(t)
{ 
	auto teethPtr = p.applyProcedure(teeth);

	affected_teeth.reserve(teethPtr.size());

	for (auto& tooth : teethPtr) {
		affected_teeth.push_back(tooth->index());
	}
}

Snapshot::Snapshot(const ToothContainer& t, Date& date) :
	date(date),
	procedure_name(QObject::tr("Initial oral status").toStdString()),
	teeth(t)
{

}
