#include <string>
#include <vector>
#include "../include/Note.hpp"
#include "../include/Date.hpp"
#include "../include/Page.hpp"
#include <iostream>
//default Page's constructor
Page::Page(short id):id(id){
    repIsCalculated=false;
    date.calculateDate(id);
    notes.resize(repNumber+1);
    isModified=false;
}

//Page's method to calculate the future dates of repetitions
void Page::calculateRepetitions(){

    //1: day rep
    if(date.getDayName()==6)
        repetitions.push_back(id+2); //we don't repeat on sunday and saturaday <(^-^)>
    else if(date.getDayName()==5)
        repetitions.push_back(id+3);
    else
        repetitions.push_back(id+1);

    //2: rep 1 week
    repetitions.push_back(id+7); //EZ

    //3: monthly rep
    for(int i=0;i<repNumber-2;++i){

        short days=28*(i+1)+id; //in this way I can roughly calculate the days for the following month
        Date temp;
        short monthForComparsion=(date.getMonth()+i)%12;

        while(date.getDayName()!=temp.calculateDate(days).getDayName()||temp.getMonth()==monthForComparsion) //makes the calculation accurate
            ++days;

        repetitions.push_back(days);
    }

    repIsCalculated=true;
}

//setter method
void Page::setIsModified(bool newState){isModified=newState;}

//getter methods
const std::vector<Note> &Page::getNotesConst()const{return notes;}
std::vector<Note> &Page::getNotes(){return notes;}
Note &Page::getNote(short index){
    if(notes.size()<repNumber+1)
        notes.resize(repNumber+1);
    return notes[index];
}
unsigned short Page::getId()const{return id;}
const std::vector<short> &Page::getRepetitions(){
    if(!repIsCalculated)
        calculateRepetitions();
    return repetitions;
}
const Date &Page::getDate()const{return date;}
bool Page::getIsModified()const{return isModified;}
Page &Page::operator=(const Page &other){
    this->date=other.date;
    this->notes=other.notes;
    this->id=other.id;
    this->repetitions=other.repetitions;
    this->repIsCalculated=other.repIsCalculated;
    this->isModified=other.isModified;

    return *this;
}
