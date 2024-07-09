#include "Interface.h"
#include <iostream>

void Interface::Add_page(IMAGE *page){
    pages.push_back(page);
    buttons.push_back({});
    textboxes.push_back({});
}

void Interface::Add_Button(Button *bt, int index){
    if(index >= 0 && index < pages.size()){
        buttons[index].push_back(bt);
    }
}

void Interface::Add_TextBox(TextBox *tb, int index){
    if(index >= 0 && index < pages.size()){
        textboxes[index].push_back(tb);
    }
}

void Interface::setCurrentIndex(int index){
    if(index >= 0 && index < pages.size()){
        current_index = index;
    }
}

void Interface::MouseClick(int m_x, int m_y){
    if(current_index >= 0 && current_index < pages.size()){
        for(Button* button : buttons[current_index]){
            if(button->CheckClick(m_x, m_y)){
                break;
            }
        }
        for(auto tb: textboxes[current_index]){
            tb->CheckClick(m_x, m_y);
        }
    }
}

void Interface::MouseMove(int m_x, int m_y){
    if(current_index >= 0 && current_index < pages.size()){
        for(Button* button : buttons[current_index]){
            button->CheckMouseOver(m_x, m_y);
        }
    }
}

void Interface::Key_input(char ch){
    if(current_index >= 0 && current_index < pages.size()){
        for(auto tb: textboxes[current_index]){
            if(tb->GetSelect()){
                tb->keyboard_input(ch);
            }
        }
    }
}

void Interface::draw(){
    if(current_index >= 0 && current_index < pages.size()){
        putimage(0, 0, pages[current_index]);
        for(Button* button : buttons[current_index]){
            button->draw();
        }
        for(auto tb: textboxes[current_index]){
            if(tb->GetSelect()){
                tb->update_cursor();
            }
            tb->draw();
        }
    }
}

Interface::Interface(int a, int b){
    width = a;
    height = b;
    current_index = -1;
    tree = new HuffmanTree();
}

void Interface::Init(){
    initgraph(width, height);
    int X = (width -  200) / 2;
    int Y = 175;
    int delta_Y = 100;
    IMAGE* page_begin_0 = new IMAGE(width, height);
    setfillcolor(RGB(240, 240, 240));
    solidrectangle(0, 0, width, height);
    std::string text_title = "Huffman Code System";
    int x_title = (width - textwidth(text_title.c_str())) / 2 - 50;
    int y_title = Y - delta_Y;
    settextcolor(BLACK);
    setbkmode(TRANSPARENT);
    settextstyle(25, 0, "");
    outtextxy(x_title, y_title, text_title.c_str());
    getimage(page_begin_0, 0, 0, width, height);
    Add_page(page_begin_0);
    IMAGE* page_input_1 = new IMAGE(width, height);
    solidrectangle(0, 0, width, height);
    getimage(page_input_1, 0, 0, width, height);
    Add_page(page_input_1);
    IMAGE* page_code_2 = new IMAGE(width, height);
    solidrectangle(0, 0, width, height);
    std::string title_2 = "Input examples:HuffmanText.txt";
    outtextxy(x_title, y_title, title_2.c_str());
    getimage(page_code_2, 0, 0, width, height);
    Add_page(page_code_2);
    IMAGE* page_decode_3 = new IMAGE(width, height);
    solidrectangle(0, 0, width, height);
    std::string title_3 = "Input examples:HuffmanCode.txt";
    outtextxy(x_title - 25, y_title, title_3.c_str());
    getimage(page_decode_3, 0, 0, width, height);
    Add_page(page_decode_3);
    IMAGE* page_output_4 = new IMAGE(width, height);
    solidrectangle(0, 0, width, height);
    std::string title_4 = "Success!";
    outtextxy(x_title + 75, y_title, title_4.c_str());
    getimage(page_output_4, 0, 0, width, height);
    Add_page(page_output_4);
    IMAGE* page_cin_5 = new IMAGE(width, height);
    solidrectangle(0, 0, width, height);
    std::string title_5 = "Input examples:4 A 3 B 2 C 1 D 4";
    outtextxy(x_title - 25, y_title, title_5.c_str());
    getimage(page_cin_5, 0, 0, width, height);
    Add_page(page_cin_5);
    IMAGE* page_fin_6 = new IMAGE(width, height);
    solidrectangle(0, 0, width, height);
    std::string title_6 = "Input examples:in.txt";
    outtextxy(x_title + 25, y_title, title_6.c_str());
    getimage(page_fin_6, 0, 0, width, height);
    Add_page(page_fin_6);
    IMAGE* page_error_code_7 = new IMAGE(width, height);
    solidrectangle(0, 0, width, height);
    std::string title_7 = "ERROR! HUFFMANTREE DOES NOT EXIST!";
    outtextxy(x_title - 75, y_title, title_7.c_str());
    getimage(page_error_code_7, 0, 0, width, height);
    Add_page(page_error_code_7);
    IMAGE* page_error_decode_8 = new IMAGE(width, height);
    solidrectangle(0, 0, width, height);
    std::string title_8 = "ERROR! HUFFMANTREE DOES NOT EXIST!";
    outtextxy(x_title - 75, y_title, title_7.c_str());
    getimage(page_error_decode_8, 0, 0, width, height);
    Add_page(page_error_decode_8);
    IMAGE* page_error_output_9 = new IMAGE(width, height);
    solidrectangle(0, 0, width, height);
    std::string title_9 = "ERROR! HUFFMANTREE DOES NOT EXIST!";
    outtextxy(x_title - 75, y_title, title_7.c_str());
    getimage(page_error_output_9, 0, 0, width, height);
    Add_page(page_error_output_9);
    Button* bt_1 = new Button(X, Y, 200, 50, "Build Huffman Tree", [&](){setCurrentIndex(1);});
    Button* input_cin = new Button(X, Y, 200, 50, "Input from keyboard", [&](){setCurrentIndex(5);});
    Button* bt_cin_confirm = new Button(X, Y + delta_Y, 200, 50, "Confirm", [&](){
        std::string s = textboxes[5][0]->GetText();
        textboxes[5][0]->clear();
        tree->BuildTree_cin(s);
        tree->stockpile();
        setCurrentIndex(1);
    });
    Button* bt_cin_back = new Button(X, Y + delta_Y * 2, 200, 50, "Back", [&](){setCurrentIndex(1);});
    Button* input_fin = new Button(X, Y + delta_Y, 200, 50, "Input from files", [&](){setCurrentIndex(6);});
    Button* bt_fin_confirm = new Button(X, Y + delta_Y, 200, 50, "Confirm", [&](){
        std::string path = textboxes[6][0]->GetText();
        textboxes[6][0]->clear();
        tree->BuildTree_fin(path);
        tree->stockpile();
        setCurrentIndex(1);
    });
    Button* bt_fin_back = new Button(X, Y + delta_Y * 2, 200, 50, "Back", [&](){setCurrentIndex(1);});
    Button* bt_1_back = new Button(X, Y + delta_Y * 2, 200, 50, "Back", [&](){setCurrentIndex(0);});
    Button* bt_2 = new Button(X, Y + delta_Y, 200, 50, "Code", [&](){
        if(tree->Get_state()){
            setCurrentIndex(2);    
        }
        else{
            setCurrentIndex(7);
        }
    });
    Button* bt_code_error = new Button(X, Y + delta_Y, 200, 50, "Back", [&](){setCurrentIndex(0);});
    Button* bt_code_confirm = new Button(X, Y + delta_Y, 200, 50, "Confirm", [&](){
        std::string path = textboxes[2][0]->GetText();
        textboxes[2][0]->clear();
        tree->Coding(path);
        setCurrentIndex(0);
    });
    Button* bt_2_back = new Button(X, Y + delta_Y * 2, 200, 50, "Back", [&](){setCurrentIndex(0);});
    Button* bt_3 = new Button(X, Y + delta_Y * 2, 200, 50, "Decode", [&](){
        if(tree->Get_state()){
           setCurrentIndex(3); 
        }
        else{
            setCurrentIndex(8);
        }
    });
    Button* bt_decode_error = new Button(X, Y + delta_Y, 200, 50, "Back", [&](){setCurrentIndex(0);});
    Button* bt_decode_confirm = new Button(X, Y + delta_Y, 200, 50, "Confirm", [&](){
        std::string path = textboxes[3][0]->GetText();
        textboxes[3][0]->clear();
        tree->Decoding(path);
        setCurrentIndex(0);
    });
    Button* bt_3_back = new Button(X, Y + delta_Y * 2, 200, 50, "Back", [&](){setCurrentIndex(0);});
    Button* bt_4 = new Button(X, Y + delta_Y * 3, 200, 50, "Vertical Output", [&](){
        if(tree->Get_state()){
            tree->Vertical_output();
            setCurrentIndex(4);
        }
        else{
            setCurrentIndex(9);
        }
    });
    Button* bt_output_error = new Button(X, Y + delta_Y, 200, 50, "Back", [&](){setCurrentIndex(0);});
    Button* bt_4_back = new Button(X, Y, 200, 50, "Back", [&](){setCurrentIndex(0);});
    Add_Button(bt_1, 0);
    Add_Button(bt_2, 0);
    Add_Button(bt_3, 0);
    Add_Button(bt_4, 0);
    Add_Button(bt_1_back, 1);
    Add_Button(input_cin, 1);
    Add_Button(input_fin, 1);
    Add_Button(bt_code_confirm, 2);
    Add_Button(bt_2_back, 2);
    Add_Button(bt_decode_confirm, 3);
    Add_Button(bt_3_back, 3);
    Add_Button(bt_4_back, 4);
    Add_Button(bt_cin_confirm, 5);
    Add_Button(bt_cin_back, 5);
    Add_Button(bt_fin_confirm, 6);
    Add_Button(bt_fin_back, 6);
    Add_Button(bt_code_error, 7);
    Add_Button(bt_decode_error, 8);
    Add_Button(bt_output_error, 9);
    TextBox* tb_5_0 = new TextBox(X, Y, 200, 30, 50);
    TextBox* tb_6_0 = new TextBox(X, Y, 200, 30, 50);
    TextBox* tb_2_0 = new TextBox(X, Y, 200, 30, 50);
    TextBox* tb_3_0 = new TextBox(X, Y, 200, 30, 50);
    Add_TextBox(tb_5_0, 5);
    Add_TextBox(tb_6_0, 6);
    Add_TextBox(tb_2_0, 2);
    Add_TextBox(tb_3_0, 3);
    setCurrentIndex(0);
}

void Interface::run(){
    ExMessage msg;
    BeginBatchDraw();
    while(true){
        DWORD time_start = GetTickCount();
        while(peekmessage(&msg)){
            switch(msg.message){
                case WM_LBUTTONDOWN:
                    MouseClick(msg.x, msg.y);
                    break;
                case WM_MOUSEMOVE:
                    MouseMove(msg.x, msg.y);
                    break;
                case WM_CHAR:
                    Key_input(msg.ch);
                    break;
            }
        }
        cleardevice();
        draw();
        FlushBatchDraw();
        DWORD time_end = GetTickCount();
        DWORD delta_time = time_end - time_start;
        if(delta_time < 1000 / 60){
            Sleep(1000 / 60 - delta_time);
        }
    }
    EndBatchDraw();
}

void Interface::Close(){
    closegraph();
}
