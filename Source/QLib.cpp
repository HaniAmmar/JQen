#include <cstddef>

#ifndef QENTEM_ALLOCATE
#define QENTEM_ALLOCATE(size) __builtin_malloc(size)
#define QENTEM_DEALLOCATE(ptr) __builtin_free(ptr)
#define QENTEM_RAW_ALLOCATE(size) __builtin_malloc(size)
#define QENTEM_RAW_DEALLOCATE(ptr) __builtin_free(ptr)

template <typename Type_T>
void *operator new(std::size_t, Type_T *ptr) noexcept {
    return ptr;
}

template <typename Type_T>
void operator delete(void *, Type_T *) noexcept {
    // No-op: required to match placement new
}
#endif // QENTEM_ALLOCATE

#include "JSON.hpp"
#include "Template.hpp"

using namespace Qentem;

struct QentemRenderStorage {
    using QTagBit = Array<Tags::TagBit>;
    using QHArray = HArray<String<char>, QTagBit>;

    inline static QHArray            Map{2};
    inline static QTagBit            TagsCache{2};
    inline static StringStream<char> Stream{64};
};

/**
 * @brief Renders a Qentem template from UTF-8 content and JSON data using optional caching.
 *
 * @param content        Pointer to template content.
 * @param content_length Length of template content in bytes.
 * @param json           Pointer to JSON string.
 * @param json_length    Length of JSON string in bytes.
 * @param name           Optional cache key name.
 * @param name_length    Length of cache key name.
 * @return const char*   Pointer to the rendered null-terminated result.
 */
extern "C" const char *JQenRender(const char *content, unsigned int content_length, const char *json,
                                  unsigned int json_length, const char *name, unsigned int name_length) noexcept {
    Array<Tags::TagBit> *tags;
    QentemRenderStorage::Stream.Clear();

    if (name_length != 0) {
        tags = &(QentemRenderStorage::Map.Get(name, name_length));
    } else {
        QentemRenderStorage::TagsCache.Clear();
        tags = &(QentemRenderStorage::TagsCache);
    }

    const Value<char> value = JSON::Parse(json, json_length);
    Template::Render(content, content_length, value, QentemRenderStorage::Stream, *tags);
    QentemRenderStorage::Stream.InsertNull();

    return QentemRenderStorage::Stream.First();
}

#ifdef JQEN_ENABLE_TESTS
#include "Test.hpp"

extern "C" const char *JQen_RunTests() {
    Qentem::TestOutput::GetStreamCache().Clear();
    Qentem::TestOutput::DisableOutput();

    Qentem::TestOutput::IsColored() = false;

    Qentem::QTest::PrintInfo();
    Qentem::Test::RunTests();
    // Qentem::MemoryRecord::PrintMemoryStatus();
    auto &ss = Qentem::TestOutput::GetStreamCache();

    ss.InsertNull();

    return ss.First();
}
#endif
