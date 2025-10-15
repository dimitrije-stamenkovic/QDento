#include "SaveDialog.h"

SaveDialog::SaveDialog(QString title, QWidget *parent)
	: QMessageBox(parent)
{
	setWindowTitle("QDento");

	setText(title);
	addButton(QString(tr("Yes")), QMessageBox::ButtonRole::YesRole);
	addButton(QString(tr("No")), QMessageBox::ButtonRole::NoRole);
	addButton(QString(tr("Cancel")), QMessageBox::ButtonRole::RejectRole);
	setIcon(QMessageBox::Warning);
}

SaveDialog::~SaveDialog()
{
}
