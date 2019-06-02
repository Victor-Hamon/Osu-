/*
** EPITECH PROJECT, 2019
** osu?
** File description:
** map data for osu?
*/

#include "includes.h"

char *cut_name(char *name_to_cut)
{
    int i = 0;
    int j = 0;
    int copying = 0;
    char *cut_name = malloc(sizeof(char) * strlen(name_to_cut));

    while(name_to_cut[i + 1] != '\0') {
        if (copying == 1) {
            cut_name[j] = name_to_cut[i];
            j++;
        }
        if (name_to_cut[i] == ':') {
            copying = 1;
            (name_to_cut[i + 1] == ' ') ? i++ : 0;
        }
        i++;
    }
    cut_name[j] = '\0';
    return (cut_name);
}

t_circles init_approach_circle(t_circles circle)
{
    sfVector2f pos;

    circle.approach_circle = sfCircleShape_create();
    pos.x = CIRCLE_SIZE * SCALE_TO_SCREEN * Scale;
    pos.y = CIRCLE_SIZE * SCALE_TO_SCREEN * Scale;
    sfCircleShape_setPointCount(circle.approach_circle, 600);
    sfCircleShape_setOrigin(circle.approach_circle, pos);
    sfCircleShape_setFillColor(circle.approach_circle, sfTransparent);
    sfCircleShape_setRadius(circle.approach_circle, CIRCLE_SIZE * SCALE_TO_SCREEN * Scale);
    sfCircleShape_setOutlineThickness(circle.approach_circle, DEFAULT_AC_THICKNESS);
    sfCircleShape_setOutlineColor(circle.approach_circle, sfWhite);
    pos.x = circle.x * SCALE_COORD_X + (CIRCLE_SIZE * SCALE_TO_SCREEN * Scale);
    pos.y = circle.y * SCALE_COORD_Y + (CIRCLE_SIZE * SCALE_TO_SCREEN * Scale);
    sfCircleShape_setPosition(circle.approach_circle, pos);
    return (circle);
}

t_circles get_circle_data(char *line, t_map *map)
{
    t_circles circle;
    sfTexture *texture = sfTexture_createFromFile("assets/hitcircle.png", NULL);
    sfVector2f pos;
    sfFont *font = sfFont_createFromFile("assets/BlackCastleMF.ttf");
    char *token = strtok (line, ",");

    circle.x = atoi(token);
    token = strtok (NULL, ",");
    circle.y = atoi(token);
    token = strtok (NULL, ",");
    circle.timing = atoi(token);
    circle.hitcircle = sfCircleShape_create();
    pos.x = CIRCLE_SIZE * SCALE_TO_SCREEN * Scale;
    pos.y = CIRCLE_SIZE * SCALE_TO_SCREEN * Scale;
    sfCircleShape_setPointCount(circle.hitcircle, 600);
    sfCircleShape_setOrigin(circle.hitcircle, pos);
    sfCircleShape_setRadius(circle.hitcircle, CIRCLE_SIZE * SCALE_TO_SCREEN * Scale);
    sfCircleShape_setTexture(circle.hitcircle, texture, sfTrue);
    pos.x = circle.x * SCALE_COORD_X + CIRCLE_SIZE * SCALE_TO_SCREEN * Scale;
    pos.y = circle.y * SCALE_COORD_Y + CIRCLE_SIZE * SCALE_TO_SCREEN * Scale;
    sfCircleShape_setPosition(circle.hitcircle, pos);
    circle.clicked = 0;
    circle.missed = 0;
    pos.x -= CIRCLE_SIZE * SCALE_TO_SCREEN * Scale + 20;
    pos.y -= CIRCLE_SIZE * SCALE_TO_SCREEN * Scale + 50;
    circle.text_when_clicked = sfText_create();
    sfText_setPosition(circle.text_when_clicked, pos);
    sfText_setFont(circle.text_when_clicked, font);
    sfText_setCharacterSize(circle.text_when_clicked, 80);
    sfText_setOutlineColor(circle.text_when_clicked, sfBlack);
    sfText_setOutlineThickness(circle.text_when_clicked, 5);
    circle = init_approach_circle(circle);
    return (circle);
}

void create_hitobjects(t_map *map, int i)
{
    int j = 0;

    for (j = i; map->map_infos[j] != NULL; j++);
    map->hit_objects = malloc(sizeof(t_circles) * (j + 1));
    j = 0;
    while (map->map_infos[i] != NULL) {
        map->hit_objects[j] = get_circle_data(map->map_infos[i], map);
        j++;
        i++;
    }
    map->nb_circle = j;
}

void find_background_name(t_map *map, int x)
{
    int i = 0;
    int j = 0;

    map->background_name = malloc(sizeof(char) * (strlen(map->map_infos[x]) + 1));
    for (; map->map_infos[x][i] != '"'; ++i);
    i++;
    for (;map->map_infos[x][i] != '"'; ++i, ++j)
        map->background_name[j] = map->map_infos[x][i];
    map->background_name[j] = '\0';
}

void get_map_data(t_map *map)
{
    int i = 0;

    map->scale.x = SCALE_TO_SCREEN;
    map->scale.y = SCALE_TO_SCREEN;
    while (map->map_infos[i] != NULL) {
        if (strncmp(map->map_infos[i], "AudioFilename:", 14) == 0)
            map->audio_name = strdup(cut_name(map->map_infos[i]));
        if (strncmp(map->map_infos[i], "Title:", 6) == 0)
            map->song_title = strdup(cut_name(map->map_infos[i]));
        if (strncmp(map->map_infos[i], "Artist:", 7) == 0)
            map->artist = strdup(cut_name(map->map_infos[i]));
        if (strncmp(map->map_infos[i], "Version:", 8) == 0)
            map->version = strdup(cut_name(map->map_infos[i]));
        if (strncmp(map->map_infos[i], "Creator:", 8) == 0)
            map->creator = strdup(cut_name(map->map_infos[i]));
        if (strncmp(map->map_infos[i], "[HitObjects]", 12) == 0)
            create_hitobjects(map, i + 1);
        if (strncmp(map->map_infos[i], "//Background", 12) == 0)
            find_background_name(map, i + 1);
        i++;
    }
}