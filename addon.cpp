#include <napi.h>


Napi::Value Add( const Napi::CallbackInfo& info ) {

    Napi::Env env = info.Env();

    if ( info.Length() < 2 ) {
        Napi::TypeError::New( env, "Wrong number of arguments" ).ThrowAsJavaScriptException();
        return env.Null();
    }

    if ( !info[ 0 ].IsNumber() || !info[ 1 ].IsNumber() ) {
        Napi::TypeError::New( env, "Wrong arguments" ).ThrowAsJavaScriptException();
        return env.Null();
    }

    return Napi::Number::New(env, info[ 0 ].As<Napi::Number>().DoubleValue() + info[ 1 ].As<Napi::Number>().DoubleValue());
}

Napi::Object Sample( const Napi::CallbackInfo& info ) {
    Napi::Env env = info.Env();

    Napi::Object ret = Napi::Object::New(env);

    for(int i=0;i<10;i++){
        ret.Set( Napi::String::New(env, std::to_string(i)) , Napi::String::New(env, std::to_string(i + 100)) );
    }

    return ret;
}

Napi::Object Init( Napi::Env env, Napi::Object exports ) {
    exports.Set( Napi::String::New( env, "add" ), Napi::Function::New( env, Add ) );
    exports.Set( Napi::String::New( env, "sample" ), Napi::Function::New( env, Sample ) );
    return exports;
}

NODE_API_MODULE( addon, Init )
