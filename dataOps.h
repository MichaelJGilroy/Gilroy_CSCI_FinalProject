#ifndef DATAOPS_H 
#define DATAOPS_H 
#include <string>
#include <vector>


struct dataPoint{
		int date;
		double closep;
		double highp;
		double lowp;
		double openp;
		double volume;
        dataPoint * next;
    	dataPoint * previous;

        dataPoint(int in_date, double in_close, double in_high, double in_low, double in_open, double in_volume)
        {
			date = in_date;
			closep = in_close;
			highp = in_high;
			lowp = in_low;
			openp = in_open;
			volume = in_volume;
            next = NULL;
            previous = NULL;
        }

};

class dataOps {
        public:
                dataOps();
                ~dataOps();
                std::string pullStockData(std::string symbol);
				void writeStockData(std::string data, std::string name);
				void generateHash(std::string name);
				void insertHash(std::vector <dataPoint *> points);
				int convertDate(std::string date);
				dataPoint * findDataPoint(int date);
				void printDataPoint(dataPoint * d, std::string symbol);
				double findAllTimeHigh();
				std::string findAllTimeHighDate();
				double bestDayNum();
        private:
				std::vector <dataPoint *> points;
                int hashSum(int x);
                int tableSize = 31;
                dataPoint* hashTable[31];
	
};

#endif

