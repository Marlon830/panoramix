/*
** EPITECH PROJECT, 2023
** B-CCP-400-MPL-4-1-panoramix-marlon.pegahi
** File description:
** panoramix.h
*/

#pragma once

#include <pthread.h>
#include <semaphore.h>

typedef struct mutex_nb_servings_s {
    int *nb_servings_left;
    int *is_druid_cooking;
    int *nb_refill;
    pthread_mutex_t mutex;
} mutex_nb_servings_t;

typedef struct villager_s {
    int id;
    int nb_fought;
    int has_drinked; // TODO: maybe remove this or change to bool
    int nb_fights;
    pthread_t thread;
    sem_t *sem1;
    sem_t *sem2;
    mutex_nb_servings_t *mutex_nb_servings;
} villager_t;

typedef struct druid_s {
    int nb_refills;
    int nb_in_pot;
    int pot_size;
    pthread_t thread;
    sem_t *sem1;
    sem_t *sem2;
    mutex_nb_servings_t *mutex_nb_servings;
} druid_t;

typedef struct panoramix_s {
    int nb_villagers;
    int pot_size;
    int nb_fights;
    int nb_refills;
    int is_druid_cooking;
    villager_t **villagers;
    druid_t *druid;
    mutex_nb_servings_t *mutex_nb_servings;
    sem_t sem1;
    sem_t sem2;
} panoramix_t;

void init_panoramix(panoramix_t *pano);
void run_panoramix(panoramix_t *pano);
void *villager_thread(void *arg);
void *druid_thread(void *arg);
