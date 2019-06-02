/*
** EPITECH PROJECT, 2019
** osu?
** File description:
** osu! like but it's osu?
*/
#include "includes.h"

void print_map_data(osu *osu)
{
    printf("\e[32m\e[01m(๑・ω・๑) NOW PLAYING :\e[33m\e[01m%s\n\e[0m", osu->map->song_title);
    printf("\e[32m\e[01m(๑・ω・๑) MADE BY :\e[33m\e[01m%s\n\e[0m", osu->map->artist);
    printf("\e[32m\e[01m(๑・ω・๑) MAPPED BY :\e[33m\e[01m%s\n\e[0m", osu->map->creator);
    printf("\e[32m\e[01m(๑・ω・๑) Difficulty -->\e[33m\e[01m%s\n\e[0m", osu->map->version);
}

void init_game(osu *osu, char **av)
{
    osu->map = init_map(av);
}

int main(int ac, char *av[])
{
    osu *osu = malloc(sizeof(*osu));

    if (ac != 2 || av[1] == NULL)
        return (84);
    init_game(osu, av);
    osu->input.input_A = 0;
    osu->input.input_Z = 0;
    print_map_data(osu);
    start_game(osu, av[1]);
    return 0;
}