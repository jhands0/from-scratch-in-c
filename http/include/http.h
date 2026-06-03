#define MESSAGE_LEN     1000
#define HOST_LEN        50
#define USER_AGENT_LEN  100
#define BODY_LEN        1000
#define RESPONSE_LEN    1000

typedef enum {
    GET,
    HEAD,
    POST,
    PUT,
    DELETE,
    CONNECT,
    OPTIONS,
    TRACE,
    PATCH
} request_type_t;

typedef enum {
    OK,
    NO_CONTENT,
    BAD_REQUEST,
    UNAUTHORIZED,
    FORBIDDEN,
    NOT_FOUND
} response_code_t;

typedef struct {
    request_type_t  type;
    char            host[HOST_LEN];
    char            user_agent[USER_AGENT_LEN];
    char            body[BODY_LEN];   
} http_message_t;
