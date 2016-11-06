/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConfigurationManager.h
 * Author: francesco
 *
 * Created on 5. November 2016, 19:37
 */

#ifndef CONFIGURATIONMANAGER_H
#define CONFIGURATIONMANAGER_H

#define OPT_LOGFILE 1
#define UDP_RATE (1024 * 1024) /* 1 Mbps */
#define DURATION 10 /* seconds */
#define DEFAULT_TCP_BLKSIZE (128 * 1024)  /* default read/write block size */
#define DEFAULT_UDP_BLKSIZE 8192

#include <iostream>

#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

class ConfigurationManager {

public:
    ConfigurationManager();
    virtual ~ConfigurationManager();
    
    int parseArguments( int argc, char **argv);
    
private:
    void printUsage();
    char *logfile;				/* --logfile option */
};

/* -------------------------------------------------------------------
 * usage
 * ------------------------------------------------------------------- */

const char usage_shortstr[] = "Usage: ccstop [-s|-c host] [options]\n"
                           "Try `ccstop --help' for more information.\n";

const char usage_longstr[] = "Usage: ccstop [-s|-c host] [options]\n"
                           "       ccstop [-h|--help] [-v|--version]\n\n"
                           "\n"
                           "Server or Client:\n"
                           "  -p, --port      #         server port to listen on/connect to\n"
                           "  -l, --logfile f           send output to a log file\n"
                           "  -d, --debug               emit debugging output\n"
                           "  -v, --version             show version information and quit\n"
                           "  -h, --help                show this message and quit\n"
                           "\n"
                           "Server specific:\n"
                           "  -s, --server              run in server mode\n"
                           "\n"
                           "Client specific:\n"
                           "  -c, --client    <host>    run in client mode, connecting to <host>\n"
                           "  -P, --pcap f              uses pcap file for ovet channel input"
                           "  -S, --script s            script file controlling the covert channel inpout"
                           "  -b, --bandwidth           target bandwidth in bits/sec (0 for unlimited)\n"
                           "                            (optional slash and packet count for burst mode)\n"
			   "\n %s \n"
			   ;

#endif /* CONFIGURATIONMANAGER_H */

