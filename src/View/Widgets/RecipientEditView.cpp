#include "RecipientEditView.h"

#include <QPainter>

RecipientEditView::RecipientEditView(RecipientPresenter& presenter, QWidget *parent)
    : QDialog(parent), presenter(presenter)
{
	ui.setupUi(this);

	setWindowTitle(tr("Recipient"));

	lineEdits[ID] = ui.idEdit;
	lineEdits[Name] = ui.nameEdit;
	lineEdits[Address] = ui.addressEdit;
	lineEdits[Phone] = ui.phoneEdit;

	for (auto e : lineEdits) e->setErrorLabel(ui.errorLabel);

    connect(ui.okButton, &QPushButton::clicked, this, [&] { presenter.okPressed();});

    connect(ui.idEdit, &QLineEdit::textChanged, this, [&](const QString& text) { 

		bool isValid = ui.idEdit->isValid();

		if (ui.idEdit->isValid()) presenter.idValidInput();
	});

	presenter.setRecipientEditView(this);
}

void RecipientEditView::setRecipient(const Recipient& r)
{
	ui.idEdit->blockSignals(true);

	ui.nameEdit->setText(r.name.c_str());
	ui.addressEdit->setText(r.address.c_str());
	ui.idEdit->setText(r.identifier.c_str());
	ui.phoneEdit->setText(r.phone.c_str());
	ui.idEdit->blockSignals(false);
}

Recipient RecipientEditView::getRecipient()
{
	Recipient r;
	r.name = ui.nameEdit->text().toStdString();
	r.address = ui.addressEdit->text().toStdString();
	r.identifier = ui.idEdit->text().toStdString();
	r.phone = ui.phoneEdit->text().toStdString();

	return r;
}

void RecipientEditView::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
	painter.fillRect(QRect(0, 0, width(), height()), Qt::white);
}

LineEdit* RecipientEditView::lineEdit(LineEditType type)
{
	return lineEdits[type];
}


RecipientEditView::~RecipientEditView()
{}

