#pragma once

#include "Model/TabType.h"

struct RowInstance
{
	const TabType type;
	long long rowID{0};
	long long patientRowId{0};
    bool permissionToOpen = true; //set to false if the document is created by another user
	RowInstance(TabType t) : type(t) {}
};
