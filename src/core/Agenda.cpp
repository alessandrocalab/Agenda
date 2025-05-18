#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include "../include/StorageManager.hpp"
#include "../include/Page.hpp"
#include "../include/Date.hpp"
#include "../include/Agenda.hpp"


//Agenda methods:
Agenda::Agenda(){

    Date today;//setting the starting page to the today date
    today.calculateTodayDate();

    selectedId=findIndexByDate(today.getYear(),today.getMonth(),today.getDay());
    loadNewPage();
}

bool Agenda::dateCheck(short year, short month, short day)const{
    if(year<2024||year>2112)
        return false;
    if(month<1||month>12)
        return false;

    short monthsLimits[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(isLeap(year))
        ++monthsLimits[1];
    if(day<1||day>monthsLimits[month-1])
        return false;

    return true;
}


short Agenda::findIndexByDate(short year, short month, short day)const{ //method to find an Index using a Date
    if(!dateCheck(year,month,day))
        return -1;

    // 2024/01/01 is the index 0
    short calcIndex=day-1;

    //2. setting the days from the years
    short years=year-2024;
    for(short i=0;i<years;++i)
        calcIndex+=isLeap(year-1-i)? 366:365;



    //3. setting days from the Months
    static const short stgDOM[12]={0,31,59,90,120,151,181,212,243,273,304,334};//starting days of the months
    calcIndex+=stgDOM[month-1];

    if(isLeap(year)&&month>2)
        ++calcIndex;

    return calcIndex;
}

bool Agenda::changePage(short moves){ //method to change the page with a number from the selected page
    if(selectedId+moves>PAGE_LIMIT||selectedId+moves<0){
        std::cerr<<"limit reached"<<std::endl;
        return false;
    }
    else{
        selectedId+=moves;
        short tempIndex=linearSearch(selectedId,loadedPagesIndexes);

        if(tempIndex==-1)
            loadNewPage();
        else
            selectedIndex=tempIndex;
    }

    if(loadedPagesNumber>50)
        unLoadPages();

    return true;
}

bool Agenda::changePage(short year, short month, short day){//overloading to select the page with a date
    short temp=findIndexByDate(year,month,day);
    if(temp==-1)
        return false;
    selectedId=temp;

    short tempIndex=linearSearch(selectedId,loadedPagesIndexes);

    if(tempIndex==-1)
        loadNewPage();
    else
        selectedIndex=tempIndex;

    if(loadedPagesNumber>50)
        unLoadPages();

    return true;
}

void Agenda::addNote(const std::string &note){ //method to add a newNote
    //0: loaidng the pages to set the note (or checking if they are already loaded)
    std::vector<short> repetitition=loadedPages[selectedIndex].getRepetitions();

    for(auto &rep: repetitition){
        if(rep>PAGE_LIMIT)
            rep=-1;

        short newRepIndex=linearSearch(rep, loadedPagesIndexes);
        if(newRepIndex==-1){
            loadNewPage(rep);
            rep=loadedPages.size()-1;
        }
        else
            rep=newRepIndex;
    }

    //1: saving the note for today
    Note &toDayNote=loadedPages[selectedIndex].getNote(0);
    toDayNote.addNote(note);
    loadedPages[selectedIndex].setIsModified(true);

    //2:saving the other pages
    for(short i=1;i<=Page::repNumber;++i){
        if(repetitition[i-1]==-1)
            break;

        short pageIndex=repetitition[i-1];

        Note &toAdd=loadedPages[pageIndex].getNote(i);
        if(toAdd.getDate().empty())
            toAdd.setDate(getSelectedFormattedDate());
        toAdd.addNote(note);
        loadedPages[pageIndex].setIsModified(true);
    }

    savePages();
}

void Agenda::deleteNote(short index){ //method to delete one or all notes in the today section
    //0: loading the pages to set the note (or checking if they are already loaded)
    std::vector<short> repetitition=loadedPages[selectedIndex].getRepetitions();

    for(auto &rep: repetitition){
        if(rep>PAGE_LIMIT)
            rep=-1;

        short newRepIndex=linearSearch(rep, loadedPagesIndexes);
        if(newRepIndex==-1){
            loadNewPage(rep);
            rep=loadedPages.size()-1;
        }
        else
            rep=newRepIndex;
    }

     //1: deleting the note for today
    Note &toDayNote=loadedPages[selectedIndex].getNote(0);
    toDayNote.remNote(index);
    loadedPages[selectedIndex].setIsModified(true);

    //2: deleting the other pages
    for(short i=1;i<=Page::repNumber;++i){
        if(repetitition[i-1]==-1)
            break;

        short pageIndex=repetitition[i-1];

        Note &toAdd=loadedPages[pageIndex].getNote(i);
        toAdd.remNote(index);
        loadedPages[pageIndex].setIsModified(true);
    }

    savePages();
}

void Agenda::unLoadPages(){//method to free the memory
    savePages();

    Page tempSelected=loadedPages[selectedIndex];

    for(short i=0;i<loadedPagesNumber;++i){
        loadedPagesIndexes.pop_back();
        loadedPages.pop_back();
    }

    loadedPagesIndexes.push_back(selectedId);
    loadedPages.push_back(tempSelected);
    selectedIndex=0;
    loadedPagesNumber=1;
}

void Agenda::loadNewPage(){ //method to load a new selected page
    Page newPage(selectedId);
    storage.loadPage(newPage);
    loadedPages.push_back(newPage);
    loadedPagesIndexes.push_back(selectedId);
    selectedIndex=loadedPagesIndexes.size()-1;

    ++loadedPagesNumber;
}

void Agenda::loadNewPage(short index){ //overloading to load a page that is not selected
    Page newPage(index);
    storage.loadPage(newPage);
    loadedPages.push_back(newPage);
    loadedPagesIndexes.push_back(index);

    ++loadedPagesNumber;
}

std::string Agenda::getSelectedFormattedDate()const{
    return loadedPages[selectedIndex].getDate().getFormattedDate();
}

std::vector<Note> Agenda::getSelectedNotes()const{
    return loadedPages[selectedIndex].getNotesConst();
}


void Agenda::savePages(){ //method to save the modified pages
    for(auto &page: loadedPages){
        if(!page.getIsModified())
            continue;

        storage.savePage(page);

        page.setIsModified(false);
    }
}


