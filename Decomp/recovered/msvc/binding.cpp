// Source pilot from render_helpers.cpp, VA 0x52f5b0. No virtual destructor
// inserted: callback remains vtable slot 4, as observed in the original.
struct Binding {
    virtual void slot0(); virtual void slot1(); virtual void slot2();
    virtual void slot3(); virtual void operation();
};
struct Bindings {
    unsigned char prefix[0xe1c]; Binding* tables[6][280];
    __declspec(noinline) void cleanup();
};
void Bindings::cleanup() {
    for(unsigned col=0;col<280;++col)
        for(unsigned table=0;table<6;++table)
            if(tables[table][col]) tables[table][col]->operation();
}
