#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

bool is_not_valid_json(const char* json_data) {
    bool in_string = false;
    bool in_escape_sequence = false;
    bool in_number = false;
    bool in_array = false;
    bool in_object = false;
    bool in_boolean = false;
    int bracket_counter = 0;
    int brace_counter = 0;
    int colon_counter = 0;
    int comma_counter = 0;
    char c;
    for (int i = 0; i < strlen(json_data); i++) {
        c = json_data[i];
        cout << "Znak: " << c << endl;
        if (c == '\"') {
            if (!in_escape_sequence) {
                in_string = !in_string;
                in_boolean = false;
                continue;
            }
        }
        if (c == '\\') {
            in_escape_sequence = !in_escape_sequence;
            continue;
        }
        if (in_string) {
            continue;
        }
        if (c == '-' || (c >= '0' && c <= '9')) {
            if (!in_number) {
                in_number = true;
                in_boolean = false;
            }
            continue;
        }
        in_number = false;
        if (in_boolean && !isalpha(c)) {
            in_boolean = false;
        }
        if (c == ':') {
            if (!in_object) {
                return i;
            }
            colon_counter++;
            in_boolean = false;
            continue;
        }
        if (c == ',') {
            if (!(in_array || in_object)) {
                return i;
            }
            comma_counter++;
            in_boolean = false;
            continue;
        }
        if (c == '[') {
            in_array = true;
            bracket_counter++;
            in_boolean = false;
            continue;
        }
        if (c == ']') {
            if (!in_array) {
                return i;
            }
            bracket_counter--;
            in_boolean = false;
            if (bracket_counter == 0) {
                in_array = false;
            }
            continue;
        }
        if (c == '{') {
            in_object = true;
            brace_counter++;
            in_boolean = false;
            continue;
        }
        if (c == '}') {
            if (!in_object) {
                return i;
            }
            brace_counter--;
            in_boolean = false;
            if (brace_counter == 0) {
                in_object = false;
            }
            continue;
        }
        if ((c == 't' || c == 'f') && !in_boolean) {
            in_boolean = true;
            continue;
        }
        if (!isspace(c) && c != '\n' && !in_boolean) {
            int essa;
            essa = c;
            return i;
        }
    }
    return !in_string && !in_escape_sequence && !in_number && !in_array && !in_object && !in_boolean && bracket_counter == 0 && brace_counter == 0 && colon_counter == comma_counter;
}


int main(int argc, char* argv) {

    char choice;
    ifstream size_file("nazwa_pliku.json", ios::binary);
    // ifstream file("nazwa_pliku.json", ios_base::in);
    ifstream file;
    int where;
    char* arr;
    const auto begin = size_file.tellg();
    size_file.seekg(0, ios::end);
    const auto end = size_file.tellg();
    const auto fsize = (end - begin);
    
    do {

        cin >> choice;
       switch (choice) {
        case 'h':
            cout << "Projekt_JSON Andrzej Zwirko 193749" << endl;
            cout << "Zaimplementowane operacje: h, o, c" << endl;
            break;
        case 'o':
            char input[100];
            cin >> input;
            file.open("nazwa_pliku.json");

            if (file.is_open()) {
                cout << "Plik " << input << "jest otwarty" << endl;
            }
            else {
                cout << "Plik " << input << "nie jest otwarty" << endl;
            }
            break;
        case 'c':
            //ifstream file;
            file.open("nazwa_pliku.json");

            if (file.is_open()) {
                cout << "Plik (nazwa_pliku.json) jest otwarty." << endl;
            }
            else {
                cout << "Plik (nazwa_pliku.json) nie jest otwarty." << endl;
            }

            arr = new char[fsize];

            file.get(arr, fsize, '\0');

            cout << fsize << endl;
            cout << strlen(arr) << endl;

            //where = 0;

            if (is_not_valid_json(arr)) {
                cout << "Blad: nieprawidlowy plik json" << endl;
                //cout << "Blad w znaku numer: " << where << endl;
            }
            else {
                cout << "Prawidlowy plik json" << endl;
            }

            delete arr;
            break;
        case 'q':
            break;
        default:
            cout << "Nie ma takiej opcji" << endl;
            break;
        }
    } while (choice != 'q');

    return 0;
}
