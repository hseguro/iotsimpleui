#include "ui.h"

int main(){
    IoTUI ui = IoTUI();
    if(!ui.Init()){
        printf("ERROR: initializing drawer.");
    }
    ui.Send("Hola que tal");
    //ui.DrawCube
}