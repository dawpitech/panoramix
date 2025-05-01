/*
** EPITECH PROJECT, 2025
** panoramix
** File description:
** panoramix.h
*/

#ifndef PANORAMIX_H
    #define PANORAMIX_H

    #include <pthread.h>
    #include <semaphore.h>
    #include <stdbool.h>

    #define EXIT_FAILURE_TECH 84

typedef struct {
    sem_t not_enough_potion_sem;
    sem_t refill_occurred_sem;
    pthread_mutex_t potion_access_mtx;
    int remaining_potions;
    pthread_mutex_t stdout_available;
    bool all_villagers_asleep;
} context_t;

typedef struct {
    int id;
    int remaining_fights;
    context_t *context;
} villager_data_t;

typedef struct {
    pthread_t thread;
    villager_data_t villager_data;
} villager_t;

typedef struct {
    context_t *context;
    int remaining_refills;
    int pot_size;
} druid_data_t;

typedef struct {
    pthread_t thread;
    druid_data_t druid_data;
} druid_t;

typedef struct {
    int nb_villagers;
    int pot_size;
    int nb_fights;
    int nb_refills;
    villager_t *villagers;
    druid_t *druid;
    context_t *context;
} village_t;

#endif //PANORAMIX_H
