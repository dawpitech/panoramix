/*
** EPITECH PROJECT, 2025
** panoramix
** File description:
** panoramix.c
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "panoramix.h"
#include "villager.h"

void print_usage(void)
{
    fprintf(stderr, "USAGE: ./panoramix <nb_villagers> <pot_size>"
        " <nb_fights> <nb_refills>\n");
}

int parse_args(panoramix_t *config, const int argc, const char **argv)
{
    if (argc != 5) {
        print_usage();
        fprintf(stderr, "panoramix: Wrong number of parameters\n");
        return -1;
    }
    config->nb_villagers = (int) strtol(argv[1], NULL, 10);
    config->pot_size = (int) strtol(argv[2], NULL, 10);
    config->nb_fights = (int) strtol(argv[3], NULL, 10);
    config->nb_refills = (int) strtol(argv[4], NULL, 10);
    if (config->nb_villagers > 0 &&
        config->pot_size > 0 &&
        config->nb_fights > 0 &&
        config->nb_refills > 0)
        return 0;
    print_usage();
    fprintf(stderr, "panoramix: Values must be >0\n");
    return -1;
}

int threads_init(panoramix_t *config)
{
    config->villagers = calloc(sizeof(villager_t), config->nb_villagers);
    if (config->villagers == NULL)
        return -1;
    for (int i = 0; i < config->nb_villagers; i++) {
        config->villagers[i].villager_data.id = i + 1;
        pthread_create(&config->villagers[i].thread, NULL,
            villager_entrypoint, &config->villagers[i].villager_data);
    }
    for (int i = 0; i < config->nb_villagers; i++) {
        pthread_join(config->villagers[i].thread, NULL);
    }
    return 0;
}

int main(const int argc, const char **argv)
{
    panoramix_t config = {0};

    if (parse_args(&config, argc, argv) != 0 || threads_init(&config) != 0)
        return EXIT_FAILURE_TECH;

    return 0;
}
