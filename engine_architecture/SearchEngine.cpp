#include "SearchEngine.h"

SearchEngine::SearchEngine() {
    search_path = "/mnt/c/Users/wnahl/OneDrive/Desktop/JSONData/archive/archive";
    //C:\Users\wnahl\OneDrive\Desktop\JSONData\archive\archive
    cout << "-----------------------------------------------" << endl;
    cout << "-------   Will Nahley's Search Engine   -------" << endl;
}

void SearchEngine::go() {

    int choice = 0;

    do {
        cout << "-----------------------------------------------" << endl;
        cout << "Please choose one of the following options (enter an integer):" << endl;
        cout << "1: Enter a query" << endl;
        cout << "2: View the index" << endl;
        cout << "3. Clear the index" << endl;
        cout << "4. Parse or populate" << endl;
        cout << "5. View statistics of search engine" << endl;
        cout << "6. Quit" << endl;
        cout << endl << "Selection: ";

        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                //Query
                {
                    cout << "Please enter a query:" << endl;
                    string search_term;
                    getline(cin, search_term);


                    QueryProcessor query(search_term, search_path);

                    /*IndexHandler index_handler (search_term, search_path, 'o');*/
                    vector<string> ids = query.generate_full_set();

                    unsigned long results_size = 15;
                    int min = std::min(ids.size(), results_size);

                    cout << "The term '" << search_term << "' appears in " << ids.size() << " document(s):" << endl;
                    for (int i = 0; i < min; i++) {
                        cout << (i + 1) << ": " << ids[i] << endl;
                    }
                }
                break;
            case 2:
                //View index
                {
                    cout << "Which index would you like to view? (TEXT, ORG, PERSON)" << endl;
                    string x = "";
                    cin >> x;
                    if (x == "TEXT") {
                        ifstream in("/mnt/c/Users/wnahl/OneDrive/Desktop/Classwork/2022 Spring/CS 2342/22s-final-project-will-nahley/persistence_index/PersistenceIndex.txt");

                        if (in.peek() != std::ifstream::traits_type::eof()) {
                            while (!in.eof()) {
                                string cur_line;
                                getline(in, cur_line, '\n');
                                cout << cur_line << endl;
                            }
                        } else {
                            cout << "There is nothing currently in the TEXT index" << endl;
                        }
                    }

                }
                break;
            case 3:
                //Clear the indices
                {
                    ofstream clear_terms("/mnt/c/Users/wnahl/OneDrive/Desktop/Classwork/2022 Spring/CS 2342/22s-final-project-will-nahley/persistence_index/PersistenceIndex.txt");
                    ofstream clear_persons("/mnt/c/Users/wnahl/OneDrive/Desktop/Classwork/2022 Spring/CS 2342/22s-final-project-will-nahley/persistence_index/PersonIndex.txt");
                    ofstream clear_orgs("/mnt/c/Users/wnahl/OneDrive/Desktop/Classwork/2022 Spring/CS 2342/22s-final-project-will-nahley/persistence_index/OrgIndex.txt");

                    clear_terms.clear();
                    clear_persons.clear();
                    clear_orgs.clear();

                    cout << "Indices have been cleared." << endl;
                }

                break;
            case 4:
                //Parse / populate
                break;
            case 5:
                //View statistics of search engine
                break;
            case 6:
                //Quit
                break;
            default:
                cout << "Not a valid selection..." << endl;
                break;
        }


    } while (choice != 6);

}
