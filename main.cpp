#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <algorithm>

namespace fsys = std::filesystem;

struct file_data {
    std::string name;
};

std::string trim_path(const std::string& path)
{
    std::size_t last = path.find_last_of("/\\");
    return path.substr(last+1);
}

void print_file_data(const file_data& data)
{
    std::cout << data.name << std::endl;
}

int main(int argc, char* argv[]) 
{
    if (argc > 2) {
        std::cout << "Usage: " << argv[0] << " [DIRECTORY]" << std::endl;
        return 1;    
    }
    
    std::string dir;
    if (argc == 1) {
        dir = fsys::current_path();
    }
    else {
        dir = argv[1];
    }

    std::vector<file_data> files;
    for (const fsys::directory_entry& entry : fsys::directory_iterator(dir)) {
        file_data file;
        file.name = trim_path(entry.path().string());

        files.push_back(file);
    } 

    std::for_each(files.begin(), files.end(), print_file_data);
    
    return 0;
}
