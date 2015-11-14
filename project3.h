//
//  project3.h
//  LMan
//
//  Created by Hannah Wang on 11/13/15.
//  Copyright (c) 2015 Hannah. All rights reserved.
//

#ifndef LMan_project3_h
#define LMan_project3_h

#include <string>

struct logEntry {
    std::string timeStamp;
    std::string category;
    std::string message;
    
    logEntry(): timeStamp("a"), category("a"), message("a") {}
    
    void operator=(const logEntry &other) {
        timeStamp = other.timeStamp;
        category = other.category;
        message = other.message;
    }
};


#endif
