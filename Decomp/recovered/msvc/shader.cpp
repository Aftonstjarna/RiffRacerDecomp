// Original wsShader base initializer VA 0x5421b0; preserve untouched gaps.
struct Shader {
    unsigned vtable, unknown04, unknown08;
    unsigned f0c, f10, f14, f18, f1c, f20, f24, f28, f2c, f30, f34, f38;
    unsigned unknown3c, unknown40, f44, unknown48, unknown4c, f50, f54;
    __declspec(noinline) Shader();
};
Shader::Shader() : vtable(0x9fe7e0), f0c(0), f10(0), f14(0), f18(0),
    f1c(0), f20(0), f24(0), f28(0), f2c(0), f30(0), f34(0), f38(0),
    f44(0), f50(0), f54(0) {}
