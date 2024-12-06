#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flight.h"

int main(){
    Flight list[MAX];
    
    // Initialize destinations
    Destination NAIA = newDest("Ninoy Aquino International AP", 1);
    Destination Clark = newDest("Clark International AP", 2);
    Destination Francisco = newDest("Francisco Bangoy International AP", 2);
    Destination Iloilo = newDest("Iloilo International AP", 2);
    Destination Panglao = newDest("Panglao International AP", 3);
    Destination Bicol = newDest("Bicol International AP", 4);
    Destination Bantayan = newDest("Bantayan AP", 5);
    Destination Alto = newDest("Alto Airfield", 6);
    
    // Create flight list
    list[0] = newFlight(101, "PAL", newSched(30, 10), NAIA);
    list[1] = newFlight(302, "CebuPac", newSched(30, 10), Clark);
    list[2] = newFlight(301, "PAL", newSched(30, 12), Francisco);
    list[3] = newFlight(108, "SG", newSched(30, 5), Iloilo);
    list[4] = newFlight(205, "Boieng", newSched(45, 6), Panglao);
    list[5] = newFlight(208, "PAL", newSched(30, 6), Bicol);
    list[6] = newFlight(407, "CebuPac", newSched(10, 15), Bantayan);
    list[7] = newFlight(310, "Emirates", newSched(10, 15), NAIA);
    list[8] = newFlight(609, "PAL", newSched(20, 22), NAIA);
    
    FILE *fp;
    
    // Write to destination file
    fp = fopen("destination_file.dat", "wb");
    if(fp != NULL){
        fwrite(list, sizeof(Flight), 9, fp);
    } else {
        printf("\nDestination file does not exist.");
    }
    
    PriorityQueue flights = { .count = 0 };  // Initialize the priority queue
    Flight p;
    
    // Read from destination file
    fp = fopen("destination_file.dat", "rb");
    if (fp != NULL){
        while (fread(&p, sizeof(Flight), 1, fp)) {
            insertFlight(&flights, p);  // Insert each flight into the priority queue
        }
        fclose(fp);  // Always close the file after reading
    } else {
        printf("Failed to open file for reading.\n");
        return 1;  // Exit if file cannot be opened
    }

    display(flights);  // Display flights in priority order
    
    // Create a new priority queue for filtered flights
    PriorityQueue newQueue = { .count = 0 };
    
    // Filter flights scheduled before a specific flight
    flightsBefore(&flights, list[6], &newQueue);
    display(newQueue);
    
    return 0;  // Successfully complete the program
}
