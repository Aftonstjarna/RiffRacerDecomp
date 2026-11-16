struct Local { unsigned name; unsigned flags; unsigned end; };
struct Symbols { unsigned char reserved[24]; Local* locals; };
struct Function { Symbols* symbols; unsigned char reserved0[20]; unsigned position; unsigned char reserved1[22]; unsigned char active; unsigned char reserved2[121]; unsigned short indices[256]; };
struct Compiler { unsigned char reserved[28]; Function* function; };
void __fastcall remove_active_locals(Compiler* compiler, int target)
{
    Function* function = compiler->function;
    while (function->active > target) {
        --function->active;
        function->symbols->locals[function->indices[function->active]].end = function->position;
    }
}
