#include "stdafx.h"
#include "HtmlDecode.h"


static const std::unordered_map<std::string, std::string> KEYS = { 
	{ "&quot;", "\"" },
	{ "&apos;", "'" },
	{ "&lt;", "<" },
	{ "&gt;", ">" },
	{ "&amp;", "&" } 
};

std::string ReplaceAll(const std::string &str, const std::string &search, const std::string &replace)
{
	if (search.empty())
	{
		return str;
	}
	size_t pos = 0;
	std::string result;
	for (size_t foundPos = 0; (foundPos = str.find(search, pos)) != std::string::npos; pos = foundPos + search.length())
	{
		result.append(str, pos, foundPos - pos);
		result.append(replace);
	}
	return result.append(str.substr(pos));
}

std::string HtmlDecode(const std::string &html)
{
	std::string result = html;

	for (auto &key : KEYS)
	{
		result = ReplaceAll(result, key.first, key.second);
	}

	return result;
}

