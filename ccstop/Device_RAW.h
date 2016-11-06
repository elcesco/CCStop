/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Device_RAW.h
 * Author: francesco
 *
 * Created on October 30, 2016, 11:34 AM
 */

#ifndef DEVICE_RAW_H
#define DEVICE_RAW_H

#define MY_DEST_MAC0 00
#define MY_DEST_MAC1 11
#define MY_DEST_MAC2 22
#define MY_DEST_MAC3 33
#define MY_DEST_MAC4 44
#define MY_DEST_MAC5 55

#define TTL 128


#include <iostream>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <netinet/ether.h>

#include "Devices.h"

class Device_RAW : public Devices {
public:
    Device_RAW();
    virtual ~Device_RAW();

    virtual int addFilter();
    virtual int removeFilter();

    virtual int open();
    virtual int close();

    int send(char* sendbuf, int len);
    virtual int receive();

    virtual bool isConnected();


private:
    int sockfd;
    struct ifreq if_idx;

    unsigned short csum(unsigned short *buf, int nwords);

};

#endif /* DEVICE_RAW_H */

