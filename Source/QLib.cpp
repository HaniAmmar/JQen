#include "Template.hpp"

#include <emscripten/bind.h>
#include <emscripten/val.h>

using namespace emscripten;

std::string JQen_Render(const std::string &content, const std::string &json)
{
    const Qentem::JSON::Value value = Qentem::JSON::Parse(json.c_str(), json.length());
    Qentem::String temp = Qentem::Template<>::Render(content.c_str(), content.length(), &value);
    return std::string(temp.Char(), temp.Length());
}

EMSCRIPTEN_BINDINGS(jqen_module)
{
    function("JQen_Render", &JQen_Render);
}
