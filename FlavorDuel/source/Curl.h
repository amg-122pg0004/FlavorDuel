#pragma once
#define CURL_STATICLIB
#pragma comment(lib,"libcurl.lib")
#include <string>
#include <curl.h>

class Curl {
public:
	Curl();
	void Get(const std::string  url, std::string& err, std::string& body);
	void Post(const std::string  url, const std::string  postData, std::string& err, std::string& body);
};