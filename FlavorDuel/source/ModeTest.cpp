#include "ModeTest.h"
#include <sstream>
#include <picojson.h>
#include <codecvt>
#include <memory>
#include "Curl.h"
#include "testUI.h"

namespace {
	constexpr auto TestURL = "http://localhost:9000";
}

Flavor::ModeTest::ModeTest()
{
	this->SetLayer(1);
	this->SetName("ModeTest");
}

bool Flavor::ModeTest::Initialize()
{
	ModeBase::Initialize();
	_testCard.name = "|“S‚Ì‹T";
	_testCard.flavorText = "d‚¢b—…‚Í‚Ç‚ñ‚ÈUŒ‚‚à‚Í‚¶‚­B";

	picojson::object jsonObject;
	auto nameUTF8 = AppFrame::CharacterCodeConvert::ConvertShiftJISToUTF8(_testCard.name);
	auto textUTF8 = AppFrame::CharacterCodeConvert::ConvertShiftJISToUTF8(_testCard.flavorText);
	jsonObject.insert(std::make_pair("name", picojson::value(nameUTF8)));
	jsonObject.insert(std::make_pair("text", picojson::value(textUTF8)));
	picojson::value value(jsonObject);
	std::string jsonString = value.serialize();

	//Curl* curl = new Curl();
	//
	//curl->post(TestURL, jsonString, [](std::string error, std::string body) {
	//	if (error != "") {
	//		std::cerr << "ERROR: " << error << std::endl;
	//	}
	//	else {
	//		std::cout << "POST Response body:" << std::endl;
	//		std::cout << body << std::endl;
	//	}
	//});
	//
	//auto wide = AppFrame::CharacterCodeConvert::ConvertUTF8ToWide(curl->GetBody());
	//auto shiftJisText = AppFrame::CharacterCodeConvert::ConvertWideToShiftJIS(wide);
	//_testCard.tips = shiftJisText;

	auto test = std::make_unique<testUI>();
	this->GetUICanvasServer()->Add(std::move(test));

	return false;
}

bool Flavor::ModeTest::Terminate()
{
	return false;
}

bool Flavor::ModeTest::Update(InputManager& input)
{
	ModeBase::Update(input);
	return false;
}

bool Flavor::ModeTest::Render()
{
	std::stringstream ss;
	ss << _testCard.name << "\n";
	ss << _testCard.flavorText << "\n";
	DrawString(0, 0, ss.str().c_str(), AppFrame::Color::White);
	ModeBase::Render();
	return false;
}

bool Flavor::ModeTest::Debug()
{
	ModeBase::Debug();
	return false;
}
