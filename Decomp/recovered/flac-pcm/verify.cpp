#include "matching.hpp"
int main(int argc,char**argv){try{
    require(argc==3,"usage: verify ORIGINAL LOOP.bin");
    auto original=read(argv[1]);require(rr::sha(original)==rr::gameHash,"original hash mismatch");
    rr::matching::Image image(original);
    auto expected=rr::matching::slice(original,image.offset(0xf91f0,34),34);
    auto constant=rr::matching::slice(original,image.offset(0x606428,4),4);
    require(u32(constant,0)==0x38000000,"PCM scale differs");
    auto report=rr::matching::compare(expected,read(argv[2]));
    report["original_exe_sha256"]=rr::sha(original);
    report["original_rva"]=0xf91f0;
    report["classification"]="transcribed_partial_loop_test_oracle";
    report["certified_matching_credit"]=0;
    std::cout<<report.dump(2)<<'\n';return report["byte_equal"].get<bool>()?0:1;
}catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 2;}}
