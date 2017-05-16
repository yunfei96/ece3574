#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

int main(int argc, char*argv[])
{
    if (argc == 2)
    {
        string display_string;
        string input = argv[1];
        ifstream in(input, ios::binary);
        uint8_t value; //read in every 8 bit, 1 char, 2 hex number
        if(in.fail()) //if it does not read in file is not found
        {
            cout << "input file not found"<< endl;
            return EXIT_FAILURE;
        }
        in.read(reinterpret_cast<std::fstream::char_type*>(&value), sizeof(value));
        int count = 0; //control change lane every 16 loop
        int space = 0; //for hex, it is group as 2 bytes. So every 4 hex number will be displayed with a space
        int all = 0; //how many lines are there
        if(in.fail())
        {
            //file is empty
            return EXIT_SUCCESS;
        }
        cout << hex << setw(6) << setfill('0') << all << "0: ";
        while (!in.fail())
        {
            count++;
            space++;
            if (count == 17) //if the it has output 16 bit hex in a line
            {
                cout << " "<< display_string << endl;
                display_string = "";
                all++;
                cout << hex << setw(6) << setfill('0') << all << "0: ";
                count = 1;
            }
            if (isprint(value)) //if the value is printable, print it out
                display_string = display_string + char(value);
            else
                display_string = display_string + '.';
            if (space == 2) //hex is grouped with 2 bytes, 4 hex number, so i need to read in twice and output a space
            {
                cout << hex << setw(2) << setfill('0') << int(value) << " ";
                space = 0;
            }
            else
            {
                cout << hex << setw(2) << setfill('0') << int(value); 
            }
            
            in.read(reinterpret_cast<std::fstream::char_type*>(&value), sizeof(value));
        }
        in.close(); //close the file
        if (count != 9) //if the hex does not fill out a line
        {
            int remain_fillup;
            if (count % 2 == 1) //if finished with out grouping
            {
                remain_fillup = 2*(16 - count) + (16 - count)/2 + 1;
            }
            else //if finished with grouping
            {
                remain_fillup = 2 * (16 - count) + (16 - count) / 2;
            }
            
            for (int i = 0; i < remain_fillup; i++) //output space and the text
            {
                cout << " ";
            }
            cout << " " << display_string << endl; //set blank space
        }
        return EXIT_SUCCESS;
    }
    else //if argument number is not right
    {
        cout << "FAIL!!!!!! the correct command arg is exe name + file name" << endl;
        return EXIT_FAILURE;
    }
}
