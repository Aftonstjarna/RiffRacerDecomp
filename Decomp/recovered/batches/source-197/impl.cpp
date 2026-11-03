#include "impl.hpp"
// Game.exe 0x4a5c40..0x4a5e76. ECX owner, no stack parameters,
// no meaningful return value. Called by shutdown and creation failure paths
// (e.g. 0x4a0a93, 0x4a4c20). Does not free the owner or install a vtable.
// Slot +8 is COM Release: stdcall, explicit resource pointer, result ignored.
static void release(Resource* resource) {
    if (resource) resource->vtable->release(resource);
}
// The next pointer is fetched after Release, BEFORE the previous field clears.
// Keeping this order also handles a Release callback modifying owner slots.
static Resource* advance(Resource*& previous, Resource*& next) {
    Resource* result = next;
    previous = 0;
    return result;
}
void RR_THISCALL Device::releaseQueries() {
    for (unsigned i=0; i<2; ++i) {
        Resource** group=queries470[i];
        Resource* current=group[2];
        release(current);
        current=advance(group[2],group[1]);
        release(current);
        current=advance(group[1],group[0]);
        release(current);
        group[0]=0;
    }
}
void RR_THISCALL Device::destroy() {
    releaseQueries();
    Resource* current=resource290;
    release(current);
    current=advance(resource290,resource28c);
    release(current);
    current=advance(resource28c,resource204);
    release(current);
    resource204=0;
    for (unsigned i=0; i<33; ++i) {
        release(resources298[i]);
        resources298[i]=0;
    }
    current=resource21c;
    release(current);
    current=advance(resource21c,resource218);
    release(current);
    current=advance(resource218,resource214);
    release(current);
    resource214=0;
    state220[0]=0; state220[1]=0; state220[2]=0; state220[3]=0;
    // Two pairs interleaved: +428,+420 then +42c,+424.
    for (unsigned i=0; i<2; ++i) {
        current=resources420[i+2];
        release(current);
        current=advance(resources420[i+2],resources420[i]);
        release(current);
        resources420[i]=0;
    }
    current=resource430;
    release(current);
    current=advance(resource430,resource438);
    release(current);
    current=advance(resource438,resource434);
    release(current);
    current=advance(resource434,resource440);
    release(current);
    current=advance(resource440,resource43c);
    release(current);
    current=advance(resource43c,resource448);
    release(current);
    current=advance(resource448,resource444);
    release(current);
    current=advance(resource444,resource078);
    release(current);
    current=advance(resource078,resource07c);
    release(current);
    current=advance(resource07c,resource070);
    release(current);
    current=advance(resource070,resource074);
    release(current);
    resource074=0;
}
