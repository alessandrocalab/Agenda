#include <string>
#include <vector>
#include "../include/Note.hpp"
#include "../include/Date.hpp"
#include "../include/Page.hpp"
#include <iostream>
//default Page's constructor
Page::Page(short id):id(id){
    repIsCalculated=false;
    dateIsCalculated=false;
}

//Page's method to calculate the future dates of repetitions
void Page::calculateRepetitions(){
    if(!dateIsCalculated) //it calculate the date of the page if it has not yet been calculated
        date.calculateDate(id);

    //1: day rep
    if(date.getDayName()==6)
        repetitions.push_back(id+2); //we don't repeat on sunday <(^-^)>
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

        std::cout<<temp.calculateDate(days).getFormattedDate()<<std::endl;

        repetitions.push_back(days);
    }

    repIsCalculated=true;
}

//getter methods
std::vector<Note> &Page::getNotes(){return notes;}
unsigned short Page::getId()const{return id;}
const std::vector<short> &Page::getRepetitions(){
    if(!repIsCalculated)
        calculateRepetitions();
    return repetitions;
}
