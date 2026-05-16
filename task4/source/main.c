#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>

int main(int argc, char *argv[]) 
{
    opterr = 0;

    char* short_opts = (char*)calloc((size_t)argc, sizeof(char));
    if(!short_opts) return 1;
    
    int short_cnt = 0;
    char** long_opts = (char**)calloc((size_t)argc, sizeof(char*));
    if(!long_opts)
    {
        free(short_opts);
        return 1;
    }

    int long_cnt = 0;
    char** non_opts = (char**)calloc((size_t)argc, sizeof(char*));
    if(!non_opts)
    {
        free(short_opts);
        free(long_opts);
        return 1;
    }
    int non_cnt = 0;


    struct option long_options[] = 
    {
        {"elbrus", required_argument, 0, 'e'},
        {0, 0, 0, 0}
    };

    const char* optstring = ":mcst";

    int opt = 0;
    while ((opt = getopt_long((size_t)argc, argv, optstring, long_options, NULL)) != -1) 
    {
        switch (opt) {
        case 'm':
        case 'c':
        case 's':
        case 't':
            short_opts[short_cnt++] = (char)opt;
            break;

        case 'e': 
        {

            if (strcmp(optarg, "1c+") == 0 || strcmp(optarg, "2c+") == 0 
            || strcmp(optarg, "2c3") == 0 || strcmp(optarg, "4c") == 0 
            || strcmp(optarg, "8c") == 0 || strcmp(optarg, "16c") == 0) 
            {
                char*entry = (char*)calloc(strlen("elbrus=") + strlen(optarg) + 1, sizeof(char));
                sprintf(entry, "elbrus=%s", optarg);
                long_opts[long_cnt++] = entry;
            } 
            else 
            {
                printf("Incorrect option: 'elbrus=%s'\n", optarg);
                return 1;
            }
            break;
        }

        case ':':
            printf("Incorrect option: 'elbrus='\n");
            return 1;

        case '?':
            if (optopt) 
            {
                printf("Incorrect option: '%c'\n", optopt);
            } 
            else 
            {
                const char *bad = argv[optind - 1];
                if (strncmp(bad, "--", 2) == 0) bad += 2; 
                printf("Incorrect option: '%s'\n", bad);
            }
            return 1;

        default:
            break;
        }
    }

    while (optind < argc) non_opts[non_cnt++] = argv[optind++];


    printf("Short options:");
    for (int i = 0; i < short_cnt; ++i)
    {
        printf(" '%c'", short_opts[i]);
    }
    printf("\n");
    free(short_opts);

    printf("Long options:");
    for (int i = 0; i < long_cnt; ++i) 
    {
        printf(" '%s'", long_opts[i]);
        free(long_opts[i]);
    }
    printf("\n");

    printf("Non options:");
    for (int i = 0; i < non_cnt; ++i)
    {
        printf(" '%s'", non_opts[i]);
    }
    printf("\n");
    free(non_opts);

    return 0;
}