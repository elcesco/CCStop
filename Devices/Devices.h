/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Devices.h
 * Author: francesco
 *
 * Created on October 30, 2016, 1:40 PM
 */

#ifndef DEVICES_H
#define DEVICES_H

class Devices {
    
public:
    Devices();
    virtual ~Devices();

    virtual int addFilter() = 0;
    virtual int removeFilter() = 0;
    
    virtual int open() = 0;
    virtual int close() = 0;
    
    virtual int send() = 0;
    virtual int receive() = 0;
    
    virtual bool isConnected() = 0;

private:

};

#endif /* DEVICES_H */

