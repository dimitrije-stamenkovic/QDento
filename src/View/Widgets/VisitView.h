#pragma once

#include <QWidget>

#include "ui_VisitView.h"

#include "Presenter/VisitPresenter.h"
#include "View/Graphics/TeethViewScene.h"
#include "View/TableModels/ProcedureTableModel.h"


class VisitView : public QWidget
{
    Q_OBJECT

    VisitPresenter* presenter;

    TeethViewScene* teethViewScene;

    ContextMenu* contextMenu;

    ProcedureTableModel model;

    void paintEvent(QPaintEvent* event) override;
    bool eventFilter(QObject* obj, QEvent* event) override;

    bool m_teethViewFocused {false};

public:
    VisitView(QWidget* parent = Q_NULLPTR);

    void setPresenter(VisitPresenter* presenter);

    void focusTeethView();
    void setDate(const Date& d);
    void setVisitNumber(int num);
    void setCheckModel(const CheckModel& checkModel, const CheckModel& dsnCheckModel);
    void hideSurfacePanel(bool hidden);
    void hideControlPanel(bool hidden);
    SurfacePanel* surfacePanel();
    PatientTileInfo* tileInfo();
    void repaintTooth(const ToothPaintHint& tooth);
    void setNotes(const std::array<std::string, 32>& notes);
    void setSelectedTeeth(const std::vector<int>& selectedTeeth);
    void setProcedures(const std::vector<Procedure>& m);
   
    ~VisitView();

private:
    Ui::VisitView ui;
};
