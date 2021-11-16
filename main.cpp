#include <iostream>
#include <stdio.h>
#include <iterator>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <math.h>

using namespace std;


typedef vector<string> vector_string;
#define pb push_back
#define nn cout << "\n"
#define tt cout <<"\t"
#define dbg(x) cout<<#x<<" = "<<x<<endl
#define all(v) v.begin(), v.end()

void intro();
void instructions();
void ending();
void checking(long long int  arr[], long long int  size);
long long int  exp_to_minterms(long long int  sizes, string t);
vector_string generateGrayarr(long long int  n);
void printing_binary_string(long long int  num_to_convert_to_binary, long long int  var);
long long int  bin_to_int( string s);
void kmap_display( long long int  minterm[], long long int  var);
void invoking_one(long long int  type);
void invoking_two(long long int  arr[], long long int  size,long long int  n);
void invoking_three( long long int  arr[], long long int  size, long long int  n);
void star();


class solver
{
public:
    long long int  varis;
    string donts;
    long long int  data;
    solver(long long int  num) // constrcutor
    {
        varis = num;
        donts.append(num, '-');
    }

    vector_string variables();
    string binary_convertor(long long int  decimal);
    long long int  grey_code_check(string one, string two);
    bool check_present(vector_string one, string two);
    string compliments(string one, string two);
    vector_string minimization(vector_string min_terms);
    string get_answer(string ans);
    bool string_equal(string one, string two);
    bool vector_equal(vector_string one, vector_string two);
};

vector_string solver ::variables()
{
    vector_string v_m;
    string arguments[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
    long long int  i;
    for (i = 0; i < varis; i++)
    {
        v_m.pb(arguments[i]);
    }
    return v_m;
}
string solver ::binary_convertor(long long int  num)
{
    long long int  temp = num;
    string binary_s = "";
    if (temp == 0)
    {
        binary_s = "0";
    }
    else
    {
        while (temp > 0)
        {
            if (temp % 2 == 0)
            {
                binary_s = "0" + binary_s;
            }
            else
            {
                binary_s = "1" + binary_s;
            }
            temp = temp / 2;
        }
    }
    long long int  remainder = varis - binary_s.size();
    while (remainder > 0)
    {
        binary_s = "0" + binary_s;
        remainder--;
    }
    return binary_s;
}
long long int  solver ::grey_code_check(string one, string two)
{
    long long int  diff = 0;
    for (long long int  i = 0; i < two.size(); i++)
    {
        if (two[i] != one[i])
        {
            diff++;
        }
    }
    if (diff == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
bool solver ::check_present(vector_string one, string two)
{
    for (long long int  i = 0; i < one.size(); i++)
    {
        long long int  check = one[i].compare(two);
        if (check == 0)
        {
            return true;
        }
    }
    return false;
}
string solver ::compliments(string one, string two)
{
    string result = "";
    long long int  i = 0;
    while (i < one.length())
    {
        if (two[i] != one[i])
        {
            result = result + "-";
        }
        else
        {
            result = result + one[i];
        }
        i++;
    }
    return result;
}
vector_string solver ::minimization(vector_string min_terms)
{
    long long int  size;
    vector_string result;
    size = min_terms.size();
    long long int  *visited = new long long int [size];
    long long int  i = 0;
    while (i < size)
    {
        long long int  j = i;
        while (j < size)
        {
            long long int  one_bit_d = grey_code_check(min_terms[i], min_terms[j]);
            if (one_bit_d == 1)
            {
                visited[j] = 1;
                visited[i] = 1;
                string after_compliment = compliments(min_terms[i], min_terms[j]);
                if (!check_present(result, after_compliment))
                {
                    string pushing = compliments(min_terms[i], min_terms[j]);
                    result.pb(pushing);
                }
            }
            j++;
        }
        i++;
    }

    for (long long int  i = 0; i < size; i++)
    {
        if (visited[i] != 1 && !check_present(result, min_terms[i]))
        {
            result.pb(min_terms[i]);
        }
    }
    delete[] visited;
    return result;
}
string solver ::get_answer(string ans)
{
    string result = "";
    vector_string arguments = this->variables();
    if (ans == donts)
    {
        return "1";
    }

    for (long long int  i = 0; i < ans.length(); i++)
    {
        if (ans[i] != '-')
        {
            if (ans[i] == '1')
            {
                result = result + arguments[i];
            }
            else
            {
                result = result + arguments[i] + "\'";
            }
        }
    }
    return result;
}
bool solver ::string_equal(string one, string two)
{
    if (one.size() != two.size())
    {
        return false;
    }
    for (long long int  i = 0; i < one.size(); i++)
    {
        if (one[i] != two[i])
        {
            return false;
        }
    }
    return true;
}
bool solver ::vector_equal(vector_string one, vector_string two)
{
    if (one.size() != two.size())
    {
        return false;
    }
    sort(all(one));
    sort(all(two));
    for (long long int  i = 0; i < one.size(); i++)
    {
        if (one[i] != two[i])
        {
            return false;
        }
    }
    return true;
}


int  main()
{
    intro();
    instructions();

    bool check = false;
    do
    {
        long long int  number;
        cout << "\n Enter number of variables: ";
        cin >> number;
        if (number > 26 || number < 1)
        {
            cout << "Sorry, you have entered invalid no. of variables";
            cout << endl
                 << "Try Again!!" << endl;
            continue;
        }
        invoking_one(number);
        solver k_map(number);
        long long  int  power = 1>>number;
        long long  int  truth_table[power];
        for (long long int  j = 0; j < power; j++)
        {
            truth_table[j] = -1;
        }

        cout << "Press '1' for inputing SOP i.e. min terms." << endl;
        cout << "Press '2' for inputing POS i.e. max terms." << endl;
        cout << "Press '3' for inputing a boolean expression" << endl;
        long long int  choice;
        cin >> choice;

        long long int  num;
        long long int  x = 0;
        string s;
        switch (choice)
        {
        case 1:
            cout << "Enter min terms: ( Range : 0 - " << pow(2, number) - 1 << " )" << endl;
            cout << "Enter -1 for stoppping" << endl;
            do
            {
                cin >> num;
                if (num != -1)
                {
                    truth_table[num] = 1;
                }
            } while (num != -1);
            break;
        case 2:
            for (long long int  i = 0; i < power; i++)
            {
                truth_table[i] = 1;
            }
            cout << "Enter max terms: ( Range : 0 - " << pow(2, number) - 1 << " )" << endl;
            cout << "Enter -1 for stoppping" << endl;
            do
            {
                cin >> num;
                if (num != -1)
                    truth_table[num] = 0;
            } while (num != -1);
            break;
        case 3:
            cout << "Enter boolean expression terms one by one with atmost " << number;
            cout << " variables named as below\n";
            char i;
            cout << "< ";
            for (i = 'a'; i <= 'z' && x < number; i++)
            {
                cout << i << " ";
                x++;
            }
            cout << ">";
            cout << endl
                 << "enter -1 for stopping" << endl;
            do
            {
                cin >> s;
                if (s != "-1")
                {
                    long long int  h = exp_to_minterms(number, s);
                    truth_table[h] = 1;
                }
            } while (s != "-1");
            break;
        default:
            break;
        }

        invoking_two(truth_table, power, number);

        vector<string> minterms; // for storing expressions
        for (long long int  i = 0; i < power; i++)
        {
            if (truth_table[i] == 1)
            {
                minterms.pb(k_map.binary_convertor(i));
            }
        }
        // checking(truth_table , power);
        system("pause");

        sort(all(minterms));
        do
        {
            minterms = k_map.minimization(minterms);
            sort(all(minterms));
        } while (!k_map.vector_equal(minterms, k_map.minimization(minterms)));


        invoking_three(truth_table, power, number);
        cout << "Answer: " << endl;
        nn;
        long long int  j = 0;
        for (long long int  i = 0; i < minterms.size() - 1; i++)
        {
            cout << k_map.get_answer(minterms[i]);
            cout << "+";
            j++;
        }
        cout << k_map.get_answer(minterms[j]);
        nn;
        nn;
        system("pause");
        system("cls");


        invoking_three(truth_table, power, number);
        cout << "Answer: " << endl;
        long long int  i;
        for (i = 0; i < minterms.size() - 1; i++)
        cout << k_map.get_answer(minterms[i])<<"+";
        cout << k_map.get_answer(minterms[i]);
        nn;
        star();
        cout << "Enter (1) for displaying K- Map: ";
        long long int  kmap;
        cin >> kmap;
        if (kmap == 1)
        {
            cout << "Here is the Karnaugh Graph: ";
            nn;
            kmap_display(truth_table , number);
        }
        system("pause");
        system("cls");


        cout << "\nwanna do it again?" << endl
             << "Enter 'y' for Yes and 'n' for No: ";

        char pass;
        cin >> pass;
        if (pass == 'y')
        {
            check = true;
            system("cls");
        }
        else
        {
            check = false;
            system("cls");
        }
    } while (check);
    ending();
    return 0;
}
void intro()
{
    system("cls");
    cout << "\t\t\t\t Welcome to our CS203 Project - Logic Minimizer" << endl;
    cout << "\t\t\t\t **********************************************"<<endl<<endl;
    cout << "It's a c++ program to simplify Boolean expressions inspired by Karnaugh map.\n\nFunctionality:\n";
    cout << "This project takes the input of number of Boolean variables from the user. ";
    cout << "The user should enter the input either in form of min terms(SOP),";
    cout << "max terms(POS) or can also enter the Boolean expression itself.\n\n";
    // cout<<"The program will make the k map of the given the expression,";
    // cout<<" also the minimized form of the Boolean expression.\n";
    cout << endl;
    system("pause");
    system("cls");
}
long long int  exp_to_minterms(long long int  sizes, string t)
{
    long long int  sum = 0;
    long long int  k = sizes - 1;
    long long int  p = 0;
    for (long long int  j = 0; j < t.size(); j++)
    {
        if (t[j] == 97 + p && t[j + 1] != 39)
        {
            p++;
            sum = sum + pow(2, k);
            k--;
        }
        if (t[j] == 97 + p && t[j + 1] == 39)
        {
            p++;
            k--;
        }
    }
    return sum;
}
void ending()
{
    system("pause");
    system("cls");
    cout << "\t\t-----***You are welcome***-----";
    cout << endl
         << "Created by" << endl;
    cout << "\t\t 2020csb1141 \t Vinay Kumar" << endl;
    cout << "\t\t 2020csb1143 \t Yadwinder Singh" << endl;
}
void instructions()
{
    cout << "Hi There, \nHere some info regarding inputing data: ";
    cout << endl;
    cout << endl;
    cout<<"Solving Steps: ";
    cout << endl;
    cout << "====>\tEnter number of variables";
    cout << endl;
    cout << endl;
    cout << "\t\tPick one choice of inputing i.e. ===>";
    cout << endl;
    cout << " Press '1' for inputing SOP i.e. min terms." << endl;
    cout << " Press '2' for inputing POS i.e. max terms." << endl;
    cout << " Press '3' for inputing a boolean expression" << endl;
    cout << endl;
    cout << " if pressed '1', then input min terms and enter '-1' for stopping ";
    cout << endl;
    cout << " if pressed '2', then input max terms and enter '-1' for stopping ";
    cout << endl;
    cout << " if pressed '3', then input each expression one by one and enter '-1' for stopping ";
    cout << endl;
    cout << endl;
    cout << "You are ready to go";
    cout << endl;
    cout << endl;
    cout << endl;
    system("pause");
    system("cls");
}
void checking(long long int  arr[], long long int  size)
{
    cout<<"min terms stored are: ";
    for (long long int  y = 0; y < size; y++)
    {
        if (arr[y] == 1)
            cout << y << " ";
    }
    cout<<endl;
}
void invoking_one (long long int  type)
{
    system("cls");
    cout<<"Your Input:";
    cout<<endl;
    cout<<"\tNo. of variables: "<<type;
    cout<<endl;
    cout << "**********************************************";
    cout << "*********************" << endl;
    cout<<endl;
}
void invoking_two (long long int  arr[] , long long int  size , long long int  n)
{
    system("cls");
    cout<<"Your Input:";
    cout<<endl;
    cout<<"\tNo. of variables: "<<n;
    cout<<endl;
    cout<<"Min Terms: ";
    for(long long int  i = 0; i<size; i++)
    {
        if(arr[i] == 1)
        {
            cout<<i<<" ";
        }
    }
    cout<<endl;
    cout << "**********************************************";
    cout << "***********************" << endl;
    cout<<endl;
}
void invoking_three(long long int  arr[], long long int  size, long long int  n)
{
    system("cls");
    cout << "Your Input:";
    cout << endl;
    cout << "\tNo. of variables: " << n;
    cout << endl;
    cout << "\tMin Terms: ";
    for (long long int  i = 0; i < size; i++)
    {
        if (arr[i] == 1)
        {
            cout << i << " ";
        }
    }
    nn;
    cout << "**********************************************";
    cout << "***********************" << endl;
    nn;
}
void star()
{
    cout << "**********************************************";
    cout << "***********************";
    nn;nn;
}

vector_string generateGrayarr(long long int  variables_number)
{

    vector<string> grey_code_vector;
    if(variables_number<=1)
    {
        grey_code_vector.pb(" ");
        return grey_code_vector;
    }
    grey_code_vector.pb("0");
    grey_code_vector.pb("1");
    long long int  i, j;
    for (i = 2; i < (1 << variables_number); i = i << 1)
    {
        for (j = i - 1; j >= 0; j--)
        {
            grey_code_vector.pb(grey_code_vector[j]);
        }
        for (j = 0; j < i; j++)
        {
            grey_code_vector[j] = "0" + grey_code_vector[j];
        }
        for (j = i; j < 2 * i; j++)
        {
            grey_code_vector[j] = "1" + grey_code_vector[j];
        }
    }
    return grey_code_vector;
}
long long int  bin_to_int( string s)
{
    long long int  sum = 0;
    for(long long int  i=0; i<s.size(); i++)
    {
        if(s[i] == '0')
        {
            sum = sum*2;
        }
        else
        {
            sum = sum*2 +1;
        }
    }
    return sum;
}
void kmap_display( long long int  minterm[], long long int  var)
{
    long long int  fi = var/2 + var%2;
    long long int  se = var/2;
    dbg(fi);
    dbg(se);
    string vari[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
    cout<<"Horizontal side variables: ";
    long long int  i;
    for( i=0; i<fi; i++)
    {
        cout<<vari[i]<<" ";
    }
    nn;
    long long int  x = i;
    cout<<"Vertical Side variables: ";
    for(long long int  j = 0; j<se; j++)
    {
        cout<<vari[x]<<" ";
        x++;
    }
    nn;
    tt;
    vector_string hori = generateGrayarr(fi);
    for( i=0; i<hori.size(); i++)
    {
        cout<<hori[i];
        tt;
    }
    nn;
    vector_string veri = generateGrayarr(se);
    for(long long int  x=0; x<veri.size(); x++)
    {
        cout<<veri[x];
        tt;
        for(long long int  y = 0; y<hori.size(); y++)
        {
            long long int  index = bin_to_int(hori[y] + veri[x]);
            if(minterm[index] == 1)
            {
                cout<<"X"<<"("<<index<<")";
            }
            else
            {
                cout<<".";
            }
            tt;
        }
        nn;
    }

}


