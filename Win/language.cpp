#include "language.h"
#include "resource.h"
#include <commctrl.h>

// 全局变量定义
int g_currentLanguage = LANGUAGE_ENGLISH;

// 语言切换函数实现
bool SwitchLanguage(HWND hWnd, int languageID)
{
    HINSTANCE hInstance = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);
    bool success = false;

    // 保存当前语言设置
    g_currentLanguage = languageID;

    // 根据语言ID加载相应的资源
    HMENU hNewMenu = NULL;
    switch (languageID)
    {
        case LANGUAGE_ENGLISH:
            // 加载英文资源
            hNewMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MAINFRAME));
            break;

        case LANGUAGE_CHINESE:
            // 加载中文资源
            hNewMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MAINFRAME));
            break;
    }

    if (hNewMenu)
    {
        // 替换当前菜单
        HMENU hOldMenu = GetMenu(hWnd);
        if (SetMenu(hWnd, hNewMenu))
        {
            // 销毁旧菜单
            if (hOldMenu)
                DestroyMenu(hOldMenu);
            success = true;
        }
        else
        {
            // 如果设置菜单失败，销毁新菜单
            DestroyMenu(hNewMenu);
        }
    }

    if (success)
    {
        // 刷新窗口
        DrawMenuBar(hWnd);
        InvalidateRect(hWnd, NULL, TRUE);
        UpdateWindow(hWnd);

        // 更新菜单项的选中状态
        HMENU hMenu = GetMenu(hWnd);
        if (hMenu)
        {
            HMENU hLanguageMenu = NULL;
            // 遍历菜单找到语言子菜单
            int count = GetMenuItemCount(hMenu);
            for (int i = 0; i < count; i++)
            {
                HMENU hSubMenu = GetSubMenu(hMenu, i);
                if (hSubMenu)
                {
                    MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
                    mii.fMask = MIIM_ID;
                    if (GetMenuItemInfo(hSubMenu, IDM_LANGUAGE_ENGLISH, FALSE, &mii))
                    {
                        hLanguageMenu = hSubMenu;
                        break;
                    }
                }
            }

            if (hLanguageMenu)
            {
                CheckMenuItem(hLanguageMenu, IDM_LANGUAGE_ENGLISH, 
                    (languageID == LANGUAGE_ENGLISH) ? MF_CHECKED : MF_UNCHECKED);
                CheckMenuItem(hLanguageMenu, IDM_LANGUAGE_CHINESE, 
                    (languageID == LANGUAGE_CHINESE) ? MF_CHECKED : MF_UNCHECKED);
            }
        }
    }

    return success;
}
