#pragma once
#include <string>

/// <summary>
/// このファイルをincludeするだけで、各所で扱いたいglobal変数を利用できるようになる。
/// 各変数の実定義、代入はcppで行っている。
/// 後々は.iniファイル的なアレで外部から変更可能にしたいと思っている。
/// </summary>
extern float g_WindowWidth;
extern float g_WindowHeight;
extern int g_FrameRate;
extern const char* g_GameTitle;

#define SAFE_DELETE(target) if(target!= nullptr){delete target;target = nullptr;};
#define SAFE_RELEASE(target) if(target!= nullptr){target->Release();target = nullptr;};