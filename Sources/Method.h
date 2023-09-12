#pragma once

#include <functional>
#include <type_traits>
#include <string>

namespace Inking
{
    template<typename _Return, typename ..._Args>
    class Method
    {
    public:
        using _Function = std::function<_Return(_Args...)>;
    protected:
        _Function _func = {};

        void* _object = nullptr;
        void* _pointer = nullptr;

        template<typename T_Func, typename T_Object, typename ...Phs>
        _Function _Bind(const T_Func& func, T_Object* object, const Phs&...phs)
        {
            using namespace std::placeholders;
            return std::bind(func, object, phs...);
        }

#define BIND_PLACEHOLDERS(n, ...) \
        template<int argNum, typename T_Func, typename T_Object>\
        typename std::enable_if<argNum == n, _Function>::type _Bind(const T_Func& func, T_Object* object)\
        {\
            using namespace std::placeholders; \
            return _Bind(func, object, __VA_ARGS__);\
        }

        BIND_PLACEHOLDERS(0);
        BIND_PLACEHOLDERS(1, _1);
        BIND_PLACEHOLDERS(2, _1, _2);
        BIND_PLACEHOLDERS(3, _1, _2, _3);
        BIND_PLACEHOLDERS(4, _1, _2, _3, _4);
        BIND_PLACEHOLDERS(5, _1, _2, _3, _4, _5);
        BIND_PLACEHOLDERS(6, _1, _2, _3, _4, _5, _6);
        BIND_PLACEHOLDERS(7, _1, _2, _3, _4, _5, _6, _7);
        BIND_PLACEHOLDERS(8, _1, _2, _3, _4, _5, _6, _7, _8);
        BIND_PLACEHOLDERS(9, _1, _2, _3, _4, _5, _6, _7, _8, _9);
        BIND_PLACEHOLDERS(10, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10);

    public:
        Method()
        {

        }

        Method(const _Function& func)
            :_func(func)
        {
            _pointer = *(void**)&func;
        }

        template<typename Func, typename T>
        Method(T* object, const Func& func)
        {
            _object = object;

            _func = _Bind<sizeof...(_Args)>(func, object);

            _pointer = *(void**)&func;
        }

        bool operator == (const Method& other)const
        {
            return _object == other._object && _pointer == other._pointer;
        }

        _Return operator()(const _Args&...args)const
        {
            return _func(args...);
        }

        void* GetObject()const
        {
            return _object;
        }

        void* GetPointer()const
        {
            return _pointer;
        }
    };


}
