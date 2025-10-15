#pragma once
#include <string>
#include <vector>

namespace GlobalSettings
{
	void createCfgIfNotExists();

	std::string getDbBackupFilepath();

	std::string getDbPath();
	std::string setDbPath();

	bool isADANum();

	void setToothNum(bool ADA);

	std::string getTranslationPath();
	void removeTranslationPath();
	std::string setTranslationPath();
}