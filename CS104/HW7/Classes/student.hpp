student::student()
{
	fullName = "";
	ID = "";
}

student::student(string n, string i)
{
	fullName = n;
	ID = i;
}

student::~student()
{

}

void student::setName(const string &s)
{
	fullName = s;
}

string student::getName ()
{
	return fullName;
}

void student::setID(const string &i)
{
	ID = i;
}

string student::getID ()
{
	return ID;
}

void student::printStudent() const
{
	cout << "Name: " << fullName << endl;
	cout << "ID:   " << ID << endl;
}


bool student::operator< (student const & other)
{
	if ((this->fullName) < (other.fullName))
		return true;
	return false;
}

bool student::operator> (student const & other)
{
	if ((this->fullName) > (other.fullName))
		return true;
	return false;
}

bool student::operator== (student const & other)
{
	if ((this->fullName) == (other.fullName))
		return true;
	return false;
}

bool student::operator!= (student const & other)
{
	if ((this->fullName) != (other.fullName))
		return true;
	return false;
}

bool student::operator<= (student const & other)
{
	if ((this->fullName) < (other.fullName) || (this->fullName) == (other.fullName))
		return true;
	return false;
}

bool student::operator>= (student const & other)
{
	if ((this->fullName) > (other.fullName) || (this->fullName) == (other.fullName))
		return true;
	return false;
}
