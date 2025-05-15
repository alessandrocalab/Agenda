#include <iostream>
#include "include/Date.hpp"

using namespace std;

int main()
{
    Date oggi;

    char dayname[7][10]={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
    oggi.setFormat(1);
    cout<<oggi.calculateDate(4).getFormattedDate()<<"Day "<<dayname[oggi.getDayName()]<<endl;




    return 0;
}
