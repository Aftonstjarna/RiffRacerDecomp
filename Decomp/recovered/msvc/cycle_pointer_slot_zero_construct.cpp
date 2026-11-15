struct PointerSlot {
    void* value;
    PointerSlot* __thiscall construct();
};

PointerSlot* PointerSlot::construct()
{
    value = 0;
    return this;
}
