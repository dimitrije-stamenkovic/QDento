#include "PlainTable.h"
#include "FreeFunctions.h"
#include "View/GlobalFunctions.h"
#include <QObject>

void PlainTable::addEmptyRow()
{
    for (auto& column : data) {
        column.rows.push_back(PlainCell{""});
    }
}

void PlainTable::setIndicatorToLastRow(const std::string& colorName)
{
    if (data.empty()) return;

    if (data[0].rows.empty()) return;

    QColor color(colorName.c_str());

    if (!color.isValid()) return;

    indicator_row_map[data[0].rows.size() - 1] = color;
}

PlainTable::PlainTable(const std::vector<Procedure>& pList)
{
    addColumn({QObject::tr("Date").toStdString(),100, PlainColumn::Center});
    addColumn({ QObject::tr("Code").toStdString(), 70, PlainColumn::Center });
    addColumn({ QObject::tr("Diagnosis").toStdString(), 120 });
    addColumn({ QObject::tr("Tooth").toStdString(), 70, PlainColumn::Center });
    addColumn({ QObject::tr("Procedure").toStdString(), 120 });
    addColumn({ QObject::tr("Price").toStdString(), 80, PlainColumn::Center });
    addColumn({ QObject::tr("Notes").toStdString(), 100, PlainColumn::Left });

    bool hasNhif = false;

    for (auto& p : pList) {

        addCell(0, {
            .data = p.date.toLocalFormat(),
            });
        addCell(1, PlainCell{ .data = p.code });
        addCell(2, { p.diagnosis });
        addCell(3, { p.getToothString() });
        addCell(4, { p.name });
        addCell(5, { priceToString(p.price).toStdString() });
        addCell(6, PlainCell{ .data = p.notes });
    }

}

PlainTable::PlainTable(const std::vector<BusinessOperation>& bList)
{
    addColumn({ QObject::tr("Code").toStdString(), 100, PlainColumn::Center });
    addColumn({ QObject::tr("Description").toStdString(), 400 });
    addColumn({ QObject::tr("Quantity").toStdString(), 70, PlainColumn::Center });
    addColumn({ QObject::tr("Unit Price").toStdString(), 70, PlainColumn::Center });
    addColumn({ QObject::tr("Total").toStdString(), 70, PlainColumn::Center });

    for (auto& op : bList)
    {
        addCell(0, { op.activity_code });
        addCell(1, { op.activity_name });
        addCell(2, { std::to_string(op.quantity) });
        addCell(3, { FreeFn::formatDouble(op.unit_price) });
        addCell(4, { FreeFn::formatDouble(op.value_price()) });
    }

}

