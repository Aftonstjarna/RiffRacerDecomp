#include "impl.hpp"
namespace riff {
// VA 0x58d830, size 74. Setup at 0x58e5d9 installs this function
// into +0x6d58; the reader at 0x58d89d calls that slot using three
// stack arguments, then interprets EAX as a signed byte count/error.
// Context and buffer pointee types are not established by this dispatcher.
// No read, buffering, position accounting, or callback ownership is done here.
// The original does not guard a null default
// callback, nor a null input. Those remain caller preconditions.
int32_t RIFF_CDECL audio_input_read_dispatch(AudioInput* input, void* buffer, int32_t count) {
    if (input->flags & 0x40u) {
        ReadCallback read = input->alternate_read;
        if (!read)
            return -1;
        return read(input->alternate_context, buffer, count);
    }
    return input->default_read(input->default_context, buffer, count);
}
}
