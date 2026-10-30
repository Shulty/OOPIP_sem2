#include "UI.h"
#include <conio.h>
#include <iostream>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

namespace {
    const int KEY_ENTER = 13;
    const int KEY_ESC = 27;
    const int KEY_BACKSPACE = 8;
}


size_t CenterX(const std::string& s)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    return (width - s.size()) / 2;
}

size_t CenterY()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    return height / 2 + 1;
}

void PrintTorrentArt()
{
    const WORD CLR_GREEN = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    const WORD CLR_RESET = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

    const std::string widest =
        " |_   _|__  _ __ _ __ ___ _ __ | |_      _ __ ___   __ ___  __";
    int x = static_cast<int>(CenterX(widest));

    const char* lines[6] = {
        "  _____                         _ ",
        " |_   _|__  _ __ _ __ ___ _ __ | |_      _ __ ___   __ ___  __",
        "   | |/ _ \\| '__| '__/ _ \\ '_ \\| __|____| '_ ` _ \\ / _` \\ \\/ /",
        "   | | (_) | |  | | |  __/ | | | ||_____| | | | | | (_| |>  < ",
        "   |_|\\___/|_|  |_|  \\___|_| |_|\\__|    |_| |_| |_|\\__,_/_/\\_\\",
        "      "
    };

    SetConsoleTextAttribute(hConsole, CLR_GREEN);
    for (int i = 0; i < 6; ++i) {
        SetConsoleCursorPosition(hConsole, { (SHORT)x, (SHORT)i });
        std::cout << lines[i];
    }
    std::cout.flush();
    SetConsoleTextAttribute(hConsole, CLR_RESET);
}

void PrintCenter(std::string s, int y)
{
    int x = static_cast<int>(CenterX(s));
    SetConsoleCursorPosition(hConsole, { (SHORT)x, (SHORT)y });
    std::cout << s << "\n";
    std::cout.flush();
}


int ConsoleWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

int ConsoleHeight()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void GotoXY(int x, int y)
{
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    COORD pos{ static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(hConsole, pos);
}

void PrintCenterAt(const std::string& text, int y)
{
    const int w = ConsoleWidth();
    int x = (w - static_cast<int>(text.size())) / 2;
    if (x < 0) x = 0;
    GotoXY(x, y);
    std::cout << text;
    std::cout.flush();        
}

void ClearLineAt(int y)
{
    const int w = ConsoleWidth();
    GotoXY(0, y);
    std::cout << std::string(w, ' ');
    std::cout.flush();
}

std::string ReadCenteredLine(const std::string& prompt,
    int y,
    bool maskInput,
    const std::string& initial,
    bool* isCancelled)
{
    if (isCancelled) *isCancelled = false;

    std::string value = initial;

    while (true) {
        ClearLineAt(y);

        const std::string shown = maskInput
            ? std::string(value.size(), '*')
            : value;

        PrintCenterAt(prompt + shown, y);

        const int w = ConsoleWidth();
        const int totalLen = static_cast<int>(prompt.size() + shown.size());
        int x = (w - totalLen) / 2 + totalLen;
        if (x < 0) x = 0;
        if (x >= w) x = w - 1;
        GotoXY(x, y);

        int ch = _getch();

        if (ch == KEY_ENTER)
            return value;

        if (ch == KEY_ESC) {
            if (isCancelled) *isCancelled = true;
            return std::string();
        }

        if (ch == KEY_BACKSPACE) {
            if (!value.empty()) value.pop_back();
            continue;
        }

        if (ch == 224 || ch == 0) {
            _getch();
            continue;
        }

        if (ch >= 32 && ch < 127)
            value.push_back(static_cast<char>(ch));
    }
}

void ShowMessage(const std::string& text, int y, WORD color)
{
    SetConsoleTextAttribute(hConsole, color);
    PrintCenterAt(text, y);
    SetConsoleTextAttribute(hConsole, 7);
}

void WaitAnyKey(const std::string& hint, int y)
{
    if (y > 0)
        PrintCenterAt(hint, y);
    else
        PrintCenter(hint, ConsoleHeight() - 2);
    _getch();
}