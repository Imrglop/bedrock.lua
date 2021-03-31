#pragma once
#include <string>
#include <iostream>

#define __get_current_file_name() (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define LOGX(type, c) std::cout<<"["<<type<<"]" << " (" << __get_current_file_name() << "::" << __func__ << ":" << __LINE__ << ") "<<c<<"\n"
#define llog(c) LOGX("INFO", c)
#define err(c) LOGX("ERROR", c)
#define warn(c) LOGX("WARN", c)


