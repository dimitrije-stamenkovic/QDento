#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QPainter>

#include "Presenter/PatientDialogPresenter.h"
#include "ui_PatientFormDialog.h"
#include "Model/Validators/DateValidator.h"
#include "Model/Validators/CommonValidators.h"

#include "Model/Patient.h"


struct PatientFormDialog : public QDialog
{

    QRegularExpressionValidator* phoneValidator;
    QRegularExpressionValidator* numValidator;
    QRegularExpressionValidator* nameValidator;

    NotEmptyValidator notEmpty_validator;
    DateValidator birthDate_validator;
    Ui::PatientFormDialog ui;

    void paintEvent(QPaintEvent* event) override;

    PatientDialogPresenter& presenter;

    enum PatientField { id, fname, lname, phone, address, birthdate, size };

    std::array<AbstractUIElement*, PatientField::size> patientFields;

public:
    Q_OBJECT

public:

    PatientFormDialog(PatientDialogPresenter& p, QWidget* parent = 0);
    ~PatientFormDialog();

    void setEditMode(bool editMode);
    void setTitle(const std::string& title);
    void resetFields();
    void setPatient(const Patient& patient);
    Patient getPatient();
    bool inputFieldsAreValid();
};
