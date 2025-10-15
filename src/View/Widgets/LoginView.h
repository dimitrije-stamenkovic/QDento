#pragma once

#include <QDialog>
#include "ui_LoginView.h"

class LoginPresenter;

class LoginView : public QDialog
{
	Q_OBJECT

	void paintEvent(QPaintEvent* event) override;
    LoginPresenter& presenter;
	
public:
    LoginView(LoginPresenter& p, QWidget *parent = Q_NULLPTR);
	void setDentistList(const std::vector <std::string>& doctorList);
	void disablePasswordField(bool disabled);
	~LoginView();

private:
	Ui::LoginView ui;
};
