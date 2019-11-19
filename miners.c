#define _GNU_SOURCE

void remove_spaces();
void collectorMemoryMinner();
char *readMemoryFile(char **pString);
int parseTotalMemory(int total_number, char **file_contentg);
int parseMemFree(int free_number, char **file_contentg);
float computePercentage(int number, int number1);
void collectorCPUMinner();
char *readCPUFile(char **pString);
int compute_total_process_running(int usermode, int kernelmode);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
    collectorMemoryMinner();
    collectorCPUMinner();
    return 0;
}

void collectorCPUMinner() {
    char *file_content = 0;
    int total_usermode, total_kernelmode = 0;
    file_content = readCPUFile(&file_content);

    //********** PARSE CPU USER PROCESS  **********
    char *usermodeProcess[16];
    memcpy(&usermodeProcess, &file_content[3], 9);
    usermodeProcess[15] = '\0';
    remove_spaces(&usermodeProcess);
    total_usermode = atoi(usermodeProcess);
    //printf("%d",total_usermode);

    //********** PARSE CPU KERNEL PROCESS  **********
    char *kernelmodeProcess[16];
    memcpy(&kernelmodeProcess, &file_content[11], 6);
    kernelmodeProcess[15] = '\0';
    remove_spaces(&kernelmodeProcess);

    int total_process_running = compute_total_process_running(total_usermode,total_kernelmode);
    printf("Your computer is running %d process", total_process_running);
}

int compute_total_process_running(int usermode, int kernelmode) {
    return usermode+kernelmode;
}

char *readCPUFile(char **file_content) {
    //Read /proc/stat
    FILE *cpuinfo = fopen("/proc/stat", "rb");  //rb = read binary
    size_t size = 0;

    while(getdelim(&file_content, &size, 0, cpuinfo) != -1){
        puts(file_content);
    }
    fclose(cpuinfo);
    return file_content;
}

void collectorMemoryMinner() {
    char *file_content = 0;
    int total_number, free_number;
    float percentage;

    file_content = readMemoryFile(&file_content);
    //total_number = parseTotalMemory(total_number, &file_content);
    //free_number = parseMemFree(free_number, &file_content);


    //************** PARSE TOTAL MEMORY **************
    //This code below a parseTotalMemory function.
    char *total[16];
    memcpy(&total, &file_content[9], 15);
    total[15] = '\0';
    remove_spaces(&total);
    total_number = atoi(total);


    //************** PARSE FREE MEMORY **************
    //This code below a parseMemFree function.
    char *free[16];
    memcpy(&free, &file_content[40], 13);
    free[16] = '\0';
    remove_spaces(&free);
    free_number = atoi(free);

    percentage = computePercentage(free_number, total_number);
    printf("Percentage of memory available: %f", percentage);
}

float computePercentage(int used, int total) {
    return 100.0-(float)100.0*used/total;
}

int parseMemFree(int free_number, char **file_content) {
    char *free[16];
    memcpy(&free, &file_content[40], 13);
    free[16] = '\0';
    remove_spaces(&free);
    free_number = atoi(free);
}

int parseTotalMemory(int total_number, char **file_content) {
    char *total[16];
    memcpy(&total, &file_content[9], 15);
    total[15] = '\0';

    //printf(*total);
    remove_spaces(&total);
    total_number = atoi(total);

    printf("%d", total_number);

    return total_number;
}

char *readMemoryFile(char **file_content) {
    //Read /proc/meminfo
    FILE *cpuinfo = fopen("/proc/meminfo", "rb");  //rb = read binary
    size_t size = 0;

    while(getdelim(&file_content, &size, 0, cpuinfo) != -1){
        puts(file_content);
    }
    fclose(cpuinfo);
    return file_content;
}

//Remove white space
void remove_spaces(char* s) {
    const char* d = s;
    do {
        while (*d == ' ') {
            ++d;
        }
    } while (*s++ = *d++);
}