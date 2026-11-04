# Original PE relocation evidence for menu entry guards

## Windows image relocation guards (1.2.3-4)

The original Game.exe SHA-256 is
`2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2`
(8,635,392 bytes), preferred PE image base `0x00400000`. Windows logs showed
the same executable loaded at `0x00C30000`, where fixed absolute operands in
otherwise identical function prologues invalidated the old startup checks.

The checked prologue RVAs and 32-bit absolute operand offsets are:
`50AF0+6`, `43800+6`, `8E8D0+6`, `4B530+9`, `8F580+6`, `8E9D0+6`,
`22030+6`, `48830+4`, `482B0+6`. Each operand has an original PE HIGHLOW
relocation entry. The guard now requires that entry, compares its exact expected
relocated value, and compares every remaining instruction byte unchanged.
The `4B530` guard includes all 13 bytes through the four-byte operand. No opcode
or operand masks are used; the original executable hash check remains required.

`test_engine.c` applies the original relocation table to a mapped fixture at the
observed Windows base. The original and relocated images pass; opcode/operand
mutations are rejected. This is runtime-hook validation evidence, not additional
byte-for-byte recovered source or proof of live Windows gameplay compatibility.

## Discardable relocation records

For the same supported original hash, `.reloc` section characteristics are
`0x42000040`: initialized, readable data with `IMAGE_SCN_MEM_DISCARDABLE` set.
A live Windows image is therefore not required to retain readable relocation
records after the loader applies them. ReRiff must read/copy these records from
its hash-verified original file when validating adjusted absolute operands.

This does not weaken instruction comparisons or alter original executable bytes.
A ReRiff fixture makes the live relocation region `PAGE_NOACCESS` after applying
the original relocations; exact live-prologue validation still succeeds using the
verified original records and continues to reject opcode/operand mutations.
This is validation evidence, not additional byte-for-byte source recovery credit.

Original Parse transport evidence: preserved vanilla Parse.NetFx45.dll SHA-256
`4e2f65147faec13ae5333337e3c7cd9e25028f3119fe817e059b1d2eab678522`,
method token `0x06000023`, `Parse.Internal.HttpClient.ExecuteAsync` returns
`Task<Tuple<HttpStatusCode,string>>`. It obtains `HttpRequest.Uri` and `.Method`
before request construction and returns its original task at IL `0x0291`.
ReRiff's client-note adapter intentionally extends that result; it is not
original-game reconstruction. Original Game.exe News menu ordering remains at
`gaNewsMenu.NewsItem.sortItems`, token `0x0600149E`; original News rendering and
input are preserved by the adapter.
