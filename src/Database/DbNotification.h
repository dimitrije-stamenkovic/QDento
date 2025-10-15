#pragma once
#include <vector>
#include "Model/Dental/Notification.h"

namespace DbNotification
{
    bool insert(const Notification& n);
    bool remove(long long notifRowid);
    std::vector<Notification> get(long long dentist_rowid);
    int hasNotifications(const Date& date = Date::currentDate());

}
