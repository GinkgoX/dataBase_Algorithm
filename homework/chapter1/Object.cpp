#include<iostream>
#include<cstring>

using namespace std;


/**
* A class for simulating a memory cell
*/
template<typename Object>
class MemoryCell
{
private:
	Object storedValue;
public:
	explicit MemoryCell(const Object & initialValue = Object()):storedValue(initialValue)
	{
	
	}
	
	const Object & read() const
	{
		return storedValue;
	}
	
	void write(const Object &obj)
	{
		storedValue = obj;
	}

};

int main()
{
	MemoryCell<int> mi;
	MemoryCell<string> ms("hello");
	mi.write(5);
	ms.write(ms.read() + " C++");
	cout << mi.read() << endl;
	cout << ms.read() << endl;
	return 0;
}

