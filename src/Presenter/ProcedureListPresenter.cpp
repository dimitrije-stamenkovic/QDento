#include "ProcedureListPresenter.h"
#include "Database/DbDentist.h"
#include "Database/DbProcedure.h"
#include "Model/User.h"
#include <algorithm>

ProcedureListPresenter::ProcedureListPresenter() : m_elements{ DbProcedure::getProcedureList() }
{
	auto favList = DbDentist::getFavouriteProcedures(User::dentist().rowID);

	for (auto& e : m_elements) {
		if (favList.count(e.code)) {
			e.favourite = true;
		}
	}

	sortList();
}

void ProcedureListPresenter::sortList()
{
	std::sort(m_elements.begin(), m_elements.end(), [](const ProcedureListElement& a, const ProcedureListElement& b) {

		return a.favourite != b.favourite ? 
							a.favourite > b.favourite
							:
							a.code < b.code;
	});
}

const std::vector<ProcedureListElement>& ProcedureListPresenter::getList() const
{
	return m_elements;
}

void ProcedureListPresenter::favClicked(int idx)
{
	fav_update_required = true;

	m_elements[idx].favourite = !m_elements[idx].favourite;

	sortList();
}

bool ProcedureListPresenter::hasFavourites() const
{
	return has_favourites;
}

std::set<std::string> ProcedureListPresenter::getUniqueCodes()
{
	std::set<std::string> result;

	for (auto e : m_elements) {
		result.insert(e.code);
	}

	return result;
}

void ProcedureListPresenter::addProcedureElement(const ProcedureListElement& e)
{
	m_elements.push_back(e);

	DbProcedure::setProcedureList(m_elements);

	sortList();
}

void ProcedureListPresenter::removeProcedureElement(int idx)
{
	if (idx == -1) return;

	m_elements.erase(m_elements.begin() + idx);

	DbProcedure::setProcedureList(m_elements);

	sortList();
}

void ProcedureListPresenter::editProcedureElement(const ProcedureListElement& e, int idx)
{
	if (idx == -1) return;

	m_elements[idx] = e;

	DbProcedure::setProcedureList(m_elements);

	sortList();
}


ProcedureListPresenter::~ProcedureListPresenter()
{
	if (!fav_update_required) return;

	std::vector<std::string> fav_list;

	for (auto& e : m_elements) {
		if (e.favourite) {
			fav_list.push_back(e.code);
		}
	}

	DbDentist::updateFavouriteProcedures(fav_list, User::dentist().rowID);
}
