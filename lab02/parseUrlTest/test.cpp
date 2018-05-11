#include "pch.h"
#include "ParseUrl.cpp"

TEST(GetProtocolTest, set_http_in_lower_case)
{
	std::string protocolStr = "http";

	EXPECT_EQ(GetProtocol(protocolStr), Protocol::HTTP);
}

TEST(GetProtocolTest, set_http_in_upper_case)
{
	std::string protocolStr = "HTTP";

	EXPECT_EQ(GetProtocol(protocolStr), Protocol::HTTP);
}

TEST(GetProtocolTest, set_http_in_mixed_case)
{
	std::string protocolStr = "HtTp";

	EXPECT_EQ(GetProtocol(protocolStr), Protocol::HTTP);
}

TEST(GetProtocolTest, set_https)
{
	std::string protocolStr = "https";

	EXPECT_EQ(GetProtocol(protocolStr), Protocol::HTTPS);
}

TEST(GetProtocolTest, set_ftp)
{
	std::string protocolStr = "ftp";

	EXPECT_EQ(GetProtocol(protocolStr), Protocol::FTP);
}

TEST(GetDefaultPortProtocol, get_default_port_http)
{
	Protocol protocol = Protocol::HTTP;

	EXPECT_EQ(GetDefaultProtocolPort(protocol), DEFAULT_HTTP_PORT);
}

TEST(GetDefaultPortProtocol, get_default_port_https)
{
	Protocol protocol = Protocol::HTTPS;

	EXPECT_EQ(GetDefaultProtocolPort(protocol), DEFAULT_HTTPS_PORT);
}

TEST(GetDefaultPortProtocol, get_default_port_ftp)
{
	Protocol protocol = Protocol::FTP;

	EXPECT_EQ(GetDefaultProtocolPort(protocol), DEFAULT_FTP_PORT);
}

void ParseURLTest(const std::string &urlStr, const URL &checkUrl, bool expectedResult)
{
	URL url;

	EXPECT_EQ(ParseURL(urlStr, url.protocol, url.port, url.host, url.document),
		expectedResult);

	if (expectedResult)
	{
		EXPECT_EQ(url.protocol, checkUrl.protocol);
		EXPECT_EQ(url.port, checkUrl.port);
		EXPECT_EQ(url.host, checkUrl.host);
		EXPECT_EQ(url.document, checkUrl.document);
	}
}

TEST(ParseUrlTest, empty_url)
{
	URL checkUrl;

	ParseURLTest("", checkUrl, false);
}

TEST(ParseUrlTest, only_invalid_protocol)
{
	URL checkUrl;

	ParseURLTest("qwerty", checkUrl, false);
}

TEST(ParseUrlTest, only_valid_protocol)
{
	URL checkUrl;

	ParseURLTest("http", checkUrl, false);
}

TEST(ParseUrlTest, no_colon_after_protocol)
{
	URL checkUrl;

	ParseURLTest("https//google.com", checkUrl, false);
}

TEST(ParseUrlTest, one_slashe_after_protocol)
{
	URL checkUrl;

	ParseURLTest("http:/google.com", checkUrl, false);
}

TEST(ParseUrlTest, invalid_character_on_the_url)
{
	URL checkUrl;

	ParseURLTest("http://~!@$$%^", checkUrl, false);
}

TEST(ParseUrlTest, http_and_valid_host)
{
	URL checkUrl;
	checkUrl.protocol = Protocol::HTTP;
	checkUrl.port = DEFAULT_HTTP_PORT;
	checkUrl.host = "google.com";
	checkUrl.document = "";

	ParseURLTest("http://google.com", checkUrl, true);
}

TEST(ParseUrlTest, https_and_valid_host)
{
	URL checkUrl;
	checkUrl.protocol = Protocol::HTTPS;
	checkUrl.port = DEFAULT_HTTPS_PORT;
	checkUrl.host = "google.com";
	checkUrl.document = "";

	ParseURLTest("https://google.com", checkUrl, true);
}

TEST(ParseUrlTest, ftp_and_valid_host)
{
	URL checkUrl;
	checkUrl.protocol = Protocol::FTP;
	checkUrl.port = DEFAULT_FTP_PORT;
	checkUrl.host = "google.com";
	checkUrl.document = "";

	ParseURLTest("ftp://google.com", checkUrl, true);
}

TEST(ParseUrlTest, mixed_protocol_register)
{
	URL checkUrl;
	checkUrl.protocol = Protocol::HTTP;
	checkUrl.port = DEFAULT_HTTP_PORT;
	checkUrl.host = "google.com";
	checkUrl.document = "";

	ParseURLTest("HtTp://google.com", checkUrl, true);
}

TEST(ParseUrlTest, port_is_equal_min_valid_number_minus_1)
{
	URL checkUrl;

	ParseURLTest("HtTp://google.com:0", checkUrl, false);
}

TEST(ParseUrlTest, port_is_equal_min_valid_number)
{
	URL checkUrl;
	checkUrl.protocol = Protocol::HTTP;
	checkUrl.port = 1;
	checkUrl.host = "google.com";
	checkUrl.document = "";

	ParseURLTest("HtTp://google.com:1", checkUrl, true);
}

TEST(ParseUrlTest, port_is_equal_4076)
{
	URL checkUrl;
	checkUrl.protocol = Protocol::FTP;
	checkUrl.port = 4076;
	checkUrl.host = "google.com";
	checkUrl.document = "";

	ParseURLTest("FtP://google.com:4076", checkUrl, true);
}

TEST(ParseUrlTest, port_is_more_port_is_equal_19768)
{
	URL checkUrl;
	checkUrl.protocol = Protocol::FTP;
	checkUrl.port = 19768;
	checkUrl.host = "google.com";
	checkUrl.document = "";

	ParseURLTest("FtP://google.com:19768", checkUrl, true);
}

TEST(ParseUrlTest, port_is_equal_max_valid_port_number)
{
	URL checkUrl;
	checkUrl.protocol = Protocol::HTTP;
	checkUrl.port = 65535;
	checkUrl.host = "google.com";
	checkUrl.document = "";

	ParseURLTest("HtTp://google.com:65535", checkUrl, true);
}

TEST(ParseUrlTest, port_is_equal_max_valid_port_number_plus_1)
{
	URL checkUrl;

	ParseURLTest("HtTp://google.com:65536", checkUrl, false);
}

TEST(ParseUrlTest, valid_url)
{
	URL checkUrl;
	checkUrl.protocol = Protocol::HTTP;
	checkUrl.port = 80;
	checkUrl.host = "www.mysite.com";
	checkUrl.document = "docs/document1.html?page=30&lang=en#title";

	ParseURLTest("http://www.mysite.com/docs/document1.html?page=30&lang=en#title",
		checkUrl, true);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}