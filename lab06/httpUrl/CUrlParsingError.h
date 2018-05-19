#pragma once

class CUrlParsingError : public std::invalid_argument
{
public:
	using Base = std::invalid_argument;

	CUrlParsingError(const std::string& message)
		: Base(message.c_str())
	{
	}

	CUrlParsingError(const char *message)
		: Base(message)
	{
	}
};