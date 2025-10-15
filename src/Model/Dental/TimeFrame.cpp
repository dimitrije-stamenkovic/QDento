#include "TimeFrame.h"
#include "Model/User.h"

std::string TimeFrame::getFrameName() const
{
    std::string result;

    switch (type) {
    case TimeFrameType::InitialAmb:
        result += QObject::tr("Dental Visit ").toStdString() + number + QObject::tr(" (initial status)").toStdString();
        break;
    case TimeFrameType::Procedures:
        result += QObject::tr("Dental Visit ").toStdString() + number + QObject::tr(" (procedures)").toStdString();
        break;
    case TimeFrameType::Perio:
        result += QObject::tr("Periodontal Measurment").toStdString();
        break;
    }
    return result;
}
