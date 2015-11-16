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
    std::string lowerCaseCategory;
    std::string lowerCaseMessage;
    
    int entryID;
    
    logEntry(): timeStamp("a"), category("a"), message("a"),
                lowerCaseCategory("a"), lowerCaseMessage("a"), entryID(0) {}
    
    void operator=(const logEntry &other) {
        timeStamp = other.timeStamp;
        category = other.category;
        message = other.message;
        lowerCaseCategory = other.lowerCaseCategory;
        lowerCaseMessage = other.lowerCaseMessage;
        entryID = other.entryID;
    }
};

struct timeStampCompare {
    bool operator() (logEntry* rhs, logEntry* lhs) const {
        if (rhs->timeStamp == lhs->timeStamp) {
            if (rhs->category == lhs->category) {
                return rhs->entryID < lhs->entryID;
            }
            else return rhs->category < lhs->category;
        }
        else return rhs->timeStamp < lhs->timeStamp;
    }
};

std::vector<logEntry*>::iterator lowerBoundFunc(std::vector<logEntry*>::iterator first,
                                std::vector<logEntry*>::iterator last, const std::string &val);

#endif
