#pragma once

using ChannelsData = std::map<int, std::string>;

class CTVSet
{
public:
	CTVSet();

	bool TurnOn();
	bool TurnOff();

	bool SelectChannel(int channel);
	bool SelectChannel(const std::string& channelName);
	bool IsTurnedOn() const;
	int GetSelectedChannel() const;
	bool SelectPreviousChannel();
	bool SetChannelName(int channel, const std::string& channelName);
	bool DeleteChannelName(const std::string& channelName);
	bool GetChannelName(int channel, std::string& channelName) const;
	bool GetChannelByName(const std::string& channelName, int& channel) const;
	ChannelsData GetAllChannelWithName() const;

private:
	bool RemoveChannelByName(const std::string& channelName);
	void RemoveChannelByKey(int channel);
	bool FoundByName(const std::string& channelName, int& channel) const;
	bool IsValidChannel(int channel) const;
	bool IsChannelNameExist(int channel) const;

private:
	bool m_isTrunedOn;
	int m_selectedChannel;
	int m_prevChannel;

	ChannelsData m_channelsData;
};
