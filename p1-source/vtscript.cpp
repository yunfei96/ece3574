#include "interpreter.hpp"
#include <fstream>
using namespace std;

bool calndis(Interpreter &interp, bool ok)
{
    if(ok)
    {
        Expression myresult;
        try
        {
            myresult = interp.eval();
        }
        
        catch (InterpreterSemanticError e)
        {
            cout << "Error: " << e.what() << endl;
            Interpreter new_interp;
            interp = new_interp;
            return false;
        }
        if(  myresult.type == "number")
        {
            cout << '(' << myresult.number_value << ')' << endl;
        }
        else if(myresult.type == "bool")
        {
            if(myresult.bool_value == true)
                cout << "(True)" << endl;
            else
                cout << "(False)" << endl;
        }
        return true;
    }
    cout << "Error: parsing failed" <<endl;
    Interpreter new_interp;
    interp = new_interp;
    return false;
}

int main(int argc, char *argv[])
{
    //repl mode
    if(argc == 1)
    {
        string input;
        cout << "vtscript>";
        getline(cin, input);
        Interpreter interp;
        while(cin.good())
        {
            if(input.size()!= 0)
            {
               istringstream iss(input);
                bool ok = interp.parse(iss);
                calndis(interp,ok);
            }
            cout << "vtscript>";
            getline(cin, input);
        }
    }
    //read file
    else if(argc == 2 )
    {
        string filename = argv[1];
        ifstream in(filename);
        if(!in.is_open())
        {
            cout << "Error: cannot open file" <<endl;
            return EXIT_FAILURE;
        }
        Interpreter interp;
        bool ok = interp.parse(in);
        calndis(interp,ok);
    }
    //-e mode
    else if(argc == 3 )
    {
        string flag = argv[1];
        if(flag == "-e")
        {
            istringstream iss(argv[2]);
            Interpreter interp;
            bool ok = interp.parse(iss);
            bool suc;
            suc = calndis(interp,ok);
            if(!suc)
            {
                return EXIT_FAILURE;
            }
            
        }
        else
        {
            cout << "Error: input argument not right" << endl;
            return EXIT_FAILURE;
        }
    }
    else
    {
        cout << "Error: input argument not right" << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}


