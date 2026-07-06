#include <stdio.h>
#include <curl/curl.h>

int main()
{
    CURL *curl;
    CURLcode result;

    result = curl_global_init(CURL_GLOBAL_ALL);
    if (result != CURLE_OK) 
    {
        fprintf(stderr, "curl_global_init() failed: %s\n", curl_easy_strerror(result));
        return (int) result;
    }

    curl = curl_easy_init();
    if (curl) 
    {
        curl_easy_setopt(curl, CURLOPT_URL, "nfty.sh/test-post-notifications");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "name=daniel&project=curl");

        result = curl_easy_perform(curl);
        if (result != CURLE_OK) 
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
        }

        curl_easy_cleanup(curl);
    }
}