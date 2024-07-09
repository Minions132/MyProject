#include "TextBox.h"
#include <iostream>
#include <graphics.h>

TextBox::TextBox(int a, int b, int w, int h, int max)
    : x(a), y(b), width(w), height(h), Max_size(max), is_Selected(false), show_cursor(false), pos_cursor(0)
{
}

bool TextBox::CheckClick(int m_x, int m_y){  
    if(m_x >= x && m_x <= x + width && m_y >= y && m_y <= y + height){
        is_Selected = true;
        return true;
    }
    else{
        is_Selected = false;
        pos_cursor = text.length();
        return false;
    }
}

void TextBox::keyboard_input(char ch){
    if(is_Selected){
        switch(ch){
            case '\b':
                if(!text.empty() && pos_cursor > 0){
                    text.erase(pos_cursor - 1, 1);
                    pos_cursor--;
                }
                break;
            case '\r':
            case '\n':
                pos_cursor = text.length();
                is_Selected = false;
                break;
            default:
                if(text.length() < Max_size){
                    text.insert(pos_cursor, 1, ch);
                    pos_cursor++;
                }
        }
    }
}

void TextBox::update_cursor(){
    static DWORD last = GetTickCount();
    DWORD cur = GetTickCount();
    if(cur - last >= 500){
        show_cursor = !show_cursor;
        last = cur;
    }
}

void TextBox::draw(){
    setfillcolor(WHITE);
    if(is_Selected){
        setlinecolor(RGB(0, 120, 215));
        fillrectangle(x, y, x + width, y + height);
    }
    else{
        setlinecolor(RGB(122, 122, 122));
        fillrectangle(x, y, x + width, y + height);
    }
    settextcolor(BLACK);
    setbkmode(TRANSPARENT);
    settextstyle(height * 3 / 4, 0, "");
    outtextxy(x + 5, y + (height - textheight("")) / 2, text.c_str());
    setlinecolor(BLACK);
    if(is_Selected && show_cursor){
        int X_cursor = x + 5 + textwidth(text.substr(0, pos_cursor).c_str());
        line(X_cursor, y + 2 + height / 8, X_cursor, y + height * 7 / 8 - 2);
    }
}

bool TextBox::GetSelect() const{
    return is_Selected;
}

void TextBox::clear(){
    text = "";
}

std::string TextBox::GetText(){
    return text;
}
