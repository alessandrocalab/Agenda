#ifndef DATE_HPP
#define DATE_HPP

#include <string>

bool isLeap(short year);//function to check if it is a leap year

class Date{
private:
    std::string formattedDate;
    short dayName;
    short day;
    short month;
    short year;
    static short format;
public:
    Date();

    static constexpr int SECOND_IN_A_DAY=86400;
    Date &calculateDate(long long daysFromStart=0);//method to set the attributes calculating all the values
    Date &calculateTodayDate(); //method to set the attributes to today values

    //getter methods
    std::string getFormattedDate()const;
    short getDayName()const; //0 Sunday-6 Saturday
    short getDay()const;
    short getMonth()const;
    short getYear()const;

    //setter methods
    void setFormat(short newFormat);//0 ISO, 1 EU, 2 USA
    void setFormatDate();
};

#endif // DATE_HPP
