void show_settings(std::string bssid, std::string ssid, std::string channel,
                   std::string interface) {
  std::cout << GREEN << "Settings: \n"
            << RESET << RED << " ~ " << RESET << BOLD << "BSSID: " << bssid
            << "\n"
            << RESET << RESET << RED << " ~ " << RESET << BOLD
            << "SSID: " << ssid << std::endl
            << RESET << RESET << RED << " ~ " << RESET << BOLD
            << "CHANNEL: " << channel << std::endl
            << RESET << RESET << RED << " ~ " << RESET << BOLD
            << "INTERFACE: " << interface << std::endl
            << RESET;
}

