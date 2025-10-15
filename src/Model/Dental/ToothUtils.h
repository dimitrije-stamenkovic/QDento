#pragma once

#include <unordered_map>
#include <array>
#include <string>
#include <utility>
#include "ToothIndex.h"
#include "Dental.h"

namespace ToothUtils
{
	Dental::Type getToothType(int index);
	int getToothNumber(int index, bool temporary);
	std::string getNomenclature(int index, bool temporary = false);
	std::string getNomenclature(const ToothIndex& t);
	Dental::Quadrant getQuadrant(int index);
	std::array<std::string, 6> getSurfaceNames(int index);
	std::string getName(int idx, bool temp);
};