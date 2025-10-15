#pragma once

#include <QWidget>
#include "ui_ProcedureInput.h"
#include "Model/Validators/CommonValidators.h"
#include "View/Interfaces/AbstractLineEdit.h"
#include "View/Interfaces/AbstractSpinBox.h"
#include "View/Interfaces/AbstractDateEdit.h"
#include "Model/Dental/Procedure.h"
#include "View/Interfaces/AbstractSurfaceSelector.h"
#include "View/Interfaces/AbstractRangeEdit.h"
#include "View/Interfaces/AbstractComboBox.h"
#include <optional>
#include <variant>

class ProcedureInput : public QWidget
{
	Q_OBJECT


	bool m_postDisabled = false;
	bool m_allow_singleRange = false;

	ConstructionRange getConstructionRange();
	RestorationData getRestorationData();


public:
	
	struct CommonData {

		std::string diagnosis;
		std::string notes;
		double price;
	};

	struct ResultData : public CommonData {
		std::variant<
			std::monostate, //no parameters
			bool, //supernumeral for tooth specific
			std::pair<bool, RestorationData>, //restoration
			ConstructionRange //range
		> parameters;
	};
	
	ProcedureInput(QWidget *parent = Q_NULLPTR);

	void setParamMinHeight(int height);

	void setCommonData(const CommonData& data);
	void setParameterData();
	void setParameterData(bool supernumeral);
	void setParameterData(bool supernumeral, RestorationData r);
	void setParameterData(ConstructionRange range, bool allowSingle);
	void setParameterData(bool supernumeral, ConstructionRange range, bool preferSingle);
	void setParameterData(bool supernumeral, ConstructionRange range, RestorationData r, int preferedIndex);

	ResultData getResult();

	void setErrorMsg(const std::string& errorMsg);
	void disablePost();

	std::string isValid();

	~ProcedureInput();

	Ui::ProcedureInput ui;

};
