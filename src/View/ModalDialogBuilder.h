#pragma once
#include <string>
#include <vector>

#include "Model/Dental/Procedure.h"
#include "Model/Financial/BusinessOperation.h"
#include "Model/Dental/Snapshot.h"

class QPixmap;

class PracticeManagerPresenter;
class StatisticDialogPresenter;


enum class DialogAnswer { Yes, No, Cancel };

namespace ModalDialogBuilder
{
	enum SettingsTab { General, Dentist, Practice, Company, Procedures, Diagnosis, SQL };

	DialogAnswer YesNoCancelDailog(const std::string& question);
	std::string inputDialog(const std::string& text, const std::string& title, const std::string& input = {}, bool asPassword = false, bool emptyNotAllowed = true);
	bool askDialog(const std::string& questionText);
	void showError(const std::string& error);
	void showMessage(const std::string& message);
	void saveFile(const std::string& data, const std::string& filename, const std::string& extension);
	int openButtonDialog(const std::vector<std::string>& buttonNames, const std::string& title, const std::string& description = std::string()); //returns -1 if canceled
	void openExplorer(const std::string& path);
	std::optional<std::string> getStringInput(const std::string& dialogName, const std::string& fieldName);
	std::optional<std::string> showMultilineDialog(const std::string& text, const std::string& title = "Debug", bool enableEdit = false);
	std::optional<std::vector<Procedure>> selectProcedures(const std::vector<Procedure>& procedures);
	std::optional<BusinessOperation> editBusinessOperation(const BusinessOperation& op);
	std::optional<BusinessOperation> addBusinessOperation();
	void showSnapshots(const std::vector<Snapshot>& snapshots);

	void openSettingsDialog(SettingsTab setingsTab = SettingsTab::Dentist);
};

