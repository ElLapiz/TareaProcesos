#include <stdio.h>
#include <unistd.h>
#define ERROR -1

pid_t childPid;

void imprimeHijo(int numero){
    printf("Hijo : %d\n", (numero + 1));
}

void collectCpuData(int numero){
    imprimeHijo(numero);
    printf("Hola vengo a recolectar datos de CPU\n");
    sleep(1);
}

void collectMemData(int numero){
    imprimeHijo(numero);
    printf("Hola vengo a recolectar datos de memoria\n");
    sleep(1);
}

void collectNetData(int numero){
    imprimeHijo(numero);
    printf("Hola vengo a recolectar datos de red\n");
    sleep(1);
}

void collectDiskData(int numero){
    imprimeHijo(numero);
    printf("Hola vengo a recolectar datos de disco\n");
    sleep(1);
}

void asignaTrabajo(int numero){
    switch(numero){
        case 0:
            collectCpuData(numero);
            break;
        case 1:
            collectDiskData(numero);
            break;
        case 2:
            collectMemData(numero);
            break;
        case 3:
            collectNetData(numero);
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


