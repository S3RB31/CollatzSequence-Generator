#include <random>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

class CollatzTupel
{
public:

	struct Interval_t
	{
    	int iMin, iMax;

    	Interval_t(int min, int max) :
        	iMin(min), iMax(max) {}

    	bool valid() { return (iMin >= 1 && iMax >= 3 && (iMax - iMin) > 0); }
	};

    CollatzTupel(Interval_t interval) : 
		m_Interval(interval)
    {
        cout << "Minimum: " << interval.iMin << "; Maximum: " << interval.iMax << endl;

        if(!interval.valid())
            throw invalid_argument("Invalid args! Required: (iMin >= 1 && iMax >= 3 && (iMax - iMin) > 0)");
    }

    CollatzTupel(int iStart) :
		m_Interval(Interval_t(0, 0))
    {
        if(iStart < 1)
            throw invalid_argument("Invalid arg! Required: (iStart >= 1)");

        m_NumVec.push_back(iStart);
    }

	void start()
	{
		if(m_Interval.valid())
			this->findLongest();
		else
			this->createTupel();
	}

	static CollatzTupel *createFromArgs(int argc, char **argv)
	{
		try 
		{
			switch(argc)        
			{
				case 3:
				{
					int iMin = stringToInt(argv[1]);
					int iMax = stringToInt(argv[2]);	

					return new CollatzTupel(CollatzTupel::Interval_t(iMin, iMax));
				}
				case 2:
				{ 
					int iStart = stringToInt(argv[1]);

					return new CollatzTupel(iStart);
				}
				default:
					cerr << "Usage: \n\t"
						 << argv[0] << " ([iStart] | [iMin] [iMax])\n" << endl
						 << "Calling with two args will search longest seqeuence in interval ]iMin,iMax[." << endl;
			}
		}
		catch (exception &e) { cerr << "Exception: " << e.what() << endl; }

		return nullptr;
	}
		
private:

    vector<int> m_NumVec;
	Interval_t m_Interval;

    int getCurrentNum()
    { 
        return m_NumVec.back();    
    }

    bool pushNextNum()
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

	int createTupel(bool bPrint = true)
	{
		do 
		{ 
			if(bPrint) cout << m_NumVec.size() << ":\t" << getCurrentNum() << endl; 
		} 
		while(pushNextNum());

		return m_NumVec.size(); 	
	}

	void findLongest()
	{
		int iLongestLen = -1, iLongestNum = -1;

		for(int iNum = m_Interval.iMin + 1; iNum < m_Interval.iMax; iNum++)
		{
			m_NumVec.push_back(iNum);
			int iLength = createTupel(false);

			if(iLength > iLongestLen)
			{
				iLongestLen = iLength;
				iLongestNum = iNum;
			}

			m_NumVec.clear();
		}

		cout << "The longest sequence was generated starting from " << iLongestNum << endl;
		cout << "The sequence was " << iLongestLen << " numbers long: \n" << endl;

		m_NumVec.push_back(iLongestNum);
		createTupel();
	}

	static int stringToInt(string s)
	{
		int iRet = 0;

		stringstream ss(s);
		ss >> iRet;	

		return iRet;
	}
};

int main(int argc, char **argv)
{
	CollatzTupel *collatzGen = 
		CollatzTupel::createFromArgs(argc, argv);

	if(collatzGen != nullptr)
	{	
		collatzGen->start();
		delete collatzGen;
	}

    return 0;
}

