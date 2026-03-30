/*
** EPITECH PROJECT, 2023
** B-CCP-400-MPL-4-1-panoramix-marlon.pegahi
** File description:
** druid.c
*/

#include "panoramix.h"
#include <stdio.h>

void *druid_thread(void *arg)
{
    druid_t *druid = (druid_t *)arg;

    printf("Druid: I\'m ready... but sleepy...\n");
    while (1) {
        sem_wait(druid->sem1);
        pthread_mutex_lock(&(druid->mutex_nb_servings->mutex));
        druid->nb_refills -= 1;
        printf("Druid: Ah! Yes, yes, I\'m awake! Working on it! ");
        printf("Beware I can only make %d more refills after this one.\n",
        druid->nb_refills);
        *(druid->mutex_nb_servings->nb_servings_left) = druid->pot_size;
        pthread_mutex_unlock(&(druid->mutex_nb_servings->mutex));
        sem_post(druid->sem2);
        if (druid->nb_refills == 0) {
            break;
        }
    }
    printf("Druid: I\'m out of viscum. I\'m going back to... zZz\n");
    return NULL;
}
