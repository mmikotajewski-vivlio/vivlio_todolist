#include <iostream>

#include <QCoreApplication>
#include <QCommandLineParser>

#include "readFile.h"

int main(int argc, char *argv[])
{


    QCoreApplication a(argc, argv);

    int currentArgIndex = 0;
    while(currentArgIndex != argc) {
        currentArgIndex++;
        QString currentArg { argv[currentArgIndex] };
        if(currentArg == "-h" || currentArg == "--help") {
            std::cout << "Program name : vivtodo\n"
                << "Description : Super todo list management\n"
                      << "Options :\n" <<
                    "\t --help / -h : Shows help\n" <<
                    "\t --add / -a <Thing to do between quotes> :\t\t Add a normally urgent item to the todo list\n" <<
                    "\t --add-urgent / -u <Thing to do between quotes> :\t\t Add an urgent item to the todo list\n" <<
                    "\t --add-not-so-urgent / -n <Thing to do between quotes> :\t\t Add a not urgent item to the todo list\n" <<
                    "\t --mark-as-done / -m <Task ID> :\t\t Mark the task whose ID is given in parameter as done\n"  <<
                    "\t --purge / -p :\t\t Removes all tasks marked as done\n"  <<
                    "\t If no option is provided, just displays the list of items in the TODO list sorted by priority (urgents, normally urgent, not urgent, done)"  << std::endl;
        }
    }

    auto file = readFile("/tmp/toto");

    // Suggestions :
    // Pour aider pour la suite de l'entretien ça pourrait être une bonne idée de faire tenir chaque élément
    // de la todo list sur une seule ligne, avec un caractère en début de ligne qui donne son statut

}
