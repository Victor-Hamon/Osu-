/*
** EPITECH PROJECT, 2019
** osu?
** File description:
** timing for osu?
*/

#include "includes.h"

int is_in_range(sfVector2i pos_cursor, sfVector2f pos_hitcircle, float range)
{
    float distance = 0;

    distance = pow((pos_cursor.x - pos_hitcircle.x), 2) +
    pow((pos_cursor.y - pos_hitcircle.y), 2);
    if (distance < pow(range, 2)) {
        return (1);
    }
    return (0);
}

int find_current_circle(osu *osu)
{
    int i = 0;

    for (;osu->map->hit_objects[i].clicked == 1 || osu->map->hit_objects[i].missed == 1; ++i);
    return (i);
}

float count_clicked(osu *osu)
{
    float nb = 0;

    for (int i = 0; i < osu->map->nb_circle; ++i)
        (osu->map->hit_objects[i].clicked == 1) ? nb++ : 0;
    return (nb);
}

void display_circles(int timing, osu *osu)
{
    sfVector2f pos;
    sfVector2i pos_mouse;
    sfVector2f pos_current_hit_circle;
    int window = 0;
    int current_rank = find_current_circle(osu);
    int j = current_rank - 10;

    for (int i = current_rank; i < osu->map->nb_circle; ++i, ++j) {
        sprintf(osu->text_precision,"%.2f", (osu->map->precision / current_rank) * 100);
        sprintf(osu->text_combo,"%i", osu->map->combo);
        if (i > current_rank + 100)
            return;
        pos_current_hit_circle.x = (float) osu->map->hit_objects[current_rank].x * SCALE_COORD_X + (CIRCLE_SIZE * SCALE_TO_SCREEN * Scale);
        pos_current_hit_circle.y = (float) osu->map->hit_objects[current_rank].y * SCALE_COORD_Y + (CIRCLE_SIZE * SCALE_TO_SCREEN * Scale);
        if (manage_keyA_input(osu) || manage_keyZ_input(osu)) {
            pos_mouse = sfMouse_getPositionRenderWindow(osu->w);
            if (osu->map->hit_objects[current_rank].clicked == 0 && timing <= osu->map->hit_objects[current_rank].timing + TIMING_AFTER && timing >=
            osu->map->hit_objects[current_rank].timing - TIMING_BEFORE) {
                if (is_in_range(pos_mouse, pos_current_hit_circle, CIRCLE_SIZE * SCALE_TO_SCREEN * Scale + TOLERANCE) == 1) {
                    window = abs((timing - 25) - osu->map->hit_objects[current_rank].timing);
                    if (window <= 65) {
                        sfText_setString(osu->map->hit_objects[current_rank].text_when_clicked, "300");
                        sfText_setColor(osu->map->hit_objects[current_rank].text_when_clicked, sfBlue);
                        osu->score += 300 * osu->map->combo + 1;
                        osu->map->combo++;
                        osu->map->hit_objects[current_rank].clicked = 1;
                        osu->map->precision += 1.0f;
                    } else if (window <= 125) {
                        sfText_setString(osu->map->hit_objects[current_rank].text_when_clicked, "100");
                        sfText_setColor(osu->map->hit_objects[current_rank].text_when_clicked, sfGreen);
                        osu->score += 100 * osu->map->combo + 1;
                        osu->map->combo++;
                        osu->map->hit_objects[current_rank].clicked = 1;
                        osu->map->precision += 0.75f;
                    } else if (window <= 150) {
                        sfText_setString(osu->map->hit_objects[current_rank].text_when_clicked, "50");
                        sfText_setColor(osu->map->hit_objects[current_rank].text_when_clicked, sfYellow);
                        osu->score += 50 * osu->map->combo + 1;
                        osu->map->combo++;
                        osu->map->hit_objects[current_rank].clicked = 1;
                        osu->map->precision += 0.25f;
                    } else {
                        osu->map->hit_objects[current_rank].missed = 1;
                        osu->map->combo = 0;
                    }
                }
            }
        }
        if (j >= 0 && (osu->map->hit_objects[j].missed == 0 && osu->map->hit_objects[j].clicked == 1) && timing <= osu->map->hit_objects[j].timing + 1000) {
            sfRenderWindow_drawText(osu->w, osu->map->hit_objects[j].text_when_clicked, NULL);
        }
        if (j >= 0 && (osu->map->hit_objects[j].missed == 1 && osu->map->hit_objects[j].clicked == 0) && timing <= osu->map->hit_objects[j].timing + 1000) {
            sfText_setString(osu->map->hit_objects[j].text_when_clicked, "X");
            sfText_setCharacterSize(osu->map->hit_objects[j].text_when_clicked, 120);
            sfText_setColor(osu->map->hit_objects[j].text_when_clicked, sfRed);
            sfRenderWindow_drawText(osu->w, osu->map->hit_objects[j].text_when_clicked, NULL );
        }
        if ((osu->map->hit_objects[i].clicked == 0 && osu->map->hit_objects[i].missed == 0) && timing <= osu->map->hit_objects[i].timing + TIMING_AFTER && timing >=
            osu->map->hit_objects[i].timing - TIMING_BEFORE) {
            pos.x = CIRCLE_SIZE * SCALE_TO_SCREEN * Scale - ((osu->map->hit_objects[i].timing - (timing - TIMING_BEFORE)) / APPROACH_RATE);
            pos.y = CIRCLE_SIZE * SCALE_TO_SCREEN * Scale - ((osu->map->hit_objects[i].timing - (timing - TIMING_BEFORE)) / APPROACH_RATE);
            sfCircleShape_setOrigin(osu->map->hit_objects[i].approach_circle,
                pos);
            sfCircleShape_setRadius(osu->map->hit_objects[i].approach_circle,
                CIRCLE_SIZE * SCALE_TO_SCREEN * Scale - ((osu->map->hit_objects[i].timing - (timing - TIMING_BEFORE)) / APPROACH_RATE));
            (CIRCLE_SIZE * SCALE_TO_SCREEN * Scale - ((osu->map->hit_objects[i].timing - (timing - TIMING_BEFORE)) / APPROACH_RATE) <= CIRCLE_SIZE * SCALE_TO_SCREEN * Scale)
            ? sfRenderWindow_drawCircleShape(osu->w, osu->map->hit_objects[i].approach_circle, NULL) : 0;
            sfRenderWindow_drawCircleShape(osu->w, osu->map->hit_objects[i].hitcircle, NULL);
        }
        if (osu->map->hit_objects[i].missed == 0 && osu->map->hit_objects[i].clicked == 0 && timing >= osu->map->hit_objects[i].timing + TIMING_AFTER)
        {
            osu->map->combo = 0;
            osu->map->hit_objects[i].missed = 1;
        }
    }
    if (current_rank == osu->map->nb_circle)
    {
        sfRenderWindow_close(osu->w);
    }
}