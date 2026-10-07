#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <algorithm>

namespace fsys = std::filesystem;

struct FileData 
{
    std::string name;
    uintmax_t size;
};

struct Flags
{
    bool show_hidden = false;
    bool show_size = false;
    bool show_help = false;
};

void print_usage() 
{
    std::cout << "Usage: ls [-sph] [DIRECTORY]\nUse `-h` for help" << std::endl;
}

void print_help() 
{
    std::cout << "Flags:" << std::endl;
    std::cout << "  -s: show file sizes" << std::endl;
    std::cout << "  -p: show hidden files" << std::endl;
}

std::string trim_path(const std::string& path)
{
    std::size_t last = path.find_last_of("/\\");
    return path.substr(last+1);
}

void print_file_data(const FileData& data, const Flags& optn)
{
    if (data.name[0] == '.' && !optn.show_hidden) { return; }
    if (optn.show_size) { std::cout << data.size << " "; }
    std::cout << data.name << std::endl;
}

int main(int argc, char* argv[]) 
{
    if (argc > 3) {
        print_usage();
        return 1;    
    }
    
    Flags optn;
    std::string dir;
    bool flags_set = false;
    bool dir_set = false;
    
    // Collect command arguments
    for (size_t i = 1; i < argc; i++) {
        if (*argv[i] == '-' && !flags_set) {
            for (argv[i]; *argv[i]; argv[i]++) {
                switch (*argv[i]) {
                    case 's': optn.show_size = true; break;
                    case 'p': optn.show_hidden = true; break;
                    case 'h': optn.show_help = true; break;
                }
            }
            flags_set = true;
        } else if (!dir_set) {
            dir = argv[i];
            dir_set = true;
        } else {
            print_usage();
            return 1;
        }
    }

    if (optn.show_help) {
        print_help();
        return 0;
    }

    if (!dir_set) { dir = fsys::current_path(); }

    try {
        fsys::directory_iterator it(dir);
    } catch (const fsys::filesystem_error& e) {
        std::cout << "Failed to open directory " << dir << ", make sure it exists" << std::endl;
        return 1;
    }
    
    // Collect file data
    std::vector<FileData> files;
    for (const fsys::directory_entry& entry : fsys::directory_iterator(dir)) {
        FileData file;
        file.name = trim_path(entry.path().string());
        if (!entry.is_directory()) { file.size = entry.file_size(); }

        files.push_back(file);
    } 

    // Process file data
    std::sort(files.begin(), files.end(), [](const FileData& fileone, const FileData& filetwo) {
         return fileone.name < filetwo.name; 
    });
    
    std::for_each(files.begin(), files.end(), [optn](const FileData& fd) {
        print_file_data(fd, optn); 
    });
    
    return 0;
}
