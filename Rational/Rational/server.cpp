#include <iostream>
#include <exception>
#include <string>
using namespace std;
/*string AskTimeServer() {
	throw std::system_error(EDOM, std::generic_category(), "hello world");
	throw runtime_error("Time is out");
	return " ";
}*/
class TimeServer {
public:
	string GetCurrentTime() {
		string s;
		try {
			s = AskTimeServer();
		}
		catch (system_error& e) {
			return LastFetchedTime;
		}
		/*catch(exception & ex){
			throw ex;
			//return "";
		}*/
		LastFetchedTime = s;
		return s;
	}
private:
	string LastFetchedTime = "00:00:00";
};

int main() {
	TimeServer ts;
	try {
		cout << ts.GetCurrentTime() << endl;
	}
	catch (exception & e) {
		cout << "Exception got: " << e.what() << endl;
	}
	return 0;
}