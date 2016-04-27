#include "dataOps.h"
#include <string>
#include <fstream>
#include <iostream>
#include <curl/curl.h>
#include <sstream>
#include <vector>
using namespace std;

dataOps::dataOps(){
	// initialize as null to avoid seg faults
	for(int i = 0; i < 31; i++){
		hashTable[i] = NULL;
	}
}

dataOps::~dataOps(){

}

string data;
// http://www.cplusplus.com/forum/unices/45878/
// avoid errors
size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up){ 
    for (int c = 0; c<size*nmemb; c++){
        data.push_back(buf[c]);
    }
    return size*nmemb; 
}
// stop cURL from automatically outputting all data
size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp)
{
   return size * nmemb;
}
string dataOps::pullStockData(string symbol){
	curl_global_init( CURL_GLOBAL_ALL );
	CURL * curl;
	CURLcode res;
	string content;
	curl = curl_easy_init();
	// insert user input into Yahoo API URL
	string urlPre = "http://chartapi.finance.yahoo.com/instrument/1.0/";
	string urlPost = "/chartdata;type=quote;range=2y/csv";
	string url = urlPre + symbol + urlPost;
	if(curl){
		// easy cURL functions for setting options
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
		// output cURL diagnostic info
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);	
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);

		ostringstream out;
		out << res << endl;
		content = out.str();
		cout << "Data retrieved! Outputting to " << symbol << ".txt" << endl;
	}
	return data;
}
void dataOps::writeStockData(string data, string name){
	ofstream newFile;
	newFile.open(name + ".txt");
	newFile << data << endl;
	newFile.close();
}

int dataOps::hashSum(int x){
	int sum = x;
	sum = sum % 31;
	return sum;
}

void dataOps::insertHash(vector <dataPoint *> v){
	for(int i = 0; i < v.size(); i++){
		int index = hashSum(v[i]->date);
		if(hashTable[index] == NULL){
			hashTable[index] = v[i];
		}
		else{
			dataPoint * current = hashTable[index];
			while(current->next != NULL){
				current = current->next;
			}
			v[i]->previous = current;
			current->next = v[i];
		}
	}
}

void dataOps::generateHash(string name){
	ifstream file;
	file.open(name + ".txt");
	string line;
	
	int lineNum = 0;
	int index = 0;
	int date;
	double close, high, low, open, volume;
	if(file.is_open()){
		// loop by line
		while(getline(file,line)){
			// set up linestream for comma delimited data
			stringstream lineStream(line);
			string value;
			// loop by comma delimiter through line
			while(getline(lineStream, value, ',')){
				if(lineNum > 18){
					if(index == 0){
						if(value == ""){
							break;
						}
						date = stoi(value);
					}
					else if(index == 1){
						close = stod(value);
					}
					else if(index == 2){
						high = stod(value);
                                        }
					else if(index == 3){
						low = stod(value);
                                        }
					else if(index == 4){
						open = stod(value);
                                        }
					else if(index == 5){
                        volume = stod(value);
                                        }
				index++;
				}
				if(index == 6){
					index = 0;
				}
			}
			// create vector for easy hash table creation
			if(lineNum > 18){
				dataPoint * node = new dataPoint(date, close, high, low, open, volume);
				points.push_back(node);
			}
			lineNum++;
		}
	}
	insertHash(points);
}

// formatting from [MM/DD/YY] string to [YYYY/MM/DD] int
int dataOps::convertDate(string date){
	int result;
	string newString = "20" + date.substr(6,2) + date.substr(0,2) + date.substr(3,2);
	result = stoi(newString);
	return result;
}

// search hash table
dataPoint * dataOps::findDataPoint(int date){
	int index = hashSum(date);
	bool found = false;
	dataPoint * current = hashTable[index];
	while(current !=NULL){
		if(current->date == date){
			found = true;
			return current;
		}
		current = current->next;
	}
	if(found == false){
		cout << "Could not find any data for this date!" << endl;
		return NULL;
	}
}

void dataOps::printDataPoint(dataPoint * d, string symbol){
	if(d == NULL){
		return;
	}
	string date = to_string(d->date);
	string newString = date.substr(4, 2) + "/" + date.substr(6,2) + "/" + date.substr(0,4);
	cout << "Data for " << symbol << " on the date " << newString << ":" << endl;
	cout << "High: " << d->highp << endl;
	cout << "Low: " << d->lowp << endl;
	cout << "Opening price: " << d->openp << endl;
	cout << "Closing price: " << d->closep << endl;
	cout << "Volume traded: " << fixed <<  d->volume << endl;
}

double dataOps::findAllTimeHigh(){
	double max = 0;
	for(int i = 0; i < points.size(); i++){
		if(points[i]->highp > max){
			max = points[i]->highp;
		}
	}
	return max;
}

string dataOps::findAllTimeHighDate(){
	dataPoint * highest = NULL;
	double max = 0;
	for(int i = 0; i < points.size(); i++){
		if(points[i]->highp > max){
			highest = points[i];
		}
	}
	string date = to_string(highest->date);
	string newString = date.substr(4, 2) + "/" + date.substr(6,2) + "/" + date.substr(0,4);
	return newString;
}

double dataOps::bestDayNum(){
	double result = 0;
	for(int i = 0; i< points.size(); i++){
		if(points[i]->closep > points[i]->openp){
			if(points[i]->closep - points[i]->openp > result){
				result = points[i]->closep - points[i]->openp;
			}
		}
	}
	return result;
}
