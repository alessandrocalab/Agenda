#include <iostream>
#include "include/Date.hpp"
#include "include/Note.hpp"
#include "include/Page.hpp"

using namespace std;

int main()
{
    //test Date
    Date oggi;
    //char dayname[7][10]={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
    oggi.setFormat(1);
    //cout<<oggi.calculateDate(4).getFormattedDate()<<"Day "<<dayname[oggi.getDayName()]<<endl;

    //test Note
    /*Note note(oggi.calculateTodayDate().getFormattedDate());
    note.addNote("First note");
    note.addNote("Second note");
    cout<<"Notes:"<<endl;
    for(const auto &note : note.getNotes())
        cout<<note<<endl;
    */
    //test Page
    Page page(340);
    vector<short> reps=page.getRepetitions();
    for(const auto &rep:reps)
        cout<<rep<<endl;




    return 0;
}
