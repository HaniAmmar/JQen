#include "JSON.hpp"
#include "Template.hpp"

#include <emscripten/bind.h>
#include <emscripten/val.h>

using namespace emscripten;

static std::string JQen_Render(const std::string &content, const std::string &json, const std::string &name) {
    using QTagBit = Qentem::Array<Qentem::Tags::TagBit>;
    using QHArray = Qentem::HArray<Qentem::String<char>, QTagBit>;

    static QHArray                    cache;
    static Qentem::StringStream<char> stream;
    static QTagBit                    tags_cache;
    QTagBit                          *tags;

    stream.Clear();

    if (name.length() != 0) {
        tags = &(cache.Get(name.c_str(), name.length()));
    } else {
        tags_cache.Clear();
        tags = &tags_cache;
    }

    const Qentem::Value<char> value = Qentem::JSON::Parse(json.c_str(), json.length());
    Qentem::Template::Render(content.c_str(), content.length(), value, stream, *tags);

    return std::string{stream.First(), stream.Length()};
}

static std::string JQen_Render(const std::string &content, const std::string &json) {
    return JQen_Render(content, json, "");
}

#ifdef JQEN_ENABLE_TESTS
#include "Test.hpp"

std::wstring JQen_RunTests() {
    std::wstringstream wss{};
    Qentem::TestOutPut::SetStreamCache(&wss);

    Qentem::TestOutPut::IsColored() = false;

    Qentem::QTest::PrintInfo();
    Qentem::Test::RunTests();
    // Qentem::MemoryRecord::PrintMemoryStatus();

    return wss.str();
}
#endif

EMSCRIPTEN_BINDINGS(overload) {
    function("JQen_Render", select_overload<std::string(const std::string &, const std::string &)>(JQen_Render));
    function("JQen_Render",
             select_overload<std::string(const std::string &, const std::string &, const std::string &)>(JQen_Render));

#ifdef JQEN_ENABLE_TESTS
    function("JQen_RunTests", &JQen_RunTests);
#endif
}
