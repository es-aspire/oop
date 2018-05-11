#pragma once

#include "TVSet.h"
#include <functional>
#include <tuple>

class CTVSetController
{
public:
	CTVSetController(CTVSet& tvSet, std::istream& input, std::ostream& output);
	bool HandleCommand();

private:
	void Info(std::istream& args) const;
	void TurnOn(std::istream& args);
	void TurnOff(std::istream& args);
	void SelectChannel(std::istream& args);
	void SelectPreviousChannel(std::istream& args);
	void SelectChannelByName(std::istream& args);
	void SetChannelName(std::istream& args);
	void DeleteChannelName(std::istream& args);

private:
	using ActionMap = std::map<std::string, std::function<void(std::istream& args)>>;

	const ActionMap m_actionMap;

	std::istream& m_input;
	std::ostream& m_output;
	CTVSet& m_tvSet;
};
