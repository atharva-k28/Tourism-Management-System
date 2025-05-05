#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
char adminf[] = "Trip.txt";
char userf[] = "Reservation.txt";

struct login
{
    string username;
    int pin;
};
struct login l[100] = {{"Harshada", 1234}, {"Parth", 1414}, {"Atharva", 3232}, {"Bhoomi", 9898}, {"Anish", 9897}, {"Admin1", 9998}, {"Admin2", 8898}};

struct tour
{
    char ad_place[20], ad_code[20], ad_country[20], ad_days[20], ad_prices[20];
    char us_phone[20], us_name[20], us_people[20], us_date[20], us_status[20], us_dcode[20];
};

class Tourist
{
public:
    int verify_username(string name)
    {
        try
        {
            for (int i = 0; i < 100; i++)
            {
                if (l[i].username == name)
                {
                    return i;
                }
            }
            throw name;
        }
        catch (string)
        {
            // cout << "Invalid Username: " << name << endl;
            return -1;
        }
    }

    int verify_pin(int pin_check, int index)
    {
        try
        {
            if (index >= 0 && l[index].pin == pin_check)
            {
                return index;
            }
            throw pin_check;
        }
        catch (int)
        {
            // cout << "Invalid PIN: " << pin_check << endl;
            return -1;
        }
    }
};

class admin : public Tourist
{
public:
    void log_in();
    void ad_pack(tour r);
    tour ad_unpack(char a[]);
    void ad_writedata();
    void ad_display();
    void ad_modify();
};

class user : public Tourist
{
private:
    static int next_index;

public:
    void sign_in();
    void login();
    void us_pack(tour r);
    tour us_unpack(char a[]);
    void us_writedata();
    void us_display();
    void us_search();
    void us_modify();
};

// ADMIN PANEL FUNCTIONS
void admin::log_in()
{
    int a;
    int pass;
    string n;
    int attempts = 1;
    while (true)
    {
        if (attempts <= 3)
        {
            cout << "Enter username" << endl;
            cin >> n;
            a = verify_username(n);
            if (a >= 0)
            {
                cout << "Enter PIN" << endl;
                cin >> pass;
                if (verify_pin(pass, a) >= 0)
                {
                    cout << "Admin login successfully\n"
                         << endl;
                    return;
                }
                else
                {
                    cout << "Incorrect Pin" << endl;
                }
            }
            else
            {
                cout << "Incorret Username:" << endl;
            }
            attempts++;
        }
        else
        {
            cout << "Maximum Attempts Reached.\nExiting Program.\n"
                 << endl;
            exit(0);
        }
    }
}

void admin::ad_pack(tour r)
{
    fstream fp;
    fp.open(adminf, ios::out | ios::app);
    if (!fp)
    {
        cout << "\nCannot open file";
        exit(0);
    }

    char buff[100];
    strcpy(buff, r.ad_code);
    strcat(buff, "|");
    strcat(buff, r.ad_place);
    strcat(buff, "|");
    strcat(buff, r.ad_country);
    strcat(buff, "|");
    strcat(buff, r.ad_days);
    strcat(buff, "|");
    strcat(buff, r.ad_prices);
    strcat(buff, "|");
    fp << buff << endl;
    fp.close();
}

tour admin::ad_unpack(char buff[])
{
    tour r;
    int i = 0, j = 0;
    while (buff[j] != '|')
        r.ad_code[i++] = buff[j++];
    r.ad_code[i] = '\0';
    i = 0;
    j++;

    while (buff[j] != '|')
        r.ad_place[i++] = buff[j++];
    r.ad_place[i] = '\0';
    i = 0;
    j++;

    while (buff[j] != '|')
        r.ad_country[i++] = buff[j++];
    r.ad_country[i] = '\0';
    i = 0;
    j++;

    while (buff[j] != '|')
        r.ad_days[i++] = buff[j++];
    r.ad_days[i] = '\0';
    i = 0;
    j++;

    while (buff[j] != '|')
        r.ad_prices[i++] = buff[j++];
    r.ad_prices[i] = '\0';

    return r;
}

void admin::ad_writedata()
{
    tour s;
    cout << "Enter the Destination Code: D-";
    cin >> s.ad_code;
    cout << "Enter the Destination Place: ";
    cin.ignore();
    cin.getline(s.ad_place, 20);
    cout << "Enter the Country of the Destination: ";
    cin.getline(s.ad_country, 20);
    cout << "Enter the Number of Days of the Trip: ";
    cin >> s.ad_days;
    cout << "Enter the Cost of the Trip: ";
    cin >> s.ad_prices;

    ad_pack(s);
    cout << "New trip added successfully!\n";
}

void admin::ad_display()
{
    fstream fp;
    char buff[100];
    tour r;
    fp.open(adminf, ios::in);
    if (!fp)
    {
        cout << "\nCannot open file";
        exit(0);
    }

    cout << "-------------------------------------------------------------------------------------------------\n";
    cout << "Sr No.\t\tDEST. CODE\tPLACE\t\tCOUNTRY\t\tDAYS\t\tPRICES\n";
    cout << "-------------------------------------------------------------------------------------------------\n";
    int c = 1;

    while (fp.getline(buff, 100))
    {
        r = ad_unpack(buff);
        cout << c++ << "\t\t" << "D-" << r.ad_code << "\t\t" << r.ad_place << "\t\t" << r.ad_country
             << "\t\t" << r.ad_days << "\t\t" << r.ad_prices << endl;
    }
    fp.close();
}

void admin::ad_modify()
{
    fstream fp;
    char ad_code[15], buff[100];
    int i, j, ch;
    tour s[100];

    fp.open(adminf, ios::in);
    if (!fp)
    {
        cout << "\nCannot open file";
        exit(0);
    }

    cout << "\nEnter the Destination Code to be Modified: D-";
    cin >> ad_code;
    i = 0;

    while (fp.getline(buff, 100))
    {
        s[i++] = ad_unpack(buff);
    }
    fp.close();

    for (j = 0; j < i; j++)
    {
        if (strcmp(s[j].ad_code, ad_code) == 0)
        {
            cout << "VALUES OF THE TRIP\n";
            cout << "\nDestination Code: " << s[j].ad_code;
            cout << "\nDestination Place: " << s[j].ad_place;
            cout << "\nDestination Country: " << s[j].ad_country;
            cout << "\nNo of days of Trip: " << s[j].ad_days;
            cout << "\nTotal Cost of the Trip: " << s[j].ad_prices;
            cout << "\n\nWhat you want to update:";
            cout << "\n1. Change Destination ";
            cout << "\n2. Change Number of days of trip";
            cout << "\n3. Change Cost of trip\n";
            cin >> ch;

            switch (ch)
            {
            case 1:
                cout << "New Destination Place: ";
                cin.ignore();
                cin.getline(s[j].ad_place, 20);
                cout << "New Country: ";
                cin.getline(s[j].ad_country, 20);
                break;
            case 2:
                cout << "New Number of Days: ";
                cin >> s[j].ad_days;
                break;
            case 3:
                cout << "New Total Cost: ";
                cin >> s[j].ad_prices;
                break;
            }
            break;
        }
    }

    if (j == i)
    {
        cout << "\nTrip not found!";
        return;
    }

    fp.open(adminf, ios::out | ios::trunc);
    if (!fp)
    {
        cout << "\nCannot open file";
        exit(0);
    }

    for (j = 0; j < i; j++)
    {
        ad_pack(s[j]);
    }

    fp.close();
    cout << "\nTrip updated successfully!\n";
}

// USER PANEL FUNCTIONS

void user::sign_in()
{
    if (next_index >= 100)
    {
        cout << "User limit reached. Cannot sign in more users." << endl;
        return;
    }

    cout << "Create a username: " << endl;
    cin >> l[next_index].username;

    cout << "Enter a suitable PIN: " << endl;
    cin >> l[next_index].pin;

    next_index++;
    cout << "User signed in successfully" << endl;
}

void user::login()
{
    string name;
    int pin_check, a;
    int attempts = 1;

    while (true)
    {
        if (attempts <= 3)
        {
            cout << "Enter the username: ";
            cin >> name;
            a = verify_username(name);
            if (a >= 0)
            {
                cout << "Enter the PIN: ";
                cin >> pin_check;
                if (verify_pin(pin_check, a) >= 0)
                {
                    cout << "Login successful!" << endl;
                    return;
                }
                else
                {
                    cout << "\nIncorrect PIN. Please try again.\n"
                         << endl;
                }
            }
            else
            {
                cout << "\nIncorrect Username. Please try again.\n"
                     << endl;
            }
            attempts++;
        }
        else
        {
            cout << "Maximum Attempts Reached.\nExiting Program.\n"
                 << endl;
            exit(0);
        }
    }
}

int user::next_index = 6;

void user::us_pack(tour r)
{
    fstream fp;
    fp.open(userf, ios::out | ios::app);
    if (!fp)
    {
        cout << "\nFile Not Found";
        exit(0);
    }

    char buff[100];
    strcpy(buff, r.us_name);
    strcat(buff, "|");
    strcat(buff, r.us_phone);
    strcat(buff, "|");
    strcat(buff, r.us_people);
    strcat(buff, "|");
    strcat(buff, r.us_dcode);
    strcat(buff, "|");
    strcat(buff, r.us_date);
    strcat(buff, "|");
    strcat(buff, r.us_status);
    strcat(buff, "|");
    fp << buff << endl;
    fp.close();
}

tour user::us_unpack(char buff[])
{
    tour r;
    int i = 0, j = 0;

    while (buff[j] != '|')
        r.us_name[i++] = buff[j++];
    r.us_name[i] = '\0';
    i = 0;
    j++;

    while (buff[j] != '|')
        r.us_phone[i++] = buff[j++];
    r.us_phone[i] = '\0';
    i = 0;
    j++;

    while (buff[j] != '|')
        r.us_people[i++] = buff[j++];
    r.us_people[i] = '\0';
    i = 0;
    j++;

    while (buff[j] != '|')
        r.us_dcode[i++] = buff[j++];
    r.us_dcode[i] = '\0';
    i = 0;
    j++;

    while (buff[j] != '|')
        r.us_date[i++] = buff[j++];
    r.us_date[i] = '\0';
    i = 0;
    j++;

    while (buff[j] != '|')
        r.us_status[i++] = buff[j++];
    r.us_status[i] = '\0';

    return r;
}

void user::us_writedata()
{
    tour r;
    cout << "\n\nEnter Your Name: ";
    cin.ignore();
    cin.getline(r.us_name, 20);
    cout << "Enter Your Contact No.: ";
    cin >> r.us_phone;
    cout << "Enter Number of Tourists: ";
    cin >> r.us_people;
    cout << "Enter the Destination Code: D-";
    cin >> r.us_dcode;
    cout << "Enter Date of Journey (DD/MM/YY): ";
    cin >> r.us_date;
    cout << "\nEnter 'Confirm' to confirm the reservation: ";
    cin >> r.us_status;

    us_pack(r);
    cout << "\nReservation made successfully!\n";
}

void user::us_display()
{
    fstream fp;
    char buff[100];
    tour r;
    fp.open(userf, ios::in);
    if (!fp)
    {
        cout << "\nFile Not Found";
        exit(0);
    }

    cout << "--------------------------------------------------------------------------------------------\n";
    cout << "Sr No.\t\tNAME\t\t\tPHONE\t\t\tPEOPLE\t\tSTATUS\n";
    cout << "--------------------------------------------------------------------------------------------\n";

    int c = 1;

    while (fp.getline(buff, 100))
    {
        r = us_unpack(buff);
        cout << c++ << "\t\t" << r.us_name << "\t\t" << r.us_phone << "\t\t" << r.us_people
             << "\t\t" << r.us_status << endl;
    }
    fp.close();
}

void user::us_search()
{
    fstream fp;
    char us_phone[20], buff[100];
    tour r;
    fp.open(userf, ios::in);
    if (!fp)
    {
        cout << "\nFile Not Found";
        exit(0);
    }

    cout << "\nEnter the Contact No. of the Reservation: " << endl;
    ;
    cin >> us_phone;

    while (fp.getline(buff, 100))
    {
        r = us_unpack(buff);
        if (strcmp(r.us_phone, us_phone) == 0)
        {
            cout << "\nReservation found!\n";
            cout << "\nName: " << r.us_name;
            cout << "\nDestination Code: " << r.us_dcode;
            cout << "\nJourney Date: " << r.us_date;
            cout << "\nNo. of Tourists: " << r.us_people;
            cout << "\nStatus: " << r.us_status << endl;
            fp.close();
            return;
        }
    }

    cout << "\nReservation not found!\n";
    fp.close();
}

void user::us_modify()
{
    fstream fp;
    char us_phone[20], buff[100];
    tour r[100];
    int i = 0, j, ch;

    fp.open(userf, ios::in);
    if (!fp)
    {
        cout << "\nFile Not Found" << endl;
        exit(0);
    }

    cout << "\nEnter the Contact No. of the Reservation to be Canceled: ";
    cin >> us_phone;

    while (fp.getline(buff, 100))
    {
        r[i++] = us_unpack(buff);
    }
    fp.close();

    for (j = 0; j < i; j++)
    {
        if (strcmp(r[j].us_phone, us_phone) == 0)
        {
            cout << "\nCurrent Status: " << r[j].us_status;
            cout << "\nEnter 'Cancel' to cancel the reservation: ";
            cin >> r[j].us_status;
            break;
        }
    }

    if (j == i)
    {
        cout << "\nReservation not found!";
        return;
    }

    fp.open(userf, ios::out | ios::trunc);
    if (!fp)
    {
        cout << "\nFile Not Found";
        exit(0);
    }

    for (j = 0; j < i; j++)
    {
        us_pack(r[j]);
    }

    fp.close();
    cout << "\nReservation cancelled successfully!\n";
}

int main()
{
    cout << "\t\t WELCOME TO TOURIST RESERVATION SYSTEM\n\n\n";
    cout << "Press Enter to continue\n";
    cin.get();

    int choice, ch1, ch2;
    admin ad;
    user us;

    while (true)
    {
    a:
        cout << "--------------------------------------------------------------------------------------------\n";
        cout << "					MENU						     \n";
        cout << "--------------------------------------------------------------------------------------------\n";
        cout << "1. ADMIN\n";
        cout << "2. USER\n";
        cout << "Enter any other key to exit\n\n";
        cout << "Enter Your Option: ";
        cin >> choice;
        switch (choice)
        {
        case 1: // Admin panel
            ad.log_in();

            cout << "WELCOME ADMIN\n";
            cout << "Enter your option:\n";
            cout << "1. New trips\n";
            cout << "2. Display Trips\n";
            cout << "3. Display Reservations\n";
            cout << "4. Update Trip\n";
            cout << "5. Go Back\n";
            cout << "Enter any other key to exit\n";

            while (true)
            {
                cout << "\nENTER YOUR CHOICE: ";
                cin >> ch1;
                switch (ch1)
                {
                case 1:
                    ad.ad_writedata();
                    break;
                case 2:
                    ad.ad_display();
                    break;
                case 3:
                    us.us_display();
                    break;
                case 4:
                    ad.ad_modify();
                    break;
                case 5:
                    goto a;
                    break;
                default:
                    cout << "Exiting Admin panel\n";
                    goto EXIT;
                }
            }
            break;

        case 2: // User panel
            int i;
            cout << "Press\n1.Sign-in\nAlready a user?\n2.Login " << endl;
            cin >> i;
            switch (i)
            {
            case 1:
                us.sign_in();
                break;
            case 2:
                us.login();
                break;
            default:
                cout << "invalid choice\n";
                break;
            }
            cout << "WELCOME USER\n";
            cout << "Enter your option:\n";
            cout << "1. New Reservation\n";
            cout << "2. Search Reservation\n";
            cout << "3. Cancel Reservation\n";
            cout << "4. Go Back\n";
            cout << "Enter any other key to exit\n";

            while (true)
            {
                cout << "\nENTER YOUR CHOICE: ";
                cin >> ch2;
                switch (ch2)
                {
                case 1:
                    cout << "Choose Your destination\n";
                    ad.ad_display();
                    us.us_writedata();
                    break;
                case 2:
                    us.us_search();
                    break;
                case 3:
                    us.us_modify();
                    break;
                case 4:
                    goto a;
                default:
                    cout << "Exiting User panel...\n";
                    goto EXIT;
                }
            }
            break;

        default:
            cout << "Exiting system...\n";
            goto EXIT;
        }
    }

EXIT:
    return 0;
}