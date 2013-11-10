/* 
 * File:   main.c
 * Author: palmyman
 *
 * Created on November 9, 2013, 5:53 PM
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct TLevel {
    int altitude;
    long int area;
    long int currentArea;
    long unsigned int volume;
} TLEVEL;

typedef struct TBuffer {
    TLEVEL * levels[400000];
    unsigned int records;
    long unsigned volume;
} TBUFFER;

int readCount(int * count) {
    printf("Zadejte pocet nadrzi:\n");
    if (!scanf("%d", count) || *count < 1)
        return 0;
    return 1;
}

int findIndex(const TBUFFER * buffer, int altitude, unsigned int * targetIndex) {
    int from = 0, to = buffer->records - 1, loop = -1, middle = 0;
    while (from <= to && buffer->records) {
        loop++;
        middle = (from + to) / 2;
        if (altitude < buffer->levels[middle]->altitude)
            to = middle - 1;
        else if (altitude > buffer->levels[middle]->altitude)
            from = middle + 1;
        else {
            * targetIndex = middle;
            return 1;
        }
    }
    * targetIndex = from;
    return 0;
}

int findIndexVol(const TBUFFER * buffer, unsigned int volume, unsigned int * targetIndex) {
    int from = 0, to = buffer->records - 1, loop = -1, middle = 0;
    while (from <= to && buffer->records) {
        loop++;
        middle = (from + to) / 2;
        if (volume < buffer->levels[middle]->volume)
            to = middle - 1;
        else if (volume > buffer->levels[middle]->volume)
            from = middle + 1;
        else {
            * targetIndex = middle;
            return 1;
        }
    }
    * targetIndex = from;
    return 0;
}

int readOneDispenser(TBUFFER * buffer) {
    int alt, h, w, d;
    unsigned int targetIndex;
    TLEVEL * top, * bottom;
    if (scanf("%d %d %d %d", &alt, &h, &w, &d) != 4 ||
            h < 1 || w < 1 || d < 1)
        return 0;

    bottom = (TLEVEL *) malloc(sizeof (* bottom));
    top = (TLEVEL *) malloc(sizeof (* top));

    bottom->altitude = alt;
    bottom->area = w * d;
    bottom->currentArea = 0;
    bottom->volume = 0;

    top->altitude = alt + h;
    top->area = -1 * w * d;
    top->currentArea = 0;
    top->volume = 0;

    if (!findIndex(buffer, bottom->altitude, &targetIndex)) {
        unsigned int i;
        for (i = buffer->records; i > targetIndex; i--) {
            buffer->levels[i] = buffer->levels[i - 1];
        }
        buffer->levels[targetIndex] = bottom;
        buffer->records++;
    } else {
        buffer->levels[targetIndex]->area += bottom->area;
        free(bottom);
    }

    if (!findIndex(buffer, top->altitude, &targetIndex)) {
        unsigned int i;
        for (i = buffer->records; i > targetIndex; i--) {
            buffer->levels[i] = buffer->levels[i - 1];
        }
        buffer->levels[targetIndex] = top;
        buffer->records++;
    } else {
        buffer->levels[targetIndex]->area += top->area;
        free(top);
    }

    buffer->volume += h * w * d;
    return 1;
}

void freeBuffer(TBUFFER * buffer) {
    unsigned int i;
    for (i = 0; i < buffer->records; i++) {
        free(buffer->levels[i]);
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

float evalAltitude(const TBUFFER * buffer, unsigned int volume) {
    unsigned int currentLevelArea = 0, blockVolume;

    unsigned int i;
    for (i = 0; i < buffer->records - 1; i++) {
        currentLevelArea += buffer->levels[i]->area;

        blockVolume = currentLevelArea * abs(buffer->levels[i + 1]->altitude - buffer->levels[i]->altitude);
        if (volume < blockVolume) {
            //printf("found index = %d\n", i);
            return buffer->levels[i]->altitude + ((float) volume / currentLevelArea);
        } else if (blockVolume == volume) {
            //printf("found index = %d\n", i);
            return buffer->levels[i + 1]->altitude;
        } else {
            volume -= blockVolume;
        }
    }
    return -49;
}

float evalAltitudeDynamic(const TBUFFER * buffer, unsigned int volume) {
    unsigned int i = 0;
    findIndexVol(buffer, volume, &i);
    i--;
    //printf("found index = %d\n", i);

    return buffer->levels[i]->altitude + (((float) volume - buffer->levels[i]->volume )/ buffer->levels[i]->currentArea);
}

void printBuffer(const TBUFFER * buffer) {
    unsigned int i;
    printf("Buffer has %u records with %lu total volume\n", buffer->records, buffer->volume);
    printf("I\tALT\tAREA\tTAREA\tTVOL\n");
    for (i = 0; i < buffer->records; i++) {
        printf("%d\t %d\t %ld\t %ld\t %lu\n", i, buffer->levels[i]->altitude, buffer->levels[i]->area, buffer->levels[i]->currentArea, buffer->levels[i]->volume);
    }
}

void evalBlockVolumes(TBUFFER * buffer) {
    unsigned int i;
    unsigned int currentLevelArea = 0, blockVolume = 0;

    buffer->levels[0]->volume = 0;
    //buffer->levels[buffer->records - 1]->volume = buffer->volume;
    for (i = 0; i < buffer->records - 1; i++) {
        currentLevelArea += buffer->levels[i]->area;
        buffer->levels[i]->currentArea = currentLevelArea;
        blockVolume += currentLevelArea * abs(buffer->levels[i + 1]->altitude - buffer->levels[i]->altitude);
        buffer->levels[i + 1]->volume = blockVolume;
    }
}

/*
 * 
 */
int main(int argc, char** argv) {
    TBUFFER buffer;
    int count = 0, status = 0;
    int volume = 0;

    if (!readCount(&count) || !readDispensers(&buffer, count)) {
        printf("Nespravny vstup.\n");
        return 0;
    }

    evalBlockVolumes(&buffer);

    //printBuffer(&buffer);
    status = readVolume(&volume);
    printf("Zadejte objem vody:\n");
    while (status != EOF) {
        if (!status) {
            printf("Nespravny vstup.\n");
            freeBuffer(&buffer);
            return 0;
        }
        if (volume == 0)
            printf("Prazdne.\n");
        else if ((unsigned) volume > buffer.volume)
            printf("Pretece.\n");
        else {
            //printf("h = %f\n", evalAltitude(&buffer, volume));
            printf("h = %f\n", evalAltitudeDynamic(&buffer, volume));
        }
        status = readVolume(&volume);
    };

    freeBuffer(&buffer);

    return (EXIT_SUCCESS);
}

