#include <iostream>
#include <graphics.h>
#include "HuffmanTree.h"
#include "Interface.h"

int main(){
    Interface i(800, 600);
    i.Init();
    i.run();
    i.Close();
}