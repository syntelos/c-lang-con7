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
#ifndef _syntelos_con7_h
#define _syntelos_con7_h

#include "syntelos.h"
/*
 * The state of the binary octet sequence found in the
 * "con7" structure "content".
 */
typedef enum con7_state {

    con7_state_none = 0,
    con7_state_encoded = 1,
    con7_state_decoded = 2

} con7_state;
/*
 * Note that (1 == sizeof(void)) and (void*)++ == ((void*)+1)
 */
typedef struct con7 {

    con7_state state;

    size_t size;

    void *content;

} con7;
/*
 * Allocate structure and content sequence.
 */
con7* con7_init(size_t);
/*
 * Free structure and content sequence.
 */
void con7_destroy(con7*);
/*
 * Count the length of the continuation code found within the argument
 * vector.  A continuation code has at least one octet, unless the
 * argument is null or empty.
 */
size_t con7_count(void*,size_t);
/*
 * The input is an eight bit continuation code.  The output
 * is a seven bit octet sequence.
 */
con7* con7_decode(void*,size_t);
/*
 * The input is a seven bit octet sequence.  The output is
 * an eight bit continuation code.
 */
con7* con7_encode(void*,size_t);

#endif
