#include <random>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

struct CollatzInterval_t
{
    int iMin, iMax;

    CollatzInterval_t(int min, int max) : 
        iMin(min), iMax(max) {}

    bool valid() { return (iMin >= 2 && iMax >= 3); }
};

class CollatzTupel
{
public:

    CollatzTupel() : CollatzTupel(CollatzInterval_t(2, 100)) { }

    CollatzTupel(CollatzInterval_t interval) 
    {
        cout << "Minimum: " << interval.iMin << "; Maximum: " << interval.iMax << endl;

        if(!interval.valid())
        {
            throw invalid_argument("Invalid args! Required: (iMin >= 2 && iMax >= 3)");
            return;
        }

        random_device rd;
        m_NumVec.push_back((rd() % interval.iMax) + interval.iMin);
     }

    CollatzTupel(int iStart)
    {
        cout << "Start: " << iStart << endl;

        if(iStart < 1)
        {    
            throw invalid_argument("Invalid arg! Required: (iStart >= 1)");
            return;
        }

        m_NumVec.push_back(iStart);
    }

    int getNum()
    { 
        return m_NumVec.back();    
    }

    bool getNextNumber()
    {
        if(m_NumVec.back() != 1)
        {
            if(m_NumVec.back() % 2 == 0) 
                m_NumVec.push_back(m_NumVec.back() / 2);
            else    
                m_NumVec.push_back((3 * m_NumVec.back()) + 1);

            return true;
        }
        
        return false;
    }
    
private:

    vector<int> m_NumVec;
};

int main(int argc, char **argv)
{
    CollatzTupel *collatzGen = nullptr;

    try 
	{
        switch(argc)        
        {
            case 2:
            { 
                int iStart = 0;
                stringstream ss(argv[1]);
            
                ss >> iStart;
            
                collatzGen = new CollatzTupel(iStart);
                break;
            }
            case 3:
            {
                int iMin = 0,
                    iMax = 0;
            
                stringstream ss(argv[1]);
            
                ss >> iMin;
            
                   ss.clear(); 
                ss.str(argv[2]);
            
                ss >> iMax;
            
                collatzGen = new CollatzTupel(CollatzInterval_t(iMin, iMax));
                break;
            }
            case 1:
            case 0:
                collatzGen = new CollatzTupel();
            default:
                cerr << "Usage: \n\t"
                      << argv[0] << "( [iStart] | [iMax] [iMin] )\n" << endl;
                
                if(argc > 3) return 0;
        }
    }
    catch (exception &e)
    {
    	cerr << "Exception: " << e.what() << endl;
        return 0;
    }

    cout << "Hello! This is your collatz-tupel:" << endl;
    
    do {
        cout << collatzGen->getNum() << std::endl;        
    } 
    while(collatzGen->getNextNumber());

    return 0;
}

