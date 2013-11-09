/* 
 * File:   main.c
 * Author: palmyman
 *
 * Created on November 9, 2013, 5:53 PM
 */

#include <stdio.h>
#include <stdlib.h>
typedef struct TDispenser {
    int alt, height, base;
} TDISPENSER;

typedef struct TBuffer {
    TDISPENSER * buffer[200000];
    int records, volume;    
    
} TBUFFER;

int readCount() {
    int count;
    printf("Zadejte pocet nadrzi:\n");
    if(!scanf("%d", &count) || count < 1)
        return 0;
    return count;
}

int readDispensers(TBUFFER * buffer, int count) {
    int i, alt, h, w, d;
    buffer->records = 0;
    buffer->volume = 0;
    printf("Zadejte parametry nadrzi:\n");
    for (i = 0; i < count; i++) {
        if(scanf("%d %d %d %d", &alt, &h, &w, &d) != 4 ||
                h < 1 || w < 1 || d < 1)
            return 0;
        buffer->buffer[i]->alt = alt;
        buffer->buffer[i]->height = h;
        buffer->buffer[i]->base = w * d;
        buffer->records++;
        buffer->volume += h * w * d;
    }
    return 1;
}

/*
 * 
 */
int main(int argc, char** argv) {
    
    return (EXIT_SUCCESS);
}

