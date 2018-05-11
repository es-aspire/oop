#include "stdafx.h"
#include "../tv/TVSet.cpp"


TEST_CASE("Utills test")
{
	GIVEN("trim test")
	{
		WHEN("string without whitespace symbol at the beginning and at the end")
		{
			REQUIRE(Trim("hello world") == "hello world");
		}

		AND_WHEN("string without whitespace symbol at the beginning and with at the end")
		{
			REQUIRE(Trim("hello world     ") == "hello world");
		}
		
		AND_WHEN("string with whitespace symbol at the beginning and without at the end")
		{
			REQUIRE(Trim("     hello world") == "hello world");
		}
	}

	GIVEN("Remove extra blanks")
	{
		WHEN("string with length 1 and with blank symbol")
		{
			REQUIRE(RemoveExtraBlanks(" ") == "");
		}

		AND_WHEN("string with length 1 and with alphanumeric symbol")
		{
			REQUIRE(RemoveExtraBlanks("w") == "w");
		}

		AND_WHEN("string without extra blanks")
		{
			REQUIRE(RemoveExtraBlanks("hello world") == "hello world");
		}

		AND_WHEN("string with extra blanks at the beginning")
		{
			REQUIRE(RemoveExtraBlanks("    hello world") == "hello world");
		}

		AND_WHEN("string with extra blanks at the center")
		{
			REQUIRE(RemoveExtraBlanks("hello      world") == "hello world");
		}
		
		AND_WHEN("string with extra blanks at the ending")
		{
			REQUIRE(RemoveExtraBlanks("hello world     ") == "hello world");
		}

		AND_WHEN("string contrains only blank symbol")
		{
			REQUIRE(RemoveExtraBlanks("      ") == "");
		}
	}
}

namespace
{

void SelectChannelTest(CTVSet& tvSet, int selectedChannel, bool success, int expectedChannel)
{
	REQUIRE(tvSet.SelectChannel(selectedChannel) == success);
	REQUIRE(tvSet.GetSelectedChannel() == expectedChannel);
}

void SetChannelNameTest(CTVSet& tvSet, int channel, const std::string& channelName, ChannelsData expectedChannelsData, bool isSuccess)
{
	REQUIRE(tvSet.SetChannelName(channel, channelName) == isSuccess);
	REQUIRE(tvSet.GetAllChannelWithName() == expectedChannelsData);
}

void SelectChannelByNameTest(CTVSet& tvSet, const std::string& selectedChannelName, bool success, int expectedChannel)
{
	REQUIRE(tvSet.SelectChannel(selectedChannelName) == success);
	REQUIRE(tvSet.GetSelectedChannel() == expectedChannel);
}

} // namespace

TEST_CASE("TVSet")
{
	CTVSet tvSet;

	GIVEN("tvSet")
	{
		WHEN("Initially")
		{
			THEN("tv is turned off and channel 0")
			{
				REQUIRE(tvSet.IsTurnedOn() == false);
				REQUIRE(tvSet.GetSelectedChannel() == 0);
			}

			AND_WHEN("is turned off")
			{
				THEN("does not allow to turn off")
				{
					REQUIRE(!tvSet.TurnOff());
					REQUIRE(tvSet.IsTurnedOn() == false);
				}

				AND_THEN("does not allow to change a channel")
				{
					SelectChannelTest(tvSet, 0, false, 0);
					SelectChannelTest(tvSet, 1, false, 0);
					SelectChannelTest(tvSet, 2, false, 0);
					SelectChannelTest(tvSet, 45, false, 0);
					SelectChannelTest(tvSet, 99, false, 0);
					SelectChannelTest(tvSet, 100, false, 0);
				}

				AND_THEN("does not allow to set channel name")
				{
					REQUIRE(!tvSet.SetChannelName(1, "dct"));
					REQUIRE(tvSet.GetAllChannelWithName().empty());
				}

				AND_THEN("does not allow to delete channel name")
				{
					REQUIRE(!tvSet.DeleteChannelName("dct"));
					REQUIRE(tvSet.GetAllChannelWithName().empty());
				}

				AND_THEN("does not allow to get channel name")
				{
					std::string channelName;
					REQUIRE(!tvSet.GetChannelName(4, channelName));
					REQUIRE(channelName.empty());
				}

				AND_THEN("does not allow to get channel by name")
				{
					int channel = 0;
					REQUIRE(!tvSet.GetChannelByName("dct", channel));
					REQUIRE(channel == 0);
				}

				AND_THEN("does not allow to select previous channel")
				{
					REQUIRE(!tvSet.SelectPreviousChannel());
					REQUIRE(tvSet.GetSelectedChannel() == 0);
				}

				AND_THEN("does not allow to select channel by name")
				{
					REQUIRE(!tvSet.SelectPreviousChannel());
					REQUIRE(tvSet.GetSelectedChannel() == 0);
				}

				AND_THEN("allow to turn on")
				{
					REQUIRE(tvSet.TurnOn());
					REQUIRE(tvSet.IsTurnedOn() == true);
				}
			}

			AND_WHEN("is turned on")
			{
				REQUIRE(tvSet.TurnOn());
				REQUIRE(tvSet.IsTurnedOn());
				
				WHEN("the first time")
				{
					THEN("selected channel is a 1")
					{
						REQUIRE(tvSet.GetSelectedChannel() == 1);
					}
				}

				THEN("does not allow to turn on")
				{
					REQUIRE(!tvSet.TurnOn());
					REQUIRE(tvSet.IsTurnedOn() == true);
				}

				THEN("allow turn off")
				{
					REQUIRE(tvSet.TurnOff());
					REQUIRE(tvSet.IsTurnedOn() == false);
				}

				THEN("allow to channge valid channel")
				{
					SelectChannelTest(tvSet, 1, true, 1);
					SelectChannelTest(tvSet, 2, true, 2);
					SelectChannelTest(tvSet, 45, true, 45);
					SelectChannelTest(tvSet, 65, true, 65);
					SelectChannelTest(tvSet, 35, true, 35);
					SelectChannelTest(tvSet, 99, true, 99);
				}

				AND_THEN("does not allow to set channel name")
				{
					WHEN("channel name is empty string")
					{
						SetChannelNameTest(tvSet, 15, "", { }, false);
					}

					AND_WHEN("channel name is contains only blank symbol")
					{
						SetChannelNameTest(tvSet, 15, "      ", {}, false);
					}
				}

				AND_THEN("allow to set channel name")
				{
					WHEN("channel name string contains blank symbol at beginning")
					{
						ChannelsData channelsData = { { 15, "dct" } };
						SetChannelNameTest(tvSet, 15, "      dct", channelsData, true);
					}

					AND_WHEN("channel name string contains blank symbol at ending")
					{
						ChannelsData channelsData = { { 15, "dct" } };
						SetChannelNameTest(tvSet, 15, "dct      ", channelsData, true);
					}

					AND_WHEN("channel name string contains blank symbol at middle")
					{
						ChannelsData channelsData = { { 15, "hello world" } };
						SetChannelNameTest(tvSet, 15, "  hello    world  ", channelsData, true);
					}

					AND_WHEN("valid channel name")
					{
						REQUIRE(tvSet.SetChannelName(1, "dct"));
						REQUIRE(tvSet.SetChannelName(2, "Discovery"));
						REQUIRE(tvSet.SetChannelName(3, "matchtv"));

						THEN("allow to redefine exist channel name")
						{
							ChannelsData channelsData = { { 1, "dct" }, { 2, "Discovery" }, { 3, "nhl" } };
							SetChannelNameTest(tvSet, 3, "nhl", channelsData, true);
						}

						AND_THEN("allow to identify exist channel name to other channel")
						{
							ChannelsData channelsData = { { 3, "dct" }, { 2, "Discovery" }};
							SetChannelNameTest(tvSet, 3, "dct", channelsData, true);
						}
					}
				}

				AND_THEN("allow to delete channel name")
				{
					REQUIRE(tvSet.SetChannelName(1, "dct"));
					REQUIRE(tvSet.DeleteChannelName("dct"));
					REQUIRE(tvSet.GetAllChannelWithName().empty());
				}

				AND_WHEN("channel name exist")
				{
					REQUIRE(tvSet.SetChannelName(1, "dct"));
					REQUIRE(tvSet.SetChannelName(2, "Discovery"));
					REQUIRE(tvSet.SetChannelName(3, "matchtv"));

					AND_THEN("allow to select exist channel name")
					{
						SelectChannelByNameTest(tvSet, "dct", true, 1);
					}

					AND_THEN("allow to get the name of the channel by channel number")
					{
						std::string channelName;
						REQUIRE(tvSet.GetChannelName(1, channelName));
						REQUIRE(channelName == "dct");
					}

					AND_THEN("allow to get the channel number by the name of the channel")
					{
						int channel = 0;
						REQUIRE(tvSet.GetChannelByName("dct", channel));
						REQUIRE(channel == 1);
					}
				} 

				AND_WHEN("channel name not exist")
				{
					REQUIRE(tvSet.SetChannelName(1, "dct"));
					REQUIRE(tvSet.SetChannelName(2, "Discovery"));
					REQUIRE(tvSet.SetChannelName(3, "matchtv"));

					AND_THEN("does not allow to select not exist channel name")
					{
						SelectChannelByNameTest(tvSet, "nba", false, 1);
					}

					AND_THEN("does not allow to learn the name of the channel by channel number")
					{
						std::string channelName;
						REQUIRE(!tvSet.GetChannelName(5, channelName));
						REQUIRE(channelName == "");
					}

					AND_THEN("does not allow to learn the channel number by the name of the channel")
					{
						int channel = 0;
						REQUIRE(!tvSet.GetChannelByName("nba", channel));
						REQUIRE(channel == 0);
					}
				}
				
				AND_THEN("does not allow to change invalid channel")
				{
					SelectChannelTest(tvSet, 1000, false, 1);
					SelectChannelTest(tvSet, 100, false, 1);
					SelectChannelTest(tvSet, 0, false, 1);
					SelectChannelTest(tvSet, -1, false, 1);
				}

				AND_WHEN("turn on the TV turns off")
				{
					SelectChannelTest(tvSet, 45, true, 45);

					REQUIRE(tvSet.TurnOff());
					REQUIRE(!tvSet.IsTurnedOn());
					REQUIRE(tvSet.TurnOn());
					REQUIRE(tvSet.IsTurnedOn());

					AND_THEN("the channel on which it was previously turned off")
					{
						REQUIRE(tvSet.GetSelectedChannel() == 45);
					}
				}

				AND_THEN("allow selected previous channel")
				{
					SelectChannelTest(tvSet, 45, true, 45);
					SelectChannelTest(tvSet, 67, true, 67);
					SelectChannelTest(tvSet, 5, true, 5);
					REQUIRE(tvSet.SelectPreviousChannel());
					REQUIRE(tvSet.GetSelectedChannel() == 67);
				}
			}
		}
	}
}
