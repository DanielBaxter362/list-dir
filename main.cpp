#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <sys/stat.h>
#include <unistd.h>

#include <iostream>
#include <cstdlib>

extern "C" int nftw_callback(const char* fpath, const struct stat* sb, int typeflag, struct FTW *ftwbuf)
{
    const char* filename = fpath + ftwbuf->base;
    
    switch (typeflag) {
        case FTW_D:
            if (ftwbuf->level == 0) {
                return FTW_CONTINUE;
            } else {
                std::cout << filename << std::endl;
                return FTW_SKIP_SUBTREE; // Don't traverse subdirectories
            }
        case FTW_F:
            std::cout << filename << std::endl;
            return FTW_CONTINUE;
        case FTW_SL:
            std::cout << filename << std::endl;
            return FTW_CONTINUE;
    }
    
    std::cout << "Error when listing directory!" << std::endl;
    return FTW_STOP;
}   

int main(int argc, char* argv[]) 
{
    if (argc > 2) {
        std::cout << "Usage: " << argv[0] << " [DIRECTORY]" << std::endl;
        return 1;    
    }
    
    char* dir;
    bool should_free = false;
    if (argc == 1) {
        dir = get_current_dir_name();
        should_free = true;
    }
    else {
        dir = argv[1];
    }

    
    nftw(dir, nftw_callback, 1, FTW_PHYS | FTW_ACTIONRETVAL);
    
    if (should_free) { free(dir); }
    return 0;
}
