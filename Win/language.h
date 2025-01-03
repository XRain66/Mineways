#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <windows.h>

// 语言切换函数声明
bool SwitchLanguage(HWND hWnd, int languageID);

// 语言ID定义
#define LANGUAGE_ENGLISH    0
#define LANGUAGE_CHINESE    1

// 当前语言
extern int g_currentLanguage;

#endif // LANGUAGE_H
