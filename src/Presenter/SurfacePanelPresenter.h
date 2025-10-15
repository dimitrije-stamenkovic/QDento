#pragma once

#include "InputEnums.h"
#include "ButtonSurfaceMatrix.h"
#include "Model/Dental/Dental.h"

class Tooth;

enum class SurfaceClick {rightClick, leftClick};
enum class SurfaceState { none, restoration, caries, secondary, defective, nonCaries };
class SurfacePanel;
class VisitPresenter;

class SurfacePanelPresenter
{
	SurfacePanel* view;
	VisitPresenter* statusControl;
	std::array <std::tuple<int, SurfaceState>, 6> surfaceState;

	int currentIndex;
	ButtonSurfaceMatrix matrix;

public:
		SurfacePanelPresenter();

		void notesClicked();
		void setView(SurfacePanel* view);
		void setStatusControl(VisitPresenter* status_presenter);
		void setTooth(const Tooth& tooth, bool hasNotes);
		void buttonClicked(ButtonPos position, SurfaceClick click);
		void sideButtonClicked(Dental::StatusType stat);

};

