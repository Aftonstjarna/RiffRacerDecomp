// Original resource_reference_release.S, VA 0x41cd10. Zero test after a
// wrapping decrement, vslot 0 gets flag 1; reference slot remains unchanged.
struct Resource { virtual void dispose(unsigned); unsigned count; };
struct Slot { Resource* resource; __declspec(noinline) void release(); };
void Slot::release() {
    Resource* p=resource;
    if(p && --p->count==0) p->dispose(1);
}
