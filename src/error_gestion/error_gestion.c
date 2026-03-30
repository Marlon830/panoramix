/*
** EPITECH PROJECT, 2023
** B-CCP-400-MPL-4-1-panoramix-marlon.pegahi
** File description:
** error_gestion.c
*/

#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include "panoramix.h"

int error_gestion(panoramix_t *pano, int argc, char const *argv[])
{
    long num = 0;
    char *endptr;

    for (int i = 1; i != argc; i++) {
        errno = 0;
        num = strtol(argv[i], &endptr, 10);
        if ((errno == ERANGE && (num == LONG_MAX || num == LONG_MIN))
        || (errno != 0 && num == 0))
            return 84;
        if (endptr == argv[i] || *endptr != '\0' || num <= 0)
            return 84;
    }
    pano->nb_villagers = strtol(argv[1], &endptr, 10);
    pano->pot_size = strtol(argv[2], &endptr, 10);
    pano->nb_fights = strtol(argv[3], &endptr, 10);
    pano->nb_refills = strtol(argv[4], &endptr, 10);
    return 0;
}
