#include "JSON.hpp"
#include "Template.hpp"

#include <emscripten/bind.h>
#include <emscripten/val.h>

using namespace emscripten;

std::string JQen_Render(const std::string &content, const std::string &json)
{
    const Qentem::Value<char> value = Qentem::JSON::Parse(json.c_str(), json.length());
    const Qentem::StringStream<char> temp = Qentem::Template::Render(content.c_str(), content.length(), &value);
    return std::string(temp.First(), temp.Length());
}

#ifdef JQEN_ENABLE_TESTS
#include <sstream>
static std::wstringstream jqen_ss;
#define QENTEM_OUTPUT_STREAM jqen_ss
#include "Test.hpp"

std::wstring JQen_RunTests()
{
    Qentem::TestOutPut::SetColoredOutput(false);
    jqen_ss = std::wstringstream{};
    Qentem::TestHelper::PrintInfo();
    Qentem::Test::RunTests();
    // Qentem::MemoryRecord::PrintMemoryStatus();

    return jqen_ss.str();
}
#endif

EMSCRIPTEN_BINDINGS(jqen_module)
{
    function("JQen_Render", &JQen_Render);
#ifdef JQEN_ENABLE_TESTS
    function("JQen_RunTests", &JQen_RunTests);
#endif
}
