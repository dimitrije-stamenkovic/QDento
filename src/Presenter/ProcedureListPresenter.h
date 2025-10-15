#pragma once
#include "Model/Dental/ProcedureListElement.h"
#include <set>

class ProcedureListPresenter {

	std::vector<ProcedureListElement> m_elements;

	bool fav_update_required = false;

	bool has_favourites = false;
	
	void sortList();

public:
	ProcedureListPresenter();

	const std::vector<ProcedureListElement>& getList() const;
	void favClicked(int idx);
	bool hasFavourites() const; 
	std::set<std::string> getUniqueCodes();
	void addProcedureElement(const ProcedureListElement& e);
	void editProcedureElement(const ProcedureListElement& e, int idx);
	void removeProcedureElement(int idx);
	~ProcedureListPresenter();
};