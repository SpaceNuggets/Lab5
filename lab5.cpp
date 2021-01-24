#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>

using namespace std;
class Macierz{
    public:
        Macierz operator+(Macierz &other);
        Macierz operator-(Macierz &other);
        Macierz operator*(Macierz &other);
        string operator[](int);
        
       
        int** mm;
        int a,b;
        Macierz(int x,int y){
            a=x;
            b=y; 
            mm = new int*[x];
            for(int i = 0; i <x; ++i)
                mm[i] = new int[y];       
            for(int i=0;i<x;i++){
                for(int j=0;j<y;j++){
                    mm[i][j]=0;
                }
            }      
        }
        Macierz(int x){
            a=x;
            b=x;
            mm = new int*[x];
            for(int i = 0; i <x; ++i)
                mm[i] = new int[x];
            for(int i=0;i<x;i++){
                for(int j=0;j<x;j++){
                    mm[i][j]=0;
                }
            }    
        }
        Macierz(std::string filename, std::string path){
            string cokol=path+"\\"+filename;
            ifstream filel(cokol);
            string rows, columns,co;
            getline(filel,columns, ' ');
            getline(filel,rows,'\n');
            a=stoi(rows);
            b=stoi(columns);
            mm = new int*[a];
            for(int i = 0; i <a; ++i)
                mm[i] = new int[b]; 
            for(int i=0;i<a;i++){
                for(int j=0;j<b;j++){
                    getline(filel,co,' ');
                     mm[i][j]=stoi(co);
                 }
                    
            }    
            filel.close();
        }
        void set(int n,int m, int val){
             if(n>=a||m>=b){
                cout <<"Nie istnieje taka pozcyja\n";
                return;
            }
            mm[n][m]=val;
        }
        int get(int n,int m){
            if(n>=a||m>=b){
                cout <<"Nie istnieje taka pozcyja\n";
                return NULL;
            }
            return mm[n][m];
        }
        Macierz add(Macierz m2){
            if(a!=m2.rows()||b!=m2.cols()){
                cout <<"Macierze maja rozne rozmiary\n";
                return NULL;
            }
            Macierz m3(m2.rows(),m2.cols());
             for(int i=0;i<a;i++){
                for(int j=0;j<b;j++){
                    m3.set(i,j,mm[i][j]+m2.get(i,j));
                }
            }   
            return m3;
        }
        Macierz subtract(Macierz m2){
            if(a!=m2.rows()||b!=m2.cols()){
                cout <<"Macierze maja rozne rozmiary\n";
                return NULL;
            }
            Macierz m3(m2.rows(),m2.cols());
             for(int i=0;i<a;i++){
                for(int j=0;j<b;j++){
                    m3.set(i,j,mm[i][j]-m2.get(i,j));
                }
            }   
            return m3;
        }
        Macierz multiply(Macierz m2){
            if(a!=m2.rows()||b!=m2.cols()){
                cout <<"Macierze maja rozne rozmiary\n";
                return NULL;
            }
            Macierz m3(m2.rows(),m2.cols());
             for(int i=0;i<a;i++){
                for(int j=0;j<b;j++){
                    m3.set(i,j,mm[i][j]*m2.get(i,j));
                }
            }   
            return m3;
        }
        int cols(){
            return b;
        }
        int rows(){
            return a;
        }
        void print(){
             for(int i=0;i<a;i++){
                for(int j=0;j<b;j++){
                   cout<<mm[i][j]<<" ";
                }
                cout << endl;
            }   
        }
        void store(std::string filename, std::string path){
            string cokol=path+"\\"+filename;
            ofstream filel(cokol);
            filel<<b<<" "<<a<<endl;
            for(int i=0;i<a;i++){
                for(int j=0;j<b;j++){
                   filel<<mm[i][j]<<" ";
                }
                filel << endl;
            }   
            filel.close();
        }
        bool operator==(Macierz &other){//przeciazanie operatora rownosci
            if(a!=other.rows()||b!=other.cols()){
                cout <<"Macierze maja rozne rozmiary\n";
                return 0;
            }
            for(int i=0;i<a;i++){
                for(int j=0;j<b;j++){
                    if(mm[i][j]==other.get(i,j))
                        continue;
                    else
                    {
                        return 0;
                    }
            
                }
             }   
             return 1;
        }
        friend ostream & operator<<(ostream &wyjscie, Macierz &other){//przeciazanie operatora wyjscia
            for(int i=0;i<other.rows();i++){
                for(int j=0;j<other.cols();j++){
                   wyjscie <<other.get(i,j)<<" ";
                }
                wyjscie << endl;
            }   
            return wyjscie;

        }

};
Macierz Macierz::operator+( Macierz &other){//przeciazanie operatora dodawania
    if(a!=other.rows()||b!=other.cols()){
        cout <<"Macierze maja rozne rozmiary\n";
        return NULL;
    }
    Macierz m3(other.rows(),other.cols());
    for(int i=0;i<a;i++){
        for(int j=0;j<b;j++){
            m3.set(i,j,mm[i][j]+other.get(i,j));
        }
    }   
    return m3;  
}
Macierz Macierz::operator-( Macierz &other){//przeciazanie operatora odejmowania
    if(a!=other.rows()||b!=other.cols()){
        cout <<"Macierze maja rozne rozmiary\n";
        return NULL;
    }
    Macierz m3(other.rows(),other.cols());
    for(int i=0;i<a;i++){
        for(int j=0;j<b;j++){
            m3.set(i,j,mm[i][j]-other.get(i,j));
        }
    }   
    return m3;
}
Macierz Macierz::operator*( Macierz &other){//przeciazanie operatora mnozenia
    if(a!=other.rows()||b!=other.cols()){
        cout <<"Macierze maja rozne rozmiary\n";
        return NULL;
    }
    Macierz m3(other.rows(),other.cols());
    for(int i=0;i<a;i++){
        for(int j=0;j<b;j++){
            m3.set(i,j,mm[i][j]*other.get(i,j));
        }
    }   
    return m3;
}
string Macierz::operator[](int index){//przeciazanie operatora []
    string returnValue="";
    for(int i=0;i<b;i++){
        returnValue+=to_string(mm[index][i])+ " ";
    }
    return returnValue;
}



int main()
{
   Macierz hello(5);
   Macierz hello2(5,5);
   for(int i=0;i<hello.rows();i++){//creating first array
        for(int j=0;j<hello.cols();j++){
            hello.set(i,j,1);
        }          
    }  
    cout<<"Macierz 1 wyglada nastepujaco:\n";
    hello.print();
   for(int i=0;i<hello2.rows();i++){//creating second array
        for(int j=0;j<hello2.cols();j++){
            hello2.set(i,j,2);
        }          
    }  
    cout<<"Macierz 2 wyglada nastepujaco:\n";
    hello2.print();
    cout <<"Macierz dodawania wygladaja nastepujaco:\n";
    Macierz helloAdd(5,5);
    helloAdd=hello+hello2;//uzywanie + do dodawaia macierzy
    helloAdd.print();
    cout <<"Macierz odejmowania wygladaja nastepujaco:\n";
    Macierz helloSubtract(5);
    helloSubtract=hello2-hello;//uzywanie - do odejmowania macierzy
    helloSubtract.print();
    cout <<"Macierz mnozenia wygladaja nastepujaco:\n";
    Macierz helloMultiply(5);
    helloMultiply=hello*hello2;//uzywanie * do odejmowania macierzy
    helloMultiply.print();
    if(helloSubtract==hello)//porownywanie macierzy, prawda
        cout <<"Macierz odejmowania i macierz 1 sa rowne\n";
    else
        cout <<"Macierze odejmowania i macierz 1 nie sa rowne\n";
    if(helloSubtract==hello2)//porownywanie macierzy, falsz
        cout <<"Macierz odejmowania i macierz 2 sa rowne\n";
    else
        cout <<"Macierze odejmowania i macierz 2 nie sa rowne\n";    
    cout <<"Wypisywanie przeciazaonym operatorem wyjscia\n";
    cout << hello;
    cout <<"Wypisywanie zawartosci danego wiersza macierzy operatorem []\n";
    cout << hello2[3];
    
}