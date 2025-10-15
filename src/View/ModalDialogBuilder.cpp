#include "ModalDialogBuilder.h"

#include "View/Widgets/ProcedureDialog.h"

#include <QScreen>
#include <QWidget>
#include <QGuiApplication>
#include <QProcess>
#include <QDesktopServices>

#include "View/Widgets/SaveDialog.h"

DialogAnswer ModalDialogBuilder::YesNoCancelDailog(const std::string& question)
{
	SaveDialog s(question.c_str());
	s.exec();

	QAbstractButton* clicked = s.clickedButton();

	switch (s.buttonRole(clicked))
	{
	case QMessageBox::ButtonRole::YesRole:
		return DialogAnswer::Yes;
	case QMessageBox::ButtonRole::NoRole:
		return DialogAnswer::No;
	default:
		return DialogAnswer::Cancel;
	}
}

#include "View/Widgets/ProcedurePrintSelectDialog.h"

std::optional<std::vector<Procedure>> ModalDialogBuilder::selectProcedures(const std::vector<Procedure>& procedures)
{
	std::vector<Procedure> result;

	ProcedurePrintSelectDialog dialog(procedures);

	if (dialog.exec() == QDialog::Rejected) {
		return {};
	}

	auto selectedIndexes = dialog.selectedProcedures();

	for (auto idx : selectedIndexes) {
		result.push_back(procedures[idx]);
	}

	return result;
}

#include <QFileDialog>
/*
std::optional<std::string> ModalDialogBuilder::getMonthNotifFromFile()
{
	QString filePath = QFileDialog::getOpenFileName(nullptr, 
		"Изберете месечно известие", "", "XML files(*.xml)");

	if (filePath.isEmpty())
		return {};
	return filePath.toStdString();
}
*/

#include "View/Widgets/BusinessOperationDialog.h"
std::optional<BusinessOperation> ModalDialogBuilder::editBusinessOperation(const BusinessOperation& op)
{
	BuisnessOperationDialog d(op);
	d.exec();
	return d.getResult();
}

std::optional<BusinessOperation> ModalDialogBuilder::addBusinessOperation()
{
	BuisnessOperationDialog d;
	d.exec();
	return d.getResult();
}

#include "View/SubWidgets/SnapshotViewer.h"
void ModalDialogBuilder::showSnapshots(const std::vector<Snapshot>& snapshots)
{
	QDialog d;
	d.setWindowTitle(QDialog::tr("Treatment Result"));
	QVBoxLayout* mainLayout = new QVBoxLayout(&d);
	mainLayout->setContentsMargins(0, 0, 0, 0);
	d.setLayout(mainLayout);
	SnapshotViewer* v = new SnapshotViewer(&d);
	mainLayout->addWidget(v);
	v->setSnapshots(snapshots);
	d.exec();
}

bool ModalDialogBuilder::askDialog(const std::string& questionText)
{
	QMessageBox msg;

	msg.setWindowTitle("QDento");

	msg.setText(QString::fromStdString(questionText));
	msg.addButton(QString(QObject::tr("Yes")), QMessageBox::ButtonRole::YesRole);
	msg.addButton(QString(QObject::tr("No")), QMessageBox::ButtonRole::NoRole);
	msg.setIcon(QMessageBox::Question);
	msg.exec();

	QAbstractButton* clicked = msg.clickedButton();

	return (msg.buttonRole(clicked) == QMessageBox::YesRole);
}

void ModalDialogBuilder::showError(const std::string& error)
{
	QMessageBox msgBox;
	msgBox.setIcon(QMessageBox::Critical);
	msgBox.setWindowTitle(QMessageBox::tr("Error"));
	msgBox.setText(QMessageBox::tr(error.c_str()));
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.exec();

}

#include "View/Widgets/MultilineDialog.h"

std::optional<std::string> ModalDialogBuilder::showMultilineDialog(const std::string& text, const std::string& title, bool enableEdit)
{
	MultilineDialog d(text);

	if (enableEdit) {
		d.enableEditing();
	}

	d.setWindowTitle(QObject::tr(title.c_str()));
	d.exec();

	return d.getResult();
}

void ModalDialogBuilder::showMessage(const std::string& message)
{
	QMessageBox msgBox;
	msgBox.setModal(true);
	msgBox.setText(QObject::tr(message.c_str()));
	msgBox.exec();
}

void ModalDialogBuilder::saveFile(const std::string& data,
	const std::string& filename,
	const std::string& extension)
{
	QString filePath = QFileDialog::getSaveFileName(
		nullptr,
		QObject::tr("Save document"),
		QString::fromStdString(filename),
		QString::fromStdString(extension));

	if (filePath.isEmpty())
		return;

	QFile file(filePath);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return;

	QTextStream out(&file);
	out.setEncoding(QStringConverter::Encoding::Utf8);
	out << QString::fromStdString(data);
	file.close();

	QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
}

#include "View/Widgets/SettingsDialog.h"

void ModalDialogBuilder::openSettingsDialog(SettingsTab tab)
{
	SettingsDialog d;
	d.focusTab((SettingsDialog::SettingsTab)tab);
	d.exec();
}

#include "View/Widgets/ButtonDialog.h"

int ModalDialogBuilder::openButtonDialog(const std::vector<std::string>& buttonNames, const std::string& title, const std::string& description)
{
	ButtonDialog d(buttonNames, title, description);

	d.exec();

	return d.getResult();
}

void ModalDialogBuilder::openExplorer(const std::string& path)
{
	#ifdef _WIN32    //Code for Windows
		QProcess::startDetached("explorer.exe", { "/select,", QDir::toNativeSeparators(path.c_str()) });
	#elif defined(__APPLE__)    //Code for Mac
        QString pathstr = "tell application \"Finder\" to reveal POSIX file \"";
        pathstr += path;
        pathstr += "\"" ;
        QProcess::execute("/usr/bin/osascript", { "-e", pathstr });
		QProcess::execute("/usr/bin/osascript", { "-e", "tell application \"Finder\" to activate" });
    #endif
        Q_UNUSED(path)
        return;
}

#include <QInputDialog>

std::optional<std::string> ModalDialogBuilder::getStringInput(const std::string& dialogName, const std::string& fieldName)
{
	bool ok;

	QString text = QInputDialog::getText(NULL, dialogName.data(),
		fieldName.data(),
		QLineEdit::Password, QString(), &ok);

	if (text.isEmpty()) return {};

	return text.toStdString();

}

#include "View/Widgets/InputDialog.h"

std::string ModalDialogBuilder::inputDialog(
	const std::string& text, 
	const std::string& title, 
	const std::string& input, 
	bool asPassword, 
	bool emptyNotAllowed
)
{
	InputDialog d(asPassword);
	d.setLabel(text);
	d.setTitle(title);
	d.setInput(input);
	d.enableNotEmptyValidator(emptyNotAllowed);
	d.exec();
	return d.result();
}



