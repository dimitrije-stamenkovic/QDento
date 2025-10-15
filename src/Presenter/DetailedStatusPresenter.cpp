#include "DetailedStatusPresenter.h"

#include "Presenter/CheckModel.h"
#include "Database/DbNotes.h"
#include "View/Graphics/PaintHint.h"
#include "View/ModalDialogBuilder.h"
#include "View/Widgets/DetailedStatus.h"

DetailedStatusPresenter::DetailedStatusPresenter(int tooth_index ,long long patientRowId, const std::vector<Procedure>& toothProcedures)
    : view(nullptr),
    m_procedures(toothProcedures),
    patientRowId(patientRowId),
    m_tooth_index(tooth_index)
{
	m_notes = DbNotes::getNote(patientRowId, tooth_index);
}

void DetailedStatusPresenter::setView(DetailedStatus* view)
{
	this->view = view; 

	view->setHistoryData(m_procedures);
	
	view->setNotes(m_notes);

	view->focusNotes(m_notes.size() || m_procedures.empty());

	view->setHistoryData(m_procedures);
}

void DetailedStatusPresenter::okPressed()
{
	m_notes = view->getNotes();

	DbNotes::saveNote(m_notes, patientRowId, m_tooth_index);
}

void DetailedStatusPresenter::open()
{
	DetailedStatus d(*this);
	d.exec();
}


