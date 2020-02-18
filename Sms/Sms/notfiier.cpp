#include <string>
#include <vector>
#include <memory>
#include <iostream>
using namespace std;

void SendSms(const string& number, const string& message) {
	cout << "Send '" << message << "' to number " << number << endl;
}

void SendEmail(const string& email, const string& message) {
	cout << "Send '" << message << "' to e-mail " << email << endl;
}









class INotifier {
public:
	virtual void Notify(const string& message) = 0;
};

class SmsNotifier : public INotifier {
private:
	const string number;
public:
	SmsNotifier(string s): number(s){}
	void Notify(const string& message) override {
		SendSms(number, message);
	}
};

class EmailNotifier : public INotifier {
private:
	const string email;
public:
	EmailNotifier(string mail) : email(mail) {}
	void Notify(const string& message) override {
		SendEmail(email, message);
	}
};


void Notify(INotifier& notifier, const string& message) {
	notifier.Notify(message);
}

int main() {
	SmsNotifier sms{ "+7-495-777-77-77" };
	EmailNotifier email{ "na-derevnyu@dedushke.ru" };

	Notify(sms, "I have White belt in C++");
	Notify(email, "And want a Yellow one");
	return 0;
}