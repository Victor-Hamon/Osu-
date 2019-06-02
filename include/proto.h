/*
** EPITECH PROJECT, 2019
** osu?
** File description:
** functions prototypes for osu?
*/

#ifndef PROTO_H_
#define PROTO_H_

#include <stdbool.h>
#include "struct.h"

/*create_map.c*/
t_map *init_map(char **av);
char *open_map(char *filepath);

/*get_map_data.c*/
void get_map_data(t_map *map);

/*start_game.c*/
void start_game(osu *osu, char *path);

/*init_beatmap.c*/
void init_beatmap(osu *osu, char *genpath);

/*manage_timing.c*/
void display_circles(int timing, osu *osu);

/*manage_score.c*/
bool manage_keyA_input(osu *osu);
bool manage_keyZ_input(osu *osu);

#endif /* PROTO_H_ */
