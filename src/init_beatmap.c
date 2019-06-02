/*
** EPITECH PROJECT, 2019
** osu?
** File description:
** beatmap for an osu? play
*/

#include "includes.h"

char *my_strcat(char *a, char *b)
{
    int a_len   = (int) strlen(a);
    int b_len   = (int) strlen(b);
    int len     = a_len + b_len;
    char *str   = malloc(sizeof(char) * (len + 1));

    for (int i = 0; i < len; i++)
        str[i] = i < a_len ? a[i] : b[i - a_len];
    str[len] = 0;
    return str;
}

void init_beatmap(osu *osu, char *genpath)
{
    sfVector2f origin_cursor;
    sfVector2f pos;
    sfFont *font = sfFont_createFromFile("assets/BlackCastleMF.ttf");

    pos.x = 1600.0f;
    pos.y = 10.0f;
    origin_cursor.x = 20.0f;
    origin_cursor.y = 20.0f;
    osu->cursor = sfTexture_createFromFile("assets/cursor.png", NULL);
    osu->cursor_s = sfSprite_create();
    osu->score_txt = sfText_create();
    sfText_setPosition(osu->score_txt, pos);
    sfText_setFont(osu->score_txt, font);
    sfText_setCharacterSize(osu->score_txt, 80);
    sfText_setOutlineColor(osu->score_txt, sfBlack);
    sfText_setOutlineThickness(osu->score_txt, 8);
    pos.x = 40.0f;
    pos.y = 900.0f;
    //combotext
    osu->combo_txt = sfText_create();
    sfText_setPosition(osu->combo_txt, pos);
    sfText_setFont(osu->combo_txt, font);
    sfText_setCharacterSize(osu->combo_txt, 140);
    sfText_setOutlineColor(osu->combo_txt, sfBlack);
    sfText_setOutlineThickness(osu->combo_txt, 8);
    pos.x = 1600.0f;
    pos.y = 80.0f;
    osu->precision_txt = sfText_create();
    sfText_setPosition(osu->precision_txt, pos);
    sfText_setFont(osu->precision_txt, font);
    sfText_setCharacterSize(osu->precision_txt, 80);
    sfText_setOutlineColor(osu->precision_txt, sfBlack);
    sfText_setOutlineThickness(osu->precision_txt, 8);
    sfSprite_setTexture(osu->cursor_s,osu->cursor, sfFalse);
    sfSprite_setOrigin(osu->cursor_s, origin_cursor);
    osu->beatmap = sfMusic_createFromFile(my_strcat(strdup(genpath), strdup(osu->map->audio_name)));
    osu->map->background_texture = sfTexture_createFromFile(my_strcat(strdup(genpath), strdup(osu->map->background_name)), NULL);
    osu->map->background_sprite = sfSprite_create();
    sfSprite_setScale(osu->map->background_sprite, osu->map->scale);
    sfSprite_setTexture(osu->map->background_sprite, osu->map->background_texture, sfTrue);
    sfMusic_play(osu->beatmap);
}