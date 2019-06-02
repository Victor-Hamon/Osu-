/*
** EPITECH PROJECT, 2019
** osu?
** File description:
** game has started
*/

#include "includes.h"

sfRenderWindow *createWindow(int width, int height)
{
    sfRenderWindow *window;
    sfVideoMode mode = {width, height, 32};

    window = sfRenderWindow_create(mode, "Game", sfClose | sfFullscreen, NULL);
    return window;
}

char *find_genpath(char *path)
{
    int checkpoint = 0;
    char *gen_path = malloc(sizeof(char) * (strlen(path) + 1));

    for (int i = 0; path[i] != '\0'; ++i) {
        if (path[i] == '/')
            checkpoint = i;
    }
    strncpy(gen_path, path, checkpoint + 1);
    gen_path[checkpoint + 1] = '\0';
    return (gen_path);
}

void display_cursor(sfVector2i pos_mouse, osu *osu)
{
    sfVector2f pos_sprite;

    pos_sprite.x = (float) pos_mouse.x;
    pos_sprite.y = (float) pos_mouse.y;
    sfSprite_setPosition(osu->cursor_s, pos_sprite);
    sfRenderWindow_drawSprite(osu->w, osu->cursor_s, NULL);
}

void display_score(osu *osu)
{
    sfText_setString(osu->score_txt, osu->text_score);
    sfRenderWindow_drawText(osu->w, osu->score_txt, NULL);
    sfText_setString(osu->precision_txt, osu->text_precision);
    sfRenderWindow_drawText(osu->w, osu->precision_txt, NULL);
    sfText_setString(osu->combo_txt, osu->text_combo);
    sfRenderWindow_drawText(osu->w, osu->combo_txt, NULL);
}

void start_game(osu *osu, char *path)
{
    sfVector2i pos_mouse;
    osu->w = createWindow(1920, 1080);

    init_beatmap(osu, find_genpath(path));
    osu->score = 0;
    osu->map->precision = 0.0f;
    sfRenderWindow_setMouseCursorVisible(osu->w, sfFalse);
    while (sfRenderWindow_isOpen(osu->w)) {
        sprintf(osu->text_score, "%d", osu->score);
        pos_mouse = sfMouse_getPositionRenderWindow(osu->w);
        display_cursor(pos_mouse, osu);
        sfRenderWindow_display(osu->w);
        sfRenderWindow_clear(osu->w, sfBlack);
        osu->timing = sfMusic_getPlayingOffset(osu->beatmap);
        sfRenderWindow_drawSprite(osu->w, osu->map->background_sprite, NULL);
        display_score(osu);
        display_circles(osu->timing.microseconds / 1000, osu);
    }
}