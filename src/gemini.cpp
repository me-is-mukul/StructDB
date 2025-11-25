#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"
#define CLEAR   "\033[2J\033[1;1H"

using json = nlohmann::json;

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main(int argc, char* argv[]) {
    const char* key = std::getenv("GEMINI_API_KEY");
    if (!key) {
        std::cerr << "GEMINI_API_KEY environment variable not set\n";
        return 1;
    }
    std::string apiKey = key;

    json payload = {
        {"contents", {{
            {"parts", {{
                {"text", argv[1]}
            }}}
        }}}
    };

    CURL* curl = curl_easy_init();
    if (!curl) return 1;

    std::string response;
    std::string url = "https://generativelanguage.googleapis.com/v1beta/models/gemini-2.5-flash:generateContent";

    std::string body = payload.dump();

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, ("x-goog-api-key: " + apiKey).c_str());
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "Accept: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, body.size());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        std::cerr << "CURL Error: " << curl_easy_strerror(res) << std::endl;
        return 1;
    }

    try {
        json parsed = json::parse(response);
        std::string text = parsed["candidates"][0]["content"]["parts"][0]["text"];
        std::cout << CYAN << "\n>>> : " << text << RESET <<"\n";
    } catch (...) {
        std::cerr << "Error parsing response JSON\n";
    }

    return 0;
}
