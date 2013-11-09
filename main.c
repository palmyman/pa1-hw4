/* 
 * File:   main.c
 * Author: palmyman
 *
 * Created on November 9, 2013, 5:53 PM
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct TDispenser {
    int bottomAlt, topAlt;
    unsigned int base;
} TDISPENSER;

typedef struct TBuffer {
    TDISPENSER * bottom[200000];
    TDISPENSER * top[200000];
    unsigned int records;
    long unsigned volume;
} TBUFFER;

int readCount(int * count) {
    printf("Zadejte pocet nadrzi:\n");
    if (!scanf("%d", count) || *count < 1)
        return 0;
    return 1;
}

unsigned int findBottomIndex(const TBUFFER * buffer, int bottomAlt) {
    int from = 0, to = buffer->records - 1, loop = -1, middle = 0;
    while (from <= to && buffer->records) {
        loop++;
        middle = (from + to) / 2;
        if (bottomAlt < buffer->bottom[middle]->bottomAlt)
            to = middle - 1;
        else if (bottomAlt > buffer->bottom[middle]->bottomAlt)
            from = middle + 1;
        else {
            return middle;

        }
    }
    return from;
}

unsigned int findTopIndex(const TBUFFER * buffer, int topAlt) {
    int from = 0, to = buffer->records - 1, loop = -1, middle = 0;
    while (from <= to && buffer->records) {
        loop++;
        middle = (from + to) / 2;
        if (topAlt < buffer->top[middle]->topAlt)
            to = middle - 1;
        else if (topAlt > buffer->top[middle]->topAlt)
            from = middle + 1;
        else {
            return middle;

        }
    }
    return from;
}

int readOneDispenser(TBUFFER * buffer) {
    int alt, h, w, d;
    unsigned int targetIndex;
    TDISPENSER * dispenser;
    if (scanf("%d %d %d %d", &alt, &h, &w, &d) != 4 ||
            h < 1 || w < 1 || d < 1)
        return 0;

    dispenser = (TDISPENSER *) malloc(sizeof (dispenser));

    dispenser->bottomAlt = alt;
    dispenser->topAlt = alt + h;
    dispenser->base = w * d;

    targetIndex = findBottomIndex(buffer, alt);
    //printf("bottomIndex = %d\n", targetIndex);
    int i;
    for (i = buffer->records; i > targetIndex; i--) {
        buffer->bottom[i] = buffer->bottom[i - 1];
    }
    buffer->bottom[targetIndex] = dispenser;

    targetIndex = findTopIndex(buffer, alt + h);
    //printf("topIndex = %d\n", targetIndex);
    for (i = buffer->records; i > targetIndex; i--) {
        buffer->top[i] = buffer->top[i - 1];
    }
    buffer->top[targetIndex] = dispenser;

    buffer->records++;
    buffer->volume += h * w * d;
    return 1;
}

void freeBuffer(TBUFFER * buffer) {
    int i;
    for (i = 0; i < buffer->records; i++) {
        free(buffer->bottom[i]);
    }
    buffer->records = 0;
    buffer->volume = 0;
}

int readDispensers(TBUFFER * buffer, int count) {
    int i;
    buffer->records = 0;
    buffer->volume = 0;
    printf("Zadejte parametry nadrzi:\n");
    for (i = 0; i < count; i++) {
        if (!readOneDispenser(buffer))
            return 0;
    }
    return 1;
}

int readVolume(int * volume) {
    int status = scanf("%d", volume);    
    if (!status || *volume < 0) return 0;
    return status;
}

float evalAltitude(TBUFFER * buffer, int volume) {
    return 0;
}

/*
 * 
 */
int main(int argc, char** argv) {
    TBUFFER buffer;
    int count = 0, volume = 0, status = 0;

    if (!readCount(&count) || !readDispensers(&buffer, count)) {
        printf("Nespravny vstup.\n");
        return 0;
    }

    printf("Zadejte objem vody:\n");
    do {
        status = readVolume(&volume);
        if (!status) {
            printf("Nespravny vstup.\n");
            freeBuffer(&buffer);
            return 0;
        }
        if (volume == 0)
            printf("Prazdne.\n");
        else if (volume > buffer.volume)
            printf("Pretece.\n");
        else
            printf("h = %f\n", evalAltitude(&buffer, volume));

    } while (status != EOF);

    freeBuffer(&buffer);

    return (EXIT_SUCCESS);
}

