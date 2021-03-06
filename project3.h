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
    
    unsigned int entryID;
    
    logEntry(std::string a, std::string b, std::string c, unsigned int d):
            timeStamp(a), category(b), message(c), entryID(d) {}
};

struct sortCompare {
    bool operator() (const logEntry &rhs, const logEntry &lhs) const {
        if (rhs.timeStamp == lhs.timeStamp) {
            if (rhs.lowerCaseCategory == lhs.lowerCaseCategory) {
                return rhs.entryID < lhs.entryID;
            }
            else return rhs.lowerCaseCategory < lhs.lowerCaseCategory;
        }
        else return rhs.timeStamp < lhs.timeStamp;
    }
};

struct timeStampCompare {
    bool operator() (const logEntry &rhs, const std::string &lhs) const {
        return rhs.timeStamp < lhs;
    }
};

std::vector<logEntry*>::iterator lowerBoundFunc(std::vector<logEntry*>::iterator first,
                                                std::vector<logEntry*>::iterator last, const std::string &val);

#endif