#pragma once
#include <string>
#include <windows.h>

extern HANDLE hConsole;

size_t CenterX(const std::string& s);
size_t CenterY();

void PrintTorrentArt();
void PrintCenter(std::string s, int y);

int ConsoleWidth();
int ConsoleHeight();

void GotoXY(int x, int y);
void PrintCenterAt(const std::string& text, int y);   
void ClearLineAt(int y);

std::string ReadCenteredLine(const std::string& prompt,
    int y,
    bool maskInput = false,
    const std::string& initial = "",
    bool* isCancelled = nullptr);

void ShowMessage(const std::string& text, int y, WORD color);
void WaitAnyKey(const std::string& hint = "Нажмите любую клавишу...", int y = 0);

constexpr WORD ACCENT_COLOR = 2;    // яркий зелёный
constexpr WORD OK_COLOR = 10;   // зелёный
constexpr WORD ERR_COLOR = 12;   // красный