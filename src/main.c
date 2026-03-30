/*
** EPITECH PROJECT, 2023
** B-CCP-400-MPL-4-1-panoramix-marlon.pegahi
** File description:
** main.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "displays.h"
#include "error_gestion.h"
#include "panoramix.h"

int main(int argc, char const *argv[])
{
    panoramix_t *pano = malloc(sizeof(panoramix_t));

    if (argc == 1) {
        displays_usage();
        return 0;
    }
    if (argc != 5) {
        fprintf(stderr, "Invalid number of arguments\n");
        displays_usage();
        return 84;
    }
    if (error_gestion(pano, argc, argv) == 84)
        return 84;
    init_panoramix(pano);
    run_panoramix(pano);
    return 0;
}
