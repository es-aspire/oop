#include "pch.h"
#include "HtmlDecode.cpp"

void ReplaceAllTest(const std::string &str, const std::string &search,
    const std::string &replace, const std::string &resultCheck)
{
	std::string result = ReplaceAll(str, search, replace);
	EXPECT_EQ(result, resultCheck);
}

TEST(HtmlDecodeTest, test_1231234)
{
	ReplaceAllTest("12312312345", "1231234", "Hello", "123Hello5");
}

TEST(HtmlDecodeTest, test_mama)
{
	ReplaceAllTest("mama", "ma", "mama", "mamamama");
}

TEST(HtmlDecodeTest, test_empty_search_string)
{
	ReplaceAllTest("mama", "", "mama", "mama");
}

TEST(HtmlDecodeTest, test_empty_repalce_string)
{
	ReplaceAllTest("mama", "ma", "", "");
}

void HtmlDecodeTest(const std::string &str, const std::string &resultCheck)
{
	std::string result = HtmlDecode(str);
	EXPECT_EQ(result, resultCheck);
}

TEST(HtmlDecodeTest, empty_string_for_decode)
{
	HtmlDecodeTest("", "");
}

TEST(HtmlDecodeTest, string_without_replacemanet_substring)
{
	HtmlDecodeTest("Hello world!", "Hello world!");
}

TEST(HtmlDecodeTest, html_markup)
{
	std::string str = "&lt;!DOCTYPE html&gt;&lt;html lang=en&gt;&lt;head&gt;&lt;meta charset=&quot;utf-8&quot;&gt;&lt;/head&gt;&lt;body&gt;&lt;h2&gt;Hello World &quot;&quot;&apos;&apos;&lt;/h2&gt;&lt;/body&gt;&lt;/html&gt;";
	std::string resultCheck = "<!DOCTYPE html><html lang=en><head><meta charset=\"utf-8\"></head><body><h2>Hello World \"\"''</h2></body></html>";
	HtmlDecodeTest("&lt;!DOCTYPE html&gt;&lt;html lang=en&gt;&lt;head&gt;&lt;meta charset=&quot;utf-8&quot;&gt;&lt;/head&gt;&lt;body&gt;&lt;h2&gt;Hello World &quot;&quot;&apos;&apos;&lt;/h2&gt;&lt;/body&gt;&lt;/html&gt;",
		"<!DOCTYPE html><html lang = en><head><meta charset = \"utf-8\"></head><body><h2>Hello World \"\"''</h2></body></html>");
}

TEST(HtmlDecodeTest, cat_test)
{
	std::string str = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
	std::string resultCheck = "Cat <says> \"Meow\". M&M's";

	HtmlDecodeTest("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s", 
		"Cat <says> \"Meow\". M&M's");
}

TEST(HtmlDecodeTest, decode_html_entities_when_one_entitity_may_include_other_after_decode)
{
	HtmlDecodeTest("&amp;lt;", "&lt;");
}

TEST(HtmlDecodeTest, AllVariantTests) 
{
	for (const auto & key : KEYS)
	{
		HtmlDecodeTest(key.first, key.second);
	}
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
