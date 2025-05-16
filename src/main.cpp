#include <iostream>
#include "include/Date.hpp"
#include "include/Note.hpp"
#include "include/Page.hpp"
#include "include/StorageManager.hpp"


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
    /*Page page(340);
    vector<Note> &temp=page.getNotes();
    Note voidNote;
    temp.push_back(voidNote);
    temp[0].addNote("Prima nota oggi");
    temp[0].addNote("seconda nota oggi");
    temp.push_back(voidNote);
    temp[1].setDate("12/12/2024");
    temp[1].addNote("cacca 1 giono");
    temp.push_back(voidNote);
    temp.push_back(voidNote);
    temp[3].setDate("01/12/2024");
    temp[3].addNote("1 Mese");
*/

    //test StorageManager

   /* StorageManager storage;
    vector<short> mod;
    mod.push_back(340);
    vector<Page> pages;
    pages.push_back(page);
    if(storage.savePages(mod,pages))
        cout<<"File salvato con sucesso"<<endl;
    */

    Page page(340);
    StorageManager storage;
    if(storage.loadPage(page)){
        cout<<"Caricamento efettua to con sucesso"<<endl;
        const vector<Note> temp=page.getNotesConst();
    cout<<temp[1].getDate();
    }
    else{
        cout<<"Impossibile trovare il file"<<endl;
    }



    return 0;
}
