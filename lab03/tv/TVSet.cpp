#include "stdafx.h"
#include "TVSet.h"

namespace
{
std::string Trim(const std::string& str)
{
	if (str.empty() || (str.size() == 1 && str[0] == ' '))
	{
		return "";
	}
	constexpr char BLANK_SYMBOL = ' ';
	size_t beginPos = str.find_first_not_of(BLANK_SYMBOL);
	if (beginPos == std::string::npos)
	{
		beginPos = 0;
	}
	size_t endPos = str.find_last_not_of(BLANK_SYMBOL);
	if (endPos == std::string::npos)
	{
		endPos = str.size() - 1;
	}
	std::string result = str.substr(beginPos, endPos - beginPos + 1);

	return result;
}

std::string RemoveExtraBlanks(const std::string& str)
{
	std::regex pattern(" +");
	std::string result = std::regex_replace(str, pattern, " ");
	return Trim(result);
}
} // namespace

CTVSet::CTVSet()
	: m_isTrunedOn(false)
	, m_selectedChannel(1)
	, m_prevChannel(1){};

bool CTVSet::TurnOn()
{
	if (m_isTrunedOn)
	{
		return false;
	}

	m_isTrunedOn = true;

	return true;
}

bool CTVSet::TurnOff()
{
	if (!m_isTrunedOn)
	{
		return false;
	}

	m_isTrunedOn = false;

	return true;
}

bool CTVSet::SelectChannel(int channel)
{
	if (!m_isTrunedOn || !IsValidChannel(channel))
	{
		return false;
	}

	m_prevChannel = m_selectedChannel;
	m_selectedChannel = channel;

	return true;
}

bool CTVSet::SelectChannel(const std::string& channelName)
{
	if (!m_isTrunedOn)
	{
		return false;
	}

	int channel = 0;
	if (!FoundByName(channelName, channel))
	{
		return false;
	}

	m_prevChannel = m_selectedChannel;
	m_selectedChannel = channel;

	return true;
}

bool CTVSet::IsTurnedOn() const
{
	return m_isTrunedOn;
}

int CTVSet::GetSelectedChannel() const
{
	return m_isTrunedOn ? m_selectedChannel : 0;
}

bool CTVSet::SelectPreviousChannel()
{
	if (!m_isTrunedOn)
	{
		return false;
	}

	std::swap(m_selectedChannel, m_prevChannel);

	return true;
}

bool CTVSet::SetChannelName(int channel, const std::string& channelName)
{
	std::string trimmedChannelName = RemoveExtraBlanks(channelName);

	if (!m_isTrunedOn || trimmedChannelName.empty() || !IsValidChannel(channel))
	{
		return false;
	}

	RemoveChannelByName(trimmedChannelName);

	if (IsChannelNameExist(channel))
	{
		m_channelsData.at(channel) = trimmedChannelName;
	}
	else
	{
		m_channelsData.emplace(channel, trimmedChannelName);
	}

	return true;
}

bool CTVSet::DeleteChannelName(const std::string& channelName)
{
	return m_isTrunedOn ? RemoveChannelByName(channelName) : false;
}

bool CTVSet::GetChannelName(int channel, std::string& channelName) const
{
	if (!m_isTrunedOn || !IsValidChannel(channel) || !IsChannelNameExist(channel))
	{
		return false;
	}

	channelName = m_channelsData.at(channel);

	return true;
}

bool CTVSet::GetChannelByName(const std::string& channelName, int& channel) const
{
	return m_isTrunedOn ? FoundByName(channelName, channel) : false;
}

ChannelsData CTVSet::GetAllChannelWithName() const
{
	return m_channelsData;
}

bool CTVSet::RemoveChannelByName(const std::string& channelName)
{
	int channel = 0;
	if (!FoundByName(channelName, channel))
	{
		return false;
	}

	RemoveChannelByKey(channel);

	return true;
}

void CTVSet::RemoveChannelByKey(int channel)
{
	m_channelsData.erase(channel);
}

bool CTVSet::FoundByName(const std::string& channelName, int& channel) const
{
	auto isEqual = [&channelName](const std::pair<int, std::string>& element) {
		return element.second == channelName;
	};

	auto it = std::find_if(m_channelsData.begin(), m_channelsData.end(), isEqual);

	if (it != std::end(m_channelsData))
	{
		channel = it->first;

		return true;
	}

	return false;
}

bool CTVSet::IsValidChannel(int channel) const
{
	return (channel >= 1 && channel <= 99);
}

bool CTVSet::IsChannelNameExist(int channel) const
{
	return m_channelsData.find(channel) != m_channelsData.end();
}
