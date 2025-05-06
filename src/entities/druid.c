/*
** EPITECH PROJECT, 2025
** panoramix
** File description:
** druid.c
*/

#include <stdarg.h>
#include <stdio.h>

#include "druid.h"
#include "panoramix.h"

static void druid_say(const druid_data_t *druid_data, char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    pthread_mutex_lock(&druid_data->context->stdout_available);
    printf("Druid: ");
    vprintf(fmt, args);
    pthread_mutex_unlock(&druid_data->context->stdout_available);
    va_end(args);
}

// ReSharper disable once CppParameterMayBeConstPtrOrRef
// ReSharper disable CppDFAConstantFunctionResult
void *druid_entrypoint(void *arg)
{
    druid_t *druid = (druid_t *) arg;
    druid_data_t *druid_data = &druid->druid_data;

    druid_say(druid_data, "I'm ready... but sleepy...\n");
    while (druid_data->remaining_refills > 0) {
        sem_wait(&druid_data->context->not_enough_potion_sem);
        if (druid_data->context->all_villagers_asleep)
            return NULL;
        druid_data->remaining_refills -= 1;
        druid_data->context->remaining_potions = druid_data->pot_size;
        druid_say(druid_data, "Ah! Yes, yes, I'm awake! Working on it! "
            "Beware I can only make %d more refills after this one.\n",
            druid_data->remaining_refills);
        sem_post(&druid_data->context->refill_occurred_sem);
    }
    druid_say(druid_data, "I'm out of viscum. I'm going back to... zZz\n");
    return NULL;
}
