void help() {
  std::cout << "\033[2J\033[1;1H"
            << "------------- < Friendly > --------------\n"
            << BOLD << "\nMisc\n" << RESET
            << "Help \033[31m:\033[0m\t\t\t help \n"
            << "Quit \033[31m:\033[0m\t\t\t quit\n"

            << BOLD << "\nSet options\n" << RESET
            << "Set ssid \033[31m:\033[0m\t\t set_ssid\n"
            << "Set bssid \033[31m:\033[0m\t\t set_bssid\n"
            << "Set channel \033[31m:\033[0m\t\t set_channel\n"
            << "Set Gateway \033[31m:\033[0m\t\t set_gateway_ip\n"
            << "Set Target IP \033[31m:\033[0m\t\t set_target_ip\n"
            << "Set interface  \033[31m:\033[0m\t set_interface\n"

            << BOLD << "\nShow commands\n" << RESET
            << "Show Modules \033[31m:\033[0m\t\t show_modules\n"
            << "Show Settings \033[31m:\033[0m\t\t show_settings\n"
            << "Show Help \033[31m:\033[0m\t\t show_help\n"

            << BOLD << "\nAttack modules\n" << RESET
            << "Arp poisoning \033[31m:\033[0m\t\t arp_poison\n"
            << "Generate wordlist \033[31m:\033[0m\t gen_speedport_w500\n"
            << "---------------- < MAN > ----------------\n\n"
            << BOLD << "\nMisc\n" << RESET
            << GREEN << "Help: \n"
            << RESET << RED << " ~ " << RESET << BOLD << " Arguments:\n"
            << RESET << "\t[" << GREEN << "+" << RESET "]"
            << " show_help:\n"
            << "\t[" << GREEN << "+" << RESET "]"
            << " help:\n\n"
            << RED << " ~ " << RESET << BOLD << "Description:\n"
            << RESET << " Print the help manual \n\n"

            << GREEN << "Quit: \n"
            << RESET << RED << " ~ " << RESET << BOLD << " Arguments:\n"
            << RESET << "\t[" << GREEN << "+" << RESET "]"
            << " quit:\n\n"
            << RED << " ~ " << RESET << BOLD << "Description:\n"
            << RESET << " Quit with 0 \n\n"

            << BOLD << "\n\nSet options\n" << RESET
            << GREEN << "set_ssid: \n"
            << RESET << RED << " ~ " << RESET << BOLD << " Arguments:\n"
            << RESET << "\t[" << GREEN << "+" << RESET "]"
            << " set_ssid [string]:\n\n"
            << RED << " ~ " << RESET << BOLD << "Description:\n"
            << RESET << "Set ssid \n\n"

            << GREEN << "set_bssid: \n"
            << RESET << RED << " ~ " << RESET << BOLD << " Arguments:\n"
            << RESET << "\t[" << GREEN << "+" << RESET "]"
            << " set_bssid [string]:\n\n"
            << RED << " ~ " << RESET << BOLD << "Description:\n"
            << RESET << "Set bssid \n\n"

            << GREEN << "set_channel: \n"
            << RESET << RED << " ~ " << RESET << BOLD << " Arguments:\n"
            << RESET << "\t[" << GREEN << "+" << RESET "]"
            << " set_channel [int]:\n\n"
            << RED << " ~ " << RESET << BOLD << "Description:\n"
            << RESET << "Set channel \n\n"

            << GREEN << "set_gateway_ip: \n"
            << RESET << RED << " ~ " << RESET << BOLD << " Arguments:\n"
            << RESET << "\t[" << GREEN << "+" << RESET "]"
            << " set_gateway_ip [string:\n\n"
            << RED << " ~ " << RESET << BOLD << "Description:\n"
            << RESET << "Set channel \n\n"

            << GREEN << "set_target_ip: \n"
            << RESET << RED << " ~ " << RESET << BOLD << " Arguments:\n"
            << RESET << "\t[" << GREEN << "+" << RESET "]"
            << " set_target_ip [int]:\n\n"
            << RED << " ~ " << RESET << BOLD << "Description:\n"
            << RESET << "Set target ip for arp poisoning \n\n"

            << GREEN << "set_gateway_ip: \n"
            << RESET << RED << " ~ " << RESET << BOLD << " Arguments:\n"
            << RESET << "\t[" << GREEN << "+" << RESET "]"
            << " set_gateway_ip [int]:\n\n"
            << RED << " ~ " << RESET << BOLD << "Description:\n"
            << RESET << "Set gateway ip for arp poisoning \n\n"

            << BOLD << "\n\nShow options\n" << RESET << GREEN << "List Modules: \n"
            << RESET << RED << " ~ " << RESET << BOLD << " Arguments:\n"
            << RESET << "\t[" << GREEN << "+" << RESET "]"
            << " show_modules:\n\n"
            << RED << " ~ " << RESET << BOLD << "Description:\n"
            << RESET << " Print all modules \n\n"

            << GREEN << "Show help: \n"
            << RESET << RED << " ~ " << RESET << BOLD << " Arguments:\n"
            << RESET << "\t[" << GREEN << "+" << RESET "]"
            << " show_help:\n\n"
            << RED << " ~ " << RESET << BOLD << "Description:\n"
            << RESET << " Print the help manual \n\n"

            << GREEN << "Show settings: \n"
            << RESET << RED << " ~ " << RESET << BOLD << " Arguments:\n"
            << RESET << "\t[" << GREEN << "+" << RESET "]"
            << " show_settings:\n\n"
            << RED << " ~ " << RESET << BOLD << "Description:\n"
            << RESET << " Print all settings which are in use \n\n"

            << BOLD << "\n\nAttack options\n" << RESET
            << GREEN << "Arp poisoning: \n"
            << RESET << "\t[" << GREEN << "+" << RESET "]"
            << " arp_poison:\n\n"
            << RED << " ~ " << RESET << BOLD << "Description:\n"
            << RESET << " Arp_poison clients in a network \n\n"

            << GREEN << "Generate wordlists: \n"
            << RESET << "\t[" << GREEN << "+" << RESET "]"
            << " gen_speedport_w500:\n\n"
            << RED << " ~ " << RESET << BOLD << "Description:\n"
            << RESET << " Generate speed port wordlist for the speedsport w500 \n\n"
            << "---------------- < MAN > ----------------\n\n";
}

