#include "kernel/pstat.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

struct pstat pinfo;

int main(int argc, char *argv[]){
    // get pinfo
    getpinfo(&pinfo);
    // iterate over all processes
    for(int i = 0; i < NPROC; i++){
        // print stats for processes in use
        if(pinfo.inuse[i] > 0){
            printf("Process %d: Ticks = %d, Tickets = %d\n", i, pinfo.ticks[i], pinfo.tickets[i]);
        }
    }
}