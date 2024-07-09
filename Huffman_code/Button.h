#pragma once
#include <iostream>
#include <functional>

class Button{
private:
    int x;
    int y;
    int width;
    int height;
    float scale;
    bool isMouseOver;
    std::string text;
    std::function<void()> OnClick;
public:
    Button(int a, int b, int w, int h, const std::string &t, const std::function<void()> &f);
    void CheckMouseOver(int m_x, int m_y);
    bool CheckClick(int m_x, int m_y);
    void draw();
};