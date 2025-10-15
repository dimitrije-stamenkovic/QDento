#pragma once
#include <QObject>
#include <string_view>
//Some important enums and string literals
namespace Dental
{
	enum Type { Molar, Premolar, Frontal };

	constexpr int teethCount = 32;

	enum Surface { Occlusal, Medial, Distal, Buccal, Lingual, Cervical, SurfaceCount };
	enum Quadrant { First, Second, Third, Fourth };
	enum BridgePos { Begin, Middle, End };
	enum MobilityDegree { I, II, III, MobilityCount };
	enum class StatusType { General, Restoration, Caries, NonCariesLesion, DefectiveRestoration, Mobility };

	enum Status {
		Healthy,
		Temporary,
		Restoration,
		Caries,
		DefectiveRestoration,
		NonCariesLesion,
		Pulpitis,
		Necrosis,
		Resorption,
		ApicalLesion,
		RootCanal,
		Post,
		Root,
		Fracture,
		Missing,
		Periodontitis,
		Mobility,
		Crown,
		Bridge,
		Splint,
		Implant,
		HasSupernumeral,
		Impacted,
		Denture,
		Calculus,
		StatusCount
	};

	inline const std::string statusNames[StatusCount]
	{
		QObject::tr("Healthy Tooth").toStdString(), 
		QObject::tr("Primary Tooth").toStdString(), 
		QObject::tr("Restoration").toStdString(),
		QObject::tr("Caries").toStdString(),
		QObject::tr("Defective Restoration").toStdString(),
		QObject::tr("Non-Caries Lesion").toStdString(),
		QObject::tr("Pulpitis").toStdString(),
		QObject::tr("Necrosis").toStdString(),
		QObject::tr("Resorption").toStdString(),
		QObject::tr("Apical Lesion").toStdString(),
		QObject::tr("Root Canal Treatment").toStdString(),
		QObject::tr("Radicular Post").toStdString(),
		QObject::tr("Rood / Severely Destroyed Tooth").toStdString(),
		QObject::tr("Fracture").toStdString(),
		QObject::tr("Missing Tooth").toStdString(),
		QObject::tr("Periodontitis").toStdString(),
		QObject::tr("Mobility").toStdString(),
		QObject::tr("Crown").toStdString(),
		QObject::tr("Bridge").toStdString(),
		QObject::tr("Splint / Adhesive Bridge").toStdString(),
		QObject::tr("Implant").toStdString(),
		QObject::tr("Supernumeral Tooth").toStdString(),
		QObject::tr("Impacted Tooth").toStdString(),
		QObject::tr("Denture").toStdString(),
		QObject::tr("Calculus").toStdString()
	};

	inline const  std::string mobilityNames[MobilityCount]
	{
		QObject::tr("Mobility I").toStdString(), 
		QObject::tr("Mobility II").toStdString(),
		QObject::tr("Mobility III").toStdString()
	};

	inline const  std::string surfaceNames[SurfaceCount]
	{
		QObject::tr("Occlusal/Incisal").toStdString(), 
		QObject::tr("Medial").toStdString(), 
		QObject::tr("Distal").toStdString(),
		QObject::tr("Vestibular").toStdString(),
		QObject::tr("Lingual").toStdString(),
		QObject::tr("Cervical").toStdString()
	};

}