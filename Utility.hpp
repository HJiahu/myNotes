/*********************************************************************************
*     File Name           :     Utility.h
*     Created By          :     HJiahu
*     Creation Date       :     [2016-06-17 11:05]
*     Last Modified       :     [2016-06-17 11:07]
*     Description         :     sth useful and error handers
**********************************************************************************/

#ifndef MY_UTILITY_HPP
#define MY_UTILITY_HPP

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<cstring>
#include<cstdio>
#include<ctime>

//获得系统当前时间，包括年月与时间
static std::string currentDateTime(void){
    time_t ct = time(NULL);
    std::string date_time(ctime(&ct));
    *(date_time.end()-1) = ' ';
    return date_time;
}

//当出现系统错误时使用此函数中断 进程并记录错误在log.txt中
static void DieWithSystemMessage(std::string msg = ""){
    std::ofstream out("logs.txt",std::fstream::app);
    std::ostringstream line_buff;
    line_buff<<"Die @ "<<currentDateTime()<<": ";
    line_buff<<msg<<". Sys: "<<strerror(errno)<<std::endl;
    out<<line_buff.str()<<std::flush;

    std::cerr<<line_buff.str() <<"Press any key to exit!\n";
    getchar();
    exit(0);
}

//当出现用户错误时，例如输入的数据不对时中断进程并保存错误记录
static void DieWithUserMessage(std::string msg){
    std::ofstream out("logs.txt",std::fstream::app);
    std::ostringstream line_buff;
    line_buff<<"Die @ "<<currentDateTime()<<": ";
    line_buff<<msg<<std::endl;
    std::cerr<<line_buff.str()<<"\npress any key to exit."<<std::endl;
    out<<line_buff.str()<<std::flush;

    std::cerr<<line_buff.str() <<"Press any key to exit!\n";
    getchar();
    exit(0);
}

//警告但不中断进程
static void WarningWithUserMessage(std::string msg = ""){
    std::ofstream out("logs.txt",std::fstream::app);
    std::ostringstream line_buff;
    line_buff<<"Warning @ "<<currentDateTime()<<": ";
    line_buff<<msg<<std::endl;
    out<<line_buff.str()<<std::flush;
    std::cerr<<line_buff.str()<<std::flush;
}

#endif 






















