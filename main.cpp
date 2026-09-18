#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <algorithm>

namespace fsys = std::filesystem;

struct file_data {
    std::string name;
};

struct flags {
    bool show_hidden = false;
    bool show_size = false;
}

std::string trim_path(const std::string& path)
{
    std::size_t last = path.find_last_of("/\\");
    return path.substr(last+1);
}

void print_usage() {
    std::cout << "Usage: " << argv[0] << "[-sh] [DIRECTORY]" << std::endl;
}

void print_file_data(const file_data& data)
{
    std::cout << data.name << std::endl;
}

int main(int argc, char* argv[]) 
{
    if (argc > 3) {
        print_usage();
        return 1;    
    }
    
    flags optn;
    std::string dir;
    bool flags_set = false;
    bool dir_set = false;

    for (size_t i = 0; i < argc - 1; i++) {
        if (*argv[i] == '-' && !flags_set) {
            for (argv[i]; *argv[i]; argv[i]++) {
                switch (*p) {
                    case 's': optn.show_size = true;
                    case 'h': optn.show_hidden = true;
                }
            }
            flags_set = true;
        } else if (!dir_set) {
            dir = argv[i];
            flags_set = true;
        } else {
            print_usage();
            return 1;
        }
    }

    if (!dir_set) { dir = fsys::current_path(); }

    std::vector<file_data> files;
    for (const fsys::directory_entry& entry : fsys::directory_iterator(dir)) {
        file_data file;
        file.name = trim_path(entry.path().string());

        files.push_back(file);
    } 

    std::for_each(files.begin(), files.end(), print_file_data);
    
    return 0;
}
