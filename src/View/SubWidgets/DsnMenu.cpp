#include "DsnMenu.h"
#include "Presenter/VisitPresenter.h"
#include "View/Theme.h"

using namespace Dental;

DsnMenu::DsnMenu()
{

    setStyleSheet(Theme::getPopupMenuStylesheet());

    for (int i = 0; i < Dental::StatusCount; i++)
    {
        if (
            i == static_cast<int>(Dental::Bridge) ||
            i == static_cast<int>(Dental::Splint) ||
            i == static_cast<int>(Dental::Implant) ||
            i == static_cast<int>(Dental::Denture) ||
            i == static_cast<int>(Dental::HasSupernumeral)
        )
        {
            continue;
        }

        menuAction[i] = new QAction(Dental::statusNames[i].data());

        connect(menuAction[i], &QAction::triggered, [this, i]() { this->presenter->setToothStatus(StatusType::General, i, true); });
    }

    addAction(menuAction[Dental::Healthy]);
    addAction(menuAction[Dental::Temporary]);

    QMenu* obturMenu = addMenu(tr("Restoration"));
    QMenu* defObturMenu = addMenu(tr("Defect Restoration"));
    QMenu* cariesMenu = addMenu(tr("Caries"));
    QMenu* nonCariesMenu = addMenu(tr("Non-Caries Lesion"));
    QMenu* mobilityMenu = addMenu(tr("Mobility"));

    QString surfName[SurfaceCount] = { tr("Occlusal"), tr("Medial"), tr("Distal"), tr("Vestibular"), tr("Lingual"), tr("Cervical") };

    for (int i = 0; i < SurfaceCount; i++)
    {
        surfObt[i] = obturMenu->addAction(surfName[i]);
        connect(surfObt[i], &QAction::triggered, [this, i]() {this->presenter->setToothStatus(StatusType::Restoration, i, true); });

        surfDefObt[i] = defObturMenu->addAction(surfName[i]);
        connect(surfDefObt[i], &QAction::triggered, [this, i]() {this->presenter->setToothStatus(StatusType::DefectiveRestoration, i, true); });

        surfCar[i] = cariesMenu->addAction(surfName[i]);
        connect(surfCar[i], &QAction::triggered, [this, i]() {this->presenter->setToothStatus(StatusType::Caries, i, true); });

        surfNonCar[i] = nonCariesMenu->addAction(surfName[i]);
        connect(surfNonCar[i], &QAction::triggered, [this, i]() {this->presenter->setToothStatus(StatusType::NonCariesLesion, i, true); });
    }

    for (int i = 0; i < MobilityCount; i++)
    {
        mobilityDegree[i] = mobilityMenu->addAction(mobilityNames[i].data());
        connect(mobilityDegree[i], &QAction::triggered, [this, i]() {
            this->presenter->setToothStatus(StatusType::Mobility, i, true); });

    }

    addSeparator();
   
    addAction(menuAction[Dental::Pulpitis]);
    addAction(menuAction[Dental::ApicalLesion]);
    addAction(menuAction[Dental::Necrosis]);
    addAction(menuAction[Dental::Resorption]);
    addAction(menuAction[Dental::RootCanal]);
    addAction(menuAction[Dental::Post]);
    addAction(menuAction[Dental::Missing]);
    addAction(menuAction[Dental::Root]);
    addAction(menuAction[Dental::Fracture]);
    addAction(menuAction[Dental::Impacted]);
    addAction(menuAction[Dental::Periodontitis]);
    addAction(menuAction[Dental::Calculus]);
    addAction(menuAction[Dental::Crown]);
    
    auto removeDsn = addAction(tr("Remove"));
    connect(removeDsn, &QAction::triggered, [this]() {this->presenter->setOther(OtherInputs::removeDsn); });

}

void DsnMenu::setModel(const CheckModel& checkModel)
{
    this->setModel(checkModel.generalStatus, menuAction);
    this->setModel(checkModel.restorationStatus, surfObt);
    this->setModel(checkModel.cariesStatus, surfCar);
    this->setModel(checkModel.mobilityStatus, mobilityDegree);
    this->setModel(checkModel.nonCariesStatus, surfNonCar);
    this->setModel(checkModel.defRestoStatus, surfDefObt);
}