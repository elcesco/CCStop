/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CCStop.cpp
 * Author: francesco
 * 
 * Created on October 30, 2016, 11:43 AM
 */

#include "CCStop.h"

using namespace std;

CCStop::CCStop()
{
	std::cout << "enter CCStop::CCStop()" << std::endl;
}

CCStop::~CCStop()
{
	std::cout << "enter CCStop::~CCStop()" << std::endl;
}

/*
 * 
 */
int main(int argc, char** argv)
{
	std::cout << "starting..." << std::endl;

	unique_ptr<CCStop> ccmain(new CCStop());

	unique_ptr<ConfigurationManager> config(new ConfigurationManager());
	config->parseArguments(argc, argv);

	unique_ptr<Device_RAW> cc_device(new Device_RAW());
	cc_device->open();

	while (false);

	std::cout << "done." << std::endl;

	return 0;
}