/**
* A Employee class with name and salary;
* find maxmun salary in Emplyee Object array; 
*/

#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

class Employee
{
private:
	string name;
	double salary;
public:
	const string & getName() const
	{
		return name;
	}
	
	void setValue(const string &nm, double s)
	{
		name = nm;
		salary = s;
	}
	
	void show(ostream &out)const
	{
		out << name << " : " << salary << endl;
	}
	
	bool operator<(const Employee & emp)const
	{
		return salary < emp.salary;
	}
};

ostream & operator<<(ostream &out, const Employee &emp)
{
	emp.show(out);
	return out;
}

template <typename Compareable>
const Compareable & findMax(const vector<Compareable> &a);

int main()
{
	vector<Employee> ve(3);	
	ve[0].setValue("Python", 7000);
	ve[1].setValue("Java", 7500);
	ve[2].setValue("C++", 7000);
	cout << findMax(ve) << endl;
	return 0;
}

/**
* return the maxmum item in array a;
* assume a.size() > 0;
* Compareable objects must provide operator< and operator=
*/

template <typename Compareable>
const Compareable & findMax(const vector<Compareable> &a)
{
	int maxIndex = 0;
	for(int i = 1; i < a.size(); i++)
	{
		if(a[maxIndex] < a[i])
		{
			maxIndex = i;
		}
	}
	return a[maxIndex];
}
