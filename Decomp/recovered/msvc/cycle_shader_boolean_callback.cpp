class ShaderBooleanCallback {
    unsigned char reserved[20];
    bool enabled;
public:
    void apply(const unsigned char* value);
};

void ShaderBooleanCallback::apply(const unsigned char* value) {
    enabled = *value != 0;
}
