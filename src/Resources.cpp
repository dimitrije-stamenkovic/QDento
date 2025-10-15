#include "Resources.h"
#include <QFile>
#include <QTextStream>

std::string Resources::fromPath(const char* path)
{
	QFile file(path);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream in(&file);

	QString result = in.readAll();

	return result.toStdString();
}

std::vector<std::string> Resources::dbSchema() {

	std::vector<std::string> result;

	QFile inputFile(":/db/dbSchema.txt");
	if (inputFile.open(QIODeviceBase::ReadOnly))
	{
		QTextStream in(&inputFile);
		while (!in.atEnd())
        {

            result.emplace_back(in.readLine().toStdString());
		}
		inputFile.close();
	}
	return result;
}

std::vector<std::string> Resources::getMigrationScript(int version)
{
	std::vector<std::string> result;
	//the file has to be included in qrc
	QString path = ":/migrations/db_migrateTo";
	path += QString::number(version);
	path += ".txt";

	QFile inputFile(path);
	if (inputFile.open(QIODevice::ReadOnly))
	{
		QTextStream in(&inputFile);
		while (!in.atEnd())
		{
            result.emplace_back(in.readLine().toStdString());
		}
		inputFile.close();
	}
	return result;
}

