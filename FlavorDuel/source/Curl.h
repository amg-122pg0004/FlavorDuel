#pragma once
#define CURL_STATICLIB
#pragma comment(lib,"libcurl.lib")
#include <string>
#include <curl.h>

/** A definition of the function pointer for http callback */
typedef void (*CurlCallback)(std::string err, std::string body);

/**
 * Curl HTTP client class
 *
 * Usage:
 * ```c++
 * void callback(string err, string body)
 * {
 *    if (err != "") {
 *      std::cerr << "Error:" << err << std::endl;
 *    } else {
 *      std::cout << body << std::endl;X
 *    }
 * }
 *
 * Curl* curl = new Curl();
 * curl.get("https://www.google.com/", callback);
 * ```
 *
 * or use lambda function:
 *
 * ```c++
 * Curl* curl = new Curl();
 * curl->get(url, [](string err, string body) {
 * 	 if (err != "") {
 *     cerr << "ERROR: " << err << endl;
 *   } else {
 *     cout << body << endl;
 *   }
 * });
 *	```
 */
class Curl {
public:

    /** user-agent */
    std::string  useragent = "libcurl-agent/1.0";
    /** timeout */
    int timeout = 30L; // timeout 30 seconds

    Curl() {
        //
    }

    /**
     * HTTP GET
     */
    void get(const std::string  url, const CurlCallback callback) {
        CURL* curl;
        CURLcode result;

        this->body = ""; // init result body.
        std::string  err = "";

        curl_global_init(CURL_GLOBAL_ALL);
        curl = curl_easy_init();

        if (curl == NULL) {
            err = "curl_easy_init() failed on " + url;
            return callback(err, "");
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, this->invoke_write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, this->useragent.c_str()); // UA
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, this->timeout); // timeout
        // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); // verbose
        result = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        curl_global_cleanup();

        if (result != CURLE_OK) {
            err = "curl_easy_perform() failed on " + url + " (ret:" + std::to_string(result) + ")";
            return callback(err, "");
        }
        return callback(err, this->body);
    }

    /**
     * HTTP POST
     */
    void post(const std::string  url, const std::string  data, const CurlCallback cb) {
        CURL* curl;
        CURLcode result;

        this->body = ""; // init result body.
        std::string  err = "";

        curl_global_init(CURL_GLOBAL_ALL);
        curl = curl_easy_init();

        if (curl == NULL) {
            err = "curl_easy_init() failed on " + url;
            return cb(err, "");
        }
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        std::string escapeData = curl_easy_escape(curl, data.c_str(), data.size());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, escapeData.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, this->invoke_write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, this->useragent.c_str()); // UA
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, this->timeout); // timeout
        // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); // verbose
        result = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        curl_global_cleanup();

        if (result != CURLE_OK) {
            err = "curl_easy_perform() failed on " + url + " (ret:" + std::to_string(result) + ")";
            return cb(err, "");
        }
        this->body = curl_easy_unescape(curl, this->body.c_str(), this->body.size(),NULL);
        return cb(err, this->body);
    }
    std::string GetBody() { return body; }
private:

    /** response body */
    std::string body;

    // TIP: CURLOPT_WRITEFUNCTION ‚Å‚Í ˆø”‚Æ‚È‚éŠÖ”‚É static ‚µ‚©ó‚¯•t‚¯‚È‚¢‚Ì‚Å‹­ˆø‚É static cast ‚µ‚Ä‚¢‚Ü‚·:
    // see: https://curl.se/docs/faq.html#Using_C_non_static_functions_f
    static size_t invoke_write_data(char* buffer, size_t size, size_t nmemb, void* f) {
        // Call non-static member function.
        return static_cast<Curl*>(f)->write_data(buffer, size, nmemb, f);
    }

    /** a callback function for libcurl request */
    size_t write_data(char* buffer, size_t size, size_t nmemb, void* f) {
        int dataLength = size * nmemb;
        this->body.append(buffer, dataLength);
        return dataLength;
    }
};