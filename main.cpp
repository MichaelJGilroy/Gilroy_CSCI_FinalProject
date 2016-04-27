// Michael Gilroy
// CSCI 2270 Final Project
// 4/26/2016

#include "dataOps.h"
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char * argv[]){
	// reference class
	dataOps d;
	// strings for user inputs
	string symbol = "";
	string date;
	string userInput;
    bool pow = true;
    
    while(pow){
                cout << "======Main Menu======" << endl;
                cout << "1. Insert stock symbol" << endl;
                cout << "2. Find stock info by date" << endl;
                cout << "3. Find all time highest price" << endl;
                cout << "4. Find biggest spike" << endl;
                cout << "5. Quit" << endl;

                cin >> userInput;

               switch(stoi(userInput)){
					case 1:
					{
						if(symbol != ""){
							// to avoid crashing, the program will not accept another stock symbol after one has been entered
							cout << "Sorry! Only one stock symbol can be taken per run. Please CTRL-C and run again to use a different symbol." << endl;
							break;
						}
						cout << "Enter a stock symbol: " << endl;
						cin >> symbol;
						// pull data using cURL
						string pulled = d.pullStockData(symbol);
						// write data to text file
						d.writeStockData(pulled, symbol);
						// use data from file to build a hash table
						d.generateHash(symbol);
						break;
					}
					case 2:
					{
						if(symbol == ""){
							// step 1 is manditory
							cout << "No stock info retrieved! Do option (1) before this step!" << endl;
							break;
						}
						cout << "Enter a date [mm/dd/yy]: " << endl;
						cin >> date;
						// convert user input to Yahoo's date format
						int newDate = d.convertDate(date);
						// use this date to search
						dataPoint * found = d.findDataPoint(newDate);
						d.printDataPoint(found, symbol);
						break;
					}
					case 3:
					{
						if(symbol == ""){
							// step 1 is manditory
							cout << "No stock info retrieved! Do option (1) before this step!" << endl;
							break;
						}
						cout << "The all time highest price for " << symbol << " was " << d.findAllTimeHigh() << " on the day " << d.findAllTimeHighDate() << endl;
						break;
					}
					case 4:
					{
						if(symbol == ""){
							// step 1 is manditory
							cout << "No stock info retrieved! Do option (1) before this step!" << endl;
							break;
						}
						cout << "The most that " << symbol << " stock rose in one day rose was " << d.bestDayNum() << endl;
						break;
					}
					case 5:
					{
						cout << "Goodbye!" << endl;
						pow = false;
					}
                }
        }
        return 0;
}

