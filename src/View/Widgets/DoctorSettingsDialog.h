#pragma once

#include <QDialog>
#include "ui_DoctorSettingsDialog.h"

#include "Model/Validators/CommonValidators.h"
#include "Presenter/DoctorDialogPresenter.h"

class DoctorSettingsDialog final : public QDialog
{
	Q_OBJECT

    DentistDialogPresenter& presenter;

	void paintEvent(QPaintEvent* event) override;

	NotEmptyValidator fieldValidator;

public:
    DoctorSettingsDialog(DentistDialogPresenter& presenter, QWidget *parent = Q_NULLPTR);

	void setDoctor(const Dentist& dentist);
	Dentist get();
    void setToReadOnly();

	~DoctorSettingsDialog();

private:
	Ui::DoctorSettingsDialog ui;
};
