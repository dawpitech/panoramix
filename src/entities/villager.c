/*
** EPITECH PROJECT, 2025
** panoramix
** File description:
** villager.c
*/

#include <stdarg.h>
#include <stdio.h>

#include "villager.h"

static void villager_say(const villager_data_t *villager_data, char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    printf("Villager %d: ", villager_data->id);
    vprintf(fmt, args);
    va_end(args);
}

void *villager_entrypoint(void *arg)
{
    villager_data_t *villager_data = arg;
    villager_say(villager_data, "Going into battle!\n");

    villager_say(villager_data, "I'm going to sleep now.\n");
    return NULL;
}
