/*
** EPITECH PROJECT, 2025
** panoramix
** File description:
** panoramix.h
*/

#ifndef PANORAMIX_H
    #define PANORAMIX_H

    #include <pthread.h>
    #include <stdbool.h>

    #define EXIT_FAILURE_TECH 84

typedef struct {
    int id;
    int remaining_fights;
    bool exhausted;
} villager_data_t;

typedef struct {
    pthread_t thread;
    villager_data_t villager_data;
} villager_t;

typedef struct {
    int nb_villagers;
    int pot_size;
    int nb_fights;
    int nb_refills;
    villager_t *villagers;
    pthread_t druid;
} panoramix_t;

#endif //PANORAMIX_H
