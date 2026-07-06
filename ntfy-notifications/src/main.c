#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

int main(int argc, char **argv)
{
    if (argc == 1) {
        fprintf(stderr, "Too few arguments: \n");
        return 0;
    }

    if (argc > 2) {
        fprintf(stderr, "Too many arguments: \n");
        return 0;
    }

    FILE *fptr = fopen("topic.txt", "r");

    char topic[30];
    fgets(topic, 30, fptr);

    fclose(fptr);

    char url[50] = "https://nfty.sh/";
    strcat(url, topic);

    const char *message = argv[1];
    const size_t length = strlen(message);

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
        curl_easy_setopt(curl, CURLOPT_URL, url);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, length);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, message);

        result = curl_easy_perform(curl);
        if (result != CURLE_OK) 
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
        }

        curl_easy_cleanup(curl);
    }
}