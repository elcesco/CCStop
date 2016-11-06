/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CCStop.h
 * Author: francesco
 *
 * Created on October 30, 2016, 11:43 AM
 */

#ifndef CCSTOP_H
#define CCSTOP_H

#include <cstdlib>
#include <iostream>
#include <memory>

#include "Devices/Device_RAW.h"
#include "Devices/Device_PCAP.h"
#include "Devices/Device_TUN.h"

#include "ConfigurationManager.h"

class CCStop {
public:
    CCStop();
    virtual ~CCStop();
private:

};

#endif /* CCSTOP_H */

