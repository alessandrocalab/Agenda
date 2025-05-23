#include <iostream>
#include "include/Date.hpp"
#include "include/Note.hpp"
#include "include/Page.hpp"
#include "include/StorageManager.hpp"
#include "include/Agenda.hpp"

#include <cstdlib>
#include <termios.h>
#include <unistd.h> // Per STDIN_FILENO

void setRawMode(bool enable) {
    static bool initialized = false;
    static termios oldt, newt;

    if (!initialized) {
        tcgetattr(STDIN_FILENO, &oldt); // salva l'originale solo una volta
        initialized = true;
    }

    if (enable) {
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO); // disattiva input "normale" ed echo
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // ripristina tutto perfettamente
    }
}

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

    /*Page page(340);
    StorageManager storage;
    if(storage.loadPage(page)){
        cout<<"Caricamento efettua to con sucesso"<<endl;
        const vector<Note> temp=page.getNotesConst();
    cout<<temp[1].getDate();
    }
    else{
        cout<<"Impossibile trovare il file"<<endl;
    }
    */
    //test Agenda
    Agenda a;
    short menu;
    string nota;
    vector<Note> Notes;
    setRawMode(true);
    while(1){
        system("clear");
        cout<<"Data: "<<a.getSelectedFormattedDate()<<endl;
        Notes=a.getSelectedNotes();

        if(!Notes[0].getNotes().empty())
            cout<<"Oggi:"<<endl;
        for(const auto &note: Notes[0].getNotes())
            cout<<note<<endl;

        if(!Notes[1].getNotes().empty())
            cout<<"\nRipetizione 1 giorno: "<<Notes[1].getDate()<<endl;
        for(const auto &note: Notes[1].getNotes())
            cout<<note<<endl;

        if(!Notes[2].getNotes().empty())
            cout<<"\nRipetizione 1 settimana: "<<Notes[2].getDate()<<endl;
        for(const auto &note: Notes[2].getNotes())
            cout<<note<<endl;

        if(!Notes[3].getNotes().empty())
            cout<<"\nRipetizione 1 mese: "<<Notes[3].getDate()<<endl;
        for(const auto &note: Notes[3].getNotes())
            cout<<note<<endl;

        if(!Notes[4].getNotes().empty())
            cout<<"\nRipetizione 2 mesi: "<<Notes[4].getDate()<<endl;
        for(const auto &note: Notes[4].getNotes())
            cout<<note<<endl;

        if(!Notes[5].getNotes().empty())
            cout<<"\nRipetizione 3 mesi: "<<Notes[5].getDate()<<endl;
        for(const auto &note: Notes[5].getNotes())
            cout<<note<<endl;



        menu=getchar();
        switch(menu){
            case 'd':
                a.changePage(1);
            break;
            case 'a':
                a.changePage(-1);
            break;
            case '+':
                setRawMode(false);
                cin>>nota;
                a.addNote(nota);
                setRawMode(true);
            break;
            case '-':
                a.deleteNote(-1);
            break;

        }

    }


    return 0;
}
