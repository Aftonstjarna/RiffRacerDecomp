// Source pilot from Decomp/recovered/render_helpers.cpp; original VA 0x458810.
// Use a member to reproduce original thiscall ABI; not credited as matching.
struct Matrix { float v[12]; __declspec(noinline) void scale(float,float,float); };
void Matrix::scale(float x,float y,float z) {
    for(unsigned i=0;i<3;++i) v[i]*=x;
    for(unsigned i=3;i<6;++i) v[i]*=y;
    for(unsigned i=6;i<9;++i) v[i]*=z;
}
