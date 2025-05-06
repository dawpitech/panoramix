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
#include "druid.h"
#include "villager.h"

static void print_usage(void)
{
    fprintf(stderr, "USAGE: ./panoramix <nb_villagers> <pot_size>"
        " <nb_fights> <nb_refills>\n");
}

static int parse_args(village_t *config, const int argc, const char **argv)
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
    if (config->nb_villagers > 0 && config->pot_size > 0 &&
        config->nb_fights > 0 && config->nb_refills > 0)
        return 0;
    print_usage();
    fprintf(stderr, "panoramix: Values must be >0\n");
    return -1;
}

static int village_init(village_t *village)
{
    village->villagers = calloc(village->nb_villagers,
        sizeof(villager_t));
    village->druid = calloc(1, sizeof(druid_t));
    village->context = calloc(1, sizeof(context_t));
    if (village->villagers == NULL || village->druid == NULL ||
        village->context == NULL)
        return -1;
    village->context->remaining_potions = village->pot_size;
    village->druid->druid_data.remaining_refills = village->nb_refills;
    village->druid->druid_data.pot_size = village->pot_size;
    village->druid->druid_data.context = village->context;
    sem_init(&village->context->not_enough_potion_sem, 0, 0);
    sem_init(&village->context->refill_occurred_sem, 0, 0);
    pthread_mutex_init(&village->context->potion_access_mtx, NULL);
    pthread_mutex_init(&village->context->stdout_available, NULL);
    return 0;
}

static void launch_threads(const village_t *village)
{
    for (int i = 0; i < village->nb_villagers; i++) {
        village->villagers[i].villager_data.id = i;
        village->villagers[i].villager_data.remaining_fights =
            village->nb_fights;
        village->villagers[i].villager_data.context = village->context;
    }
    pthread_create(&village->druid->thread, NULL, druid_entrypoint,
        village->druid);
    for (int i = 0; i < village->nb_villagers; i++)
        pthread_create(&village->villagers[i].thread, NULL,
            villager_entrypoint, &village->villagers[i]);
    for (int i = 0; i < village->nb_villagers; i++)
        pthread_join(village->villagers[i].thread, NULL);
    village->context->all_villagers_asleep = true;
    sem_post(&village->context->not_enough_potion_sem);
    pthread_join(village->druid->thread, NULL);
}

// after bisous with Maxime
static void destroy_the_gaule(const village_t *village)
{
    sem_destroy(&village->context->refill_occurred_sem);
    sem_destroy(&village->context->not_enough_potion_sem);
    pthread_mutex_destroy(&village->context->potion_access_mtx);
    pthread_mutex_destroy(&village->context->stdout_available);
    free(village->villagers);
    free(village->druid);
    free(village->context);
}

int main(const int argc, const char **argv)
{
    village_t gaule = {0};

    if (parse_args(&gaule, argc, argv) != 0 || village_init(&gaule) != 0)
        return EXIT_FAILURE_TECH;
    launch_threads(&gaule);
    destroy_the_gaule(&gaule);
    return EXIT_SUCCESS;
}
