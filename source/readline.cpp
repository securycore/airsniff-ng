static char **completion(const char *, int, int);
char* generate(const char*,int);
char * dupstr (char*);
void *xmalloc (int);

const char* cmd [] = {
    "show_modules",
    "show_help",
    "set_bssid",
    "set_ssid",
    "arp_poison",
    "set_gateway_ip",
    "set_target_ip",
    "set_target_mac",
    "set_channel",
    "set_interface",
    "show_settings",
    "gen_speedport_w500",
    "clear",
    "help",
    "quit" ,
    0 };

static char** completion( const char * text , int start,int end)
{
  char **matches;

  matches = (char **)NULL;

  if (start == 0)
    matches = rl_completion_matches ((char*)text, &generate);
  else
    rl_bind_key('\t', rl_abort);

  return (matches);

}

char* generate(const char* text, int state)
{
  static int list_index, len;
  const char *name;

  if (!state) {
    list_index = 0;
    len = strlen (text);
  }

  while ((name = cmd[list_index])) {
    list_index++;

    if (strncmp (name, text, len) == 0)
      return (dupstr((char *)name));
  }

  return ((char *)NULL);

}

char * dupstr (char* s) {
  char *r;

  r = (char*) xmalloc ((strlen (s) + 1));
  strcpy (r, s);
  return (r);
}

void * xmalloc (int size)
{
  void *buffer;

  buffer = malloc (size);
  if (!buffer) {
    fprintf (stderr, "Error: Out of memory. Exiting.'n");
    exit (1);
  }

  return buffer;
}

void show_modules ()
{
    std::cout << "No modules found \n";
}
void read_user_input()
{

    using std::cin;
    using std::cout;
    using std::endl;
    using std::string;
    using std::vector;
    using namespace boost;

    char *buffer;

    /*
     * Variables definition
     */
    string command; // for input
    string option; // only fist word from input line

    /*
     * User settings
     */

    float v = 1.0;
    vector<string> SET;
    for (int i = 0; i<= 10;i++)
        SET.push_back("Not found");
    /*
     * BSSID at 0
     * CHANNEL at 1
     * SSID at 2
     * INTERFACE at 3
     */

    // Menu for while loop
    bool Menu = true;

    // completion using tab
    rl_attempted_completion_function = completion;

    // clear display and print banner
    cout << "\033[2J\033[1;1H" << BLUE << BOLD
         <<  "    o             o  ,-  ,- \n"
         <<  ",-: . ;-. ,-. ;-. .  |   |      ;-. ,-: \n"
         <<  "| | | |   `-. | | |  |-  |- --- | | | | \n"
         <<  "`-` ' '   `-' ' ' '  |   |      ' ' `-| \n"
         <<  "                    -'  -'          `-' "
         << RESET << "(" << v << ")\n";

    read_history("commands/airplay-ng.history");
    while(Menu==true) {

        // Read input with custom design
        buffer = readline("\033[31m>\033[34m>\033[0m ");

        // Trim last whitespaces
        size_t last = command.find_last_not_of(' ');
        command = command.substr(0, (last+1));

        add_history(buffer);
        write_history("commands/airplay-ng.history");

        // char to string
        string command(buffer);

        boost::char_separator<char> sep(" ");
        typedef boost::tokenizer< boost::char_separator<char> > t_tokenizer;
        t_tokenizer tok(command, sep);

        // Only print the first argument
        for (t_tokenizer::iterator beg = tok.begin(); beg != tok.end(); ++beg)
        {
            option = *beg;
            break;
        }

        // Custom completion with tab
        rl_bind_key('\t',rl_complete);

        /*
         * Options
         */
        if (option == "help" || option == "show_help")
            help();
        else if (option == "show_modules")
            show_modules();
        else if (option == "quit")
            exit(0);
        else if (option == "set_bssid")
            SET.at(0) = command.erase(0,10);
        else if (option == "set_channel")
            SET.at(1) = command.erase(1,12);
        else if (option == "set_ssid")
            SET.at(2) = command.erase(0,9);
        else if (option == "set_target_mac")
            SET.at(4) = command.erase(0,12);
        else if (option == "set_interface")
            SET.at(3) = command.erase(0,14);
        else if (option == "set_target_ip")
            SET.at(5) = command.erase(0,14);
        else if (option == "set_gateway_ip")
            SET.at(6) = command.erase(0,15);
        else if (option == "arp_poison")
            arp_main(SET.at(3).c_str(),SET.at(5).c_str(),SET.at(6).c_str());
        else if ( option == "show_settings" )
            show_settings(SET.at(0),SET.at(2),SET.at(1),SET.at(3));
        else if ( option == "clear" )
            cout << "\033[2J\033[1;1H";
        else if ( option == "gen_speedport_w500" )
            gen_speedport_w500(SET.at(0),SET.at(2));
        else if ( option != "")
            system(command.c_str());
        /*
         * Options
         */

        // Write to buffer
        add_history(buffer);
  }
    // clear bufferfer
    free(buffer);
}

