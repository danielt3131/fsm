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
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SPLIT_FILE 1
#define MERGE_FILE 2

int selectionCLI(int argc, char **argv, char *inputFileName, char *outputFileName, int *fileChunkSize){
    // Help menu
    if (argc == 2 && (strcmp(argv[1], "-h") == 0 || (strcmp(argv[1], "help") == 0)) {
        printf("The cli arguments are input file path, output file path, mode selector, and segment size\n");
        printf("The mode selector:\n");
        printf("1 to split a file\n");
        printf("2 to merge a file\n");
        printf("The segment size argument is expected as the number of bytes and is only used if the mode selector is 1\n");
        return (EXIT_SUCCESS);
    }
    if (argc > 3){
    inputFileName = argv[1];
    outputFileName = argv[2];
    if (argc > 4){
        *fileChunkSize = atoll(argv[4]);
    }
    if (atoi(argv[3]) == SPLIT_FILE){
        splitFile(inputFileName, outputFileName, (*fileChunkSize));
        free(inputFileName);
        free(outputFileName);
        return (EXIT_SUCCESS);
    } else if (atoi(argv[3]) == MERGE_FILE){
        mergeFile(inputFileName, outputFileName);
        free(inputFileName);
        free(outputFileName);
        return (EXIT_SUCCESS);
    } else{
        fprintf(stderr, "Wrong command line arguments\n");
        free(inputFileName);
        free(outputFileName);
        return (EXIT_FAILURE);
    }
}