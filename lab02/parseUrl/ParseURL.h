#pragma once

enum class Protocol;

struct URL
{
	std::string urlStr;
	Protocol protocol;
	int port = 0;
	std::string host;
	std::string document;
};

bool ReadURL(std::istream &input, URL &url);
bool ParseURL(std::string const& url, Protocol &protocol, int &port, 
	std::string &host, std::string &document);
void PrintURLData(std::ostream &output, const URL &url);