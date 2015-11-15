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

struct timeStampCompare {
    bool operator() (std::pair<int,logEntry>* &rhs, std::pair<int,logEntry>* &lhs) const {
        if (rhs->second.timeStamp == lhs->second.timeStamp) {
            if (rhs->second.category == lhs->second.category) {
                return rhs->first < lhs->first;
            }
            else return rhs->second.category < lhs->second.category;
        }
        else return rhs->second.timeStamp < lhs->second.timeStamp;
    }
};


#endif
