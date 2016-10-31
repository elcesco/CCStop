/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Device_RAW.cpp
 * Author: francesco
 * 
 * Created on October 30, 2016, 11:34 AM
 */

#include <linux/if_packet.h>

#include "Device_RAW.h"

Device_RAW::Device_RAW() {
    std::cout << "enter Device_RAW::Device_RAW()" << std::endl;
}

Device_RAW::~Device_RAW() {
    std::cout << "enter Device_RAW::~Device_RAW()" << std::endl;
    
}

int Device_RAW::open() {
    
    // Open RAW socket to send on
    if ((sockfd = socket(AF_PACKET, SOCK_RAW, IPPROTO_RAW)) == -1) {
        std::cout << "socket" << std::endl;
    } else {
        std::cout << "sockfd: " << sockfd << std::endl;
    }
    
    // Get the index of the interface to send on
    memset(&if_idx, 0, sizeof(struct ifreq));
    strncpy(if_idx.ifr_name, "ens33", IFNAMSIZ-1);
    if(ioctl(sockfd, SIOCGIFINDEX, &if_idx) < 0) {
        std::cout << "SIOCGIFINDEX" << std::endl;
    }
    
    //Get the MAC address of the interface to send on
    struct ifreq if_mac;
    memset(&if_mac, 0, sizeof(struct ifreq));
    strncpy(if_mac.ifr_name, "ens33", IFNAMSIZ-1);
    if(ioctl(sockfd, SIOCGIFHWADDR, &if_mac) < 0)
        std::cout << "SIOCGIFHWADDR" << std::endl;
        
    //Get the IP address of the interface to send on
    struct ifreq if_ip;
    memset(&if_ip, 0, sizeof(struct ifreq));
    strncpy(if_ip.ifr_name,"ens33", IFNAMSIZ-1);
    if(ioctl(sockfd, SIOCGIFADDR, &if_ip) < 0)
        std::cout << "SIOCGIFADDR" << std::endl;
    
    //Construct the Ethernet header
    int tx_len = 0;
    char sendbuf[1024];
    struct ether_header *eh = (struct ether_header *) sendbuf;
    
    memset(sendbuf, 0, 1024);
    
    eh->ether_shost[0] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[0];
    eh->ether_shost[1] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[1];
    eh->ether_shost[2] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[2];
    eh->ether_shost[3] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[3];
    eh->ether_shost[4] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[4];
    eh->ether_shost[5] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[5];
    
    eh->ether_dhost[0] = MY_DEST_MAC0;
    eh->ether_dhost[1] = MY_DEST_MAC1;
    eh->ether_dhost[2] = MY_DEST_MAC2;
    eh->ether_dhost[3] = MY_DEST_MAC3;
    eh->ether_dhost[4] = MY_DEST_MAC4;
    eh->ether_dhost[5] = MY_DEST_MAC5;
    
    eh->ether_type = htons(ETH_P_IP);
    tx_len += sizeof(struct ether_header);
    
    //Construct the IP header
    struct iphdr *iph = (struct iphdr *) (sendbuf + sizeof(struct ether_header));
    
    iph->ihl = 5;
    iph->version = 4;
    iph->tos = 16; // low delay
    iph->id = htons(54321);
    iph->ttl = TTL; //hops
    iph->protocol = 17; //UDP
    
    //iph->saddr = inet_addr(inet_ntoa(((struct sockaddr_in *) &if_ip.ifr_addr)->sin_addr));
    iph->saddr = inet_addr("192.168.0.222");
    iph->daddr = inet_addr("192.168.0.111");
    
    tx_len += sizeof(struct iphdr);
    
    //Construct the UDP header
    struct udphdr *udph = (struct udphdr *) (sendbuf + sizeof(struct iphdr) + sizeof(struct ether_header));
    
    udph->source = htons(3423);
    udph->dest = htons(5342);
    udph->check = 0;
    tx_len += sizeof(struct udphdr);
    
    //Fill in UDP
    sendbuf[tx_len++] = 0xde;
    sendbuf[tx_len++] = 0xad;
    sendbuf[tx_len++] = 0xbe;
    sendbuf[tx_len++] = 0xef;
    
    //Fill in remaining header info
    udph->len = htons(tx_len - sizeof(struct ether_header) - sizeof(struct iphdr));
    iph->tot_len = htons(tx_len - sizeof(struct ether_header));
    iph->check = csum((unsigned short *)(sendbuf + sizeof(struct ether_header)), sizeof(struct iphdr)/2);
    
    //Send the raw ethernet packet
    send(sendbuf, tx_len);
}

int Device_RAW::close() {
    
    return -1;
}


int Device_RAW::addFilter() {
    
    return -1;
}
    
int Device_RAW::removeFilter() {
    
    return -1;
}
    
int Device_RAW::send(char* sendbuf, int len){
    
    //Destination address
    struct sockaddr_ll socket_address;
    
    //Index of the network device
    socket_address.sll_ifindex = if_idx.ifr_ifindex;
    
    //Adress length
    socket_address.sll_halen = ETH_ALEN;
    
    //Destination MAC address
    socket_address.sll_addr[0] = MY_DEST_MAC0;
    socket_address.sll_addr[1] = MY_DEST_MAC1;
    socket_address.sll_addr[2] = MY_DEST_MAC2;
    socket_address.sll_addr[3] = MY_DEST_MAC3;
    socket_address.sll_addr[4] = MY_DEST_MAC4;
    socket_address.sll_addr[5] = MY_DEST_MAC5;
    
    //Send the raw ethernet packet
    if (sendto(sockfd, sendbuf, len, 0, (struct sockaddr*) &socket_address, sizeof(struct sockaddr_ll)) < 0 ) {
        std::cout << "send failed" << std::endl;
        return -1;
    }
    
    return 0;
}
 
int Device_RAW::receive() {
    
    return -1;
};
    
bool Device_RAW::isConnected() {
    
    return true;
};

// *****************************************************************************
// PRIVATE FUNCTIONS
// *****************************************************************************

unsigned short Device_RAW::csum(unsigned short *buf, int nwords) {
    unsigned long sum;
    for(sum=0; nwords>0; nwords--)
        sum += *buf++;
    sum = (sum >> 16) + (sum &0xffff);
    sum += (sum << 16);
    return (unsigned short) (~sum);
}