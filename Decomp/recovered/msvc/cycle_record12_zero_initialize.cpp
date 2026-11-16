// Original ABI: ECX holds the record pointer, EDX the count.
// Each record has three 32-bit fields and occupies 12 bytes.
struct Record12 { unsigned first, second, third; };
void __fastcall initialize_records(Record12* records, unsigned count)
{
    while (count) {
        if (records) {
            records->first = 0;
            records->second = 0;
            records->third = 0;
        }
        ++records;
        --count;
    }
}
