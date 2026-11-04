extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*,unsigned);
extern "C" unsigned exercise_frame();
extern "C" int test_main(){
 unsigned first[4]={0xdeadbeef,1,2,3}, second[4]={0xabcdef01,4,5,6};
 if(test_install_fs(nullptr)!=-22)return 1;
 for(unsigned i=0;i<64;++i){
  auto p=(i&1)?first:second;
  if(test_install_fs(p)!=0||test_get_fs_head()!=p[0])return 2;
  if(exercise_frame()!=p[0]||test_get_fs_head()!=p[0])return 3;
  if(test_install_fs(nullptr)!=-22||test_get_fs_head()!=p[0])return 4;
 }
 if(first[1]!=1||first[2]!=2||first[3]!=3||second[1]!=4||second[2]!=5||second[3]!=6)return 5;
 const char msg[]="PASS: FS setup, 64 rebindings, frame restoration and rejected null backing\n";
 test_write(msg,sizeof(msg)-1);return 0;
}
