#include "StringFitting.h"
#include "appframe.h"
#include <vector>

std::string Flavor::StringFitting::InsertLineBreak(std::string text, int characterNumber)
{
	if (text.empty()) {
		return text;
	}

	//“K‹X‰üs
	int countByte{ 0 };
	std::vector<int> insertIndex;
	for (int i = 0; i < static_cast<int>(text.size());) {
		int checkByte = AppFrame::ShiftJISChecker::Check(text.at(i));
		countByte += checkByte;
		i += checkByte;
		if (countByte > characterNumber) {
			insertIndex.emplace_back(i);
			countByte = 0;
		}
	}
	std::string result{ text };
	for (auto itr = insertIndex.rbegin(); itr != insertIndex.rend(); ++itr) {
		result.insert((*itr), "\n");
	}
	if (result.back() != '\n') {
		result.insert(result.end(), '\n');
	}
	return result;
}
