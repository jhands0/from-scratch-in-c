#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

char* get_event_type(unsigned short type)
{
    switch (type)
    {
        case 0:
            return "EV_SYN";
        case 1:
            return "EV_KEY";
        case 2:
            return "EV_REL";
        case 3:
            return "EV_ABS";
        case 4:
            return "EV_MSC";
        case 5:
            return "EV_SW";
        case 17:
            return "EV_LED";
        case 18:
            return "EV_SND";
        case 20:
            return "EV_REP";
        case 21:
            return "EV_FF";
        case 22:
            return "EV_PWR";
        case 23:
            return "EV_FF_STATUS";
        case 31:
            return "EV_MAX";
        case 32:
            return "EV_CNT";
        default:
            return "n/a";
    }
}

char* get_code(unsigned short code)
{
    switch (code) {
        case 0:
            return "REL_X";
        case 1:
            return "REL_Y";
        case 2:
            return "REL_Z";
        case 3:
            return "REL_RX";
        case 4:
            return "REL_RY";
        case 5:
            return "REL_RZ";
        case 6:
            return "REL_HWHEEL";
        case 7:
            return "REL_DIAL";
        case 8:
            return "REL_WHEEL";
        case 9:
            return "REL_MISC";
        default:
            return "n/a";
    }
}

void print_help(char* exec_alias)
{
    printf("USAGE:\n");
    printf("\t%s <event/file/path> [OPTIONS]\n\n", exec_alias);

    printf("OPTIONS:\n");
    printf("\t-h <help>\t\tPrints program help to the screen\n");
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        print_help(argv[0]);
        exit(0);
    }

    if (!strcmp(argv[1], "-h"))
    {
        print_help(argv[0]);
        exit(0);
    }

    char *mousepath = argv[1];
    printf("Intercepting device %s ...\n", mousepath);
    int fd = open(mousepath, 0, O_RDONLY);
    printf("File descriptor: %d\n", fd);

    struct input_event ie;

    while (1)
    {
        read(fd, &ie, sizeof(ie));
        printf("\nEvent recieved.\n");
        printf("Time = %lds %ldus\n", ie.time.tv_sec, ie.time.tv_usec);

        char* type;
        type = get_event_type(ie.type);
        printf("Event Type = %s\n", type);

        char* code;
        code = get_code(ie.code);
        printf("Code = %s\n", code);

        int value;
        value = ie.value;
        printf("Value = %d\n", value);
    }
}
