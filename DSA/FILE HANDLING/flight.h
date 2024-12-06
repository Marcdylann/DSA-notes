#ifndef FLIGHT_H
#define FLIGHT_H

#define MAX 20

typedef char String[30];

typedef struct {
    int minute;
    int hour;
} Schedule;

typedef struct {
    String destName;
    int destPriority;
} Destination;

typedef struct {
    int flightCode;
    String aircraft;
    Schedule flightSched;
    Destination flightDest;
} Flight;

typedef struct {
    Flight elems[MAX];
    int count;
} PriorityQueue;

Flight newFlight(int flightCode, String aircraft, Schedule flightSched, Destination flightDest);
Schedule newSched(int minute, int hour);
Destination newDest(String destName, int destPriority);
void displayFlight(Flight a);
void insertFlight(PriorityQueue *list, Flight a);
int comparePrio(Flight a, Flight b);
void display(PriorityQueue list);
Flight dequeue(PriorityQueue* list);
void flightsBefore(PriorityQueue *list, Flight a, PriorityQueue* new);

#endif
