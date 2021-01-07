//
// Created by Yossi Levi on 12/06/2019.
//
#include <cstdio>
#include <string.h>
#include <fstream>
#include <cstdlib>
#include <sys/stat.h>
#include <stdio.h>
#include <algorithm>

using std::string;

void TEST1();
void TEST2();
void TEST3();
void TEST4();
void TEST5();
void TEST6();
void TEST7();
void TEST8();
void TEST9();
void TEST10();

std::string get_striped_line(std::ifstream &file)
{
    string str;
    getline(file, str);
    str.erase(std::find_if(str.rbegin(), str.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), str.end());
    return str;
}

int main(){
    mkdir("results", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    TEST1();
    TEST2();
    TEST3();
    TEST4();
    TEST5();
    TEST6();
    TEST7();
    TEST8();
    TEST9();
    TEST10();
    freopen("results/finalresults.txt","w",stdout);
    string line1,line2;
    std::ifstream File2;
    std::ifstream File1;
    File1.open("results/test1myresult.txt");
    File2.open("test1result.txt");
    int pass=1;
    while(!File1.eof()||!File2.eof()){
        line1 = get_striped_line(File1);
        line2 = get_striped_line(File2);
        if(line1!=line2){
            pass=0;
        }
    }
    File1.close();
    File2.close();
    pass?printf("TEST 1 PASSED\n"):printf("TEST 1 FAILED\n");
    File1.open("results/test2myresult.txt");
    File2.open("test2result.txt");
    pass=1;
    while(!File1.eof()||!File2.eof()){
        line1 = get_striped_line(File1);
        line2 = get_striped_line(File2);
        if(line1!=line2){
            pass=0;
        }
    }
    File1.close();
    File2.close();
    pass?printf("TEST 2 PASSED\n"):printf("TEST 2 FAILED\n");
    File1.open("results/test3myresult.txt");
    File2.open("test3result.txt");
    pass=1;
    while(!File1.eof()||!File2.eof()){
        line1 = get_striped_line(File1);
        line2 = get_striped_line(File2);
        if(line1!=line2){
            pass=0;
        }
    }
    File1.close();
    File2.close();
    pass?printf("TEST 3 PASSED\n"):printf("TEST 3 FAILED\n");
    File1.open("results/test4myresult.txt");
    File2.open("test4result.txt");
    pass=1;
    while(!File1.eof()||!File2.eof()){
        line1 = get_striped_line(File1);
        line2 = get_striped_line(File2);
        if(line1!=line2){
            pass=0;
        }
    }
    File1.close();
    File2.close();
    pass?printf("TEST 4 PASSED\n"):printf("TEST 4 FAILED\n");
    File1.open("results/test5myresult.txt");
    File2.open("test5result.txt");
    pass=1;
    while(!File1.eof()||!File2.eof()){
        line1 = get_striped_line(File1);
        line2 = get_striped_line(File2);
        if(line1!=line2){
            pass=0;
        }
    }
    File1.close();
    File2.close();
    pass?printf("TEST 5 PASSED\n"):printf("TEST 5 FAILED\n");
    File1.open("results/test6myresult.txt");
    File2.open("test6result.txt");
    pass=1;
    while(!File1.eof()||!File2.eof()){
        line1 = get_striped_line(File1);
        line2 = get_striped_line(File2);
        if(line1!=line2){
            pass=0;
        }
    }
    File1.close();
    File2.close();
    pass?printf("TEST 6 PASSED\n"):printf("TEST 6 FAILED\n");
    File1.open("results/test7myresult.txt");
    File2.open("test7result.txt");
    pass=1;
    while(!File1.eof()||!File2.eof()){
        line1 = get_striped_line(File1);
        line2 = get_striped_line(File2);
        if(line1!=line2){
            pass=0;
        }
    }
    File1.close();
    File2.close();
    pass?printf("TEST 7 PASSED\n"):printf("TEST 7 FAILED\n");
    File1.open("results/test8myresult.txt");
    File2.open("test8result.txt");
    pass=1;
    while(!File1.eof()||!File2.eof()){
        line1 = get_striped_line(File1);
        line2 = get_striped_line(File2);
        if(line1!=line2){
            pass=0;

        }
    }
    File1.close();
    File2.close();
    pass?printf("TEST 8 PASSED\n"):printf("TEST 8 FAILED\n");
    File1.open("results/test9myresult.txt");
    File2.open("test9result.txt");
    pass=1;
    while(!File1.eof()||!File2.eof()){
        line1 = get_striped_line(File1);
        line2 = get_striped_line(File2);
        if(line1!=line2){
            pass=0;
        }
    }
    File1.close();
    File2.close();
    pass?printf("TEST 8 PASSED\n"):printf("TEST 8 FAILED\n");
    File1.open("results/test9myresult.txt");
    File2.open("test9result.txt");
    pass=1;
    while(!File1.eof()||!File2.eof()){
        line1 = get_striped_line(File1);
        line2 = get_striped_line(File2);
        if(line1!=line2){
            pass=0;
        }
    }
    File1.close();
    File2.close();
    pass?printf("TEST 9 PASSED\n"):printf("TEST 9 FAILED\n");
    File1.open("results/test10myresult.txt");
    File2.open("test10result.txt");
    pass=1;
    while(!File1.eof()||!File2.eof()){
        line1 = get_striped_line(File1);
        line2 = get_striped_line(File2);
        if(line1!=line2){
            pass=0;
        }
    }
    File1.close();
    File2.close();
    pass?printf("TEST 10 PASSED\n"):printf("TEST 10 FAILED\n");
return 0;

}