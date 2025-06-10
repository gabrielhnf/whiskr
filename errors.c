#include "errors.h"

void sendError(int line, char* where, char* message){
    printf("Error @ ln %d in %s: %s", line, where, message);

}

void report(int line, char* message){
    sendError(line, "", message);

}
