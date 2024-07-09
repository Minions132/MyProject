#pragma once
#include <iostream>

class TextBox{
private:
    int x;
    int y;
    int width;
    int height;
    bool is_Selected;
    bool show_cursor;
    int pos_cursor;
    int Max_size;
    std::string text;
public:
    TextBox(int a, int b, int w, int h, int max);
    bool CheckClick(int m_x, int m_y);
    void keyboard_input(char ch);
    void update_cursor();
    void draw();
    bool GetSelect() const;
    void clear();
    std::string GetText();
};