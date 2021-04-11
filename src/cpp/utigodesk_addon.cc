#include <codecvt>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "napi.h"
#include "nlohmann/json.hpp"
#include "win32utils/win32utils.h"

using namespace std;
namespace fs = std::filesystem;

static void ArrayConsumer(const char16_t* array, size_t length, std::u16string& str) {
    for (size_t index = 0; index < length; index++) {
        str += array[ index ];
        fprintf(stderr, "array[%zu] = %c\n", index, array[ index ]);
    }
}

static Napi::Value mainEntry(const Napi::CallbackInfo& info) {
    if (info.Length() != 1) {
        Napi::Error::New(info.Env(), "Expected exactly one argument").ThrowAsJavaScriptException();
        return info.Env().Undefined();
    }
    if (!info[ 0 ].IsArrayBuffer()) {
        Napi::Error::New(info.Env(), "Expected an ArrayBuffer").ThrowAsJavaScriptException();
        return info.Env().Undefined();
    }

    Napi::ArrayBuffer buf = info[ 0 ].As<Napi::ArrayBuffer>();

    std::u16string jsonStr;
    std::u16string optionStr;
    ArrayConsumer(reinterpret_cast<char16_t*>(buf.Data()), buf.ByteLength() / sizeof(char16_t), jsonStr);

    optionStr = jsonStr;

    std::wstring absCurrentPath            = fs::current_path();
    std::wstring dosomethingExeInstallPath = absCurrentPath + TEXT("\\resources\\app.asar.unpacked\\Release\\dosomething.exe");
    std::wstring dosomethingExeDebugPath   = absCurrentPath + TEXT("\\Release\\dosomething.exe");
    std::wstring dosomethingExePath;
    if (fs::exists(dosomethingExeInstallPath)) {
        dosomethingExePath = dosomethingExeInstallPath;
    } else if (fs::exists(dosomethingExeDebugPath)) {
        dosomethingExePath = dosomethingExeDebugPath;
    } else {
        return info.Env().Undefined();
    }

    std::wstring configFilePath = absCurrentPath + TEXT("\\dosomething.conf");

    if (optionStr == u"CallFromJavaScript1a") {  //小心任意执行漏洞，所以才判断命令
        std::wstring args = TEXT("/start ") + configFilePath;
        win32utils::runAsUser(dosomethingExePath, args, SW_HIDE);  //显示C++界面或者以runAsAdmin运行，请将nShow = SW_SHOW
    } else if (optionStr == u"CallFromJavaScript2bc") {
        std::wstring args = TEXT("/stop ") + configFilePath;
        win32utils::runAsUser(dosomethingExePath, args, SW_HIDE);
    }

    return info.Env().Undefined();
}

static Napi::Value statusEntry(const Napi::CallbackInfo& info) {

    return info.Env().Undefined();
}

static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "mainEntry"), Napi::Function::New(env, mainEntry));
    exports.Set(Napi::String::New(env, "statusEntry"), Napi::Function::New(env, statusEntry));
    return exports;
}

NODE_API_MODULE(addon, Init)
