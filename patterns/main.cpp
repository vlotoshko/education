//#include <QCoreApplication>
#include "afactorymethod.h"
#include "aabctractfactory.h"
#include "abuilder.h"
#include <iostream>
#include <cstring>

using std::string;
using std::cout;
using std::cin;
using std::endl;



int main(/*int argc, char *argv[]*/)
{
//  QCoreApplication a(argc, argv);
//  return a.exec();



  char arr[1000]="";
 char arrstr[100]="";
 char str[100]="";
 cout << "Vvedit rechna ->";
 cin.getline(arr, 1000);
 arr[strlen(arr)] = ' ';
 int k = 0, pamuat = 100;
 for (int i = 0; i < strlen(arr); i++)
 if (arr[i] != ' ')
 arrstr[k++] = arr[i];
 else
 {
 if (pamuat > k)
 pamuat = k, strcpy(str, arrstr);
 arrstr[0]='/0';
 k = 0;
 }
 cout << str;


  return 0;
}
