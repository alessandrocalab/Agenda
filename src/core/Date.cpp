#include "../include/Date.hpp"
#include <string>
#include <ctime>


bool isLeap(short year){//function to check if it is a leap year
    return ((year%4==0&&year%100!=0)||year%400==0);
}

Date::Date(){} //default constructor

//static attributes initialization
short Date::format=0;

Date &Date::calculateDate(long long daysFromStart){//Method to calculate and set all data attributes
    long long seconds=daysFromStart*SECOND_IN_A_DAY;

    std::tm start{};    //Standard c++ structure for representing dates
    start.tm_year=124;  //offset from 1900, so it's 2024
    start.tm_mon=0;     //January
    start.tm_mday=1;    //the 1st

    std::time_t base=std::mktime(&start); //seconds osince 01/01/1970 (unix epoch)
    std::time_t target=base+ seconds; //adding the number of days from the input parameter

    std::tm tmCopy=*std::localtime(&target); //converting the target time into a local date using the system's time zone

    //setting the class'attributes based on tmCopy data
    day=tmCopy.tm_mday;
    month=tmCopy.tm_mon+1;
    year=tmCopy.tm_year+1900;
    dayName=tmCopy.tm_wday;

    Date::setFormatDate();

    return *this;
}

Date &Date::calculateTodayDate(){ //Method to set the attributes to today's date
    std::time_t today=time(0); //setting the time now
    std::tm tmCopy=*std::localtime(&today);

    //setting the class'attributes from tm_ptr data
    day=tmCopy.tm_mday;
    month=tmCopy.tm_mon+1;
    year=tmCopy.tm_year+1900;
    dayName=tmCopy.tm_wday;

    Date::setFormatDate();

    return *this;
}

//class Date getter methods
std::string Date::getFormattedDate()const{return formattedDate;}
short Date::getDayName()const{return dayName;}
short Date::getDay()const{return day;}
short Date::getMonth()const{return month;}
short Date::getYear()const{return year;}

//class Date setter methods
void Date::setFormat(short newFormat){format=newFormat;}

void Date::setFormatDate(){
    switch (format){
        case 0://YYYY/MM/DD ISO
            formattedDate=std::to_string(year)+"/"+(month<10 ? "0":"")+std::to_string(month)+"/"+(day<10 ? "0":"")+std::to_string(day);
        break;

        case 1://DD/MM/YYYY EU
            formattedDate=(day<10 ? "0":"")+std::to_string(day)+"/"+(month<10 ? "0":"")+std::to_string(month)+"/"+std::to_string(year);
        break;

        case 2://MM/DD/YYYY USA
            formattedDate=(month<10 ? "0":"")+std::to_string(month)+"/"+(day<10 ? "0":"")+std::to_string(day)+"/"+std::to_string(year);
        break;
    }
}
