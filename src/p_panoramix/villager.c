/*
** EPITECH PROJECT, 2023
** B-CCP-400-MPL-4-1-panoramix-marlon.pegahi
** File description:
** villager.c
*/

#include "panoramix.h"
#include <stdio.h>
#include <stdlib.h>

void villager_thread_bis(villager_t *villager)
{
    printf("Villager %d: I need a drink... I see %d servings left.\n",
    villager->id, *(villager->mutex_nb_servings->nb_servings_left));
    if (*(villager->mutex_nb_servings->nb_servings_left) == 0) {
        printf("Villager %d: Hey Pano wake up! We need more potion.\n",
        villager->id);
        if (*(villager->mutex_nb_servings->nb_refill) == 0) {
            printf("Villager %d: The druid sleeps, bye.\n", villager->id);
            pthread_mutex_unlock(&(villager->mutex_nb_servings->mutex));
            pthread_exit(NULL);
        }
        *(villager->mutex_nb_servings->is_druid_cooking) = 1;
        pthread_mutex_unlock(&(villager->mutex_nb_servings->mutex));
        sem_post(villager->sem1);
        sem_wait(villager->sem2);
        pthread_mutex_lock(&(villager->mutex_nb_servings->mutex));
        *(villager->mutex_nb_servings->is_druid_cooking) = 0;
    }
    *(villager->mutex_nb_servings->nb_servings_left) -= 1;
    pthread_mutex_unlock(&(villager->mutex_nb_servings->mutex));
    villager->has_drinked = 1;
}

void villager_fights(villager_t *villager)
{
    villager->nb_fought += 1;
    printf("Villager %d: Take that roman scum! Only %d left.\n",
    villager->id, villager->nb_fights - villager->nb_fought);
    villager->has_drinked = 0;
}

void *villager_thread(void *arg)
{
    villager_t *villager = (villager_t *)arg;

    printf("Villager %d: Going into battle!\n", villager->id);
    while (1) {
        if (villager->nb_fought == villager->nb_fights)
            break;
        if (villager->has_drinked) {
            villager_fights(villager);
            continue;
        }
        pthread_mutex_lock(&(villager->mutex_nb_servings->mutex));
        if (*(villager->mutex_nb_servings->is_druid_cooking)) {
            pthread_mutex_unlock(&(villager->mutex_nb_servings->mutex));
            continue;
        }
        villager_thread_bis(villager);
    }
    printf("Villager %d: I\'m going to sleep now.\n", villager->id);
    return NULL;
}
