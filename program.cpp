#include<iostream>
#include<fstream>
#include<iomanip>
#include<string.h>
int get_file_emp();
using namespace std;


class employee
{

public:
    int empid;
    char ename[50];
    char designation[50];
    float salary;
    int holidays_allowed;
    friend void search();
    friend void remove_employee();
public:
    void accept()
    {

        cout<<endl<<"Enter emp ID: ";
        cin>>empid;
        cout<<endl<<"Enter Ename ";
        cin>>ename;
        cout<<endl<<"Enter Designation";
        cin>>designation;
         cout<<endl<<"Enter Salary";
        cin>>salary;
         cout<<endl<<"Enter Holidays_Allowed";
        cin>>holidays_allowed;
    }
    void show_data()
    {

        cout<<endl;
        cout<<setw(12);
        cout<<empid;
         cout<<setw(50);
        cout<<ename;
         cout<<setw(25);
        cout<<designation;
         cout<<setw(10);
        cout<<salary;
         cout<<setw(10);
        cout<<holidays_allowed;
    }
}empobj;

class salary_disburse
{
private:
    int empid;
    char name[50];
    char month[50];
    char year[50];
    char date[15];
    int holidays;
    float amount_given;
    friend void show_salary();
    friend void show_amount();
public:
    void display()
    {
        cout<<endl<<setw(15);
        cout<<empid;
        cout<<setw(20);
        cout<<month;
        cout<<setw(20);
        cout<<year;
        cout<<setw(30);
        cout<<date;
        cout<<setw(10);
        cout<<holidays;
        cout<<setw(20);
        cout<<amount_given;
    }
    void  new_salary()
    {
        cout<<endl<<"Enter empid";
        cin>>empid;
        int p=get_file_emp();
        int flag=0;
        fstream rd;
        rd.open("employees.txt",ios::in);
        for(int i=1;i<=p;i++)
        {
            rd.read((char*)&empobj,sizeof(empobj));
            if(empobj.empid==empid)
            {
                cout<<endl<<"-----------------------------------Employee Details------------------------------------------";
                empobj.show_data();
                flag=1;
                cout<<endl<<"----------------------------------------------------------------------------------------------";
                break;
            }
        }
        if(flag==1)
        {
            cout<<endl<<"Employee ID Okay";


            cout<<endl<<"Enter Month";
            cin>>month;
            cout<<endl<<"Enter Year";
            cin>>year;
            cout<<endl<<"Enter Date of Salary";
            cin>>date;
            cout<<endl<<"Enter Holidays taken";
            cin>>holidays;

            if(holidays>empobj.holidays_allowed)
            {
                int diff=holidays-empobj.holidays_allowed;
                float perday_salary=empobj.salary/30;
                amount_given=perday_salary*(30-diff);

            }
            else
            {
                amount_given=empobj.salary;
            }
            cout<<endl<<"Net Salary to be disbursed "<<amount_given;
        }
        else
        {
            cout<<endl<<"Employee ID not Okay";
        }
    }

}salobj;
int get_file_emp()
{
    fstream rd;
    rd.open("employees.txt",ios::in);
    rd.seekg(0,ios::end);
    int p=rd.tellg()/sizeof(empobj);
    rd.close();
    return p;
}
void  add_employee()
{
    int empid;
    cout<<endl<<"Enter employee id ";
    cin>>empid;
    int x=0;
    fstream rd;
    rd.open("employees.txt",ios::in);
    rd.seekg(0,ios::end);
    int p=rd.tellg()/sizeof(empobj);
    rd.seekg(0,ios::beg);
    for(int i=1 ;i<=p ;i++)
    {
        rd.read((char *)&empobj,sizeof(empobj));
        if(empobj.empid==empid)
        {
            cout<<endl<<"Sorry,this ID has already been taken ";
            x=1;
            break;
        }

    }
    if(x==0)
    {
            cout<<endl<<"It's new id ,please enter the ID ";
            empobj.accept();
            fstream wr;
            wr.open("employees.txt",ios::app);
            wr.write((char*)&empobj,sizeof(empobj));
            wr.close();
            cout<<endl<<"Object created Successfully";

    }
    rd.close();
}
void display()
{

    fstream rd;
    rd.open("employees.txt",ios::in);
    rd.seekg(0,ios::end);
    int p=rd.tellg()/sizeof(empobj);
    rd.seekg(0,ios::beg);
     cout<<endl;
        cout<<setw(12);
        cout<<"Empid";
         cout<<setw(50);
        cout<<"Ename";
         cout<<setw(25);
        cout<<"Designation";
         cout<<setw(10);
        cout<<"Salary";
         cout<<setw(20);
        cout<<"Hoildays_allowed";
        cout<<endl<<"----------------------------------------------------------------------------------------------------------";
    for(int i=1 ;i<=p ;i++)
    {

        rd.read((char*)&empobj,sizeof(empobj));
        empobj.show_data();

    }
    rd.close();
    cout<<endl<<"----------------------------------------------------------------------------------------------------------";
}
void search()
{

    int eid;
    cout<<endl<<"Enter Employee ID ";
    cin>>eid;
    int count=get_file_emp();
    fstream rd;
    rd.open("employees.txt",ios::in);
    cout<<endl;
        cout<<setw(12);
        cout<<"Empid";
         cout<<setw(50);
        cout<<"Ename";
         cout<<setw(25);
        cout<<"Designation";
         cout<<setw(10);
        cout<<"Salary";
         cout<<setw(20);
        cout<<"Hoildays_allowed";
     cout<<endl<<"----------------------------------------------------------------------------------------------------------";
    for(int i=1;i<=count;i++)
    {

        rd.read((char*)&empobj,sizeof(empobj));
        if(empobj.empid==eid)
        {
            empobj.show_data();
        }
    }
     cout<<endl<<"----------------------------------------------------------------------------------------------------------";
}
void remove_employee()
{
    int eid;
    cout<<endl<<"Enter Employee ID to be removed";
    cin>>eid;
    int count=get_file_emp();
    fstream rd,wr;
    rd.open("employees.txt",ios::in);
    wr.open("temp.txt",ios::out);
    for(int i=1; i<=count; i++)
    {
        rd.read((char*)&empobj,sizeof(empobj));
        if(empobj.empid==eid)
        {
            cout<<endl<<"Object Removed";

        }
        else
        {
            wr.write((char*)&empobj,sizeof(empobj));
        }
    }
    wr.close();
    rd.close();
    remove("employees.txt");
    rename("temp.txt","employees.txt");
}
void give_salary()
{
    fstream wr;
    wr.open("salary.txt",ios::app);
    salobj.new_salary();
    wr.write((char*)&salobj,sizeof(salobj));
    cout<<endl<<"Salary Disbursed Successfully ";
}
void show_salary()
{
    char month[30],year[10];
    cout<<endl<<"Enter Month";
    cin>>month;
    cout<<endl<<"Enter Year";
    cin>>year;

    fstream rd;
    rd.open("salary.txt",ios::in);
    rd.seekg(0,ios::end);
    int size=rd.tellg()/sizeof(salobj);
    rd.seekg(0,ios::beg);

        cout<<endl<<setw(15);
        cout<<"Employee ID";
        cout<<setw(20);
        cout<<"Month";
        cout<<setw(20);
        cout<<"Year";
        cout<<setw(30);
        cout<<"Date";
        cout<<setw(10);
        cout<<"Holidays";
        cout<<setw(20);
        cout<<"Salary Given";
        cout<<endl<<"---------------------------------------------------------------------------------------------------------------------";
    for(int i=1 ;i<=size;i++)
    {
        rd.read((char*)&salobj,sizeof(salobj));
        if(strcmp(salobj.month,month)==0 && strcmp(salobj.year,year)==0)
        {
            salobj.display();
        }
    }
        cout<<endl<<"----------------------------------------------------------------------------------------------------------------------";
}
void show_amount()
{
    int empid;
    cout<<endl<<"Enter Employee ID ";
    cin>>empid;
    fstream rd;
    rd.open("salary.txt",ios::in);
    rd.seekg(0,ios::end);
    int size=rd.tellg()/sizeof(salobj);
    rd.seekg(0,ios::beg);
    cout<<endl<<setw(15);
        cout<<"Employee ID";
        cout<<setw(20);

        cout<<"Month";
        cout<<setw(20);
        cout<<"Year";
        cout<<setw(30);
        cout<<"Date";
        cout<<setw(10);
        cout<<"Holidays";
        cout<<setw(20);
        cout<<"Salary Given";
        cout<<endl<<"---------------------------------------------------------------------------------------------------------------------";
    for(int i=1 ;i<=size ;i++)
    {
        rd.read((char*)&salobj,sizeof(salobj));
        if(salobj.empid==empid)
        {
            salobj.display();
        }
    }

}
void search_name()
{
    char name[50];
    cout<<endl<<"Enter the name ";
    cin>>name;
    fstream rd;
    rd.open("employees.txt",ios::in);
    rd.seekg(0,ios::end);
    int size=rd.tellg()/sizeof(empobj);
    rd.seekg(0,ios::beg);
    cout<<endl;
        cout<<setw(12);
        cout<<"Empid";
         cout<<setw(50);
        cout<<"Ename";
         cout<<setw(25);
        cout<<"Designation";
         cout<<setw(10);
        cout<<"Salary";
         cout<<setw(20);
        cout<<"Hoildays_allowed";
    cout<<endl<<"---------------------------------------------------------------------------------------------------------------------";
    for(int i=1 ;i<=size;i++)
    {
        rd.read((char*)&empobj,sizeof(empobj));
        if(strcmp(empobj.ename,name)==0)
        {
            empobj.show_data();
        }
    }
    cout<<endl<<"---------------------------------------------------------------------------------------------------------------------";
}

int main()
{
    while(1)
    {

        cout<<endl<<"Press 1 to Add New Employee";
        cout<<endl<<"Press 2 to View all Employees";
        cout<<endl<<"Press 3 to Search all employees";
        cout<<endl<<"Press 4 to Remove Employee";
        cout<<endl<<"Press 5 to Disburse Salary";
        cout<<endl<<"Press 6 to Check Monthly Salary Report";
        cout<<endl<<"Press 7 to show salary disbursed of employee";
        cout<<endl<<"Press 8 to search by name";
        cout<<endl<<"Press 9 to Exit";
        int choice;
        cout<<endl<<"Enter your Choice";
        cin>>choice;
        if(choice==1)
        {
            add_employee();
        }
        else if(choice==2)
        {
            display();
        }
        else if(choice ==3)
        {
            search();
        }
        else if(choice ==4)
        {
            remove_employee();
        }
        else if(choice ==5)
        {
            give_salary();
        }
        else if(choice==6)
        {
            show_salary();
        }
        else if(choice ==7)
        {
            show_amount();
        }
        else if(choice ==8)
        {
            search_name();
        }
        else
        {
                break;
        }


    }

}

