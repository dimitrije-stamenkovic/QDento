#include "Parser.h"
#include <json.h>
#include "Model/Dental/ToothUtils.h"
#include "Model/Dental/ToothContainer.h"
#include "Model/Dental/PerioStatus.h"
#include "Model/Dental/Procedure.h"
#include "Model/TableStructs.h"
#include "Model/Financial/BusinessOperation.h"
#include "Model/Financial/Invoice.h"
#include "Model/Settings.h"

std::string Parser::write(const PerioStatus& status)
{
	Json::Value json;
	
	json["PD"] = Json::Value(Json::arrayValue);
	for (auto& pd : status.pd)
		json["PD"].append(pd);

	json["CAL"] = Json::Value(Json::arrayValue);
	for (auto& cal : status.cal)
		json["CAL"].append(cal);

	json["BOP"] = Json::Value(Json::arrayValue);
	for (auto& bop : status.bop)
		json["BOP"].append(static_cast<int>(bop));
	
	json["AG"] = Json::Value(Json::arrayValue);
	for (auto& ag : status.ag)
		json["AG"].append(ag);
	
	json["Furc"] = Json::Value(Json::arrayValue);
	for (auto& furc : status.furcation)
		json["Furc"].append(furc);

	json["FMBS"] = Json::Value(Json::arrayValue);
	for (auto& FMBS : status.FMBS)
		json["FMBS"].append(static_cast<int>(FMBS));

	json["FMPS"] = Json::Value(Json::arrayValue);
	for (auto& FMPS : status.FMPS)
		json["FMPS"].append(static_cast<int>(FMPS));

	json["Disabled"] = Json::Value(Json::arrayValue);
	for (auto& d : status.disabled)
		json["Disabled"].append(static_cast<int>(d));

	json["Smoker"] = status.smoker;
	json["BoneLoss"] = status.boneLoss;
	json["Restore"] = status.completeRestorationNeeded;
	json["Sys"] = status.systemic;

	Json::FastWriter writer;

	return writer.write(json);
}

using namespace Dental;

std::string Parser::write(const ToothContainer& status)
{
	Json::Value statusJson = Json::arrayValue;

	auto writeToothStatus = [](const Tooth& t) -> Json::Value
	{
		Json::Value toothJson;

		auto writeDentistMade = [](long long rowid) -> Json::Value
		{
			Json::Value result;
			if (rowid) {
				result["rowid"] = rowid;
			}
			return result;
		};

		auto writeConstruction = [](long long rowid, BridgePos p) -> Json::Value
		{
			Json::Value result;
			if (rowid) {
				result["rowid"] = rowid;
			}
			result["Pos"] = static_cast<int>(p);
			return result;
		};


		toothJson["index"] = t.index();
		toothJson["temp"] = t[Temporary];

		if (t[Healthy]) toothJson["H"] = 1;
		if (t[Pulpitis]) toothJson["P"] = 1;
		if (t[Necrosis]) toothJson["N"] = 1;
		if (t[Resorption]) toothJson["Res"] = 1;
		if (t[ApicalLesion]) toothJson["G"] = 1;
		if (t[Calculus]) toothJson["T"] = 1;
		if (t[Fracture]) toothJson["F"] = 1;
		if (t[Root]) toothJson["R"] = 1;
		if (t[Impacted]) toothJson["Re"] = 1;
		if (t[Periodontitis]) toothJson["Pa"] = 1;
		if (t[Mobility]) toothJson["M"] = static_cast<int>(t.m_degree);

		if (t[Caries])
		{
			toothJson["C"] = Json::arrayValue;

			auto& arr = t.getSurfaceBoolStatus(Caries);

			for (int i = 0; i < SurfaceCount; i++)
			{
				if (!arr[i]) continue;
				Json::Value cariesJson;
				cariesJson["Surf"] = i;
				toothJson["C"].append(cariesJson);
			}
		}

		if (t[NonCariesLesion])
		{
			
			toothJson["NC"] = Json::arrayValue;

			auto& arr = t.getSurfaceBoolStatus(NonCariesLesion);

			for (int i = 0; i < SurfaceCount; i++)
			{
				if (!arr[i]) continue;
				Json::Value nonCariesLesion;
				nonCariesLesion["Surf"] = i;
				toothJson["NC"].append(nonCariesLesion);
			}
		}

		if (t[Restoration])
		{
			toothJson["O"] = Json::arrayValue;

			auto& arr = t.getSurfaceBoolStatus(Restoration);

			for (int i = 0; i < SurfaceCount; i++)
			{
				if (!arr[i]) continue;

				Json::Value restorationJson;
				restorationJson["Surf"] = i;
				restorationJson["LPK"] = t.getLPK(i);
				toothJson["O"].append(restorationJson);
			}
		}

		if (t[DefectiveRestoration])
		{

			toothJson["DR"] = Json::arrayValue;

			auto& arr = t.getSurfaceBoolStatus(DefectiveRestoration);

			for (int i = 0; i < SurfaceCount; i++)
			{
				if (!arr[i]) continue;

				Json::Value defRestJson;
				defRestJson["Surf"] = i;
				defRestJson["LPK"] = t.getLPK(i);
				toothJson["DR"].append(defRestJson);
			}
		}

		if (t[Denture]) toothJson["X"] = writeDentistMade(t.getLPK(Denture));
		if (t[RootCanal]) toothJson["Rc"] = writeDentistMade(t.getLPK(RootCanal));
		if (t[Missing]) toothJson["E"] = writeDentistMade(t.getLPK(Missing));
		if (t[Implant]) toothJson["I"] = writeDentistMade(t.getLPK(Implant));
		if (t[Crown]) toothJson["K"] = writeDentistMade(t.getLPK(Crown));
		if (t[Post]) toothJson["Rp"] = writeDentistMade(t.getLPK(Post));

		if (t[Bridge]) toothJson["B"] = writeConstruction(t.getLPK(Bridge), t.position);
		if (t[Splint]) toothJson["S"] = writeConstruction(t.getLPK(Splint), t.position);

		return toothJson;
	};

	for (auto& t : status)
	{
		if (t.noData()) continue;

		auto toothJson = writeToothStatus(t);
		if (t[HasSupernumeral]) {
			toothJson["D"] = writeToothStatus(t.getSupernumeral());
		}

		statusJson.append(toothJson);
	}

	Json::FastWriter writer;

	return writer.write(statusJson);

}


void Parser::parse(const std::string& jsonString, ToothContainer& status)
{
	Json::Value statusJson;
	Json::Reader reader;

	auto parseTooth = [](const Json::Value& jsonTooth, Tooth& tooth) mutable
	{
		tooth.setStatus(Temporary, jsonTooth["temp"].asBool());
		tooth.setStatus(Healthy, jsonTooth.isMember("H"));
		tooth.setStatus(Pulpitis, jsonTooth.isMember("P"));
		tooth.setStatus(ApicalLesion, jsonTooth.isMember("G"));
		tooth.setStatus(Calculus, jsonTooth.isMember("T"));
		tooth.setStatus(Fracture, jsonTooth.isMember("F"));
		tooth.setStatus(Root, jsonTooth.isMember("R"));
		tooth.setStatus(Periodontitis, jsonTooth.isMember("Pa"));
		tooth.setStatus(Impacted, jsonTooth.isMember("Re"));
		tooth.setStatus(Necrosis, jsonTooth.isMember("N"));
		tooth.setStatus(Resorption, jsonTooth.isMember("Res"));

		tooth.setStatus(Mobility, jsonTooth.isMember("M"));

		if (tooth[Mobility]) {
			tooth.m_degree = static_cast<MobilityDegree>(jsonTooth["M"].asInt());
		}

		if (jsonTooth.isMember("C"))
		{
			for (auto& c : jsonTooth["C"])
			{
				tooth.setSurface(Dental::Caries, c["Surf"].asInt(), true);
			}
		}

		if (jsonTooth.isMember("NC"))
		{
			for (auto& c : jsonTooth["NC"])
			{
				tooth.setSurface(Dental::NonCariesLesion, c["Surf"].asInt(), true);
			}
		}

		if (jsonTooth.isMember("O"))
		{
			for (auto& o : jsonTooth["O"])
			{
				auto surface = o["Surf"].asInt();
				tooth.setSurface(Dental::Restoration, surface, true);
				tooth.setDentistRowid(surface, o["rowid"].asLargestInt());
			}
		}

		if (jsonTooth.isMember("DR"))
		{
			for (auto& o : jsonTooth["DR"])
			{
				auto surface = o["Surf"].asInt();
				tooth.setSurface(Dental::DefectiveRestoration, surface, true);
				tooth.setDentistRowid(surface, o["rowid"].asLargestInt());
			}
		}

		auto dentistMadeParser = [](const Json::Value& json, Tooth& tooth, const char* numenclature, Dental::Status code)
		{
			if (!json.isMember(numenclature)) return;

			tooth.setStatus(code);
			tooth.setDentistRowid(code, json[numenclature]["rowid"].asLargestInt());
		};

		dentistMadeParser(jsonTooth, tooth, "K", Crown);
		dentistMadeParser(jsonTooth, tooth, "I", Implant);
		dentistMadeParser(jsonTooth, tooth, "Rc", RootCanal);
		dentistMadeParser(jsonTooth, tooth, "E", Missing);
		dentistMadeParser(jsonTooth, tooth, "Rp", Post);
		dentistMadeParser(jsonTooth, tooth, "X", Denture);

		auto constructionParser = [](const Json::Value& json, Tooth& tooth, const char* numenclature, Dental::Status code)
		{
			if (!json.isMember(numenclature)) return;

			tooth.setStatus(code);
			tooth.position = static_cast<BridgePos>(json[numenclature]["Pos"].asInt());
			tooth.setDentistRowid(code, json[numenclature]["rowid"].asLargestInt());
		};

		constructionParser(jsonTooth, tooth, "B", Bridge);
		constructionParser(jsonTooth, tooth, "S", Splint);

	};

	if(!reader.parse(jsonString, statusJson)) return;

	for (auto& toothJson : statusJson)
	{
		auto idx = toothJson["index"].asInt();

		auto& tooth = status[idx];

		parseTooth(toothJson, tooth);

		if (toothJson.isMember("D"))
		{
			tooth.setStatus(Dental::HasSupernumeral, true);
			parseTooth(toothJson["D"], tooth.getSupernumeral());
		}
	}

}

std::string Parser::write(const Invoice& inv)
{
	Json::Value json;

	auto mainDoc = inv.mainDocument();
	if (mainDoc) {
        json["mainDocumentNum"] = (Json::Int64)mainDoc->number;
		json["mainDocumentDate"] = mainDoc->date.to8601();
	}

	json["operations"] = Json::Value(Json::arrayValue);

	for (auto op : inv.businessOperations)
	{
		Json::Value operation;

		operation["code"] = op.activity_code;
		operation["name"] = op.activity_name;
		operation["quantity"] = op.quantity;
		operation["price"] = op.unit_price;

		json["operations"].append(operation);
	}

	json["taxEventDate"] = inv.taxEventDate.to8601();
	json["paymentType"] = static_cast<int>(inv.paymentType);
    json["VAT"] = inv.VAT;

	Json::FastWriter writer;
	return writer.write(json);
}

void Parser::parse(const std::string& jsonString, DetailsSummary& summary)
{
	Json::Value procedure;
	Json::Reader reader;

	bool parsingSuccessful = reader.parse(jsonString, procedure);

	if (!parsingSuccessful) {
		return;
	}

	summary.procedureDiagnosis = procedure["diagnosis"].asString();

	if (!procedure["name"].isNull())
	{
		summary.procedureName = procedure["name"].asString();
	}

}

void Parser::parse(const std::string& jsonString, PerioStatus& status)
{
	Json::Value json;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(jsonString, json);

	if (!parsingSuccessful) {
		return;
	}

	const Json::Value& pd = json["PD"];
	for (int i = 0; i < pd.size(); i++)
		status.pd[i] = pd[i].asInt();

	const Json::Value& cal = json["CAL"];
	for (int i = 0; i < cal.size(); i++)
		status.cal[i] = cal[i].asInt();

	const Json::Value& bop = json["BOP"];
	for (int i = 0; i < bop.size(); i++)
		status.bop[i] = bop[i].asBool();

	const Json::Value& ag = json["AG"];
	for (int i = 0; i < ag.size(); i++)
		status.ag[i] = ag[i].asInt();

	const Json::Value& furc = json["Furc"];
	for (int i = 0; i < furc.size(); i++)
		status.furcation[i] = furc[i].asInt();
	
	const Json::Value& fmps = json["FMPS"];
	for (int i = 0; i < fmps.size(); i++)
		status.FMPS[i] = fmps[i].asBool();

	const Json::Value& fmbs = json["FMBS"];
	for (int i = 0; i < fmbs.size(); i++)
		status.FMBS[i] = fmbs[i].asBool();

	const Json::Value& disabled = json["Disabled"];
	for (int i = 0; i < disabled.size(); i++)
		status.disabled[i] = disabled[i].asBool();

	status.smoker = json["Smoker"].asInt();
	status.boneLoss = json["BoneLoss"].asInt();
	status.completeRestorationNeeded = json["Restore"].asBool();
	status.systemic = json["Sys"].asBool();
}

void Parser::parse(const std::string& jsonString, Invoice& invoice)
{
	Json::Value json;

	Json::Reader reader;

	bool parsingSuccessful = reader.parse(jsonString, json);

	if (!parsingSuccessful) {
		throw std::invalid_argument("could not parse invoice data");
	}

	if (json.isMember("mainDocumentNum")) {
		invoice.setMainDocumentData(
            json["mainDocumentNum"].asInt64(),
			Date(json["mainDocumentDate"].asString())
		);
	}

	for (const auto& operation : json["operations"])
	{

		double price = operation["price"].asDouble();
		int quantity = operation["quantity"].asInt();

		invoice.businessOperations.emplace_back(
				operation["code"].asString(),
				operation["name"].asString(),
				price, quantity
		);
	}

    invoice.VAT = json["VAT"].asInt();
	invoice.taxEventDate = Date(json["taxEventDate"].asString());
	invoice.paymentType = static_cast<PaymentType>(json["paymentType"].asInt());
}


std::string Parser::parseDiagnosis(const std::string& jsonProcedureString)
{
	Json::Value json;
	Json::Reader reader;

	bool parsingSuccessful = reader.parse(jsonProcedureString, json);

	if (!parsingSuccessful) {
		throw std::invalid_argument("could not parse procedure diagnosis");
	}

	return json["diagnosis"].asString();
}
