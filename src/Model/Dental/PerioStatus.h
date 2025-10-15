#pragma once
#include "Model/Date.h"
constexpr int upperCount = 0;
constexpr int perioSurfCount = 192;
constexpr int scoreSurfCount = 128;


struct PerioStatus
{
	long long rowid{ 0 };
	Date date{ Date::currentDate() };

	long long dentist_rowid;

	int smoker{ 0 };	
	int boneLoss{ 0 };	//bone loss %

	bool completeRestorationNeeded{ false };	
	bool systemic{ false };						

	int furcation[96]{ 0 };				
	bool disabled[32] { false };		
    int cal[perioSurfCount] { 0 };		
	int pd[perioSurfCount] { 0 };
	bool FMBS[scoreSurfCount]{ false };
	bool FMPS[scoreSurfCount]{ false }; 
	bool bop[perioSurfCount] { false };
	int ag[64] { 0 };
	int mobility[32] { 0 };

};


struct PerioWithDisabled {

	PerioWithDisabled(const PerioStatus& p) {
		for (int i = 0; i < perioSurfCount; i++) {
			
			bool disabled = p.disabled[i / 6];

			cal[i] = disabled ? 0 : p.cal[i];
			pd[i] = disabled ? 0 : p.pd[i];
			bop[i] = disabled ? 0 : p.bop[i];
		}
	}

	int cal[perioSurfCount]{ 0 };
	int pd[perioSurfCount]{ 0 };
	bool bop[perioSurfCount]{ false };

};