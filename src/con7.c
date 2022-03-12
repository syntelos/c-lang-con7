/*
 * Syntelos CON7
 * Copyright (C) 2022, John Pritchard, Syntelos
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * (LGPL and GPL) as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the LGPL
 * and GPL for more details.
 *
 * You should have received a copy of the LGPL and GPL along with this
 * program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>

#include "con7.h"

con7* con7_init(size_t length){

    con7 *re = calloc(1,sizeof(con7));
    if (null != re){
        re->size = length;
        re->content = calloc(length,1);
        if (null != re->content){

            return re;
        }
        else {
            free(re);
            return null;
        }
    }
    else {
        free(re);
        return null;
    }
}
void con7_destroy(con7* c7){
    if (null != c7){
        if (0 != c7->size && null != c7->content){

            memset(c7->content,0,c7->size);
            free(c7->content);
        }

        memset(c7,0,sizeof(con7));
        free(c7);
    }
}
size_t con7_count(void* source, size_t length){
    size_t count = 0;
    if (null != source && 0 != length){
        uint8_t *sp = source;
        off_t index;
        for (index = 0; index < length; index++){

            if (0x80 == (*sp++ & 0x80)){

                count += 1;
                continue;
            }
            else {
                count += 1;

                return count;
            }
        }
    }
    return count;
}
con7* con7_decode(void* source, size_t length){
    if (null != source && 0 != length){
        con7 *re = con7_init(length);
        if (null != re){

            uint8_t *sp = source;
            uint8_t *tp = re->content;
            off_t index;
            for (index = 0; index < length; index++){

                if (0x80 == (*sp & 0x80)){

                    *tp++ = (*sp++ & 0x7F);
                }
                else {
                    *tp++ = *sp++;

                    re->size = (index+1);

                    break;
                }
            }

            re->state = con7_state_decoded;
            return re;
        }
    }
    return null;
}
con7* con7_encode(void* source, size_t length){
    if (null != source && 0 != length){
        con7 *re = con7_init(length);
        if (null != re){

            off_t terminal = (length-1);

            uint8_t *sp = source;
            uint8_t *tp = re->content;
            off_t index;

            for (index = 0; index < terminal; index++){

                *tp++ = (*sp++ | 0x80);
            }
            *tp++ = *sp++;

            re->state = con7_state_encoded;
            return re;
        }
    }
    return null;
}
