#ifndef PAGE_HPP
#define PAGE_HPP

#include <string>
#include <vector>
#include "../include/Note.hpp"
#include "../include/Date.hpp"

class Page{
private:
    Date date;
    std::vector<Note> notes;
    unsigned short id;
    std::vector<short> repetitions;
    bool repIsCalculated;
    bool isModified;

    //method to calculate the future dates of repetitions
    void calculateRepetitions();

public:
    Page(short id=0);

    //constant
    static constexpr short repNumber=5;  //1 day rep, 1 week rep, 1/2/3 Months rep

    //setter method
    void setIsModified(bool newState);

    //getter methods
    const std::vector<Note> &getNotesConst()const;
    std::vector<Note> &getNotes();
    Note &getNote(short index=0);
    unsigned short getId()const;
    const std::vector<short> &getRepetitions();
    const Date &getDate()const;
    bool getIsModified()const;
    Page &operator=(const Page &other);

};

#endif // PAGE_HPP
