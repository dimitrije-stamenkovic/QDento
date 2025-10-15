#include "ProcedureContainer.h"

#include <algorithm>

#include "Model/Dental/ToothContainer.h"

void ProcedureContainer::addProcedures(const std::vector<Procedure>& p)
{
    m_proc.reserve(m_proc.size() + p.size());

    for (auto& mInsert : p)
    {
        m_proc.push_back(mInsert);
    }
}

void ProcedureContainer::addProcedure(const Procedure& p)
{
    m_proc.push_back(p);
}

void ProcedureContainer::refreshTeethTemporary(const ToothContainer& teeth)
{
    for (auto& procedure : m_proc) {

        auto index = procedure.getToothIndex();

        if (!index.isValid()) continue;

        index.temp = teeth.at(index.index, index.supernumeral)[Dental::Temporary];

        procedure.affectedTeeth = index;
    }
}

void ProcedureContainer::removeProcedure(int idx)
{
    if (idx < 0 || idx >= m_proc.size()) return;

    m_proc.erase(m_proc.begin() + idx);
}

void ProcedureContainer::replaceProcedure(const Procedure& p, int idx)
{
    if (idx < 0 || idx >= m_proc.size()) return;

    m_proc.erase(m_proc.begin() + idx);

    addProcedure(p);

}

bool ProcedureContainer::moveProcedure(int from, int to)
{
    if (from == to) return false;
    if (m_proc.empty()) return false;
    if (m_proc.size() == 1) return false;

    if (to == m_proc.size()) {
        auto temp = m_proc[from];
        m_proc.erase(m_proc.begin() + from);
        m_proc.push_back(temp);
    }
    else
    {
        auto temp = m_proc;

        m_proc.clear();

        for (int i = 0; i < temp.size(); i++)
        {
            if (i == from) continue;

            if (i == to) {
                m_proc.push_back(temp[from]);
            }

            m_proc.push_back(temp[i]);
        }
    }

    return true;
}

const Procedure& ProcedureContainer::at(int index) const
{
    return m_proc.at(index);
}

