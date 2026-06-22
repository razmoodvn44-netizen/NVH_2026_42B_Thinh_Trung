#pragma once

// Ham doi mau chu/nen tren console
// mau_nen, mau_chu: 0 - 15 (theo bang mau console cua Windows)
#ifdef _WIN32
    #include <windows.h>
    void SetColor(int mau_nen, int mau_chu)
    {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, mau_nen * 16 + mau_chu);
    }
#else
    // Tren Linux/macOS khong co console API cua Windows nen bo qua doi mau
    // (de code van bien dich va chay duoc binh thuong, khong gay loi)
    void SetColor(int mau_nen, int mau_chu) {}
#endif
