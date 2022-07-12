#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;

class Controller{
private:
    string password="HardPassword";
    string pass=" ";
    int mOption=0;
    vector <double> payments;
    vector <string> items;
    double MoneySum=0;
    char c;
public:
    int Option=0;
    double Price=0.00;
    string Bev=" ";
    bool PayOK = false;
    bool mMode = false;
    void PaymentProcessing(){
        cout << endl << "  Vending machine accepts only:  " << endl;
        cout << "  0.25$, 0.5$, 1$, 2$, 5$ coins. " << endl;
        cout << "  The machine gives the change.  " << endl << endl;
        double Rest = Price;
        double Payment =0;
        while (Rest >0){
            cout << "(Simulate not inserting coins in time by entering 0)" << endl;
            payment_error:
            cout << " Insert coin : ";
            cin >> Payment;
            if (Payment !=0 && Payment !=0.25 && Payment !=0.5 && Payment !=1 && Payment !=2 && Payment !=5){
               cout << "Invalid Operator. Please try again." << endl;
               goto payment_error;
            }
            if(Payment==0){
                return;
            }
            Rest=Rest-Payment;
        }
        MoneySum=MoneySum+Price;
        payments.push_back(Price);
        items.push_back(Bev);

        if (Rest<0){
            cout << endl << "Giving change .";
            std::this_thread::sleep_for(500ms);
            cout << ".";
            std::this_thread::sleep_for(500ms);
            cout << "." << endl;
            std::this_thread::sleep_for(500ms);
            cout << endl << "Your change is " << -Rest << "$" << endl;
        }
        PayOK = true;
    }

    void MaintenanceMenu(){
        cout << "Enter a password: ";
        cin >> pass;
        if (pass==password){
            cout << endl << "     Maintenance MENU     " << endl;
            cout << "1. History of transactions" << endl;
            cout << "2. Money withdraw         " << endl;
            cout << "3. Turn off the machine   " << endl;
            cout << "4. Return to main menu    " << endl << endl;
            m_option_error:
            cout << "Pick an option: ";
            cin >> mOption;
            if (mOption <= 0 || mOption>4){
               cout << "Invalid Operator. Please try again." << endl;
               goto m_option_error;
            }
        }else{
            cout << endl << "Wrong password. Exiting to main menu..." << endl;
            return;
        }
    }

    void SelectMoption(){
        switch (mOption){
        case 1:
            for (int j=0;j<payments.size();j++){
                cout << items[j] << " " << payments[j] << endl;
            }
            cout << endl << "Returning to maintenance menu..." << endl;
            cout << "Press any key to continue." << endl;
            cin >> c;
            mMode=false;
            break;
        case 2:
            cout << endl << "Collected: " << MoneySum << "$" << endl << endl;
            cout << "Returning to maintenance menu..." << endl;
            cout << "Press any key to continue." << endl;
            cin >> c;
            MoneySum=0;
            mMode=false;
            break;
        case 3:
            cout << "Vending Machine is shutting down .";
            std::this_thread::sleep_for(500ms);
            cout << ".";
            std::this_thread::sleep_for(500ms);
            cout << "." << endl;
            std::this_thread::sleep_for(500ms);
            exit(0);
            break;
        case 4:
            mMode=false;
            break;
        }
    }

    void SelectOption(){
        switch(Option){
        case 1:
            Bev="Coffee"; Price=2.50;
            break;
        case 2:
            Bev="Black Tea"; Price=1.50;
            break;
        case 3:
            Bev="Green Tea"; Price=1.50;
            break;
        case 4:
            Bev="Cocoa"; Price=2.00;
            break;
        case 5:
            Bev="Hot Water"; Price=1.00;
            break;
        case 6:
            Bev="Chicken Soup"; Price=3.00;
            break;
        case 7:
            Bev="Tomato Soup"; Price=3.00;
            break;
        case 8:
            Bev="Borscht"; Price=3.00;
            break;
        case 9:
            Bev="Miso Soup"; Price=3.50;
            break;
        case 10:
            Bev="Onion Soup"; Price=3.00;
            break;
        case 11:
            mMode = true;
            break;
        }
     }
};

class Feeder{
public:
    string Type;
    int ID;

    void PrepDisp(){
        cout << endl << "Preparing " << Type << ".";
        std::this_thread::sleep_for(500ms);
        cout << ".";
        std::this_thread::sleep_for(500ms);
        cout << ".";
        std::this_thread::sleep_for(500ms);
        cout << ".";
        std::this_thread::sleep_for(500ms);
        cout << "." << endl;
        std::this_thread::sleep_for(500ms);
        cout << endl << Type << " is ready." << endl;
        std::this_thread::sleep_for(2000ms);
    }

    Feeder(string type, int id){
        Type = type;
        ID = id;
    }
};

class Soup:public Feeder {
public:
    bool SoySauce;
    char s;
    Soup(string type, int id):Feeder(type, id){}
    void AskForSauce(){
        soy_error:
        cout << endl << "Do you want to add soy sauce? (y/n): ";
        cin >> s;
        if (s !='y' && s != 'n'){
            cout << "Invalid Operator. Please try again." << endl;
            goto soy_error;
        }
    }
};

class Drink:public Feeder {
public:
    int ID;
    int sugar;
    char m;
    void MilkAndSugar(){
        if (ID == 1){
            milk_error:
            cout << endl << "Do you want to add milk? (y/n): ";
            cin >> m;
            if (m !='y' && m != 'n'){
                cout << "Invalid Operator. Please try again." << endl;
                goto milk_error;
            }
        }
        if (ID>=1 && ID <5){
            sugar_error:
            cout << endl << "Set amount of sugar you want (0-6): ";
            cin >> sugar;
            if (sugar<0 || sugar>6){
                cout << "Invalid Operator. Please try again." << endl;
                goto sugar_error;
            }
        }
    }
    Drink(string type, int id):Feeder(type, id){
        ID=id;
    }
};

class Display{
public:
    int Option;
    double Price;
    string Bev;

    void Start(){
        cout << "Vending Machine is starting .";
        std::this_thread::sleep_for(500ms);
        cout << ".";
        std::this_thread::sleep_for(500ms);
        cout << "." << endl;
        std::this_thread::sleep_for(500ms);
    }


    void WhichItem(){
        cout << " " << endl;
        cout << "Available options:" << endl;
        cout << " 1. Coffee          2.50$ " << endl;
        cout << " 2. Black Tea       1.50$ " << endl;
        cout << " 3. Green Tea       1.50$ " << endl;
        cout << " 4. Cocoa           2.00$ " << endl;
        cout << " 5. Hot Water       1.00$ " << endl;
        cout << " 6. Chicken Soup    3.00$ " << endl;
        cout << " 7. Tomato Soup     3.00$ " << endl;
        cout << " 8. Borscht         3.00$ " << endl;
        cout << " 9. Miso Soup       3.50$ " << endl;
        cout << "10. Onion Soup      3.00$ " << endl;
        cout << "11. Maintenance mode      " << endl;
        cout << " " << endl;
        option_error:
        cout << "Pick an option: ";
        cin >> Option;
        if (Option <= 0 || Option>11){
           cout << "Invalid Operator. Please try again." << endl;
           goto option_error;
        }
    }
};

int main()
{
    Display display1;
    Controller controller1;

    //Starting program
    display1.Start();
    start:
    display1.WhichItem();

    //Transfer selection
    controller1.Option = display1.Option;
    controller1.SelectOption();
    if (controller1.mMode){
        controller1.MaintenanceMenu();
        controller1.SelectMoption();
        goto start;
    }
    display1.Bev=controller1.Bev;
    display1.Price=controller1.Price;

    controller1.PaymentProcessing();
    if (controller1.PayOK){
        if (controller1.Option<=5){
            Drink Item1(controller1.Bev,controller1.Option);
            Item1.MilkAndSugar();
            Item1.PrepDisp();

        }else{
            Soup Item2(controller1.Bev,controller1.Option);
            Item2.AskForSauce();
            Item2.PrepDisp();
        }
    }
    goto start;
    return 0;
}
