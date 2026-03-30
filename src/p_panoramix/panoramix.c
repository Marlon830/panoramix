/*
** EPITECH PROJECT, 2023
** B-CCP-400-MPL-4-1-panoramix-marlon.pegahi
** File description:
** panoramix.c
*/

#include "panoramix.h"
#include <stdio.h>
#include <stdlib.h>

void init_panoramix_villagers(panoramix_t *pano)
{
    pano->villagers = malloc(sizeof(villager_t *) * (pano->nb_villagers + 1));
    for (int i = 0; i < pano->nb_villagers; i++) {
        pano->villagers[i] = malloc(sizeof(villager_t));
        pano->villagers[i]->id = i;
        pano->villagers[i]->nb_fought = 0;
        pano->villagers[i]->nb_fights = pano->nb_fights;
        pano->villagers[i]->has_drinked = 0;
        pano->villagers[i]->mutex_nb_servings = pano->mutex_nb_servings;
        pano->villagers[i]->sem1 = &(pano->sem1);
        pano->villagers[i]->sem2 = &(pano->sem2);
    }
    pano->villagers[pano->nb_villagers] = NULL;
}

void init_panoramix(panoramix_t *pano)
{
    pano->is_druid_cooking = 0;
    pano->druid = malloc(sizeof(druid_t));
    pano->druid->nb_refills = pano->nb_refills;
    pano->druid->nb_in_pot = pano->pot_size;
    pano->druid->pot_size = pano->pot_size;
    pano->mutex_nb_servings = malloc(sizeof(mutex_nb_servings_t));
    pano->mutex_nb_servings->nb_servings_left = &(pano->druid->nb_in_pot);
    pano->mutex_nb_servings->is_druid_cooking = &(pano->is_druid_cooking);
    pano->mutex_nb_servings->nb_refill = &(pano->druid->nb_refills);
    pano->druid->mutex_nb_servings = pano->mutex_nb_servings;
    pano->druid->sem1 = &(pano->sem1);
    pano->druid->sem2 = &(pano->sem2);
    init_panoramix_villagers(pano);
}

void run_panoramix(panoramix_t *pano)
{
    pthread_mutex_init(&(pano->mutex_nb_servings->mutex), NULL);
    sem_init(&(pano->sem1), 0, 0);
    sem_init(&(pano->sem2), 0, 0);
    pthread_create(&(pano->druid->thread), NULL, druid_thread, pano->druid);
    for (int i = 0; i != pano->nb_villagers; i++) {
        pthread_create(&(pano->villagers[i]->thread), NULL,
        villager_thread, pano->villagers[i]);
    }
    for (int i = 0; i != pano->nb_villagers; i++) {
        pthread_join(pano->villagers[i]->thread, NULL);
    }
    sem_destroy(&(pano->sem1));
    sem_destroy(&(pano->sem2));
    pthread_mutex_destroy(&(pano->mutex_nb_servings->mutex));
    exit(0);
}
