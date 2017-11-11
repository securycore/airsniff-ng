int convert2ascii(char c) {
  int a = c;
  return a;
}

void gen_speedport_w500 (std::string ssid,std::string bssid)
{
    std::string temp;
    std::ofstream a;
    a.open("../wordlist/speedport-w500.txt");
    for (int i = 9; i<= 12;i++)
    {
        temp += bssid[i];
    }
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            for (int z = 0; z < 10; ++z) {
                a<< "SP-" << ssid[9] << z << ssid[10] << convert2ascii(bssid[8]) <<  convert2ascii(bssid[9])  << convert2ascii(bssid[10]) << x << y << z << convert2ascii(ssid[6]) << convert2ascii(ssid[7]) << "\n";
            }
        }
    }
    a.close();
}
