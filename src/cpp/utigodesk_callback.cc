#include <codecvt>
#include <iostream>
#include <string>

#include "napi.h"
#include "nlohmann/json.hpp"

using namespace std;

static void ArrayProducer(char16_t* array, size_t length, std::u16string& str) {
    for (size_t index = 0; index < length && index < str.size(); index++) {
        array[ index ] = str[ index ];
        fprintf(stderr, "array[%zu] = %c\n", index, array[ index ]);
    }
}

void RunCallback(const Napi::CallbackInfo& info) {
    Napi::Env      env = info.Env();
    Napi::Function cb  = info[ 0 ].As<Napi::Function>();
    if (false) {
        // main_s(std::string(""));
    }

    std::u16string str;
    // wstring_convert<codecvt_utf8<char16_t>, char16_t> cv;

    if (info.Length() > 1) {
        str = info[ 1 ].As<Napi::String>();
        // cout << "info[ 1 ]:" << cv.to_bytes(str) << endl;
    } else {
        str = u"(C++_callback) empty";
        // cout << "str:" << cv.to_bytes(str) << endl;
    }
    auto buf = Napi::ArrayBuffer::New(env, str.size());
    ArrayProducer(reinterpret_cast<char16_t*>(buf.Data()), buf.ByteLength() / sizeof(char16_t), str);

    cb.Call(env.Global(), {buf});
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    return Napi::Function::New(env, RunCallback);
    return exports;
}

NODE_API_MODULE(callback, Init)