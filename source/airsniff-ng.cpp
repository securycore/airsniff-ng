/* Maintainer: Deltax
 * Date: 2017-11-11
 * Purpose: Source file
 */

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <fstream>
#include <boost/tokenizer.hpp>
#include <readline/readline.h>
#include <readline/history.h>

#include "libs/color.h"
#include "print.cpp"
#include "help.cpp"
#include "arp-poison.cpp"
#include "gen_speedport_w500.cpp"
#include "readline.cpp"
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/ether.h>
#include <netinet/in.h>
#include <pcap.h>
#include <stdlib.h>
int main()
{
    read_user_input();
    return 0;
}
