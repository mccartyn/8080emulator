

#include <stdio.h>
#include <stdint.h>

/* Instead of using a switch case statement or a search for operational codes we will
attempt to use a lookup table with function pointers. The idea here is that because 
we are not memory constrained on modern computers we can store the entire op code look
up table in a static array. This will reduce the time needed to search a list for the 
opcode function pointer or fall through a case statement. */

uint16_t pc;


// Opcode functions
uint16_t na(uint8_t a, uint8_t b){
    uint16_t next_addr;
    next_addr = pc + 1; //nop is 1 byte
    perror("OpCode not implemented");
    return 0;
}

uint16_t nop(uint8_t a, uint8_t b){
    printf("nop/r/n");
    uint16_t next_addr;
    next_addr = pc + 1; //nop is 1 byte
    return next_addr;
}

// Function to get the size of a file in bytes
long getFileSize(const char *filename) {
    FILE *file = fopen(filename, "rb"); // Open the file in binary read mode
    if (file == NULL) {
        perror("Error opening file");
        return -1; // Return -1 if the file cannot be opened
    }

    fseek(file, 0, SEEK_END); // Move the file pointer to the end
    long size = ftell(file);  // Get the position of the file pointer (file size)
    fclose(file);             // Close the file
    return size;
}


// Number of handled opcodes
static const uint8_t MAX_OPCODE_NUMBER = 255;
// Create our operation function pointer type
uint16_t (*operations[(MAX_OPCODE_NUMBER]) (uint8_t, uint8_t) = {na};

// Create array of function pointers
operations[0] = nop;

int main() {
    const char *filename = "space-invaders.rom"; // Replace with your file name

    long size = getFileSize(filename);
    if (size != -1) {
        printf("The size of the file '%s' is: %ld bytes\n", filename, size);
    }

   // Open File
   FILE *rom = fopen(filename, "rb");
   
   uint8_t op = rom;
   uint8_t (*operation)(uint8_t, uint8_t);

   // Run program
   while(pc < size){
        op = rom + pc;
        operation = operations[op];
        uint8_t val = operation(0,0);
   }



    return 0;
}
