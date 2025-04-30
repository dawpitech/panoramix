/*
** EPITECH PROJECT, 2025
** panoramix
** File description:
** villager.c
*/

#include <stdarg.h>
#include <stdio.h>

#include "villager.h"
#include "panoramix.h"

static void villager_say(const villager_data_t *villager_data, char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    pthread_mutex_lock(&villager_data->context->stdout_available);
    printf("Villager %d: ", villager_data->id);
    vprintf(fmt, args);
    pthread_mutex_unlock(&villager_data->context->stdout_available);
    va_end(args);
}

// ReSharper disable once CppParameterMayBeConstPtrOrRef
void *villager_entrypoint(void *arg)
{
    const villager_t *villager = arg;
    villager_data_t villager_data = villager->villager_data;
    villager_say(&villager_data, "Going into battle!\n");

    while (villager_data.remaining_fights > 0) {
        pthread_mutex_lock(&villager_data.context->potion_access_mtx);
        villager_say(&villager_data, "I need a drink... I see %d serving "
            "left.\n", villager_data.context->remaining_potions);
        if (villager_data.context->remaining_potions <= 0) {
            villager_say(&villager_data, "Hey Pano wake up! We need more "
                "potion.\n");
            sem_post(&villager_data.context->not_enough_potion_sem);
            sem_wait(&villager_data.context->refill_occurred_sem);
        }
        villager_data.context->remaining_potions -= 1;
        pthread_mutex_unlock(&villager_data.context->potion_access_mtx);
        villager_data.remaining_fights -= 1;
        villager_say(&villager_data, "Take that roman scum! Only %d "
            "left.\n", villager_data.remaining_fights);
    }
    villager_say(&villager_data, "I'm going to sleep now.\n");
    return NULL;
}
