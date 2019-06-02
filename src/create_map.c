/*
** EPITECH PROJECT, 2019
** osu?
** File description:
** map creator for osu?
*/

#include "includes.h"

int calc_nb_line(char *map)
{
    int nb_line = 0;
    int i = 0;

    while (map[i] != '\0') {
        if (map[i] == '\n')
            nb_line++;
        i++;
    }
    return (nb_line);
}

char **split_map(char *map)
{
    int nb_line = calc_nb_line(map);
    char **map_infos = malloc(sizeof(char *) * (nb_line + 1));
    char *token = strtok(map, "\n");
    int i = 1;

    map_infos[0] = malloc(sizeof(char) * strlen(token));
    map_infos[0] = token;
    while (i < nb_line) {
        token = strtok (NULL, "\n");
        map_infos[i] = malloc(sizeof(char) * (strlen(token) + 1));
        map_infos[i] = token;
        map_infos[i][strlen(token)] = '\0';
        i++;
    }
    map_infos[i] = NULL;
    return (map_infos);
}

t_map *init_map(char **av)
{
    t_map *map = malloc(sizeof(*map));

    map->map_infos = split_map(open_map(av[1]));
    get_map_data(map);
    return (map);
}

char *open_map(char *filepath)
{
    int fd = 0;
    char *map;
    struct stat s;

    if ((fd = open(filepath, O_RDONLY)) == -1)
        exit (84);
    stat(filepath, &s);
    map = malloc(sizeof(char) * (s.st_size) + 1);
    read(fd, map, s.st_size);
    map[s.st_size] = '\0';
    close(fd);
    return (map);
}
