/*
** EPITECH PROJECT, 2019
** osu?
** File description:
** Structures header for osu?
*/

#ifndef STRUCT_H_
#define STRUCT_H_
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <SFML/Audio.h>

typedef struct s_input
{
    int input_A;
    int input_Z;
}t_input;

typedef struct s_circle
{
    int x;
    int y;
    int timing;
    int clicked;
    int missed;
    sfText *text_when_clicked;
    sfCircleShape *hitcircle;
    sfCircleShape *approach_circle;
}t_circles;

typedef struct s_map
{
    t_circles *hit_objects;
    char **map_infos;
    char *audio_name;
    char *song_title;
    char *version;
    char *creator;
    char *artist;
    char *background_name;
    sfTexture *background_texture;
    sfSprite *background_sprite;
    float nb_circle;
    float precision;
    int combo;
    sfVector2f scale;
}t_map;

typedef struct s_osu
{
    t_input input;
    sfTexture *cursor;
    sfSprite *cursor_s;
    sfRenderWindow *w;
    int score;
    char text_score[42];
    char text_precision[42];
    char text_combo[42];
    sfText *score_txt;
    sfText *precision_txt;
    sfText *combo_txt;
    sfTime timing;
    sfMusic *beatmap;
    t_map *map;
}osu;

#endif /* STRUCT_H_ */
