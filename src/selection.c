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
#include <ncurses.h>
#include <stdlib.h>
#include "selection.h"
#include "file.h"
#include "message.h"

void fileSelection(char *inputFileName, char *outputFileName){
    if (inputFileName == NULL){
        fprintf(stderr, "Unable to allocate memory. Now terminating\n");
        exit(EXIT_FAILURE);
    }
    if (outputFileName == NULL){
        free(inputFileName);
        fprintf(stderr, "Unable to allocate memory. Now terminating\n");
        exit(EXIT_FAILURE);
    }
    refresh();
    printw("Please type in the name of the input file\n");
    refresh();
    getnstr(inputFileName, MAX_FILENAME_LENGTH);
    clear();
    printw("Please type in the name of the output file\n");
    refresh();
    getnstr(outputFileName, MAX_FILENAME_LENGTH);
    clear();
}

void chunkSelection(unsigned long long *chunkSize){
    printw("Do you want to set the size for each file slice the default value is %d\n", DEFAULT_CHUNK_SIZE);
    printw("If so then press 1 otherwise press any other key\n");
    char selector = getch();
    if (selector == '1'){
        printw("Enter in the size you want each file slice to be\n");
        scanw("%llu", chunkSize);
    }
    clear();
}
int modeSelection(){
    // Init ncurses
    initscr();
    start_color();
    if(has_colors() == false){
        endwin();
        fprintf(stderr, "Terminal doesn't support colors\n");
        return(COLOR_SUPPORT_ERROR);
    }
    char *inputFileName = (char *) malloc(MAX_FILENAME_LENGTH);
    char *outputFileName = (char *) malloc(MAX_FILENAME_LENGTH);
    unsigned long long fileChunkSize = DEFAULT_CHUNK_SIZE;
    init_pair(ERROR_OUTPUT, COLOR_RED, COLOR_BLACK);
    printw("Welcome to file splitter\n");
    printw("Press 1 to split a file\n");
    printw("Press 2 to merge a file\n");
    printw("Press any other key to quit\n");
    refresh();
    char selector = getch();
    int returnValue;
    clear();
    if(selector == '1'){
        fileSelection(inputFileName, outputFileName);
        chunkSelection(&fileChunkSize);
        returnValue = splitFile(inputFileName, outputFileName, fileChunkSize);
        if(returnValue != 0){
            errorMsg(1, inputFileName, outputFileName);
            return(returnValue);
        } else {
            completedSplitMsg(inputFileName, outputFileName);
            return(returnValue);
        }
    } else if(selector == '2'){
        fileSelection(inputFileName, outputFileName);
        returnValue = mergeFile(inputFileName, outputFileName);
        if(returnValue != 0){
            errorMsg(2, inputFileName, outputFileName);
            return(returnValue);
        } else {
            completedMergeMsg(inputFileName, outputFileName);
            return(returnValue);
        }
    } else{
        endwin();
        printf("Try again\n");
        free(inputFileName);
        free(outputFileName);
        return(EXIT_FAILURE);
    }
}