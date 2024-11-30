#include <iostream>
#include <regex>
#include <string>
#include <ctime>

using namespace std;

struct Subscription {
    private:
        string userName;
        string subscriptionType;
        string expirationDate;
    public:
        Subscription(string user, string type, string date):
            userName(user),
            subscriptionType(type),
            expirationDate(date){}
        bool isDateVal() {
            regex datePat(R"(\d{2}-\d{2}-\d{4})");
            return regex_match(expirationDate, datePat);
        }
        int daysLeft(){
            if(!isDateVal()){
                cout<<"Typed date si wrong";
                return -1;
            };
            time_t now = time(0);
            tm curTime = *localtime(&now);
            tm Time = {};
            sscanf(expirationDate.c_str(), "%d-%d-%d", &Time.tm_mday, &Time.tm_mon, &Time.tm_year);
            Time.tm_year -= 1900;
            Time.tm_mon -= 1;
            time_t Timestamp = mktime(&Time);
            double seconds = difftime(Timestamp, now);
            return seconds > 0 ? seconds / (60 * 60 * 24) : 0;
        }
        
    void displayInfo() {
        cout << "User Name: " << userName << endl;
        cout << "Subscription Type: " << subscriptionType << endl;
        cout << "Expiration Date: " << expirationDate << endl;
        if (daysLeft() >= 0)
            cout << "Days until expiration: " << daysLeft() << endl;
    }
};

int main() {
    Subscription subscr("Roman", "standard", "25-12-2024");
    subscr.displayInfo();
}
