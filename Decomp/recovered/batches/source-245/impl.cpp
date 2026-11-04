#include "impl.hpp"
namespace riff {
Imports imports;
// Game.exe 0048CE10..0048CE65; cdecl, no arguments, no meaningful result.
// Application entry 005CFF90 calls this before rechecking its stop flag.
// Slots: PeekMessageA 0092D55C, DispatchMessageA 0092D57C,
// TranslateMessage 0092D59C. The adapter makes those OS dependencies explicit.
void message_pump() {
    Message message; // Original stack MSG is not initialized before PeekMessageA.
    Peek peek = imports.peek;
    if (peek(&message, 0, 0, 0, 1)) {
        Dispatch dispatch = imports.dispatch;
        Translate translate = imports.translate;
        do {
            translate(&message);
            dispatch(&message);
        } while (peek(&message, 0, 0, 0, 1));
    }
    // WM_QUIT has no special handling. Callback results are ignored.
}
}
