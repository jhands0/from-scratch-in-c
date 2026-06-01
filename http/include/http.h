#define MESSAGE_LEN     1000
#define HOST_LEN        50
#define USER_AGENT_LEN  100

enum request_type
{
    GET,
    HEAD,
    POST,
    PUT,
    DELETE,
    CONNECT,
    OPTIONS,
    TRACE,
    PATCH
};

enum response_code
{
    OK,
    NO_CONTENT,
    BAD_REQUEST,
    UNAUTHORIZED,
    FORBIDDEN,
    NOT_FOUND,
};

typedef struct 
{
    request_type    type,
    char            host[HOST_LEN],
    char            user_agent[USER_AGENT_LEN],
    char            body[1000],          
} http_message;
