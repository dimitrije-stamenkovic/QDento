#include "ProcedureTableModel.h"
#include <QIcon>

ProcedureTableModel::ProcedureTableModel(QObject* parent) : QAbstractTableModel(parent)
{
}


void ProcedureTableModel::setProcedures(const std::vector<Procedure>& rows)
{
    beginResetModel();

    this->m_procedures.clear();
    this->m_procedures.reserve(rows.size());

    for (auto& p : rows)
        this->m_procedures.emplace_back(QProcedure{p});

    endResetModel();

    emit dataChanged(index(0, 0), index(m_procedures.size(), poceduresColumnCount));
}


bool ProcedureTableModel::insertRows(int, int, const QModelIndex&)
{
    return false;
}

bool ProcedureTableModel::removeRows(int, int, const QModelIndex&)
{
    return false;
}

QVariant ProcedureTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
                case 0: return "ID";
                case 1: return tr("Date");
                case 2: return tr("Code");
                case 3: return tr("Diagnosis");
                case 4: return tr("Tooth");
                case 5: return tr("Procedure");
                case 6: return tr("Price");
                case 7: return tr("Dentist");
                case 8: return tr("Notes");
            }
        }
    }

    return QVariant();;
}

int ProcedureTableModel::rowCount(const QModelIndex&) const
{
    return m_procedures.size();
}

int ProcedureTableModel::columnCount(const QModelIndex&) const
{
    return poceduresColumnCount;
}

void ProcedureTableModel::filterProcedures(const std::vector<int>& selected)
{
    std::vector<QProcedure> filtered;

    filtered.reserve(m_procedures.size());

    for (int row : selected){
        filtered.push_back(m_procedures[row]);
    }

    m_procedures = filtered;

    QModelIndex topLeft = createIndex(0, 0);
    QModelIndex bottomRight = createIndex(m_procedures.size(), 7);
    emit dataChanged(topLeft, bottomRight);
}



QVariant ProcedureTableModel::data(const QModelIndex& index, int role) const
{

        if (!index.isValid()) return QVariant();

        int row = index.row();
        int column = index.column();

        //if (row == m_procedures.size()) return 0; //why???
        //if (m_procedures.size() == 0) return 0;


        switch (role)
        {

        case Qt::DisplayRole:
            switch (column)
            {
               case 0: return index.row();
               case 1: return m_procedures[row].date;
               case 2: return m_procedures[row].code;
               case 3: return m_procedures[row].diagnosis.size() ? m_procedures[row].diagnosis : "---";
               case 4: return m_procedures[row].tooth;
               case 5: return m_procedures[row].description;
               case 6: return m_procedures[row].price;
               case 7: return m_procedures[row].dentist;
               case 8: return m_procedures[row].notes;
               default: break;
            }
        case Qt::TextAlignmentRole:
             if (column != 8)
                return int(Qt::AlignCenter);
        }

        return QVariant();
}

ProcedureTableModel::~ProcedureTableModel()
{
}

Qt::ItemFlags ProcedureTableModel::flags(const QModelIndex&) const
{
    auto flags = Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
    return flags;
}

Qt::DropActions ProcedureTableModel::supportedDropActions() const
{
    auto flags = Qt::DropActions();
    flags |= Qt::MoveAction;
    return flags;
}


bool ProcedureTableModel::dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& index)
{

    Q_UNUSED(column)
        QModelIndex newIndex;
    if (index.isValid()) // row was dropped directly on an item (parent)
    {
        // If we apply dropMimeData without any modifications,
        // the data overwrites the given row.
        // However, we would like to insert the data *after* the given row.
        // The TableModel inserts a row if the parent is the hidden root parent
        // (provided by QModelIndex()), so we use that.
        newIndex = QModelIndex();
        row = index.row() + 1;
    }
    else
        newIndex = index;

    if (row == -1)
        row = rowCount();

    m_destinationDropRow = row;

    return QAbstractTableModel::dropMimeData(data, action, row, 0, newIndex);
}