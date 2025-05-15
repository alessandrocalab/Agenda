#ifndef NOTE_HPP
#define NOTE_HPP

#include <string>
#include <vector>
#include <iostream>

class Note{
private:
    std::string date;
    std::vector<std::string> notes;
public:
    Note(){}

    //setter methods
    Note &setNotes(const std::vector<std::string> &notes){
        this->notes=notes;
        return *this;
    }

    Note &setDate(const std::string &date){
        this->date=date;
        return *this;
    }

    //add note
    Note &addNote(const std::string &note){
        this->notes.push_back(note);
        return *this;
    }
    //remove note
    bool remNote(unsigned short index){
        if(index>=notes.size()){
            std::cerr<<"Notes' index out of range"<<std::endl;
            return false;
        }

        notes.erase(notes.begin()+index);

        return true;
    }
    //getter methods
    std::string getDate()const{
        return date;
    }

    const std::vector<std::string> &getNotes()const{
        return notes;
    }
    //operator to get notes
    std::string operator[](unsigned short index)const{
        if(index>=notes.size()){
            std::cerr<<"Notes' index out of range"<<std::endl;
            return "";
        }

        return notes[index];
    }
};

#endif // NOTE_HPP
