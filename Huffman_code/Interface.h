#pragma once
#include <vector>
#include "graphics.h"
#include "Button.h"
#include "TextBox.h"
#include "HuffmanTree.h"

class Interface{
private:
    int width;
    int height;
    int current_index;
    HuffmanTree* tree;
    std::vector<IMAGE*> pages;
    std::vector<std::vector<Button*>> buttons;
    std::vector<std::vector<TextBox*>> textboxes;
    
public:
    Interface(int a, int b);
    void Add_page(IMAGE* page);
    void Add_Button(Button* bt, int index);
    void Add_TextBox(TextBox* tb, int index);
    void setCurrentIndex(int index);
    void MouseClick(int m_x, int m_y);
    void MouseMove(int m_x, int m_y);
    void Key_input(char ch);
    void draw();
    void Init();
    void run();
    void Close();
};