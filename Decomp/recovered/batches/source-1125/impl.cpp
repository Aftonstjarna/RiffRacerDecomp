#include "impl.hpp"

// Game.exe 0x49a940: thiscall; 24-byte records, with end captured on entry.
void WorkerRecordRange::clear() {
    WorkerRecord* cursor = begin;
    WorkerRecord* const limit = end;
    while (cursor != limit) {
        WorkerObject* object = cursor->object;
        if (object) {
            char* address = reinterpret_cast<char*>(object);
            WorkerReleaseOwner* owner = reinterpret_cast<WorkerReleaseOwner*>(
                address + object->table->owner_offset);
            --owner->references; // 32-bit wraparound, as in the original.
            if (owner->references == 0)
                owner->table->release(owner, 1);
        }
        ++cursor;
    }
    end = begin; // A release callback may have changed begin.
}
