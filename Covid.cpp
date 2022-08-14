#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;
const int maxrec = 20;
string name[maxrec] = {};
string id[maxrec] = {};
string donator[maxrec] = {};
string shipments[maxrec] = {};
string quantity[maxrec] = {};

string getData(int column,
               string line) // if this function get "1,line", it indicates 1st column and the line we want to fetch data
{
    char arr[line.length() + 1];
    strcpy(arr, line.c_str());
    string toBeSend = "";
    int commaNumber = -1;

    for (int i = 0; i < line.length(); i++) {
        if (arr[i] == ',') {
            commaNumber++;
            if (column == commaNumber) {
                return toBeSend;
            } else {
                toBeSend = "";
            }
        }
        if (arr[i] != ',') { toBeSend += arr[i]; }
    }
}

void openFile() {
    string line;
    ifstream myfile("covid.txt");
    if (myfile.is_open()) {
        int x = 0;
        while (getline(myfile, line)) {
            int l = line.length();
           
            name[x] = getData(0, line);
            id[x] = getData(1, line);
            donator[x] = getData(2, line);
            shipments[x] = getData(3, line);
            quantity[x] = getData(4, line);

            x++;
        }
    } else {
        cout << "Unable to open file!" << endl;
    }
}

void AddRecord() {

    char prodname[20];
    char prodid[20];
    char proddoner[20];
    char prodships[20];
    char prodquantity[20];

    cin.ignore();

    cout << "Product Name.";
    cin.getline(prodname, 20);
    cout << "Product ID.";
    cin.getline(prodid, 20);
    cout << "Donator.";
    cin.getline(proddoner, 20);
    cout << "No of Shipments.";
    cin.getline(prodships, 20);
    cout << "Quantity Recieved(millions).";
    cin.getline(prodquantity, 20);

    for (int x = 0; x < maxrec; x++) {
        if (id[x] == "\0") {
            name[x] = prodname;
            id[x] = prodid;
            donator[x] = proddoner;
            shipments[x] = prodships;
            quantity[x] = prodquantity;
            break;
        }
    }
}

void ListRecord() {
    system("CLS");
    cout << "<< Current Items >>" << endl;
    cout << "=============================" << endl;
    int counter = 0;
    cout << "No.||NAME OF SUPPLY||SUPPLY CODE||DONATOR||NO OF SHIPMENTS||QUANTITY(millions)||" << endl
         << "---------------------\n";
    for (int x = 0; x < maxrec; x++) {
        if (id[x] != "\0") {
            counter++;
            cout << "" << counter << "  " << name[x] << "  " << id[x] << "  " << donator[x] << "  " << shipments[x]
                 << "  " << quantity[x] << endl;
        }
    }
    if (counter == 0) {
        cout << "No Records Found!!!" << endl;
    }
    cout << "========================================";
}

void SearchRecord(string search) {
    system("CLS");
    cout << "Current Records:" << endl;
    cout << "========================================" << endl;
    int counter = 0;
    for (int x = 0; x < maxrec; x++) {
        if (id[x] == search) {
            counter++;
            cout << "" << counter << "  " << name[x] << "  " << id[x] << "  " << donator[x] << "  " << shipments[x]
                 << "  " << quantity[x] << endl;
            break;
        }
    }
    if (counter == 0) {
        cout << "No Records Found!!!" << endl;
    }
    cout << "========================================";
}

void updateRecord(string search) {
    char prodname[20];
    char prodquantity[20];
    int counter = 0;
    for (int x = 0; x < maxrec; x++) {
        if (id[x] == search) {
            counter++;
            cout << "Enter Updated Quantity";
            cin.getline(prodquantity, 20);
            quantity[x] = prodquantity;
            cout << "Update Succesfull! " << endl;
            break;
        } else {
            cout << "Product not found!" << endl;
        }
    }
    if (counter == 0) {
        cout << "Invalid ID!" << endl;
    }
    cout << "========================================";
}

void deleteRecord(string search) {
    int counter = 0;
    for (int x = 0; x < maxrec; x++) {
        if (id[x] == search) {
            counter++;
            name[x] = "";
            id[x] = "";
            cout << "Successfully Deleted!" << endl;
            break;
        }
    }
    if (counter == 0) {
        cout << "Invalid ID!" << endl;
    }
    cout << "========================================";
}

void savetofile() {
    ofstream myfile;
    myfile.open("covid.txt");
    for (int x = 0; x < maxrec; x++) {
        if (id[x] == "\0") {
            break;
        } else {
            myfile << name[x] + "," + id[x] + "," + donator[x] + "," + shipments[x] + "," + quantity[x] << endl;
        }
    }
}

int main() {
    std::cout << " MENU\n";
    int option;
    string prodID;
    system("CLS");
    openFile();
    do {
        cout << "=============================" << endl;
        cout << "1-Create Records" << endl;
        cout << "2-Update Records" << endl;
        cout << "3-Delete Records" << endl;
        cout << "4-Search Records" << endl;
        cout << "5-Display All Records" << endl;
        cout << "6-Save and Exit!" << endl;
        cout << "-------------------------------" << endl;
        cout << "Select Option>>";
        cin >> option;
        switch (option) {
            case 1:
                AddRecord();
                system("CLS");
                break;
            case 2:
                cin.ignore();
                cout << "Search by Id>>";
                getline(cin, prodID);
                updateRecord(prodID);
                break;
            case 3:
                cin.ignore();
                cout << "Delete by Id>>";
                getline(cin, prodID);
                deleteRecord(prodID);
                system("CLS");
                break;
            case 4:
                cin.ignore();
                cout << "Search by Id>>";
                getline(cin, prodID);
                SearchRecord(prodID);
                break;
            case 5:
                ListRecord();
                break;
        }
    } while (option != 6);
    savetofile();
    cout << "Exit... Saving to file!" << endl;
}
