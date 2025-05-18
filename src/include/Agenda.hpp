#ifndef AGENDA_HPP
#define AGENDA_HPP

#include <vector>
#include <string>
#include "../include/StorageManager.hpp"
#include "../include/Page.hpp"

template <typename T>
short linearSearch(T toFind, const std::vector<T> container){
    short dim=container.size();

    for(short i=0;i<dim;++i)
        if(container[i]==toFind)
            return i;
    return -1;
}

class Agenda{
private:
    std::vector<Page> loadedPages;
    std::vector<short> loadedPagesIndexes;
    short selectedIndex;
    short selectedId;
    short loadedPagesNumber;
    static short dateFormat;
    StorageManager storage;
public:
    Agenda();

    static constexpr short PAGE_LIMIT=32506;//date 2112/12/31

    bool dateCheck(short year, short month, short day)const;
    short findIndexByDate(short year, short month, short day)const; //method to find an Index using a Date

    bool changePage(short moves);//method to change the selected page
    bool changePage(short year, short month, short day);
    void addNote(const std::string &note); //method to add a newNote
    void deleteNote(short index);//method to delete one or all notes in the today section
    void unLoadPages();//method to free the memory

    //storage methods
    void loadNewPage();//method to load a new page
    void loadNewPage(short index);//overloading to load a page that is not selected
    void savePages(); //method to save the modified pages

    //getter methods:
    std::string getSelectedFormattedDate()const;
    std::vector<Note> getSelectedNotes()const;



};

#endif // AGENDA_HPP
