#include "Curl.h"

namespace {
    std::string  Useragent = "libcurl-agent/1.0";
    int Timeout = 30L; // timeout 30 seconds

    size_t WriteData(char* buffer, size_t size, size_t nmemb, std::string* stream) {
        int dataLength = size * nmemb;
        stream->append(buffer, dataLength);
        return dataLength;
    }
}

Curl::Curl()
{
}

void Curl::Get(const std::string url, std::string& err, std::string& body){
    CURL* curl;
    CURLcode result;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl == NULL) {
        err = "curl_easy_init() failed on " + url;
        return ;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, Useragent.c_str());
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, Timeout);
    result = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    if (result != CURLE_OK) {
        err = "curl_easy_perform() failed on " + url + " (ret:" + std::to_string(result) + ")";
        return;
    }
    return;
}

void Curl::Post(const std::string url, const std::string postData, std::string& err, std::string& body){
        CURL* curl;
        CURLcode result;

        curl_global_init(CURL_GLOBAL_ALL);
        curl = curl_easy_init();

        if (curl == NULL) {
            err = "curl_easy_init() failed on " + url;
            return;
        }
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        std::string escapeData = curl_easy_escape(curl, postData.c_str(), postData.size());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, escapeData.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteData);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &body);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, Useragent.c_str());
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, Timeout);
        curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
        result = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        curl_global_cleanup();

        if (result != CURLE_OK) {
            err = "curl_easy_perform() failed on " + url + " (ret:" + std::to_string(result) + ")";
            return;
        }
        body = curl_easy_unescape(curl, body.c_str(), body.size(), NULL);
        return ;
    }
