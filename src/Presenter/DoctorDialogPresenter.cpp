#include "DoctorDialogPresenter.h"
#include "View/Widgets/DoctorSettingsDialog.h"
#include "Database/DbDentist.h"
#include "View/ModalDialogBuilder.h"

DentistDialogPresenter::DentistDialogPresenter() {}

DentistDialogPresenter::DentistDialogPresenter(const Dentist& dentist) :
    current_rowid(dentist.rowID),
    result(dentist)
{}

void DentistDialogPresenter::okPressed()
{
    auto dentist = view->get();

    dentist.rowID = current_rowid;

    if (current_rowid){
        DbDentist::update(dentist);
    }
    else{
        DbDentist::insert(dentist);
        
    }

    result.emplace(dentist);

    view->close();
}

void DentistDialogPresenter::setView(DoctorSettingsDialog* view)
{
    this->view = view;

    if (result.has_value()) {
        view->setDoctor(result.value());
        result.reset();
    }
        
}

std::optional<Dentist> DentistDialogPresenter::open()
{
    DoctorSettingsDialog d(*this);
    d.exec();
    
    return result;
}
