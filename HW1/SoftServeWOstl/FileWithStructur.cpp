#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

namespace generator
{
    char BigSymvol[] = "АБВГҐДЕЄЖЗІКЛМНОПРСТУФХЦЧШЩЮЯ";
    char SmalSymvol[] = "fбвгґдеєжзиіїйклмнопрстуфхцчшщьюя";
 
int createFile(int argc, char** argv) 
{
    
    setlocale(LC_ALL,".1251");

    //для универсальності задамо питання кількості слів
    int LenghFile = 0,i = 0,LenghName = 3;
    std::string LastName;
    
    std::cout << "Скільки імен згенерувати?:\n";
    std::cin>>LenghFile;    
    std::srand ( time(NULL) );
    
    if (LenghFile < 1) return 0 ;
    
     // создаем файл (дублирую флаги по умолчанию)
    std::ofstream NameFile("ListName.txt",std::ios_base::out | std::ios_base::trunc); 
    
    if (!NameFile.is_open())
    {
      std::cout << "Error open file!\n" ;
      return 0 ;
    }
    
    for (int count = 0;count < LenghFile;count++)
    {
        LenghName = 3+rand()%7; //Оскільки ми вирішили що потрібно випадкове ім'я, то воно має бути випадковим
        LastName = "";
        std::cout << "Довжина імені: " << LenghName << "\n";
        for (i = 0;i < LenghName;i++)
        {
            //srand ( time(NULL) );
            if (i==0) //Велика літера
                {        
                LastName.push_back(BigSymvol[(rand()%29 - 1)]);
                }
            else if (i<=LenghName) 
                LastName.push_back(SmalSymvol[(rand()%33 - 1)]);
         }
        std::cout  << LastName << " \n";
        //std::strncpy(WriteName, LastName, LenghName);
        //WriteName[LenghName] = '\0';
        //cout <<  WriteName << "\n";
        NameFile << LastName << "\n"; 
    }
    
    NameFile.close();                     // закриваемо файл
    return 0;
}


bool CompareString(const char * s1, const char * s2)
{
    for(int i =0;i < strlen(s1); i++)
    {
        if (s1[i] < s2[i]) return false;
    }
    
    return true;
}

int SortFile(int argc, char** argv) 
{
    
    setlocale(LC_ALL, ".1251");
    char buff1[11],buff2[11]; 
    std::ifstream NameFile("ListName.txt",std::ios_base::in); 
    std::ofstream NameFileTemp("ListName.txt.tmp",std::ios_base::out | std::ios_base::trunc);
    
    if ((!NameFile.is_open())||(!NameFileTemp.is_open()))
    {  
        std::cout << "Error open file!\n" ;
      return 0 ;
    }
    //считіваю первую строку
    NameFile.getline(buff1, 11);
    while(!NameFile.eof())
    {
        NameFile.getline(buff2, 11);
        if (CompareString(buff1,buff2)) 
        {
            NameFileTemp << buff1 << "\n";
            for (int i=0; i<=10; i++)
            buff1[i] = buff2[i];
        }
        else NameFileTemp << buff2 << "\n";   
        //getline(NameFile,buff1);
        std::cout << buff1<<"\n";
    }
    NameFileTemp << buff1 << "\n";
    NameFile.close();
    NameFileTemp.close();
 
    std::remove("ListName.txt");
    std::rename("ListName.txt.temp", "ListName.txt");
    return 0;
}

}