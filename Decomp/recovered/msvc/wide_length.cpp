// Original UTF-16 length/terminator update at VA 0x44fab0, 37 bytes.
// Valid caller-owned storage required; no capacity check or allocation.
struct WideString {
    union { unsigned short inlineChars[8]; unsigned short* heap; } storage;
    unsigned length;
    unsigned capacity;
    __declspec(noinline) void setLength(unsigned value);
};
void WideString::setLength(unsigned value) {
    length = value;
    if (capacity >= 8)
        storage.heap[value] = 0;
    else
        storage.inlineChars[value] = 0;
}
