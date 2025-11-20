#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <conio.h>
#include <string>
#include <windows.h>


using namespace std;
int start_t = 0;
int mud_number = 1;
int health_number;
string healthy = " 100% ■■■■";
struct stru
{
    string name;
    
};
stru player;
int space_num = 32;
char enemy_boss_arr[5] = {'#', '#', '#', '#', '#'};
int setting_number;
int set_difficulty = 1;
int set_defence = 1;
int set_mode = 1;
int set_airplane = 1;
int set_option = 1;
char select_button;
char back_button;
char power_ups_button;
char shoting_button;
int moving_button = 2;
int keyboard_menu ;
int score = 0;
bool power_u = true;
int number_left_right_1 = 0;
int number_left_right_2 = 1;
int puase_menu_num = 1;
string airplane_bullet_skin = "^";
bool loading;
bool enemy_boss_is_alive = true;
int timer;
int registry_number = 1;

char board_arr_chr[17][68];


void gotoxy(short y, short x){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {x, y};
    SetConsoleCursorPosition(hConsole, pos);
}

enum ConsoleColor {
    Black = 0,
    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Magenta = 5,
    Yellow = 6,
    White = 7,
    BrightBlack = 8,
    BrightBlue = 9,
    BrightGreen = 10,
    BrightCyan = 11,
    BrightRed = 12,
    BrightMagenta = 13,
    BrightYellow = 14,
    BrightWhite = 15
};
void setConsoleColor(int textColor, int backgroundColor) {
    if(set_mode == 1){
        backgroundColor = Black;
        if(textColor == Black){
            textColor = BrightWhite;
        }
    }
    else if(set_mode == 2){
        backgroundColor = BrightWhite;
        if(textColor == BrightWhite){
            textColor = Black;
        }
    }
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
    int color = backgroundColor * 16 + textColor;  
    SetConsoleTextAttribute(hConsole, color);
}
void airplane_bullet(){
    switch (set_option)
    {
    case 1:
        airplane_bullet_skin = "^";
        break;
    case 2:
        airplane_bullet_skin = "+";
        break;
    case 3:
        airplane_bullet_skin = ".";
        break;
    case 4:
        airplane_bullet_skin = "\"";
        break;
    }
}
int digit_number(int number){
    int i = 0;
    if(number == 0){
        return 1;
    }
    else{
        while(number > 0){
            number /= 10;
            i++;
        }
        return i;
    }
}
string show_timer(int time){
    int minutes;
    int seconds;
    string min;
    string sec;
    minutes = time / 60;
    seconds = time % 60;
    min += to_string(minutes);
    if(digit_number(seconds) == 1){
        sec = "0";
        sec += to_string(seconds);
    }
    else{
        sec += to_string(seconds);
    }
    string result = "";
    result += min;
    result += ":";
    result += sec;
    return result;
}
void cout_border(){
    system("cls");
    string setting_title_array[6] = {"difficulty:     ", "defence:            ", "mode:                 ", "plane:", "bullet:         "};
    string setting_array[18] = {
        "easy", "normal", "hard", "active", 
        "inactive", "night", "day", "◄(╿)►", 
        "◄◄♀►►", "(▄█▄)", "╭╯╿╰╮", "◂▲▼▲▸",
        "<■!■>", "^", "+", ".", "\"", "keyboard"
    };
    int numberOFLine[8] = {0,3, 2, 2, 6, 4, 1, 0};
    int sum = 0;
    setConsoleColor(Cyan,BrightWhite);
    cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
    cout << "┃░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░┃" << endl;
    setConsoleColor(Black,BrightWhite);
    for(int i = 0; i <= 4; i++){
        int space_sum = 0;
        setConsoleColor(Cyan,BrightWhite);
        cout << "┃░░                                                                ░░┃" << endl;
        cout << "┃░░    ";
        setConsoleColor(Black,BrightWhite);
        cout << setting_title_array[i];
        sum += numberOFLine[i];
        for(int k = sum; k < sum + numberOFLine[i + 1]; k++){
            space_sum += setting_array[k].length();
        }
        if(space_sum == 76){
            space_sum = 30;
        }
        string space_str = "";
        for(int z = 0; z < ((48 - space_sum) / (numberOFLine[i + 1] + 1)); z++){
                space_str += " ";
        }
        for(int k = sum; k < sum + numberOFLine[i + 1]; k++){
            cout << "  ";
            if(k + 1 == setting_number){
                setConsoleColor(BrightRed,BrightWhite);
                cout << setting_array[k];
                setConsoleColor(Black,BrightWhite);

            }
            else{
                if(k + 1 == set_difficulty || k + 1 == (set_defence + 3) || k + 1 == (set_mode + 5) || k + 1 == (set_airplane + 7) || k + 1 == (set_option + 13)){
                    setConsoleColor(Yellow,BrightWhite);
                    cout << setting_array[k];
                    setConsoleColor(Black,BrightWhite);
                }
                else{
                    setConsoleColor(BrightBlack,BrightWhite);
                    cout << setting_array[k];
                    setConsoleColor(Black,BrightWhite);
                }
            }
            cout << space_str;
        }
        setConsoleColor(Cyan,BrightWhite);
        cout << "░░┃" << endl;
        cout << "┃░░                                                                ░░┃" << endl;
        setConsoleColor(Black,BrightWhite);

    }
    setConsoleColor(Cyan,BrightWhite);
    cout << "┃░░                                                                ░░┃" << endl;
    cout << "┃░░                             ";
    setConsoleColor(Black,BrightWhite);
    if(setting_number == 18){
        setConsoleColor(BrightRed,BrightWhite);
        cout << "Keyboard";
        setConsoleColor(Black,BrightWhite);
    }
    else{
        cout << "Keyboard";
    }
    setConsoleColor(Cyan,BrightWhite);
    cout << "                           ░░┃" << endl;
    cout << "┃░░                                                                ░░┃" << endl;
    cout << "┃░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░┃" << endl;
    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
    setConsoleColor(Black,BrightWhite);
}
void cout_board_02(){
    system("cls");
    string space_left = "";
    string space_right = "";
    string skin_airplane = "";
    switch (set_airplane)
    {
    case 1:
        skin_airplane = " ◄(╿)► ";
        break;
    case 2:
        skin_airplane = " ◄◄♀►► ";
        break;
    case 3:
        skin_airplane = " (▄█▄) ";
        break;
    case 4:
        skin_airplane = " ╭╯╿╰╮ ";
        break;
    case 5:
        skin_airplane = " ◂▲▼▲▸ ";
        break;
    default:
        skin_airplane = " <■!■> ";
        break;
    }
    for(int i = 1; i < space_num; i++){
        space_left += " ";
    }
    for(int i = 1; i < (63 - space_num); i++){
        space_right += " ";
    }
    setConsoleColor(Cyan,BrightWhite);
    cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
    cout << "┃    score: ";
    setConsoleColor(Yellow,BrightWhite);
    cout << score; 
    setConsoleColor(Cyan,BrightWhite);
    for(int i = 0; i < (20 - digit_number(score)); i++){
        cout << " ";
    }
    cout << "time: ";
    cout << timer;
    for(int i = 0; i < (21 - digit_number(timer)); i++){
        cout << " ";
    }
    setConsoleColor(Red,BrightWhite);
    cout << healthy;
    setConsoleColor(Cyan,BrightWhite);
    cout << " ┃" << endl;
    cout << "┃┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┃" << endl;
    setConsoleColor(Black,BrightWhite);
    for(int i = 0; i <= 16; i++){
        setConsoleColor(Cyan,BrightWhite);
        cout << "┃";
        setConsoleColor(Black,BrightWhite);
        for(int j = 0; j < 68; j++){
            gotoxy(i + 3,j + 1);
            if(board_arr_chr[i][j] == '@'){
                setConsoleColor(Green,BrightWhite);
                cout << board_arr_chr[i][j];
                setConsoleColor(White,BrightWhite);
            }
            else if(board_arr_chr[i][j] == '$'){
                setConsoleColor(Green,BrightWhite);
                cout << board_arr_chr[i][j];
                setConsoleColor(White,BrightWhite);
            }
            else if(board_arr_chr[i][j] == '-'){
                setConsoleColor(Green,BrightWhite);
                cout << "■";
                setConsoleColor(White,BrightWhite);
            }
            else if(board_arr_chr[i][j] == '#'){
                setConsoleColor(Magenta,BrightWhite);
                cout << board_arr_chr[i][j];
                setConsoleColor(White,BrightWhite);
            }
            else if(board_arr_chr[i][j] == '^'){
                setConsoleColor(BrightRed,BrightWhite);
                cout << board_arr_chr[i][j];
                setConsoleColor(White,BrightWhite);
            }
            else if(board_arr_chr[i][j] == ' '){
                cout << ' ';
            }
            else{
                cout << board_arr_chr[i][j];
            }
        }
        setConsoleColor(Cyan,BrightWhite);
        cout << "┃" << endl;
        setConsoleColor(White,BrightWhite);

    }
    setConsoleColor(Cyan,BrightWhite);
    cout << "┃" << space_left << skin_airplane << space_right << "┃" << endl;
    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
    setConsoleColor(White,BrightWhite);

}
void cout_menu(int number){
    string shape_str_left;
    int colour;
    string shape_str_right;
    string menu_titles[6] = {"Load Game" , "New Game" , "How to Play" , "Leaderboard" , "Setting" , "Exit"};
    system("cls");
    setConsoleColor(Cyan,BrightWhite);
    cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
    cout << "┃░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░┃" << endl;
    setConsoleColor(Black,BrightWhite);
    for(int i = 1; i < 7; i++){
        string space = "";
        if(i == number){
            for(int k = 1; k < ((24 - menu_titles[i - 1].length())/2); k++){
                space += " ";
            }
            if(menu_titles[i - 1].length() % 2 != 0){
                
                shape_str_right = " <<  ";
            }
            else{
                shape_str_right = " << ";
            }
            shape_str_left = ">>";
            setConsoleColor(Cyan,BrightWhite);
            cout << "┃░░                                                                ░░┃" << endl;
            cout << "┃░░                  ";
            setConsoleColor(Black,BrightWhite);
            setConsoleColor(Yellow, BrightWhite);
            cout << shape_str_left << space << menu_titles[i - 1] << space << shape_str_right;
            setConsoleColor(Black,BrightWhite);
            setConsoleColor(Cyan,BrightWhite);
            cout << "                  ░░┃" << endl;
            setConsoleColor(Black,BrightWhite);
        }
        else{
            for(int k = 0; k < ((22 - menu_titles[i - 1].length())/2); k++){
                space += " ";
            }
            if(menu_titles[i - 1].length() % 2 != 0){
                shape_str_right = "       ○ ●";
            }
            else{
                shape_str_right = "      ○ ●";
            }
                shape_str_left = "● ○      ";
                colour = 1;
            setConsoleColor(Cyan,BrightWhite);
            cout << "┃░░                                                                ░░┃" << endl;
            cout << "┃░░            ";
            cout << shape_str_left << space;
            setConsoleColor(Black,BrightWhite);
            if(loading == false && i == 1){
                setConsoleColor(BrightBlack,BrightWhite);
                cout << menu_titles[i - 1];
                setConsoleColor(Black,BrightWhite);
            }
            else{
                cout << menu_titles[i - 1];
            }
            setConsoleColor(Cyan,BrightWhite);
            cout << space << shape_str_right;
            cout << "            ░░┃" << endl;
            setConsoleColor(Black,BrightWhite);

        }
    }
    setConsoleColor(Cyan,BrightWhite);
    cout << "┃░░                                                                ░░┃" << endl;
    cout << "┃░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░┃" << endl;
    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
    setConsoleColor(Black,BrightWhite);
}
void cout_puase_menu(int number){
    string shape_str_left;
    int colour;
    string shape_str_right;
    string menu_titles[4] = {"Resume" , "Save and Exit" , "Exit"};
    system("cls");
    setConsoleColor(Cyan,BrightWhite);
    cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
    cout << "┃░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░┃" << endl;
    setConsoleColor(Black,BrightWhite);
    for(int i = 1; i < 4; i++){
        string space = "";
        if(i == number){
            for(int k = 1; k < ((24 - menu_titles[i - 1].length())/2); k++){
                space += " ";
            }
            if(menu_titles[i - 1].length() % 2 != 0){
                
                shape_str_right = " <<  ";
            }
            else{
                shape_str_right = " << ";
            }
            shape_str_left = ">>";
            setConsoleColor(Cyan,BrightWhite);
            cout << "┃░░                                                                ░░┃" << endl;
            cout << "┃░░                  ";
            setConsoleColor(Black,BrightWhite);
            setConsoleColor(Yellow, BrightWhite);
            cout << shape_str_left << space << menu_titles[i - 1] << space << shape_str_right;
            setConsoleColor(Black,BrightWhite);
            setConsoleColor(Cyan,BrightWhite);
            cout << "                  ░░┃" << endl;
            setConsoleColor(Black,BrightWhite);
        }
        else{
            for(int k = 0; k < ((22 - menu_titles[i - 1].length())/2); k++){
                space += " ";
            }
            if(menu_titles[i - 1].length() % 2 != 0){
                shape_str_right = "       ○ ●";
            }
            else{
                shape_str_right = "      ○ ●";
            }
                shape_str_left = "● ○      ";
                colour = 1;
            setConsoleColor(Cyan,BrightWhite);
            cout << "┃░░                                                                ░░┃" << endl;
            cout << "┃░░            ";
            cout << shape_str_left << space;
            setConsoleColor(Black,BrightWhite);
                cout << menu_titles[i - 1];
            setConsoleColor(Cyan,BrightWhite);
            cout << space << shape_str_right;
            cout << "            ░░┃" << endl;
            setConsoleColor(Black,BrightWhite);

        }
    }
    setConsoleColor(Cyan,BrightWhite);
    cout << "┃░░                                                                ░░┃" << endl;
    cout << "┃░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░┃" << endl;
    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
    setConsoleColor(Black,BrightWhite);
}
void cout_registry_error0(){
    system("cls");
    setConsoleColor(Red,BrightWhite);
    cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
    cout << "┃░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░┃" << endl;
    cout << "┃░░                ";
    cout <<"╔══════════════════════════════╗";
    cout << "                ░░┃" << endl;
    cout << "┃░░                ";
    cout << "║ ";
    cout << player.name;
    for(int i = 0; i < 29 - player.name.length();i++){
        cout << " ";
    }
    cout << "║";
    cout <<"                ░░┃" << endl;
    cout << "┃░░                ";
    cout << "╚══════════════════════════════╝";
    cout << "                ░░┃" << endl;
    cout << "┃░░                         ";
    cout << "╭───────────╮";
    cout << "                          ░░┃" << endl;
    cout << "┃░░                         ";
    cout << "│  Confirm  │";
    cout << "                          ░░┃" << endl;
    cout << "┃░░                         ";
    cout << "╰───────────╯";
    cout << "                          ░░┃" << endl;
    cout << "┃░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░┃" << endl;
    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
    setConsoleColor(Black,BrightWhite);
}
void cout_registry_error1(){
    system("cls");
    setConsoleColor(Green,BrightWhite);
    cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
    cout << "┃░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░┃" << endl;
    cout << "┃░░                ";
    cout <<"╔══════════════════════════════╗";
    cout << "                ░░┃" << endl;
    cout << "┃░░                ";
    cout << "║ ";
    cout << player.name;
    for(int i = 0; i < 29 - player.name.length();i++){
        cout << " ";
    }
    cout << "║";
    cout <<"                ░░┃" << endl;
    cout << "┃░░                ";
    cout << "╚══════════════════════════════╝";
    cout << "                ░░┃" << endl;
    cout << "┃░░                         ";
    cout << "╭───────────╮";
    cout << "                          ░░┃" << endl;
    cout << "┃░░                         ";
    cout << "│  Confirm  │";
    cout << "                          ░░┃" << endl;
    cout << "┃░░                         ";
    cout << "╰───────────╯";
    cout << "                          ░░┃" << endl;
    cout << "┃░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░┃" << endl;
    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
    setConsoleColor(Black,BrightWhite);
}
void cout_registry(){
    system("cls");
    cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
cout << "┃░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░┃" << endl;
cout << "┃░░                ";
if(registry_number == 1){
    setConsoleColor(Yellow,BrightWhite);
    cout <<"╔══════════════════════════════╗";
    setConsoleColor(Black,BrightWhite);
}
else{
    cout <<"╔══════════════════════════════╗";
}
cout << "                ░░┃" << endl;
cout << "┃░░                ";
if(registry_number == 1){
    setConsoleColor(Yellow,BrightWhite);
    cout << "║ ";
    cout << player.name;
    for(int i = 0; i < 29 - player.name.length();i++){
        cout << " ";
    }
    cout << "║";
    setConsoleColor(Black,BrightWhite);
}
else{
    cout << "║ ";
    cout << player.name;
    for(int i = 0; i < 29 - player.name.length();i++){
        cout << " ";
    }
    cout << "║";
}
cout <<"                ░░┃" << endl;
cout << "┃░░                ";
if(registry_number == 1){
    setConsoleColor(Yellow,BrightWhite);
    cout << "╚══════════════════════════════╝";
    setConsoleColor(Black,BrightWhite);
}
else{
    cout << "╚══════════════════════════════╝";
}
cout << "                ░░┃" << endl;
cout << "┃░░                         ";
if(registry_number == 2){
    setConsoleColor(Yellow,BrightWhite);
    cout << "╭───────────╮";
    setConsoleColor(Black,BrightWhite);
}
// else if(!name && !(player.name == "")){
//     setConsoleColor(Red,BrightWhite);
//     cout << "╭───────────╮";
//     setConsoleColor(Black,BrightWhite);
// }
else{
    cout << "╭───────────╮";
}
cout << "                          ░░┃" << endl;
cout << "┃░░                         ";
if(registry_number == 2){
    setConsoleColor(Yellow,BrightWhite);
    cout << "│  Confirm  │";
    setConsoleColor(Black,BrightWhite);
}
else{
    cout << "│  Confirm  │";
}
cout << "                          ░░┃" << endl;
cout << "┃░░                         ";
if(registry_number == 2){
    setConsoleColor(Yellow,BrightWhite);
    cout << "╰───────────╯";
    setConsoleColor(Black,BrightWhite);
}
else{
    cout << "╰───────────╯";
}
cout << "                          ░░┃" << endl;
cout << "┃░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░┃" << endl;
cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
}
void move_up_down(char mud){
    if(mud == 'w' || mud == 'W' || mud == 72){
        if(2 <= mud_number && mud_number <= 6){
            mud_number--;
        }
        else if(mud_number == 1){
            mud_number = 6;
        }
    }
    else if(mud == 's' || mud == 'S'|| mud == 80){
        if(1 <= mud_number && mud_number <= 5){
            mud_number++;
        }
        else if(mud_number == 6){
            mud_number = 1;
        }
    }
    cout_menu(mud_number);
}
void move_airplane_right_left(char mrl){
    if(mrl == 'a' || mrl == 'A'){
        if(space_num == 0){
            space_num = 63;
        }
        else{
            space_num--;
        }
    }
    else if(mrl == 'd' || mrl == 'D'){
        if(space_num == 63){
            space_num = 0;
        }
        else{
            space_num++;
        }
    }
}
void move_airplane_right_left2(char mrl){
    string skin_airplane;
    bool mlb,mrb;
    switch (set_airplane)
    {
    case 1:
        skin_airplane = " ◄(╿)► ";
        break;
    case 2:
        skin_airplane = " ◄◄♀►► ";
        break;
    case 3:
        skin_airplane = " (▄█▄) ";
        break;
    case 4:
        skin_airplane = " ╭╯╿╰╮ ";
        break;
    case 5:
        skin_airplane = " ◂▲▼▲▸ ";
        break;
    default:
        skin_airplane = " <■!■> ";
        break;
    }
    if(moving_button == 1){
        mlb = (mrl == 75);
        mrb = (mrl == 77);
    }
    else{
        mlb = (mrl == 'a' || mrl == 'A');
        mrb = (mrl == 'd' || mrl == 'D');
    }
    if(mlb){
        if(space_num == 1){
            gotoxy(20,space_num);
            cout << "       ";
            space_num = 62;
            gotoxy(20,space_num);
            setConsoleColor(Cyan,BrightWhite);
            cout << skin_airplane;
            setConsoleColor(Black,BrightWhite);
        }
        else{
            space_num--;
            gotoxy(20,space_num);
            setConsoleColor(Cyan,BrightWhite);
            cout << skin_airplane;
            setConsoleColor(Black,BrightWhite);

        }
    }
    else if(mrb){
        if(space_num == 62){
            gotoxy(20,space_num);
            cout << "       ";
            space_num = 1;
            gotoxy(20,space_num);
            setConsoleColor(Cyan,BrightWhite);
            cout << skin_airplane;
            setConsoleColor(Black,BrightWhite);
        }
        else{
            space_num++;
            gotoxy(20,space_num);
            setConsoleColor(Cyan,BrightWhite);
            cout << skin_airplane;
            setConsoleColor(Black,BrightWhite);

        }
    }
}
void bye(){
    system("cls");
    cout << "▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒"<<endl;
    cout << "▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓░░▒▒▒▒▒▒▒▒▒▓▓▓▓░░▒▒▒▓▓▓▓░░▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓░░▒▒▒▒"<<endl;
    cout << "▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓░░▒▒▒▒▒▒▒▒▒▓▓▓▓░░▒▒▒▓▓▓▓░░▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓░░▒▒▒▒"<<endl;
    cout << "▒▒▒▒▓▓▓▓░░▒▒▒▒▓▓▓▓░░▒▒▒▒▒▒▒▒▓▓▓▓░░▒▒▒▓▓▓▓░░▒▒▒▒▒▒▒▒▓▓▓▓░░▒▒▒▒▒▒▒▒▒▒▒▒"<<endl;
    cout << "▒▒▒▒▓▓▓▓░░▒▒▒▒▒▒▓▓▓▓░░▒▒▒▒▒▒▓▓▓▓░░▒▒▒▓▓▓▓░░▒▒▒▒▒▒▒▒▓▓▓▓░░▒▒▒▒▒▒▒▒▒▒▒▒"<<endl;
    cout << "▒▒▒▒▓▓▓▓░░▒▒▒▒▒▒▓▓▓▓░░▒▒▒▒▒▒▓▓▓▓░░▒▒▒▓▓▓▓░░▒▒▒▒▒▒▒▒▓▓▓▓░░▒▒▒▒▒▒▒▒▒▒▒▒"<<endl;
    cout << "▒▒▒▒▓▓▓▓░░▒▒▒▒▓▓▓▓░░▒▒▒▒▒▒▒▒▓▓▓▓░░▒▒▒▓▓▓▓░░▒▒▒▒▒▒▒▒▓▓▓▓░░▒▒▒▒▒▒▒▒▒▒▒▒"<<endl;
    cout << "▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓░░▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓░░▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓░░▒▒▒▒"<<endl;
    cout << "▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓░░▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓░░▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓░░▒▒▒▒"<<endl;
    cout << "▒▒▒▒▓▓▓▓░░▒▒▒▒▓▓▓▓░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓░░▒▒▒▒▒▒▒▒▓▓▓▓░░▒▒▒▒▒▒▒▒▒▒▒▒"<<endl;
    cout << "▒▒▒▒▓▓▓▓░░▒▒▒▒▒▒▓▓▓▓░░▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓░░▒▒▒▒▒▒▒▒▓▓▓▓░░▒▒▒▒▒▒▒▒▒▒▒▒"<<endl;
    cout << "▒▒▒▒▓▓▓▓░░▒▒▒▒▒▒▓▓▓▓░░▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓░░▒▒▒▒▒▒▒▒▓▓▓▓░░▒▒▒▒▒▒▒▒▒▒▒▒"<<endl;
    cout << "▒▒▒▒▓▓▓▓░░▒▒▒▒▓▓▓▓░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓░░▒▒▒▒▒▒▒▒▓▓▓▓░░▒▒▒▒▒▒▒▒▒▒▒▒"<<endl;
    cout << "▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓░░▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓░░▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓░░▒▒▒▒"<<endl;
    cout << "▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓░░▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓░░▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓░░▒▒▒▒"<<endl;
    cout << "▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒"<<endl;
}
void enemy1(int row_num, int random){
    int row_counter = 0;
    switch (set_difficulty){
        case 1:
            row_counter = 2;
        break;
        case 2:
            row_counter = 4;
        break;
        case 3:
            row_counter = 6;
        break;
    }
    switch (random)
    {
    case 1:
            for(int j = 5; j < 64; j++){
                board_arr_chr[row_num][j] = '@';
            }
        break;
    case 2:
            for(int j = 5; j <=30; j++){
                board_arr_chr[row_num][j] = '@';
            }
            for(int j = 31 ; j < 40; j++){
                board_arr_chr[row_num][j] = ' ';
            }
            for(int j = 40; j < 64; j++){
                board_arr_chr[row_num][j] = '@';
            }
        break;
    case 3:
            for(int j = 5; j <= 20; j++){
                board_arr_chr[row_num][j] = '@';
            }
            for(int j = 21 ; j < 28; j++){
                board_arr_chr[row_num][j] = ' ';
            }
            for(int j = 28; j <= 43; j++){
                board_arr_chr[row_num][j] = '@';
            }
            for(int j = 44 ; j < 50; j++){
                board_arr_chr[row_num][j] = ' ';
            }
            for(int j = 50; j < 64; j++){
                board_arr_chr[row_num][j] = '@';
            }
        break;
    }
}
void enemy2(int row_num, int random){
    int row_counter = 0;
    switch (set_difficulty){
        case 1:
            row_counter = 2;
        break;
        case 2:
            row_counter = 4;
        break;
        case 3:
            row_counter = 6;
        break;
    }
    switch (random)
    {
    case 1:
            for(int j = 0; j < 5; j++){
                board_arr_chr[row_num][j] = ' ';
            }
            for(int j = 5; j < 64; j++){
                board_arr_chr[row_num][j] = '$';
            }
            for(int j = 65; j < 68; j++){
                board_arr_chr[row_num][j] = ' ';
            }
        break;
    case 2:
            for(int j = 0; j < 5; j++){
                board_arr_chr[row_num][j] = ' ';
            }
            for(int j = 5; j < 31; j++){
                board_arr_chr[row_num][j] = '$';
            }
            for(int j = 31 ; j < 41; j++){
                board_arr_chr[row_num][j] = ' ';
            }
            for(int j = 41; j < 64; j++){
                board_arr_chr[row_num][j] = '$';
            }
            for(int j = 65; j < 68; j++){
                board_arr_chr[row_num][j] = ' ';
            }
        break;
    case 3:
            for(int j = 0; j < 5; j++){
                board_arr_chr[row_num][j] = ' ';
            }
            for(int j = 5; j < 21; j++){
                board_arr_chr[row_num][j] = '$';
            }
            for(int j = 21 ; j < 28; j++){
                board_arr_chr[row_num][j] = ' ';
            }
            for(int j = 28; j < 44; j++){
                board_arr_chr[row_num][j] = '$';
            }
            for(int j = 44 ; j < 50; j++){
                board_arr_chr[row_num][j] = ' ';
            }
            for(int j = 50; j < 64; j++){
                board_arr_chr[row_num][j] = '$';
            }
            for(int j = 65; j < 68; j++){
                board_arr_chr[row_num][j] = ' ';
            }
        break;
    }
}
void make_enemy(int inum, int jnum){
    board_arr_chr[inum][jnum] = '@';
}
void move_down_enemy(){
    for(int j = 68; j >= 0; j--){
        for(int i = 16; i > 0; i--){
            if(board_arr_chr[i][j] == board_arr_chr[i - 1][j]){
                continue;
            }
            else if((board_arr_chr[i][j] == '@' && board_arr_chr[i - 1][j] == '$') || (board_arr_chr[i][j] == '@' && board_arr_chr[i - 1][j] == ' ') || (board_arr_chr[i][j] == ' ' && board_arr_chr[i - 1][j] == '@')){
                board_arr_chr[i][j] = board_arr_chr[i - 1][j];
                gotoxy(i + 3, j + 1);
                setConsoleColor(Green,BrightWhite);
                cout << board_arr_chr[i][j];
                setConsoleColor(Black,BrightWhite);
            }
            else if((board_arr_chr[i][j] == '$' && board_arr_chr[i - 1][j] == ' ') || (board_arr_chr[i][j] == ' ' && board_arr_chr[i - 1][j] == '$')){
                board_arr_chr[i][j] = board_arr_chr[i - 1][j];
                gotoxy(i + 3, j + 1);
                setConsoleColor(Green,BrightWhite);
                cout << board_arr_chr[i][j];
                setConsoleColor(Black,BrightWhite);
            }
            else if((board_arr_chr[i][j] == '$' && board_arr_chr[i - 1][j] == '#')){
                board_arr_chr[i][j] = ' ';
                gotoxy(i + 3, j + 1);
                setConsoleColor(Green,BrightWhite);
                cout << board_arr_chr[i][j];
                setConsoleColor(Black,BrightWhite);
            }
        }
    }
}
bool check_lose(){
    for(int i = 0; i < 68; i++){
        if(board_arr_chr[16][i] == '@'){
            return false;
        }
    }
    return true;
}
void move_left_enemy(){
    // for(int i = 1; i <= 16; i++){
    //     for(int j = 0; j < 67; j++){
    //         if(board_arr_chr[i][j] == board_arr_chr[i][j + 1]){
    //             continue;
    //         }
    //         else if((board_arr_chr[i][j] == '@' && board_arr_chr[i][j + 1] == ' ') || (board_arr_chr[i][j] == ' ' && board_arr_chr[i][j + 1] == '@') || (board_arr_chr[i][j] == '$' && board_arr_chr[i][j + 1] == ' ') || (board_arr_chr[i][j] == ' ' && board_arr_chr[i][j + 1] == '$')){
    //             board_arr_chr[i][j] = board_arr_chr[i][j + 1];
    //             gotoxy(i + 3, j + 1);
                // setConsoleColor(Green,BrightWhite);
                // cout << board_arr_chr[i][j];
                // setConsoleColor(Black,BrightWhite);
    //         }
    //     }
    // }
    for(int i = 1; i < 17;i++){
        for(int j = 0; j < 67; j++){
            if((board_arr_chr[i][j] == '@' || board_arr_chr[i][j] == '$' || board_arr_chr[i][j] == ' ') && (board_arr_chr[i][j + 1] == '@' || board_arr_chr[i][j + 1] == '$' || board_arr_chr[i][j + 1] == ' ')){
                board_arr_chr[i][j] = board_arr_chr[i][j + 1];
                gotoxy(i + 3, j + 1);
                setConsoleColor(Green,BrightWhite);
                cout << board_arr_chr[i][j];
                setConsoleColor(Black,BrightWhite);
            }
        }
    }
}
void move_right_enemy(){
    for(int i = 0; i <= 16; i++){
        for(int j = 67; j > 0; j--){
            if(board_arr_chr[i][j] == board_arr_chr[i][j - 1]){
                continue;
            }
            else if((board_arr_chr[i][j] == '@' && board_arr_chr[i][j - 1] == ' ') || (board_arr_chr[i][j] == ' ' && board_arr_chr[i][j - 1] == '@') || (board_arr_chr[i][j] == '$' && board_arr_chr[i][j - 1] == ' ') || (board_arr_chr[i][j] == ' ' && board_arr_chr[i][j - 1] == '$')){
                board_arr_chr[i][j] = board_arr_chr[i][j - 1];
                gotoxy(i + 3, j + 1);
                setConsoleColor(Green,BrightWhite);
                cout << board_arr_chr[i][j];
                setConsoleColor(Black,BrightWhite);
            }
        }
    }

    // for(int i = 1; i < 17;i++){
    //     for(int j = 67; j > 0;j--){
    //         if((board_arr_chr[i][j] == '@' || board_arr_chr[i][j] == '$' || board_arr_chr[i][j] == ' ') && (board_arr_chr[i][j - 1] == '@' || board_arr_chr[i][j - 1] == '$' || board_arr_chr[i][j - 1] == ' ')){
    //             board_arr_chr[i][j] = board_arr_chr[i][j - 1];
    //             gotoxy(i + 3, j + 1);
                // setConsoleColor(Green,BrightWhite);
                // cout << board_arr_chr[i][j];
                // setConsoleColor(Black,BrightWhite);
    //         }
    //     }
    // }
}
bool check_can_left(){
    for(int i = 0; i < 16; i++){
        if(board_arr_chr[i][0] == '@'){
            return false;
        }
    }
    return true;
}
bool check_can_right(){
    for(int i = 0; i < 16; i++){
        if(board_arr_chr[i][68] == '@'){
            return false;
        }
    }
    return true;
}
void enemy_boss(int jboss){
    for(int i = 0; i < 68; i++){
        if(board_arr_chr[0][i] == '#'){
            board_arr_chr[0][i] = ' ';
            gotoxy(3,i + 1);
            cout << board_arr_chr[0][i];
        }
    }
    if(!enemy_boss_is_alive)
        return;
    for(int k = -2; k <= 2; k++){
        board_arr_chr[0][jboss + k] = '#';
        gotoxy(3,jboss + k + 1);
        setConsoleColor(Magenta,BrightWhite);
        cout << board_arr_chr[0][jboss + k];
        setConsoleColor(Black,BrightWhite);
        
    }
}
void health_board(int num){
    switch (num){
    case 0:
        healthy = "100% ■■■■";
        break;
    case 1:
        healthy = "75%  ■■■□";
        break;
    case 2:
        healthy = "50%  ■■□□";
        break;
    case 3:
        healthy = "25%  ■□□□";
        break;
    case 4:
        healthy = "0%  □□□□";
        break;
    }
}
void enemy_shot(int& xbenemy, int& ybenemy,bool& can_enemy_shot){
    if(can_enemy_shot){
        for(int i = 15; i > 0; i--){
            if(board_arr_chr[i][ybenemy] = '@'){
                can_enemy_shot = false;
                xbenemy = i;
                break;
            }
        }
    }
    else if(!can_enemy_shot){
        if(xbenemy > 16){
            can_enemy_shot = true;
        }
        if(board_arr_chr[xbenemy + 1][ybenemy] == '<' || board_arr_chr[xbenemy + 1][ybenemy] == '>' || board_arr_chr[xbenemy + 1][ybenemy] == '!' || board_arr_chr[xbenemy + 1][ybenemy] == '^'){
            health_number++;
            can_enemy_shot = true;
        }
        else if(board_arr_chr[xbenemy + 1][ybenemy] == ' '){
            xbenemy++;
            board_arr_chr[xbenemy + 1][ybenemy] = '*';
            gotoxy(xbenemy + 4,ybenemy + 1);
            cout << board_arr_chr[xbenemy + 1][ybenemy];
        }
    }
}
void setting_move(char move_back){
    if(move_back == 'D' || move_back == 'd' || move_back == 77){
        if(setting_number < 18){
            setting_number++;
        }
    }
    else if(move_back == 'A' || move_back == 'a' || move_back == 75){
        if(setting_number > 1){
            setting_number--;
        }
    }
    else if(move_back == 'S' || move_back == 's' || move_back == 80){
        switch (setting_number)
        {
        case 17:
            setting_number += 1;
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 16:
            setting_number += 2;
            break;
        case 1:
        case 2:
        case 7:
        case 15:
            setting_number += 3;
            break;
        case 13:
        case 14:
            setting_number += 4;
            break;
        case 10:
        case 11:
        case 12:
            setting_number += 5;
            break;
        case 8:
        case 9:
            setting_number += 6;
            break;
        }
    }
    else if(move_back == 'W' || move_back == 'w'|| move_back == 72){
        switch (setting_number)
        {
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 18:
            setting_number -= 2;
            break;
        case 4:
            setting_number -= 3;
            break;
        case 16:
        case 10:
        case 11:
            setting_number -= 4;
            break;
        case 12:
        case 15:
            setting_number -= 5;
            break;
        case 13:
        case 14:
        case 17:
            setting_number -= 6;
            break;
        }
    }
}
void cout_Key_setting(){
    system("cls");
    cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
    cout << "┃░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░┃" << endl;
    cout << "┃░░                                                                ░░┃" << endl;
    cout << "┃░░        Moving:        ";
    if(keyboard_menu == 1){
        setConsoleColor(Yellow,BrightWhite);
        cout << "arrow keys ";
        if(moving_button == 1){
            cout << "■";
        }
        else{
            cout << "□";
        }
        setConsoleColor(Black,BrightWhite);
    }
    else{
        if(moving_button == 1){
        setConsoleColor(Green,BrightWhite);
        cout << "arrow keys ";
        cout << "■";
        }
        else{
            setConsoleColor(Black,BrightWhite);
            cout << "arrow keys ";
            cout << "□";
        }
        setConsoleColor(Black,BrightWhite);
    }
    if(keyboard_menu == 2){
        setConsoleColor(Yellow,BrightWhite);
        cout << "         WASD keys ";
        if(moving_button == 2){
            cout << "■";
        }
        else{
            cout << "□";
        }
        setConsoleColor(Black,BrightWhite);
    }
    else{
        if(moving_button == 2){
        setConsoleColor(Green,BrightWhite);
        cout << "         WASD keys ";
        cout << "■";
        }
        else{
            setConsoleColor(Black,BrightWhite);
            cout << "         WASD keys ";
            cout << "□";
        }
        setConsoleColor(Black,BrightWhite);
    }
        
    cout << "         ░░┃" << endl;
    cout << "┃░░                                                                ░░┃" << endl;
    cout << "┃░░                                                                ░░┃" << endl;
    cout << "┃░░        Shoting:           ";
    if(keyboard_menu == 3){
        string key_str = "";
        switch (shoting_button)
        {
        case 32:
            key_str = "Space";
            break;
        case 13:
            key_str = "Enter";
            break;
        case 16:
            key_str = "Shift";
            break;
        case 17:
            key_str = "Ctrl";
            break;
        case 18:
            key_str = "Alt";
            break;
        case 9:
            key_str = "Tab";
            break;
        case 8:
            key_str = "Backspace";
            break;
        case 27:
            key_str = "Esc";
            break;
        default:
            setConsoleColor(Yellow,BrightWhite);
            cout << shoting_button;
            setConsoleColor(Black,BrightWhite);
            break;
        }
        setConsoleColor(Yellow,BrightWhite);
        cout << key_str << endl;
        setConsoleColor(Black,BrightWhite);
    }
    else{
        string key_str = "";
        switch (shoting_button)
        {
        case 32:
            key_str = "Space";
            break;
        case 13:
            key_str = "Enter";
            break;
        case 16:
            key_str = "Shift";
            break;
        case 17:
            key_str = "Ctrl";
            break;
        case 18:
            key_str = "Alt";
            break;
        case 9:
            key_str = "Tab";
            break;
        case 8:
            key_str = "Backspace";
            break;
        case 27:
            key_str = "Esc";
            break;
            
        default:
            setConsoleColor(Green,BrightWhite);
            cout << shoting_button;
            setConsoleColor(Black,BrightWhite);
            break;
        }
        setConsoleColor(Green,BrightWhite);
        cout << key_str << endl;
        setConsoleColor(Black,BrightWhite);
    }
    cout <<"                 ░░┃" << endl;
    cout << "┃░░        Use Power-ups:         ";
    if(keyboard_menu == 4){
        string key_str = "";
        switch (power_ups_button)
        {
        case 32:
            key_str = "Space";
            break;
        case 13:
            key_str = "Enter";
            break;
        case 16:
            key_str = "Shift";
            break;
        case 17:
            key_str = "Ctrl";
            break;
        case 18:
            key_str = "Alt";
            break;
        case 9:
            key_str = "Tab";
            break;
        case 8:
            key_str = "Backspace";
            break;
        case 27:
            key_str = "Esc";
            break;
        default:
            setConsoleColor(Yellow,BrightWhite);
            cout << power_ups_button;
            setConsoleColor(Black,BrightWhite);
            break;
        }
        setConsoleColor(Yellow,BrightWhite);
        cout << key_str << endl;
        setConsoleColor(Black,BrightWhite);
    }
    else{
        string key_str = "";
        switch (power_ups_button)
        {
        case 32:
            key_str = "Space";
            break;
        case 13:
            key_str = "Enter";
            break;
        case 16:
            key_str = "Shift";
            break;
        case 17:
            key_str = "Ctrl";
            break;
        case 18:
            key_str = "Alt";
            break;
        case 9:
            key_str = "Tab";
            break;
        case 8:
            key_str = "Backspace";
            break;
        case 27:
            key_str = "Esc";
            break;
            
        default:
            setConsoleColor(Green,BrightWhite);
            cout << power_ups_button;
            setConsoleColor(Black,BrightWhite);
            break;
        }
        setConsoleColor(Green,BrightWhite);
        cout << key_str << endl;
        setConsoleColor(Black,BrightWhite);
    }
    cout << "                 ░░┃";





    cout << "┃░░                                                                ░░┃" << endl;
    cout << "┃░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░┃" << endl;
    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
    // ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
    // ┃░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░┃
    // ┃░░                                                                ░░┃
    // ┃░░        Moving:        arrow keys □         WASD keys □         ░░┃
    // ┃░░                                                                ░░┃
    // ┃░░                                                                ░░┃
    // ┃░░        Shoting:               shoting_button                   ░░┃
    // ┃░░                                                                ░░┃
    // ┃░░                                                                ░░┃
    // ┃░░        Use Power-ups:         power_ups_button                 ░░┃
    // ┃░░                                                                ░░┃
    // ┃░░                                                                ░░┃
    // ┃░░        Select button:         select_button                    ░░┃
    // ┃░░                                                                ░░┃
    // ┃░░                                                                ░░┃
    // ┃░░        Back:                 back_button                       ░░┃
    // ┃░░                                                                ░░┃
    // ┃░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░┃
    // ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
}
void move_keyboard_setting(char move){
    if(move == 'A' || move == 'a'){
        if(keyboard_menu > 1){
            keyboard_menu--;
        }
    }
    else if(move == 'D' || move == 'd'){
        if(keyboard_menu < 6){
            keyboard_menu++;
        }
    }
    else if(move == 'S' || move == 's'){
        switch (keyboard_menu)
        {
        case 1:
            keyboard_menu += 2;
            break;
        
        default:
            keyboard_menu ++;
            break;
        }
    }
    else if(move == 'W' || move == 'w'){
        switch (keyboard_menu)
        {
        case 3:
            keyboard_menu -= 2;
            break;
        
        default:
            keyboard_menu --;
            break;
        }
    }
}
bool check_enemy_line(int line_number){
    for(int i = 0; i <= 68; i++){
        if(board_arr_chr[line_number][i] == '@' || board_arr_chr[line_number][i] == '$'){
            return false;
        }
    }
    return true;
}
void game_over(){
    system("cls");
    cout << "▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒" << endl;
    cout << "▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓░▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓░▒▒▒▒▒▒▓▓░▒▒▒▒▒▒▒▒▒▓▓░▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓░▒▒▒▒▒" << endl;
    cout << "▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓░▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓░▒▒▒▒▒▒▓▓▓▓░▒▒▒▒▒▓▓▓▓░▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓░▒▒▒▒▒" << endl;
    cout << "▒▒▒▒▒▓▓▓▓░▒▒▒▓▓▓▓░▒▒▒▒▒▒▓▓▓▓░▒▒▒▓▓▓▓░▒▒▒▒▒▒▓▓▓▓▓▓░▒▓▓▓▓▓▓░▒▒▒▒▒▓▓▓▓░▒▒▒▒▒▒▒▒▒▒▒▒▒" << endl;
    cout << "▒▒▒▒▒▓▓▓▓░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓░▒▒▒▓▓▓▓░▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓░▒▒▒▒▒▓▓▓▓░▒▒▒▒▒▒▒▒▒▒▒▒▒" << endl;
    cout << "▒▒▒▒▒▓▓▓▓░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓░▒▒▒▒▒▒▓▓▓▓░▒▓▓░▒▓▓▓▓░▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓░▒▒▒▒▒▒▒" << endl;
    cout << "▒▒▒▒▒▓▓▓▓░▒▓▓▓▓▓▓░▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓░▒▒▒▒▒▒▓▓▓▓░▒▒▒▒▒▓▓▓▓░▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓░▒▒▒▒▒▒▒" << endl;
    cout << "▒▒▒▒▒▓▓▓▓░▒▓▓▓▓▓▓░▒▒▒▒▒▒▓▓▓▓░▒▒▒▓▓▓▓░▒▒▒▒▒▒▓▓▓▓░▒▒▒▒▒▓▓▓▓░▒▒▒▒▒▓▓▓▓░▒▒▒▒▒▒▒▒▒▒▒▒▒" << endl;
    cout << "▒▒▒▒▒▓▓▓▓░▒▒▒▓▓▓▓░▒▒▒▒▒▒▓▓▓▓░▒▒▒▓▓▓▓░▒▒▒▒▒▒▓▓▓▓░▒▒▒▒▒▓▓▓▓░▒▒▒▒▒▓▓▓▓░▒▒▒▒▒▒▒▒▒▒▒▒▒" << endl;
    cout << "▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓░▒▒▒▒▒▒▓▓▓▓░▒▒▒▓▓▓▓░▒▒▒▒▒▒▓▓▓▓░▒▒▒▒▒▓▓▓▓░▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓░▒▒▒▒▒" << endl;
    cout << "▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓░▒▒▒▒▒▒▓▓▓▓░▒▒▒▓▓▓▓░▒▒▒▒▒▒▓▓▓▓░▒▒▒▒▒▓▓▓▓░▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓░▒▒▒▒▒" << endl;
    cout << "▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒" << endl;
    cout << "▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒" << endl;
    cout << "▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓░▒▒▒▒▒▒▓▓▓▓░▒▒▒▓▓▓▓░▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓░▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓░▒▒▒▒" << endl;
    cout << "▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓░▒▒▒▒▒▒▓▓▓▓░▒▒▒▓▓▓▓░▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓░▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓░▒▒▒▒" << endl;
    cout << "▒▒▒▒▒▓▓▓▓░▒▒▒▓▓▓▓░▒▒▒▒▒▒▓▓▓▓░▒▒▒▓▓▓▓░▒▒▒▒▒▒▓▓▓▓░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓░▒▒▒▒▓▓▓▓░▒▒▒▒" << endl;
    cout << "▒▒▒▒▒▓▓▓▓░▒▒▒▓▓▓▓░▒▒▒▒▒▒▓▓▓▓░▒▒▒▓▓▓▓░▒▒▒▒▒▒▓▓▓▓░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓░▒▒▒▒▓▓▓▓░▒▒▒▒" << endl;
    cout << "▒▒▒▒▒▓▓▓▓░▒▒▒▓▓▓▓░▒▒▒▒▒▒▓▓▓▓░▒▒▒▓▓▓▓░▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓░▒▒▒▒▒▒▒▒▒▓▓▓▓░▒▒▒▒▓▓▓▓░▒▒▒▒" << endl;
    cout << "▒▒▒▒▒▓▓▓▓░▒▒▒▓▓▓▓░▒▒▒▒▒▒▓▓▓▓░▒▒▒▓▓▓▓░▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓░▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓░▒▒▒▒" << endl;
    cout << "▒▒▒▒▒▓▓▓▓░▒▒▒▓▓▓▓░▒▒▒▒▒▒▓▓▓▓░▒▒▒▓▓▓▓░▒▒▒▒▒▒▓▓▓▓░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓░▒▒▒▒▒▒▒▒" << endl;
    cout << "▒▒▒▒▒▓▓▓▓░▒▒▒▓▓▓▓░▒▒▒▒▒▒▓▓▓▓░▒▒▒▓▓▓▓░▒▒▒▒▒▒▓▓▓▓░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓░▒▒▒▒▒▒" << endl;
    cout << "▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓░▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓░▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓░▒▒▒▒▒▒▒▓▓▓▓░▒▒▓▓▓▓▓▓░▒▒▒▒" << endl;
    cout << "▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓░▒▒▒▒▒▒▒▒▒▒▓▓▓▓░▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓░▒▒▒▒▒▒▒▓▓▓▓░▒▒▒▒▒▓▓▓░▒▒▒▒" << endl;
    cout << "▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒" << endl;
}
void level_up(){
    setConsoleColor(Red,BrightWhite);
    gotoxy(6,15);
    cout << "┌─┐    ┌────┐  ┌─┐    ┌─┐  ┌────┐  ┌─┐";
    gotoxy(7,15);
    cout << "│ │    │ ┌──┘  │ │    │ │  │ ┌──┘  │ │";
    gotoxy(8,15);
    cout << "│ │    │ └──┐  │ |    │ |  │ └──┐  │ │";
    gotoxy(9,15);
    cout << "│ │    │ ┌──┘   ╲ ╲  ╱ ╱   │ ┌──┘  │ │";
    gotoxy(10,15);
    cout << "│ └─┐  │ └──┐    ╲ ╲╱ ╱    │ └──┐  │ └─┐";
    gotoxy(11,15);
    cout << "└───┘  └────┘     └──┘     └────┘  └───┘";
    gotoxy(12 ,15);
    cout << "        ┌─┐    ┌─┐     ┌──────┐";
    gotoxy(13,15);
    cout << "        │ │    │ │     │ ┌──┐ │";
    gotoxy(14,15);
    cout << "        │ │    │ │     │ └──┘ │";
    gotoxy(15,15);
    cout << "        │ │    │ │     │ ┌────┘";
    gotoxy(16,15);
    cout << "        │ ─────┘ │     │ │";
    gotoxy(17,15);
    cout << "        └────────┘     └─┘";
}
void move_puase_menu(char move){
    if(move == 'w' || move == 'W' || move == 72){
        if(2 <= puase_menu_num && puase_menu_num <= 3){
            puase_menu_num--;
        }
        else if(puase_menu_num == 1){
            puase_menu_num = 3;
        }
    }
    else if(move == 's' || move == 'S'|| move == 80){
        if(1 <= puase_menu_num && puase_menu_num <= 2){
            puase_menu_num++;
        }
        else if(puase_menu_num == 3){
            puase_menu_num = 1;
        }
    }
}
void defence(int number){
    for(int i = -2; i <= 2; i++ ){
        if(0 < (number + i) && (number + i) < 68){
            board_arr_chr[13][number + i] = '-';
        }
    }
}
void move_registry(char move){
    if((move == 'w' || move == 'W') && (registry_number == 2)){
        registry_number--;
    }
    else if((move == 's' || move == 'S') && (registry_number == 1)){
        registry_number++;
    }
}
bool check_be_enemy(){
    for(int i = 0; i < 17; i++){
        for(int j = 0; j < 68; j++){
            if((board_arr_chr[i][j] == '@' || board_arr_chr[i][j] == '$')){
                return true;
            }
        }
    }
    return false;
}
void loading_animation(){
    system("cls");
    setConsoleColor(BrightBlack,BrightWhite);
    cout << "                                         "<<endl;
    cout << "                              ████████                              " << endl;
    cout << "                          ████";
    setConsoleColor(Black,BrightWhite);
    cout << "████████";
    setConsoleColor(BrightBlack,BrightWhite);
    cout << "████                          " << endl;
    cout << "                        ██";
    setConsoleColor(Black,BrightWhite);
    cout << "████████████████";
    setConsoleColor(BrightBlack,BrightWhite);
    cout << "██                        " << endl;
    setConsoleColor(BrightRed,BrightWhite);
    cout << "                    ████";
    setConsoleColor(Black,BrightWhite);
    cout << "████████████████████";
    setConsoleColor(BrightRed,BrightWhite);
    cout << "████                    " << endl;
    setConsoleColor(BrightRed,BrightWhite);
    cout << "                ████";
    setConsoleColor(Red,BrightWhite);
    cout << "██████";
    setConsoleColor(Black,BrightWhite);
    cout << "████████████████";
    setConsoleColor(Red,BrightWhite);
    cout << "██████";
    setConsoleColor(BrightRed,BrightWhite);
    cout << "████                " << endl;
    setConsoleColor(BrightRed,BrightWhite);
    cout << "            ████";
    setConsoleColor(Red,BrightWhite);
    cout << "████████████████████████████████████████            " << endl;
    cout << "                ████████████████████████████████████                " << endl;
    cout << "                     ██████████████████████████                     " << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    setConsoleColor(BrightGreen,BrightWhite);
    cout << "                         ██████████████████                         " << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    setConsoleColor(Green,BrightWhite);
    cout << "                         ██████████████████                         " << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << "                       ██████████████████████                       " << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << "                       ██████████████████████                       " << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << "                       ██████████████████████                       " << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    setConsoleColor(BrightGreen,BrightWhite);
    cout << "                     ██████████████████████████                     " << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    setConsoleColor(Green,BrightWhite);
    cout << "                     ██████████████████████████                     " << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << "                     ██████████████████████████                     " << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << "                   ██████████████████████████████                   " << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << "                   ██████████████████████████████                   " << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    setConsoleColor(BrightGreen,BrightWhite);
    cout << "                   ██████████████████████████████                   " << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    setConsoleColor(Green,BrightWhite);
    cout << "                 ██████████████████████████████████                 " << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << "                 ██████████████████████████████████                 " << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << "                 ██████████████████████████████████                 " << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << "               ██████████████████████████████████████               " << endl;
    this_thread::sleep_for(chrono::milliseconds(600));
}
int main(){
    setConsoleColor(Black,BrightWhite);
    shoting_button = 32;
    power_ups_button = 16;
    for(int i = 0; i < 17; i++){
        for(int j = 0; j < 68; j++){
            board_arr_chr[i][j] = ' ';
        }
    }
    srand(time(0));
    ifstream checkfile("LoadGame.txt");
    if(checkfile){
        loading = true;
        checkfile.close();
    }
    else{
        loading = false;
    }
    while(true){
        cout_menu(mud_number);
        char move_ud;
        do{
            move_ud = getch();
            move_up_down(move_ud);
        } while(move_ud != 13);
        if(mud_number == 1 || mud_number == 2){
            fstream file;
            int bullet_x, bullet_y;
            bool shooted;
            bool enemy1_shooted;  
            int enemy1_bullet_x;
            int enemy1_bullet_y; 
            bool enemy2_shooted;  
            int enemy2_bullet_x;
            int enemy2_bullet_y; 
            int fps;
            int frame_counter;
            bool breaked = false;
            bool next = true;
            int level = 1;
            chrono::steady_clock::time_point time_counter;
            switch(mud_number){
                case 1:
                    file.open("LoadGame.txt",ios::in);
                    if(!file){
                        loading = false;
                        next = false;
                        break;
                    }
                    else{
                        loading = true;
                        for(int i = 0; i < 16; i++){
                            for(int j = 0; j < 68; j++){
                                file >> board_arr_chr[i][j];
                                if(board_arr_chr[i][j] == '?'){
                                    board_arr_chr[i][j] = ' ';
                                }
                            }
                        }
                        string deleted;
                        file >> space_num;
                        getline(file, deleted);
                        getline(file, healthy);
                        file >> number_left_right_1;
                        file >> number_left_right_2;
                        file >> score;
                        file >> shooted;
                        file >> start_t;
                        file >> player.name;
                        file.close();
                        time_counter = chrono::steady_clock::now();
                    }
                break;
                case 2:
                    player.name = "";
                    bool true_name = false;
                    char move;
                    while(true){
                        cout_registry();
                        move = getch();
                        move_registry(move);
                        if(move == 13){
                            if(registry_number == 1){
                                player.name = "";
                                cout_registry();
                                gotoxy(3,21);
                                setConsoleColor(Yellow,BrightWhite);
                                cin >> player.name;
                                setConsoleColor(Black,BrightWhite);
                                true_name = true;
                                if(getch() == 13){
                                gotoxy(3,21);
                                cout << player.name;
                                }
                            }
                            else if(registry_number == 2){
                                if(player.name.length() > 20){
                                    player.name = player.name.substr(0,20);
                                }
                                else if(player.name.length() < 3){
                                    true_name = false;
                                    cout_registry_error0();
                                    this_thread::sleep_for(chrono::milliseconds(150));
                                    cout_registry();
                                }
                                for(int i = 0; i < player.name.length(); i++){
                                    if(!((65 <= player.name[i] && player.name[i] <= 90) || (97 <= player.name[i] && player.name[i] <= 122) || (48 <= player.name[i] && player.name[i] <= 57) || (player.name[i] == '_'))){
                                        true_name = false;
                                        cout_registry_error0();
                                        this_thread::sleep_for(chrono::milliseconds(150));
                                        cout_registry();
                                        break;
                                    }
                                }
                                if(true_name){
                                    cout_registry_error1();
                                    this_thread::sleep_for(chrono::milliseconds(250));
                                    cout_registry();
                                    break;
                                }
                            }
                        }
                    }
                    // loading_animation();
                    health_number = 0;
                    healthy = "100% ■■■■";
                    shooted = false;
                    enemy1_shooted = false;  
                    enemy1_bullet_y = 0; 
                    enemy2_shooted = false;  
                    enemy2_bullet_y = 0; 
                    score = 0;
                    timer = 0;
                    enemy_boss_is_alive = true;
                    time_counter = chrono::steady_clock::now();
                    for(int i = 0; i < 17; i++){
                        for(int j = 0; j < 68; j++){
                            board_arr_chr[i][j] = ' ';
                        }
                    }
                    int row_counter = 0;
                    switch (set_difficulty){
                        case 1:
                            row_counter = 2;
                        break;
                        case 2:
                            row_counter = 4;
                        break;
                        case 3:
                            row_counter = 6;
                        break;
                    }
                    srand(time(0));
                    for(int i = 1; i <= row_counter/2; i++){
                        enemy2(i,(rand() % 3) + 1);
                    }
                    for(int i = (row_counter / 2) + 1; i <= row_counter; i++){
                        enemy1(i,(rand() % 3) + 1);
                    }
                    if(set_defence == 1){
                        for(int i = 0; i < 3; i++){
                        defence(rand() % 60 + 4);
                        }
                    }
                break;
            }
            if(next){
                frame_counter = 0;
                fps = 60;
                chrono::milliseconds frame_time(1000/fps);
                bool next_level = false;
                int speed = 20;
                system("cls");
                // for(int i = 0; i < 17; i++){
                //     for(int j = 0; j < 68; j++){
                //         cout << board_arr_chr[i][j] << "";
                //     }
                //     cout << endl;
                // }
                // getch();
                cout_board_02();
                while(true){
                    chrono::steady_clock::time_point start = chrono::steady_clock::now();
                    if(next_level){
                        level++;
                        level_up();
                        gotoxy(18,32);
                        cout << "level ";
                        cout << level;
                        this_thread::sleep_for(chrono::milliseconds(2000));
                        next_level = false;
                        shooted = false;
                        number_left_right_1 = 0;
                        number_left_right_2 = 1;
                        enemy1_shooted = false;  
                        enemy1_bullet_y = 0; 
                        enemy2_shooted = false;  
                        enemy2_bullet_y = 0; 
                        enemy_boss_is_alive = true;
                        for(int i = 0; i < 17; i++){
                            for(int j = 0; j < 68; j++){
                                board_arr_chr[i][j] = ' ';
                            }
                        }
                        int row_counter = 0;
                        switch (set_difficulty){
                            case 1:
                                row_counter = 2;
                            break;
                            case 2:
                                row_counter = 4;
                            break;
                            case 3:
                                row_counter = 6;
                            break;
                        }
                        srand(time(0));
                        for(int i = 1; i <= row_counter/2; i++){
                            enemy2(i,(rand() % 3) + 1);
                        }
                        for(int i = (row_counter / 2) + 1; i <= row_counter; i++){
                            enemy1(i,(rand() % 3) + 1);
                        }
                        if(set_defence == 1){
                            for(int i = 0; i < 3; i++){
                            defence(rand() % 60 + 4);
                            }
                            cout_board_02(); 
                        }
                    }
                    if(!check_enemy_line(16)){
                        game_over();
                        cout << "Press 'Esc' to back ...";
                        break;
                    }
                    if(!check_enemy_line(12)){
                        for(int i = 0; i < 68; i++){
                            if(board_arr_chr[13][i] == '-'){
                                gotoxy(16,i + 1);
                                cout << board_arr_chr[13][i];
                                this_thread::sleep_for(chrono::milliseconds(100));
                                board_arr_chr[13][i] = ' ';
                                gotoxy(16,i + 1);
                                cout << board_arr_chr[13][i];
                            }
                        }
                    }
                    if(_kbhit()){
                        char move_shot;
                        move_shot = getch();
                        if(move_shot == 27){
                            while(true){
                                char pmove;
                                int puase_selected;
                                cout_puase_menu(puase_menu_num);
                                pmove = getch();
                                move_puase_menu(pmove);
                                if(pmove == 13){
                                    puase_selected = puase_menu_num;
                                    if(puase_selected == 1){
                                        cout_board_02(); 
                                        break;
                                    }
                                    else if(puase_selected == 2){
                                        ofstream file("LoadGame.txt",ios::trunc);
                                        ofstream scoreFile("Leaderboard.txt",ios::app);
                                        for(int i = 0; i < 16; i++){
                                            for(int j = 0; j < 68; j++){
                                                if(board_arr_chr[i][j] == ' '){
                                                    file << '?';
                                                }
                                                else{
                                                    file << board_arr_chr[i][j];
                                                }
                                            }
                                            file << endl;
                                        }
                                        file << space_num << endl;
                                        file << healthy << endl;
                                        file << number_left_right_1 << endl;
                                        file << number_left_right_2 << endl;
                                        file << score << endl;
                                        file << shooted << endl;
                                        file << timer << endl;
                                        file << player.name << endl;
                                        file.close();
                                        scoreFile << player.name << endl;
                                        scoreFile << score << endl;
                                        scoreFile << timer << endl;
                                        scoreFile << healthy << endl;
                                        scoreFile.close();
                                        loading = true;
                                        breaked = true;
                                        break;
                                    }
                                    else{
                                        breaked = true;
                                        break;
                                    }
                                }
                            }
                            if(breaked){
                                breaked = false;
                                break;
                            }
                        }
                        move_airplane_right_left2(move_shot);
                        if(move_shot == ' ' && !shooted){
                            bullet_x = space_num + 2;
                            bullet_y = 16;
                            shooted = true;
                        }
                    }
                    if(frame_counter % 15 == 0){
                        if(!enemy1_shooted){
                            enemy1_bullet_x = (rand() % 52) + 8;
                        }
                    }
                    if(frame_counter % 15 == 0){
                        if(!enemy1_shooted){
                            for(int i = 16; i > 0; i--){
                                if(board_arr_chr[i][enemy1_bullet_x] == '@'){
                                    enemy1_bullet_y = i;
                                    enemy1_shooted = true;
                                    break;
                                }
                            }
                            if(board_arr_chr[enemy1_bullet_y + 1][enemy1_bullet_x] == ' '){
                                board_arr_chr[enemy1_bullet_y + 1][enemy1_bullet_x] = '*';
                                enemy1_bullet_y++;
                            }
                        }
                        else{
                            if(space_num <= enemy1_bullet_x && enemy1_bullet_x <= (space_num + 5) && enemy1_bullet_y == 16){
                                if(health_number < 4){
                                health_number++;
                                }
                                health_board(health_number);
                                gotoxy(1,59);
                                setConsoleColor(Red,BrightWhite);
                                cout << healthy;
                                setConsoleColor(Black,BrightWhite);
                                if(health_number == 4){
                                    remove("LoadGame.txt");
                                    game_over();
                                    getch();
                                    break;
                                }
                            }
                            if(enemy1_bullet_y > 16){
                                board_arr_chr[enemy1_bullet_y][enemy1_bullet_x] = ' ';
                                gotoxy(enemy1_bullet_y + 3,enemy1_bullet_x + 1);
                                cout << board_arr_chr[enemy1_bullet_y][enemy1_bullet_x];
                                enemy1_shooted = false;
                            }
                            else{ 
                                if(board_arr_chr[enemy1_bullet_y][enemy1_bullet_x] == '-'){
                                    gotoxy(enemy1_bullet_y + 3,enemy1_bullet_x + 1);
                                    cout << "■";
                                    this_thread::sleep_for(chrono::milliseconds(100));
                                    board_arr_chr[enemy1_bullet_y][enemy1_bullet_x] = ' ';
                                    gotoxy(enemy1_bullet_y + 3,enemy1_bullet_x + 1);
                                    cout << board_arr_chr[enemy1_bullet_y][enemy1_bullet_x];
                                }
                                else{
                                    board_arr_chr[enemy1_bullet_y][enemy1_bullet_x] = ' ';
                                    gotoxy(enemy1_bullet_y + 3,enemy1_bullet_x + 1);
                                    cout << board_arr_chr[enemy1_bullet_y][enemy1_bullet_x];
                                    board_arr_chr[enemy1_bullet_y + 1][enemy1_bullet_x] = '*';
                                    gotoxy(enemy1_bullet_y + 4,enemy1_bullet_x + 1);
                                    setConsoleColor(Red,BrightWhite);
                                    cout << board_arr_chr[enemy1_bullet_y + 1][enemy1_bullet_x];
                                    setConsoleColor(Black,BrightWhite);
                                }
                            }
                            enemy1_bullet_y++;
                        }
                    }
                    if(frame_counter > 300){
                        if(level > 2){
                            for(int i = 0; i < 68; i++){
                                if(board_arr_chr[1][i] != ' '){
                                    power_u = false;
                                    break;
                                }
                            }
                            if(power_u){
                                int num = rand() % 60 + 5;
                                board_arr_chr[1][num] = '%';
                                gotoxy(4,num + 1);
                                cout << board_arr_chr[1][num];
                                power_u = false;
                            }
                        }
                    }
                    if(frame_counter % 600 == 0){
                        power_u = true;
                    }
                    if(shooted){
                        if(bullet_y < 0){
                            shooted = false;
                            board_arr_chr[bullet_y + 1][bullet_x] = ' ';
                            gotoxy(bullet_y + 3,bullet_x + 1);
                            cout << board_arr_chr[bullet_y + 1][bullet_x];
                        }
                        else{
                            if(board_arr_chr[bullet_y][bullet_x] == ' '){
                                board_arr_chr[bullet_y + 1][bullet_x] = ' ';
                                gotoxy(bullet_y + 3,bullet_x + 1);
                                cout << board_arr_chr[bullet_y + 1][bullet_x];
                                board_arr_chr[bullet_y][bullet_x] = airplane_bullet_skin[0];
                                gotoxy(bullet_y + 2,bullet_x + 1);
                                setConsoleColor(Red,BrightWhite);
                                if(bullet_y > 0){
                                    cout << board_arr_chr[bullet_y][bullet_x];
                                }
                                else{
                                    shooted = false;
                                }
                                setConsoleColor(Black,BrightWhite);
                            }
                            else if(board_arr_chr[bullet_y][bullet_x] == '@'){
                                board_arr_chr[bullet_y][bullet_x] = '@';
                                gotoxy(bullet_y + 3,bullet_x + 1);
                                cout << board_arr_chr[bullet_y][bullet_x];
                                this_thread::sleep_for(chrono::milliseconds(100));
                                board_arr_chr[bullet_y][bullet_x] = ' ';
                                score += 10;
                                gotoxy(1 , 12);
                                setConsoleColor(Yellow,BrightWhite);
                                cout << score;
                                setConsoleColor(Black,BrightWhite);
                                gotoxy(bullet_y + 3,bullet_x + 1);
                                cout << board_arr_chr[bullet_y][bullet_x];
                                board_arr_chr[bullet_y + 1][bullet_x] = ' ';
                                gotoxy(bullet_y + 3,bullet_x + 1);
                                cout << board_arr_chr[bullet_y + 1][bullet_x];
                                shooted = false;
                            }
                            else if(board_arr_chr[bullet_y][bullet_x] == '%'){
                                gotoxy(bullet_y + 3,bullet_x + 1);
                                cout << board_arr_chr[bullet_y][bullet_x];
                                this_thread::sleep_for(chrono::milliseconds(100));
                                board_arr_chr[bullet_y][bullet_x] = ' ';
                                gotoxy(bullet_y + 3,bullet_x + 1);
                                cout << board_arr_chr[bullet_y][bullet_x];
                                if(health_number > 1){
                                    health_number--;
                                    health_board(health_number);
                                    gotoxy(1,59);
                                    setConsoleColor(Red,BrightWhite);
                                    cout << healthy;
                                    setConsoleColor(Black,BrightWhite);
                                }
                                shooted = false;
                            }
                            else if(board_arr_chr[bullet_y][bullet_x] == '-'){
                                gotoxy(bullet_y + 3,bullet_x + 1);
                                cout << "■";
                                this_thread::sleep_for(chrono::milliseconds(100));
                                board_arr_chr[bullet_y][bullet_x] = ' ';
                                gotoxy(bullet_y + 3,bullet_x + 1);
                                cout << board_arr_chr[bullet_y][bullet_x];
                                board_arr_chr[bullet_y + 1][bullet_x] = ' ';
                                gotoxy(bullet_y + 3,bullet_x + 1);
                                cout << board_arr_chr[bullet_y + 1][bullet_x];
                                shooted = false;
                            }
                            else if(board_arr_chr[bullet_y][bullet_x] == '$'){
                                board_arr_chr[bullet_y][bullet_x] = '$';
                                gotoxy(bullet_y + 3,bullet_x + 1);
                                cout << board_arr_chr[bullet_y][bullet_x];
                                this_thread::sleep_for(chrono::milliseconds(100));
                                board_arr_chr[bullet_y][bullet_x] = ' ';
                                score += 50;
                                gotoxy(1 , 12);
                                setConsoleColor(Yellow,BrightWhite);
                                cout << score;
                                setConsoleColor(Black,BrightWhite);
                                gotoxy(bullet_y + 3,bullet_x + 1);
                                cout << board_arr_chr[bullet_y][bullet_x];
                                board_arr_chr[bullet_y + 1][bullet_x] = ' ';
                                gotoxy(bullet_y + 3,bullet_x + 1);
                                cout << board_arr_chr[bullet_y + 1][bullet_x];
                                shooted = false;
                            }
                            else if(board_arr_chr[bullet_y][bullet_x] == '#'){
                                enemy_boss_is_alive = false;
                                for(int i = 0; i < 68; i++){
                                    if(board_arr_chr[0][i] == '#'){
                                        gotoxy(3,i + 1);
                                        cout << board_arr_chr[0][i];
                                        board_arr_chr[0][i] = ' ';
                                        this_thread::sleep_for(chrono::milliseconds(100));
                                        gotoxy(3,i + 1);
                                        cout << board_arr_chr[0][i]; 
                                    }
                                }
                                score += 100;
                                gotoxy(1 , 12);
                                setConsoleColor(Yellow,BrightWhite);
                                cout << score;
                                setConsoleColor(Black,BrightWhite); 
                                board_arr_chr[bullet_y + 1][bullet_x] = ' ';
                                gotoxy(bullet_y + 3,bullet_x + 1);
                                cout << board_arr_chr[bullet_y + 1][bullet_x];
                                shooted = false;
                            }
                            else{
                                board_arr_chr[bullet_y + 1][bullet_x] = ' ';
                                gotoxy(bullet_y + 3,bullet_x + 1);
                                cout << board_arr_chr[bullet_y + 1][bullet_x];
                                shooted = false;
                            }
                            bullet_y--;
                        }
                    }
                    srand(time(0));
                    if(frame_counter % 60 == 0){
                        (rand() % 59) + 5;
                            enemy_boss((rand() % 59) + 5);
                    }
                    if(frame_counter == 600){
                        move_down_enemy();
                    }
                    switch (level)
                    {
                    case 2:
                        speed = 15;
                        break;
                    case 4:
                        speed = 10;
                        break;
                    case 6:
                        speed = 5;
                        break;
                    default:
                        break;
                    }
                    if(frame_counter % speed == 0){
                        if(number_left_right_1 > number_left_right_2){
                            if(number_left_right_1 < 2){
                                number_left_right_1++;
                                move_right_enemy();
                            }
                            else if(number_left_right_1 == 2){
                                number_left_right_1--;
                                move_left_enemy();
                            }
                            number_left_right_2++;
                        }
                        else if(number_left_right_1 < number_left_right_2){
                            if(number_left_right_1 > -3){
                                number_left_right_1--;
                                move_left_enemy();
                            }
                            else if(number_left_right_1 == -3){
                                number_left_right_1++;
                                move_right_enemy();
                            }
                            number_left_right_2--;
                        }
                    }
                    if(!check_be_enemy()){
                        next_level = true;
                    }
                    chrono::steady_clock::time_point end_time = chrono::steady_clock::now();
                    chrono::milliseconds f = chrono::duration_cast<chrono::milliseconds>(end_time - start);
                    chrono::seconds duration = chrono::duration_cast<chrono::seconds>(end_time - time_counter);
                    if(f < frame_time){
                        this_thread::sleep_for(frame_time - f);
                    }
                    gotoxy(1,38);
                    timer = start_t + duration.count();
                    cout << timer;
                    frame_counter++;
                    if(frame_counter > 600){
                        frame_counter = 0;
                    }
                }
            }
        }
        else if(mud_number == 3){
            while(true){
                system("cls");
                string file;
                ifstream inFile("LearnGame.txt");
                while(getline(inFile,file)){
                    for(int i = 0; i < file.size(); i++){
                        if(file[i] == '@'){
                            setConsoleColor(Green,BrightWhite);
                            cout << file[i];
                            setConsoleColor(Black,BrightWhite);
                        }
                        else if(file[i] == '$'){
                            setConsoleColor(Green,BrightWhite);
                            cout << file[i];
                            setConsoleColor(Black,BrightWhite);
                        }
                        else if(file[i] == '#'){
                            setConsoleColor(Magenta,BrightWhite);
                            cout << file[i];
                            setConsoleColor(Black,BrightWhite);
                        }
                        else{
                            cout << file[i];
                        }
                    }
                    cout << endl;
                }
                cout << "Press " << back_button << "to back ...";
                char back;
                back = getch();
                if(back == 27){
                    break;
                }
            }
        }
        else if(mud_number == 4){
            fstream file("Leaderboard.txt");
            struct user{
                string name = "";
                int score = 0;
                int timer = 0;
                string hp = "";
            };
            user p[100];
            while(true){
                int num = 0;
                while(file >> p[num].name >> p[num].score >> p[num].timer){
                    string deleted;
                    getline(file, deleted);
                    getline(file, p[num].hp);
                    for(int j = 0; j < num; j++){
                        if(p[j].name == p[num].name){
                            if(p[j].score < p[num].score){
                                p[j] = p[num];
                            }
                            else{
                                p[num].name = "";
                            }
                            num--;
                            break;
                        }
                    }
                    num++;
                }
                for(int i = 0; i < 100; i++){
                    for(int j = i; j < 100; j++){
                        if(p[i].score < p[j].score){
                            swap(p[i],p[j]);
                        }
                    }
                }
                for(int i = 0; i < 100; i++){
                    if(p[i].name == ""){
                        for(int j = i + 1; j < 100; j++){
                            p[j-1] = p[j];
                        }
                    }
                }
                system("cls");
                setConsoleColor(Cyan,BrightWhite);
                cout << endl;
                cout << "                                       ";
                for(int i = 0; i < (27 - p[0].name.length()) / 2; i++){
                    cout << " ";
                }
                if(p[0].name == player.name){
                    setConsoleColor(Yellow,BrightWhite);
                    cout << "YOU";
                    setConsoleColor(Cyan,BrightWhite);
                }
                else{
                    cout << p[0].name;
                }
                for(int i = 0; i < (27 - p[0].name.length()) / 2; i++){
                    cout << " ";
                }
                cout << "                                       " << endl;
                cout << "                                       ┏━━━━━━━━━━━━━━━━━━━━━━━━┓                             " << endl; 
                cout << "                ";
                if(p[1].name == player.name){
                    for(int i = 0; i < (22) / 2; i++){
                        cout << " ";
                    }
                    setConsoleColor(Yellow,BrightWhite);
                    cout << "YOU";
                    setConsoleColor(Cyan,BrightWhite);
                }
                else{
                    for(int i = 0; i < (24 - p[1].name.length()) / 2; i++){
                        cout << " ";
                    }
                    cout << p[1].name;
                }
                for(int i = 0; i < (23 - p[1].name.length()) / 2; i++){
                    cout << " ";
                }
                cout << "┃          ╰ 1 ╯         ┃                             " << endl;
                cout << "                ┏━━━━━━━━━━━━━━━━━━━━━━┫                        ┃";
                for(int i = 0; i < (19 - p[2].name.length()) / 2; i++){
                    cout << " ";
                }
                if(p[2].name == player.name){
                    setConsoleColor(Yellow,BrightWhite);
                    cout << "YOU";
                    setConsoleColor(Cyan,BrightWhite);
                }
                else{
                    cout << p[2].name;
                }
                for(int i = 0; i < (21 - p[2].name.length()) / 2; i++){
                    cout << " ";
                }
                cout << "                       " << endl;
                cout << "                ┃        ╰ 2 ╯         ┃                        ┣━━━━━━━━━━━━━━━━━━━━┓         " << endl;
                cout << "                ┃                      ┃                        ┃       ╰ 3 ╯        ┃         " << endl;
                cout << "                ┃                      ┃                        ┃                    ┃         " << endl;
                cout << "                ┃";
                for(int i = 0; i < (22 - digit_number(p[1].score)) / 2; i++){
                    cout << " ";
                }
                if(digit_number(p[1].score) % 2 != 0){
                    cout << " ";
                }
                cout << p[1].score;
                for(int i = 0; i < (22 - digit_number(p[1].score)) / 2; i++){
                    cout << " ";
                }
                cout << "┃";
                for(int i = 0; i < (24 - digit_number(p[0].score)) / 2; i++){
                    cout << " ";
                }
                cout << p[0].score;
                for(int i = 0; i < (24 - digit_number(p[0].score)) / 2; i++){
                    cout << " ";
                }
                cout << " ┃";
                for(int i = 0; i < (20 - digit_number(p[2].score)) / 2; i++){
                    cout << " ";
                }
                cout << p[2].score;
                for(int i = 0; i < (20 - digit_number(p[2].score)) / 2; i++){
                    cout << " ";
                }
                cout << "┃         " << endl;
                cout << "                ┃";
                for(int i = 0; i < 9; i++){
                    cout << " ";
                }
                cout << show_timer(p[1].timer);
                if(show_timer(p[1].timer).length() == 5){
                    for(int i = 0; i < 9; i++){
                        cout << " ";
                    }
                }
                else{
                    for(int i = 0; i < 9; i++){
                        cout << " ";
                    }
                }
                cout << "┃";
                for(int i = 0; i < 10; i++){
                    cout << " ";
                }
                cout << show_timer(p[0].timer);
                if(show_timer(p[0].timer).length() == 5){
                    for(int i = 0; i < 9; i++){
                        cout << " ";
                    }
                }
                else{
                    for(int i = 0; i < 8; i++){
                        cout << " ";
                    }
                }
                cout << "┃";
                for(int i = 0; i < 8; i++){
                    cout << " ";
                }
                cout << show_timer(p[2].timer);
                if(show_timer(p[2].timer).length() == 5){
                    for(int i = 0; i < 7; i++){
                        cout << " ";
                    }
                }
                else{
                    for(int i = 0; i < 8; i++){
                        cout << " ";
                    }
                }
                cout << "┃         " << endl;
                cout << "                ┃      ";
                cout << p[1].hp;
                cout << "       ┃       ";
                cout << p[0].hp;
                cout << "        ┃     ";
                cout << p[2].hp;
                cout << "      ┃         " << endl;
                cout << "                ┗━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━┛         " << endl;
                for(int i = 3; i < num; i++){
                    if(p[i].name == ""){
                        break;
                    }
                    else{
                        if(p[i].name == player.name){
                            setConsoleColor(Yellow,BrightWhite);
                            cout << "                " << i + 1 << "- " << "YOU" << " >> " << p[i].score << " >> " << show_timer(p[i].timer) << " >> " << p[i].hp << endl;
                            setConsoleColor(Black,BrightWhite);
                        }
                        else{
                            cout << "                " << i + 1 << "- ";
                            setConsoleColor(Black,BrightWhite);
                            cout << p[i].name;
                            setConsoleColor(Cyan,BrightWhite);
                            cout << " >> ";
                            setConsoleColor(BrightYellow,BrightWhite);
                            cout << p[i].score;
                            setConsoleColor(Cyan,BrightWhite);
                            cout << " >> ";
                            setConsoleColor(Black,BrightWhite);
                            cout << show_timer(p[i].timer);
                            setConsoleColor(Cyan,BrightWhite);
                            cout << " >> ";
                            setConsoleColor(Red,BrightWhite);
                            cout << p[i].hp << endl;
                            setConsoleColor(Cyan,BrightWhite);

                        }
                    }
                }
                char back;
                back = getch();
                if(back == 27){
                    break;
                }
            }
        }
        else if(mud_number == 5){
            setting_number = 1;
            while(true){
                cout_border();
                char move_back;
                move_back = getch();
                if(move_back == 27){
                    break;
                }
                else if(move_back == 13){
                    if(1 <= setting_number && setting_number <= 3){
                        set_difficulty = setting_number;
                    }
                    else if(4 <= setting_number && setting_number <= 5){
                        set_defence = setting_number - 3;
                    }
                    else if(6 <= setting_number && setting_number <= 7){
                        set_mode = setting_number - 5;
                    }
                    else if(8 <= setting_number && setting_number <= 13){
                        set_airplane = setting_number - 7;
                    }
                    else if(14 <= setting_number && setting_number <= 17){
                        set_option = setting_number - 13;
                        airplane_bullet();
                    }
                    else{
                        keyboard_menu = 1;
                        while(true){
                            cout_Key_setting();
                            char back;
                            back = getch();
                            move_keyboard_setting(back);
                            if(back == 27){
                                break;
                            }
                            else if(back == 13){
                                if(keyboard_menu == 1 || keyboard_menu == 2){
                                    moving_button = keyboard_menu;
                                }
                                else if(keyboard_menu == 3){
                                    shoting_button = getch();
                                }
                                else if(keyboard_menu == 4){
                                    power_ups_button = getch();
                                }
                            }
                        }
                        break;
                    }
                }
                setting_move(move_back);
            }
        }
        else{
            bye();
            return 0;
        }
    }


    // ┗ ┛ ┓┏ ░ ▒ ▓ ■
    return 0;
}