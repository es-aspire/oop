#include "stdafx.h"
#include "ParseURL.h"

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP
};

namespace
{
	Protocol GetProtocol(const std::string &protocolStr)
	{
		std::string lowerProtocolStr = protocolStr;

		std::transform(lowerProtocolStr.begin(), lowerProtocolStr.end(),
			lowerProtocolStr.begin(), ::tolower);

		Protocol protocol;

		if (lowerProtocolStr == "http")
		{
			protocol = Protocol::HTTP;
		}
		else if (lowerProtocolStr == "https")
		{
			protocol = Protocol::HTTPS;
		}
		else if (lowerProtocolStr == "ftp")
		{
			protocol = Protocol::FTP;
		}

		return protocol;
	}

	int StringToInt(const std::string &str, bool &wasError)
	{
		int result = 0;
		try
		{
			result = stoi(str);
		}
		catch (const std::invalid_argument &err)
		{
			wasError = true;
			std::cerr << err.what() << "\n";
		}
		catch (std::out_of_range &err)
		{
			wasError = true;
			std::cerr << "Overflow: " << err.what() << "\n";
		}
		return result;
	}

	constexpr int DEFAULT_HTTP_PORT = 80;
	constexpr int DEFAULT_HTTPS_PORT = 443;
	constexpr int DEFAULT_FTP_PORT = 21;

	int GetDefaultProtocolPort(const Protocol &protocol)
	{
		switch (protocol)
		{
		case Protocol::HTTP:
			return DEFAULT_HTTP_PORT;
		case Protocol::HTTPS:
			return DEFAULT_HTTPS_PORT;
		case Protocol::FTP:
			return DEFAULT_FTP_PORT;
		default:
			return 0;
		}
	}

	int GetPort(const Protocol &protocol, const std::string &portStr)
	{
		int port = 0;
		bool wasError = false;

		if (portStr.empty())
		{
			port = GetDefaultProtocolPort(protocol);
		}
		else
		{
			port = StringToInt(portStr, wasError);
		}

		return !wasError ? port : 0;
	}

	bool ParsePortStr(int &port, const Protocol &protocol, const std::string &portStr)
	{
		constexpr int MIN_NUMBER_PORT = 1;
		constexpr int MAX_NUMBER_PORT = 65535;
		port = GetPort(protocol, portStr);

		if (port < MIN_NUMBER_PORT || port > MAX_NUMBER_PORT)
		{
			return false;
		}

		return true;
	}
}

bool ReadURL(std::istream &input, URL &url)
{
	return static_cast<bool>(std::getline(input, url.urlStr));
}

bool ParseURL(std::string const &url, Protocol &protocol, int &port, std::string &host, std::string &document)
{
	if (url.empty())
	{
		return false;
	}

	constexpr char REGULAR_EXPRESSION[] = "^(https?|ftp)://([A-Za-z0-9-.]+)(:?([0-9]+))?(/(.*))?$";
	std::regex pattern(REGULAR_EXPRESSION, std::regex_constants::icase);
	std::smatch match;

	if (!std::regex_match(url, match, pattern))
	{
		return false;
	}

	protocol = GetProtocol(match[1]);
	host = match[2];
	if (!ParsePortStr(port, protocol, match[4]))
	{
		return false;
	}
	document = match[6];

	return true;
}

void PrintURLData(std::ostream &output, const URL &url)
{
	output << url.urlStr
		<< "\nHOST: " << url.host
		<< "\nPORT: " << url.port
		<< "\nDOC: " << url.document << "\n";
}