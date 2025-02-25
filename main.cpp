#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <algorithm>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    list<Goat> trip2;
    list<Goat> trip3;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 12) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 4:
                cout << "Copying trip data.\n";
                copy(trip.begin(), trip.end(), trip2.begin());
                break;
            case 5:
                cout << "Filling trip data.\n";
                fill(trip.begin(), trip.end(), Goat());
                break;
            case 6:
                cout << "Merging trip data.\n";
                merge(trip.begin(), trip.end(), trip2.begin(), trip2.end(), trip.begin());
                break;
            case 7:
                cout << "Reverse trip data.\n";
                reverse(trip.begin(), trip.end());
                break;
            case 8:
                cout << "Finding upper bound trip data.\n";
                auto ub = upper_bound(trip.begin(), trip.end(), 3);
                break;
            case 9:
                cout << "Finding lower bound trip data.\n";
                auto ub = lower_bound(trip.begin(), trip.end(), 3);
                break;
            case 10:
                cout << "Replacing Goats in trip data.\n";
                replace(trip.begin(), trip.end(), Goat(), Goat("Timmy"));
                break;
            case 11:
                cout << "Clearing trip data.\n";
                trip.clear();
                break;
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Copy trip\n";
    cout << "[5] Fill trip\n";
    cout << "[6] Merge trips\n";
    cout << "[7] Reverse trip\n";
    cout << "[8] Find upper bound trip data\n";
    cout << "[9] Find lower bound trip data\n";
    cout << "[10] Replace Goats in trip data\n";
    cout << "[11] Clear trip\n";
    cout << "[12] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 4) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}