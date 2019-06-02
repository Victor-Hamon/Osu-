/*
** EPITECH PROJECT, 2019
** Project Name
** File description:
** score manager
*/

#include <stdbool.h>
#include "includes.h"

bool manage_keyA_input(osu *osu)
{
    if (sfKeyboard_isKeyPressed(sfKeyA) && osu->input.input_A != 1) {
        osu->input.input_A = 1;
        return (true);
    }
    if (!sfKeyboard_isKeyPressed(sfKeyA) && osu->input.input_A == 1)
        osu->input.input_A = 0;
    return (false);
}

bool manage_keyZ_input(osu *osu)
{
    if (sfKeyboard_isKeyPressed(sfKeyZ) && osu->input.input_Z != 1) {
        osu->input.input_Z = 1;
        return (true);
    }
    if (!sfKeyboard_isKeyPressed(sfKeyZ) && osu->input.input_Z == 1)
        osu->input.input_Z = 0;
    return (false);
}