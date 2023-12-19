/*
 * Copyright (c) 2023 Daniel J. Thompson.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 or later.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h>
#include <ncurses.h>
#include "file.h"
#include "message.h"
#include "selection.h"
#define MAX_FILENAME_LENGTH 512
#define DEFAULT_CHUNK_SIZE 1048576
#define ERROR_OUTPUT 1
#define SPLIT_FILE 1
#define MERGE_FILE 2

// CLI arguments -> InputFile, OutputFile, mode selector, FileChunkSize
int main (int argc, char **argv){
    if (argc > 1){
        if (selectionCLI(argc, argv) == 0){
            return(EXIT_SUCCESS);
        } else {
            return(EXIT_FAILURE);
        }
    } else {
        if (modeSelection() == 0){
            return(EXIT_SUCCESS);
        } else {
            return(EXIT_FAILURE);
        }
    }
}