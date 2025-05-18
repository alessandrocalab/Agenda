#ifndef STORAGEMANAGER_HPP
#define STORAGEMANAGER_HPP

#include <string>
#include <filesystem>
#include <fstream>
#include "../include/Page.hpp"

class StorageManager{
private:

template <typename FT>
    bool fileOpener(FT &file, std::filesystem::path path)const{//Method to check file opening
        file.open(path);
        if(!file.is_open()){
            std::cerr<<"Corrupt or missing file"<<std::endl;
            std::ofstream creator(path);
            if(!creator.is_open()){
                std::cerr<<"Unable to create a new file"<<std::endl;
                return false;
            }
        }

        return true;
    }

    std::filesystem::path pagePathCalculator(const Page &page)const;//Method to calculate a page path

public:
    StorageManager();

    static const std::string PAGES_PATH; //constant to define the path
    static constexpr short numberOfNotes=Page::repNumber+1; //constant to define the number of notes for each page

    bool savePage(const Page &page)const; //Method to save a page

    bool loadPage(Page &pages)const; //Method to load a page

};

#endif // STORAGEMANAGER_HPP
