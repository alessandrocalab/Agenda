#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include "../include/StorageManager.hpp"
#include "../include/Page.hpp"

namespace fs=std::filesystem;

//StorageManager methods:
StorageManager::StorageManager(){};//Default constructor

const std::string StorageManager::mainPath="data/pages/page_";//Path constant

bool StorageManager::savePage(const Page &page)const{ //Method to save a page

    //1. opening the file
    fs::path savePath=pagePathCalculator(page);
    std::ofstream file;
    if(!fileOpener(file, savePath))
        return false;

    //2. if the page is empty it just remove the file
    std::vector<Note> toSave=page.getNotesConst();//getting the notes's vectore
    if(toSave.empty()){
        fs::remove(savePath);
        std::cout<<"Empty file removed"<<std::endl;
        return true;
    }

    //3. saving
    short itNumber=0; //itNumber (iteration number) define which type of note it is (0 today homework, 1 tomorrow, 2 one week, ...)
    for(const auto &note: toSave){//iterating all the single note

        std::vector<std::string> toAdd=note.getNotes();
        if(toAdd.empty())
                continue;

        if(itNumber!=0)
            file<<"~\n"; //delimeter between two different notes

        file<<std::to_string(itNumber)+"\n";//saving the itNumber to remember the type of note

        if(itNumber>0)//for the first note (the today one) it doesn't save the date cause is arleady saved in the page
        file<<note.getDate()+"\n";

        for(const auto &i: toAdd) //adding the strings
            file<<i+"\n";

        ++itNumber;
    }

    file.close();

    return true;
}

bool StorageManager::loadPage(Page &page)const{ //Method to save a page
        //1. opening the file
        fs::path filePath=pagePathCalculator(page);
        if(!fs::exists(filePath))
            return false;

        std::ifstream file;
        fileOpener(file,filePath);

        //2. setting the variables
        std::vector<Note> &notesToSet=page.getNotes();
        notesToSet.resize(numberOfNotes);
        std::string line;
        short noteIndex;
        bool newNote=true;
        bool nextIsDate=false;

        //3. loading the page
        while(getline(file,line)){

            if(newNote){//3.1. getting the index of the note to modify
                noteIndex=std::stoi(line);
                newNote=false;
                nextIsDate=true;
            }

            else if(nextIsDate&&noteIndex!=0){ //3.2. checking if line is a date
                notesToSet[noteIndex].setDate(line);
                nextIsDate=false;
            }

            else if(line=="~"){ //3.3. checking if the end of note is reached
                newNote=true;
            }
            else //3.4. adding the value to the note
                notesToSet[noteIndex].addNote(line);
        }

        file.close();

    return true;
}


fs::path StorageManager::pagePathCalculator(const Page &page)const{ //Method to calculate a page path
    short pageId=page.getId();
    fs::path filePath=mainPath+(pageId>10000? "":(pageId>1000? "0":(pageId>100? "00":(pageId>10? "000":"0000"))))+(std::to_string(pageId))+".txt";

    return filePath;
}
