#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace generator
{
    //есть проблема с кодировкой поэтому перепишу в английскую раскладку
    //char BigSymvol[] = "АБВГҐДЕЄЖЗІКЛМНОПРСТУФХЦЧШЩЮЯ";
    int MaxBig = 26;
    char BigSymvol[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    //char SmalSymvol[] = "абвгґдеєжзиіїйклмнопрстуфхцчшщьюя";
    int MaxSmal = 26;
    char SmalSymvol[] = "abcdefghijklmnopqrstuvwxyz";
    
int createFile(int argc, char** argv) 
{
    
    //setlocale(LC_ALL,".1251");

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
                LastName.push_back(BigSymvol[(rand()%MaxBig - 1)]);
                }
            else if (i<=LenghName) 
                LastName.push_back(SmalSymvol[(rand()%MaxSmal - 1)]);
         }
        std::cout  << LastName << " \n";
        //std::strncpy(WriteName, LastName, LenghName);
        //WriteName[LenghName] = '\0';
        //cout <<  WriteName << "\n";
        NameFile << LastName << "\n"; 
    }
    
    NameFile.close();                     // закриваемо файл
    argc = LenghFile;
    return 0;
}


bool CompareString(std::string s1, std::string s2)
{
    bool result = true;
    
    if (s1 < s2) 
    {
        result = false;
    }

    return result;
}

int SortFile(int argc, char** argv) 
{
    bool Trust = true;
    int maxSizeVector = argc;
    std::vector <std::string> SortList ;
    SortList.reserve(maxSizeVector);
    
    //setlocale(LC_ALL, ".1251");
    std::string buff1,buff2; 
    std::ifstream NameFile("ListName.txt",std::ios_base::in); 
    std::ofstream NameFileTemp("ListName.txt.tmp",std::ios_base::out | std::ios_base::trunc);
    
    if ((!NameFile.is_open())||(!NameFileTemp.is_open()))
    {  
        std::cout << "Error open file!\n" ;
      return 0 ;
    }
    
    while (std::getline(NameFile, buff1))
    {
        SortList.push_back(buff1);
    }   
    NameFile.close();
    
    while(Trust)
    {
        if (maxSizeVector<1)
        {
            Trust = false;
            break;
        }
        
        for(int i = 0;i<(maxSizeVector-1);i++)
        {
            buff1 = SortList.at(i);
            buff2 = SortList.at(i+1);
            if (!CompareString(buff1,buff2))
            {
                SortList[i]   = buff2;
                SortList[i+1] = buff1;
            }
        }
        maxSizeVector--;
    }

    std::ofstream NameFileNew("ListName.txt",std::ios_base::out | std::ios_base::trunc);
    
    if (!NameFileNew.is_open())
    {
      std::cout << "Error save sort file!\n" ;
      return 0 ;
    }
    
    for (auto& i :SortList)
    {
        std::cout << i ;
    }

    NameFileNew.close();
 
    return 0;
}

}