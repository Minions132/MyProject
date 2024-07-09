#include "Button.h"
#include <iostream>
#include "graphics.h"

Button::Button(int a, int b, int w, int h, const std::string &t, const std::function<void()> &f)
    : x(a), y(b), width(w), height(h), scale(1.0f), isMouseOver(false), text(t), OnClick(f)
{    
}

void Button::CheckMouseOver(int m_x, int m_y)
{
    isMouseOver = (m_x >= x && m_x <= x + width && m_y >= y && m_y <= y + height);
    if(isMouseOver){
        scale = 0.9f;
    }
    else scale = 1.0f;
}

bool Button::CheckClick(int m_x, int m_y){
    if(m_x >= x && m_x <= x + width && m_y >= y && m_y <= y + height){
        OnClick();
        isMouseOver = false;
        scale = 1.0f;
        return true;
    }
    return false;
}

void Button::draw(){
    int s_width = width * scale;
    int s_height = height * scale;
    int s_x = x + (width - s_width) / 2;
    int s_y = y + (height - s_height) / 2;
    if(isMouseOver){
        setlinecolor(RGB(0, 120, 215));
        setfillcolor(RGB(229, 241, 251));
    }
    else{
        setlinecolor(RGB(173, 173, 173));
        setfillcolor(RGB(225, 225, 225));
    }
    fillrectangle(s_x, s_y, s_x + s_width, s_y + s_height);
    settextcolor(BLACK);
    setbkmode(TRANSPARENT);
    int text_x = s_x + (s_width - textwidth(text.c_str())) / 2;
    int text_y = s_y + (s_height - textheight("ºÚÌå")) / 2;
    outtextxy(text_x, text_y, text.c_str());
}
