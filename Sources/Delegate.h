#pragma once
 
#include <vector>

#include "Method.h"

namespace Inking
{
    template<typename _Return, typename ..._Args>
    class Delegate
    {
    public:
        using _Method = Method<_Return, _Args...>;
        using _Function = std::function<_Return(_Args...)>;

        std::vector < _Method > _methods;

        template<typename T_Object, typename T_MemberFunc>
        void PushBack(T_Object* object, const T_MemberFunc& func)
        {
            *this += {object, func};
        }
    public:

        Delegate()
        {
        }

        bool Empty()const
        {
            return !_methods.size();
        }

        operator bool()const
        {
            return _methods.size();
        }

        _Return operator()(const _Args&...args)const
        {
            return Invoke(args...);
        }

        _Return Invoke(const _Args&...args)const
        {
            auto methodNum = _methods.size();

            for (int i = 0; i < methodNum - 1; ++i)
            {
                _methods[i](args...);
            }

            return _methods[methodNum - 1](args...);
        }

        Delegate& operator += (_Function func)
        {
            _methods.push_back(func);
            return *this;
        }

        Delegate& operator += (const _Method& method)
        {
            _methods.push_back(method);
            return *this;
        }

        Delegate& operator -= (const _Method& method)
        {
            auto it = std::find(_methods.begin(), _methods.end(), method);

            if (it != _methods.end())
                _methods.erase(it);

            return *this;
        }

        Delegate& operator -= (_Function func)
        {
            return *this -= (_Method)func;
        }
    };
}

