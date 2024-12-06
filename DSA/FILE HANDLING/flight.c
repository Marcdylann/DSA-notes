#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flight.h"

void flightsBefore(PriorityQueue *list, Flight a, PriorityQueue* new) {
    FILE *fp = fopen("new_file.dat", "wb");
    if (fp == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }

    for (int i = 0; i < list->count; ++i) {
        if (list->elems[i].flightCode == a.flightCode) {
            break;
        }
        fwrite(&list->elems[i], sizeof(Flight), 1, fp);
    }

    fclose(fp);

    Flight p;
    fp = fopen("new_file.dat", "rb");
    if (fp == NULL) {
        printf("Failed to open file for reading.\n");
        return;
    }

    while (fread(&p, sizeof(Flight), 1, fp)) {
        insertFlight(new, p);  // Insert each flight into the new priority queue
    }

    fclose(fp);
}

Flight dequeue(PriorityQueue* list) {
    Flight a = list->elems[0];
    list->count--;
    int smallest = 0;
    int left = 0, right = 0;

    while (1) {
        left = smallest * 2 + 1;
        right = smallest * 2 + 2;

        if (right < list->count) {
            if (comparePrio(list->elems[smallest], list->elems[left]) == 0 &&
                comparePrio(list->elems[smallest], list->elems[right]) == 0) {
                break;
            }
            if (comparePrio(list->elems[left], list->elems[right]) == 1) {
                list->elems[smallest] = list->elems[left];
                smallest = left;
            } else {
                list->elems[smallest] = list->elems[right];
                smallest = right;
            }
        } else if (left < list->count) {
            if (comparePrio(list->elems[smallest], list->elems[left]) == 0) {
                break;
            } else {
                list->elems[smallest] = list->elems[left];
                smallest = left;
            }
        } else {
            break;
        }
    }
    list->elems[smallest] = list->elems[list->count];
    return a;
}

void display(PriorityQueue list) {
    for (int i = 0; i < list.count; ++i) {
        displayFlight(list.elems[i]);
    }
    printf("\n");
}

void insertFlight(PriorityQueue *list, Flight a) {
    int i;
    for (i = list->count; i > 0 && comparePrio(a, list->elems[(i - 1) / 2]) == 1; i = (i - 1) / 2) {
        list->elems[i] = list->elems[(i - 1) / 2];
    }
    list->elems[i] = a;
    list->count++;
}

int comparePrio(Flight a, Flight b) {
    if (a.flightSched.hour < b.flightSched.hour) {
        return 1;
    } else if (a.flightSched.hour > b.flightSched.hour) {
        return 0;
    } else {
        if (a.flightSched.minute < b.flightSched.minute) {
            return 1;
        } else if (a.flightSched.minute > b.flightSched.minute) {
            return 0;
        } else {
            if (a.flightDest.destPriority < b.flightDest.destPriority) {
                return 1;
            } else {
                return 0;
            }
        }
    }
}

void displayFlight(Flight a) {
    printf("Flight Code: %d\t| Aircraft: %s\t| Schedule: %d:%d\t| Destination: %-20s\n", a.flightCode, a.aircraft, a.flightSched.hour, a.flightSched.minute, a.flightDest.destName);
}

Destination newDest(String destName, int destPriority) {
    Destination a;
    strcpy(a.destName, destName);
    a.destPriority = destPriority;
    return a;
}

Schedule newSched(int minute, int hour) {
    Schedule a;
    a.minute = minute;
    a.hour = hour;
    return a;
}

Flight newFlight(int flightCode, String aircraft, Schedule flightSched, Destination flightDest) {
    Flight a;
    a.flightCode = flightCode;
    strcpy(a.aircraft, aircraft);
    a.flightSched = flightSched;
    a.flightDest = flightDest;
    return a;
}
