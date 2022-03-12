/*
 * Syntelos CON7
 * Copyright (C) 2021, John Pritchard, Syntelos
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bix.h"
#include "con7.h"
/*
 *
 */
typedef enum main_output {

    main_output_non = 0,
    main_output_hex = 1,
    main_output_bin = 2,
    main_output_asc = 4

} main_output;
main_output main_output_kind(const char* usr){
    if (null != usr){
        switch(*usr){
        case 'h':
            if (0 == strcmp("hex",usr)){
                return main_output_hex;
            }
            break;
        case 'b':
            if (0 == strcmp("bin",usr)){
                return main_output_bin;
            }
            break;
        case 'a':
            if (0 == strcmp("asc",usr)){
                return main_output_asc;
            }
            break;
        }
    }
    return main_output_non;
}
/*
 */
int usage(char* pn){
    fprintf(stderr,"usage\n\t%s -x <hex> -o (hex|bin|asc)\n\ndescription\n\n\tInput hex, and output HEX or BIN or ASC.\n\n",pn);
    return 1;
}
/*
 * Input hex and output HEX or BIN or ASC.
 */
int main(int argc, char** argv){
    char* pn = argv[0];
    if (5 == argc && 0 == strcmp("-x",argv[1]) && 0 == strcmp("-o",argv[3])){
        char *x7 = argv[2];
        bix *b7 = bix_decode(x7,bix_count(x7,strlen(x7)));
        if (null != b7){
            main_output kind = main_output_kind(argv[4]);

            con7 *c7 = con7_decode(b7->content,b7->size);

            switch(kind){
            case main_output_hex:
                if (null != c7 && 0 != c7->size){
                    bix *bx = bix_encode(c7->content,c7->size);
                    if (null != bx && 0 != bx->size){
                        char* cc = bx->content;
                        fprintf(stdout,"%s\n",cc);
                        return 0;
                    }
                    else {
                        return 1;
                    }
                }
                else {
                    return 1;
                }
            case main_output_bin:
                if (null != c7 && 0 != c7->size){
                    fwrite(c7->content,1,c7->size,stdout);
                    return 0;
                }
                else {
                    return 1;
                }
            case main_output_asc:
                if (null != c7 && 0 != c7->size){
                    char *cc = c7->content;
                    fprintf(stdout,"%s\n",cc);
                    return 0;
                }
                else {
                    return 1;
                }
            default:
                return 1;
            }
        }
        else {
            return 1;
        }
    }
    else {
        return usage(pn);
    }
}
