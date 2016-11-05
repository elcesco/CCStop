/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ConfigurationManager.h"

ConfigurationManager::ConfigurationManager() {
    std::cout << "enter ConfigurationManager::ConfigurationManager()" << std::endl;
}

ConfigurationManager::~ConfigurationManager() {
    std::cout << "enter ConfigurationManager::~ConfigurationManager()" << std::endl;    
}

int ConfigurationManager::parseArguments(int argc, char **argv)
{
    std::cout << "enter ConfigurationManager::parseArguments()" << std::endl;    

    static struct option longopts[] =
    {
        {"client",      required_argument,  NULL, 'c'},
        {"port",        required_argument,  NULL, 'p'},
        {"server",      no_argument,        NULL, 's'},
        {"pcap",        required_argument,  NULL, 'P'},
        {"script",      required_argument,  NULL, 'S'},
        {"bandwidth",   required_argument,  NULL, 'b'},
	{"logfile",     required_argument,  NULL, OPT_LOGFILE},
        {"version",     no_argument,        NULL, 'v'},
        {"debug",       no_argument,        NULL, 'd'},
        {"help",        no_argument,        NULL, 'h'},
        {NULL,          0,                  NULL, 0}
    };
    
    int flag;
    while ((flag = getopt_long(argc, argv, "c:p:sP:S:b:vdh", longopts, NULL)) != -1) {
        switch (flag) {
            case 'c':
                break;
            case 'p':
                break;
            case 's':
                break;
            case 'P':
	        break;
            case 'S':
	        break;
            case 'b':
                break;
	    case OPT_LOGFILE:
		logfile = strdup(optarg);
		break;
            case 'v':
                break;
            case 'd':
                break;
            case 'h':
                break;
            default:
                printUsage();
                exit(1);
        }
    }
    return 0;
}

void ConfigurationManager::printUsage()  {
    
    fprintf( stderr, usage_longstr, "ccstop");
    
}
