// Copyright 2021 SMS
// License(Apache-2.0)

#include "Assert.hpp"
#include "Logging/Logging.h"
#include "Platform.h"
#include <iostream>

#if _MSC_VER
#    define breakpoint() __debugbreak()
#else
#    define breakpoint() __builtin_trap()
#endif

namespace clem
{

void Assert::isTrue(bool expr, std::string_view msg, const std::source_location& loc)
{
    if(expr)
        return;

    auto str = std::format("Assertion failed.\nfile     : {}\nfunction : {}\nline     : {}", loc.file_name(), loc.function_name(), loc.line());
    if(!msg.empty())
        str += std::format("\nmessage  : {}", msg);

    CLEM_LOG_ERROR("assert", msg);
    CLEM_LOG_FLUSH();

    std::cout << str << std::endl;

#ifdef OS_WIN
    str += "\n\nPress Retry to debug the application";
    switch(MessageBoxA(nullptr, str.c_str(), "Clementine", MB_ICONERROR | MB_ABORTRETRYIGNORE))
    {
    case IDABORT:
        exit(-1);
        break;

    case IDRETRY:
        breakpoint();
        break;

    case IGNORE:
        break;
    }
#else
    breakpoint();
#endif
}

void Assert::isFalse(bool expr, std::string_view msg, const std::source_location& loc)
{
    isTrue(!expr, msg, loc);
}

} // namespace clem