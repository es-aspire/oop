#include "stdafx.h"
#include "../httpUrl/CHttpUrl.cpp"
#include "../httpUrl/CUrlParsingError.h"

TEST_CASE("HttpUrlTest")
{
}

bool IsEqualProtocol(Protocol lhs, Protocol rhs)
{
	return static_cast<unsigned short>(lhs) == static_cast<unsigned short>(rhs);
}

void VerifyWithoutPort(std::string const& domain, std::string const& doc, Protocol protocol, unsigned short expectedPort, std::string const& expectedUrl)
{
	try
	{
		CHttpUrl url(domain, doc, protocol);
		REQUIRE(url.GetURL() == expectedUrl);
		REQUIRE(url.GetDomain() == domain);
		REQUIRE(url.GetDocument() == (doc.empty() ? "/" : doc));
		REQUIRE(url.GetProtocol() == protocol);
		REQUIRE(url.GetPort() == expectedPort);
	}
	catch (CUrlParsingError)
	{
		REQUIRE(true);
	}
	catch (...)
	{
		REQUIRE(false);
	}
}

void VerifyWithPort(std::string const& domain, std::string const& doc, Protocol protocol, unsigned short port, std::string const& expectedUrl)
{
	try
	{
		CHttpUrl url(domain, doc, protocol, port);
		REQUIRE(url.GetURL() == expectedUrl);
		REQUIRE(url.GetDomain() == domain);
		REQUIRE(url.GetDocument() == (doc.empty() ? "/" : doc));
		REQUIRE(url.GetProtocol() == protocol);
		REQUIRE(url.GetPort() == port);
	}
	catch (CUrlParsingError)
	{
		REQUIRE(true);
	}
	catch (...)
	{
		REQUIRE(false);
	}
}

void VerifyWithUrl(std::string const& url, std::string const& expectedDomain, std::string const& expectedDoc, Protocol expectedProtocol, unsigned short expectedPort, std::string const& expectedUrl)
{
	try
	{
		CHttpUrl url(url);
		REQUIRE(url.GetURL() == expectedUrl);
		REQUIRE(url.GetDomain() == expectedDomain);
		REQUIRE(url.GetDocument() == (expectedDoc.empty() ? "/" : expectedDoc));
		REQUIRE(url.GetProtocol() == expectedProtocol);
		REQUIRE(url.GetPort() == expectedPort);
	}
	catch (CUrlParsingError)
	{
		REQUIRE(true);
	}
	catch (...)
	{
		REQUIRE(false);
	}
}

TEST_CASE("HttUrlTest")
{
	GIVEN("INitially")
	{
		WHEN("domain, document, protocol and port passed to CHttpUrl construct")
		{
			AND_WHEN("domain empty")
			{
				THEN("throw CUrllParsingError")
				{
					REQUIRE_THROWS_AS(CHttpUrl("", "/doc", Protocol::HTTPS), CUrlParsingError);
				}
			}

			AND_WHEN("domain contatin invalid character")
			{
				THEN("throw CUrllParsingError")
				{
					REQUIRE_THROWS_AS(CHttpUrl("#$@#", "/doc"), CUrlParsingError);
				}
			}

			AND_WHEN("valid domain and invalid port range")
			{
				REQUIRE_THROWS_AS(CHttpUrl("ya.ru:0", "/doc", Protocol::HTTPS), CUrlParsingError);
				REQUIRE_THROWS_AS(CHttpUrl("ya.ru:0", "/doc", Protocol::HTTPS), CUrlParsingError);
			}

			AND_WHEN("domain contain valid character")
			{
				AND_WHEN("valid port range")
				{
					THEN("construct CHttpUrl")
					{
						VerifyWithoutPort("google.com", "/doc", Protocol::HTTP, 80, "http://google.com/doc");
						VerifyWithoutPort("google.com", "", Protocol::HTTP, 80, "http://google.com/");
						VerifyWithoutPort("google.com", "/doc", Protocol::HTTPS, 443, "https://google.com/doc");
						VerifyWithoutPort("google.com", "", Protocol::HTTPS, 443, "https://google.com/");
					}
				}
			}
		}

		WHEN("domain, document, protocol and port to CHttpUrl construct")
		{
			AND_WHEN("domain is empty")
			{
				REQUIRE_THROWS_AS(CHttpUrl("", "", Protocol::HTTP, 1), CUrlParsingError);
			}

			AND_WHEN("domain contain of unresolved character")
			{
				REQUIRE_THROWS_AS(CHttpUrl("!@#", "", Protocol::HTTP, 1), CUrlParsingError);
			}

			AND_WHEN("domain contain only valid character")
			{
				AND_WHEN("port in valid range [1, 65535]")
				{
					AND_WHEN("document is empty")
					{
						VerifyWithPort("google.com", "", Protocol::HTTP, 1, "http://google.com:1/");
					}

					AND_WHEN("document length > 0")
					{
						VerifyWithPort("google.com", "/document/index.html", Protocol::HTTP, 1, "http://google.com:1/document/index.html");
					}
				}
			}
		}

		WHEN("url passed to CHttpUrl construct")
		{
			AND_WHEN("url empty")
			{
				THEN("throws CUrlParsingError")
				{
					REQUIRE_THROWS_AS(CHttpUrl(""), CUrlParsingError);
				}
			}

			AND_WHEN("invalid protocol")
			{
				THEN("throws CUrlParsingError")
				{
					REQUIRE_THROWS_AS(CHttpUrl("ht:/google.com"), CUrlParsingError);
				}
			}

			AND_WHEN("invalid delimeter after protocol")
			{
				THEN("throws CUrlParsingError")
				{
					REQUIRE_THROWS_AS(CHttpUrl("http:/google.com"), CUrlParsingError);
					REQUIRE_THROWS_AS(CHttpUrl("http//google.com"), CUrlParsingError);
				}
			}

			AND_WHEN("invalid character in domain")
			{
				THEN("throws CUrlParsingError")
				{
					REQUIRE_THROWS_AS(CHttpUrl("http://go!@#@asdogle.com"), CUrlParsingError);
				}
			}

			AND_WHEN("invalid port ragne. port < 1 or port > 65535")
			{
				THEN("throws CUrlParsingError")
				{
					try
					{
						CHttpUrl url1("http://ya.ru:0");
						CHttpUrl url2("http://ya.ru:65536");
						CHttpUrl url3("http://ya.ru:123456");
					}
					catch (CUrlParsingError)
					{
						REQUIRE(true);
					}
					catch (...)
					{
						REQUIRE(false);
					}
				}
			}

			AND_WHEN("port >= 1 and port <= 65535")
			{
				THEN("not trow CUrlParsingError")
				{
					try
					{
						CHttpUrl url1("http://ya.ru:1");
						CHttpUrl url2("http://ya.ru:4353");
						CHttpUrl url3("http://ya.ru:65535");
					}
					catch (CUrlParsingError)
					{
						REQUIRE(false);
					}
					catch (...)
					{
						REQUIRE(false);
					}
				}
			}

			AND_WHEN("valid url")
			{
				AND_WHEN("url with port is equal a default port for protocol)")
				{
					THEN("url withour port")
					{
						VerifyWithUrl("http://google.com:80", "google.com", "/", Protocol::HTTP, 80, "http://google.com/");
						VerifyWithUrl("https://google.com:443", "google.com", "/", Protocol::HTTPS, 443, "https://google.com/");
					}
				}

				THEN("not throw CUrlParsingError")
				{
					VerifyWithUrl("http://google.com", "google.com", "/", Protocol::HTTP, 80, "http://google.com/");
					VerifyWithUrl("https://google.com", "google.com", "/", Protocol::HTTPS, 443, "https://google.com/");
					VerifyWithUrl("https://google.com:23", "google.com", "/", Protocol::HTTPS, 23, "https://google.com:23/");
					VerifyWithUrl("http://google.com:23", "google.com", "/", Protocol::HTTP, 23, "http://google.com:23/");
				}
			}
		}
	}
}

TEST_CASE("output CHttpUrl")
{
	SECTION("allow to output CHttpUrl")
	{
		CHttpUrl url("http://google.com/doc");
		std::stringstream strm;
		strm << url;

		REQUIRE(strm.str() == std::string("url: 'http://google.com/doc'\nprotocol: 'http'\nport: '80'\ndomain: 'google.com'\ndocument: '/doc'"));
	}
}
