#include "stdafx.h"
#include "TVSetController.h"

namespace
{
bool StringToInt(const std::string& str, int& number)
{
	try
	{
		number = stoi(str);
		return true;
	}
	catch (const std::invalid_argument& e)
	{
		std::cerr << e.what() << "\n";
		return false;
	}
	catch (const std::out_of_range& e)
	{
		std::cerr << e.what() << "\n";
		return false;
	}
}

std::ostream & operator << (std::ostream& output, const ChannelsData& channelsData)
{
	for (const auto &channelData : channelsData)
	{
		output << channelData.first << " - " << channelData.second << "\n";
	}

	return output;
}

} // namespace

CTVSetController::CTVSetController(CTVSet& tvSet, std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_tvSet(tvSet)
	, m_actionMap({ { "Info", std::bind(&CTVSetController::Info, this, std::placeholders::_1) },
		  { "TurnOn", std::bind(&CTVSetController::TurnOn, this, std::placeholders::_1) },
		  { "TurnOff", std::bind(&CTVSetController::TurnOff, this, std::placeholders::_1) },
		  { "SelectChannel", std::bind(&CTVSetController::SelectChannel, this, std::placeholders::_1) },
		  { "SelectPrev", std::bind(&CTVSetController::SelectPreviousChannel, this, std::placeholders::_1) },
		  { "SelectChannelByName", std::bind(&CTVSetController::SelectChannelByName, this, std::placeholders::_1) },
		  { "SetChannelName", std::bind(&CTVSetController::SetChannelName, this, std::placeholders::_1) },
		  { "DeleteChannelName", std::bind(&CTVSetController::DeleteChannelName, this, std::placeholders::_1) } })
{
}

bool CTVSetController::HandleCommand()
{
	std::string commandLine;
	std::getline(m_input, commandLine);
	std::istringstream strm(commandLine);

	std::string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		it->second(strm);
		return true;
	}

	return false;
}

void CTVSetController::Info(std::istream& args) const
{
	int channel = m_tvSet.GetSelectedChannel();
	std::string channelName;

	m_output << "TV info: \n"
			 << " - is turned: " << (m_tvSet.IsTurnedOn() ? "on" : "off") << "\n"
			 << " - selected channel: " << channel << (m_tvSet.GetChannelName(channel, channelName) ? " - " + channelName : "") << "\n";

	ChannelsData channelsData = m_tvSet.GetAllChannelWithName();

	if (!channelsData.empty())
	{
		m_output << " - channels with name: \n";
		m_output << channelsData;
	}
}

void CTVSetController::TurnOn(std::istream& args)
{
	m_output << "TV " << (m_tvSet.TurnOn() ? "is turned on" : "cann't be turned on") << "\n";
}

void CTVSetController::TurnOff(std::istream& args)
{
	m_output << "TV " << (m_tvSet.TurnOff() ? "is turned off" : "cann't be turned off") << "\n";
}

void CTVSetController::SelectChannel(std::istream& args)
{
	std::string str;
	args >> str;

	if (str.empty())
	{
		m_output << "channel can not be empty\n";
	}
	else
	{
		int channel = 0;

		if (!StringToInt(str, channel))
		{
			m_output << "channel should be number\n";
		}
		else if (m_tvSet.SelectChannel(channel))
		{
			m_output << "Select channel success\n";
		}
		else
		{
			m_output << "Select channel failed\n";
		}
	}
}

void CTVSetController::SelectChannelByName(std::istream& args)
{
	std::string channelName;
	args >> channelName;

	if (channelName.empty())
	{
		m_output << "channel name can not be empty\n";
	}
	else if (!m_tvSet.SelectChannel(channelName))
	{
		m_output << "Select channel failed\n";
	}
	else
	{
		m_output << "Select channel success\n";
	}
}

void CTVSetController::SelectPreviousChannel(std::istream& args)
{
	m_output << "selected previous channel " << (m_tvSet.SelectPreviousChannel() ? "success" : "failed") << "\n";
}

void CTVSetController::SetChannelName(std::istream& args)
{
	std::string channelStr;
	args >> channelStr;
	int channel = 0;
	if (!StringToInt(channelStr, channel))
	{
		m_output << "channel should be number\n";
	}

	std::string channelName;
	args >> channelName;
	if (channelName.empty())
	{
		m_output << "channel name can not be empty\n";
	}
	else
	{
		m_output << "set channel name: '" << channelName << "' to '" << channel << " '" << (m_tvSet.SetChannelName(channel, channelName) ? "success" : "failed") << "\n";
	}
}

void CTVSetController::DeleteChannelName(std::istream& args)
{
	std::string channelName;
	args >> channelName;

	if (channelName.empty())
	{
		m_output << "channel name can not be empty\n";
	}
	else if (!m_tvSet.DeleteChannelName(channelName))
	{
		m_output << "failed delete channel name '" << channelName << "'\n";
	}
	else
	{
		m_output << "success delete channel name '" << channelName << "'\n";
	}
}
