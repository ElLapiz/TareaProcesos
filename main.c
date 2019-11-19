#include <stdio.h>
#include <unistd.h>
#include "incl/memory/Collect_Memory_Minner.cpp"
#include "incl/cpu/Collector_CPU_Minner.cpp"
#include "incl/network/Collector_Network_Minner.cpp"
#include "incl/disk/Collector_Disk_Minner.cpp"


#define ERROR -1

pid_t childPid;

void asignaTrabajo(int numero){
    switch(numero){
        case 0:
            collectCpuData();
            break;
        case 1:
            collectDiskData();
            break;
        case 2:
            collectMemData();
            break;
        case 3:
            collectNetData();
            break;
    }
}

int creaHijos(pid_t childPid) {
    int i;

    for(i = 0; i < 4; i++){
        switch(childPid = fork()){
            case -1:
                return ERROR;
            case 0:
                asignaTrabajo(i);
                _exit(0);
            default:
                sleep(1);
                break;
        }

    }
}

//*********************
//     Método main
//*********************
int main(){
    return creaHijos(childPid);
}


