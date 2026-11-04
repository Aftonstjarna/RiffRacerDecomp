// Inspect unlinked x86 COFF code sections; never mask relocations or trim bytes.
// Build with the recovery project's existing headers and libcrypto.
#include "native_blocks.hpp"
int main(int argc, char** argv) { try {
    require(argc == 4, "usage: compare ORIGINAL OBJECT_DIRECTORY BIN_DIRECTORY");
    const auto original = read(argv[1]);
    require(rr::sha(original) == rr::gameHash, "unsupported original hash");
    const rr::matching::Image image(original);
    std::filesystem::create_directories(argv[3]);
    const char* files[] = {"matrix", "binding", "release", "shader"};
    const char* scopes[] = {"ui-matrix-scale", "shader-binding-cleanup", "resource-reference-release", "shader-base-ctor"};
    auto records = rr::Json::array();
    for (unsigned n = 0; n != 4; ++n) {
        const auto object = read(std::string(argv[2]) + "/" + files[n] + ".obj");
        require(object.size() >= 20 && u16(object, 0) == 0x14c, "expected x86 COFF");
        const size_t start = 20 + u16(object, 16), count = u16(object, 2);
        require(start <= object.size() && count <= (object.size() - start) / 40, "invalid section table");
        unsigned codeSections = 0, relocations = 0;
        Bytes code;
        for (size_t s = 0; s < count; ++s) {
            const size_t p = start + s * 40;
            if (!(u32(object, p + 36) & 0x20) || !u32(object, p + 16)) continue;
            code = rr::matching::slice(object, u32(object, p + 20), u32(object, p + 16));
            ++codeSections; relocations += u16(object, p + 32);
        }
        require(codeSections == 1 && relocations == 0, "candidate needs linking; cannot qualify raw code");
        const auto block = rr::matching::nativeBlock(scopes[n]);
        const auto expected = rr::matching::slice(original, image.offset(block.rva, block.size), block.size);
        auto comparison = rr::matching::compare(expected, code);
        comparison["scope"] = scopes[n]; comparison["object_sha256"] = rr::sha(object);
        comparison["code_relocations"] = relocations;
        comparison["classification"] = "source_built_fragment_candidate_pending_certification";
        comparison["certified_matching_credit"] = 0;
        records.push_back(comparison);
        std::ofstream bin(std::string(argv[3]) + "/" + files[n] + ".bin", std::ios::binary);
        require(bool(bin), "open candidate output");
        bin.write(reinterpret_cast<const char*>(code.data()), code.size());
        require(bool(bin), "write candidate output");
    }
    std::cout << rr::Json{{"original_exe_sha256", rr::sha(original)}, {"whole_executable_compared", false}, {"fragments", records}}.dump(2) << '\n';
    return 0;
} catch (const std::exception& e) { std::cerr << e.what() << '\n'; return 1; } }
