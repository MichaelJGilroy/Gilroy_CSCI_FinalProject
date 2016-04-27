PROJECT SUMMARY:
This program is designed to pull stock data using the cURL library and give the user information based on a company's stock symbol they
input. After the data is pulled, it is stored in a hash table based on the date. After the data is stored, there are options for the 
user if they want to know more about a particular comanies' stock.

HOW TO RUN:
This is designed to be run similar to our CSCI-2270 assignments throughout the year. This program was written and tested only in the VM
provided by the school, but it should work fine with any system with g++. Compile and run using the following commands:
~$ g++ main.cpp dataOps.cpp -lcurl -std=c++11
~$ ./a.out

The "-lcurl" flag is for the cURL library, which is explained in the dependencies section.

DEPENDENCIES:
cURL is a library for downloading the cntents of a web page. In this program, it calls a simple Yahoo Finance API to dynamically retrieve 
historical stock data. To install, simply enter this:
~$ sudo apt-get install libcurl4-gnutls-dev

SYSTEM REQUIREMENTS:
This program was written and tested only in the VM provided for this course. With that being said, I'm sure this will run as planned on
command lines for Debian-based Linux distrobutions as well as the OS X terminal. No promises for native Windows compiles!

GROUP MEMBERS:
Michael Gilroy

CONTRIBUTORS:
N/A

OPEN ISSUES/BUGS:
When the user enters a stock symbol that is not recognized or does not exist, it gives an invalid argument error and aborts.
