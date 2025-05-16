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
    const unsigned short id;
    std::vector<short> repetitions;
    bool repIsCalculated;
    bool dateIsCalculated;

    //method to calculate the future dates of repetitions
    void calculateRepetitions();

public:
    Page(short id=0);

    //constant
    static constexpr short repNumber=5;  //1 day rep, 1 week rep, 1/2/3 Months rep

    //getter methods
    const std::vector<Note> &getNotesConst()const;
    std::vector<Note> &getNotes();
    unsigned short getId()const;
    const std::vector<short> &getRepetitions();
};

#endif // PAGE_HPP
