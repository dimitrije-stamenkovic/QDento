#include "LoginPresenter.h"
#include "View/ModalDialogBuilder.h"
#include "Database/DbDentist.h"
#include "Database/Database.h"
#include "Model/User.h"
#include "View/Widgets/LoginView.h"

LoginPresenter::LoginPresenter() : m_users(DbDentist::getList()) {}

bool LoginPresenter::successful()
{
    User::resetUser();

    LoginView d(*this);
    d.exec();

    return loginSuccessful;
}

void LoginPresenter::setView(LoginView* view)
{
    this->view = view;

    std::vector<std::string> names;
    names.reserve(m_users.size());

    for (auto& cred : m_users) {
        names.push_back(cred.getFullName());
    }

    view->setDentistList(names);
}

void LoginPresenter::userIdxChanged(int idx)
{
    m_currentIndex = idx;

    if (idx > -1) {
        view->disablePasswordField(m_users[idx].pass.empty());
    }
}

void LoginPresenter::okPressed(const std::string& pass, bool remember)
{
    if (m_currentIndex == -1) return; //maybe add default user?

    if (m_users[m_currentIndex].pass != pass) {
        ModalDialogBuilder::showError(QObject::tr("Wrong password").toStdString());
        return;
    }

    DbDentist::setAutoLogin(m_users[m_currentIndex].rowID, remember);
  

    login(m_users[m_currentIndex].rowID);
}

void LoginPresenter::login(long long rowid)
{
    auto dentist = DbDentist::get(rowid);

    User::setCurrentDentist(dentist.value());

    loginSuccessful = true;

    if (view) {
        view->close();
    }
}
