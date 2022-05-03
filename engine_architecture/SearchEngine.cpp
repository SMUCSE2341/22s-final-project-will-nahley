#include "SearchEngine.h"

SearchEngine::SearchEngine() {
    search_path = "/mnt/c/Users/wnahl/OneDrive/Desktop/JSONData/archive/archive";
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
        cout << "5. Quit" << endl;
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


                std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
                start = std::chrono::high_resolution_clock::now();

                QueryProcessor query(search_term, search_path);

                //vector<string> ids = query.generate_full_set();
                vector<DSDoc> docs = query.generate_sorted_set();

                unsigned long results_size = 15;
                int min = std::min(docs.size(), results_size);


                if (min == 0) {
                    end = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> time_in_seconds = end - start;
                    cout << std::fixed << time_in_seconds.count() << std::endl;
                    cout << "There are no documents that match your query." << endl;
                    break;
                }
                end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> time_in_seconds = end - start;
                cout << "Runtime in seconds: " << std::fixed << time_in_seconds.count() << std::endl;

                cout << "There are " << docs.size() << " documents that match your query:" << endl;
                int view_again = 0;
                do {
                    for (int i = 0; i < min; i++) {
                        cout << (i + 1) << ": " << docs[i].get_title() << endl;
                        cout << '\t' << docs[i].get_publication() << endl;
                        cout << '\t' << docs[i].get_url() << endl;
                        cout << '\t' << docs[i].get_date_published() << endl;
                    }
                    cout << endl;
                    int article_selection = 0;


                    do {
                        cout << "Please select an article to view the entire text: ";
                        cin >> article_selection;
                        if (article_selection < 1 || article_selection > min) {
                            cout << "Invalid selection... Try again." << endl;
                        }
                    } while (article_selection < 1 || article_selection > min);
                    article_selection--; //subtracting 1 because we want indices from 0->14 or 0->minimum-1

                    cout << endl;
                    cout << docs[article_selection].get_title() << endl;
                    cout << "-----------------------------------------------------------------" << endl;
                    cout << docs[article_selection].get_text() << endl;

                    cout << endl <<"If you would like to return to the main menu, please enter 0" << endl;
                    cout << "If you would like to view other articles from this query, please enter 1: ";
                    cin >> view_again;
                    cout << endl;
                } while (view_again != 0);

            }
                break;
            case 2:
                //View index
            {
                string i_path;
                string x = "";

                do {
                    cout << "Which index would you like to view? (TEXT, ORG, PERSON)" << endl;
                    cin >> x;

                    if (x == "TEXT")
                        i_path = "/mnt/c/Users/wnahl/OneDrive/Desktop/Classwork/2022 Spring/CS 2342/22s-final-project-will-nahley-2/persistence_index/PersistenceIndex.txt";
                    else if (x == "ORG")
                        i_path = "/mnt/c/Users/wnahl/OneDrive/Desktop/Classwork/2022 Spring/CS 2342/22s-final-project-will-nahley-2/persistence_index/OrgIndex.txt";
                    else if (x == "PERSON")
                        i_path = "/mnt/c/Users/wnahl/OneDrive/Desktop/Classwork/2022 Spring/CS 2342/22s-final-project-will-nahley-2/persistence_index/PersonIndex.txt";
                } while (x != "TEXT" && x != "ORG" && x != "PERSON");

                ifstream in(i_path);
                if (in.peek() != std::ifstream::traits_type::eof()) {
                    while (!in.eof()) {
                        string cur_line;
                        getline(in, cur_line, '\n');
                        cout << cur_line << endl;
                    }
                } else {
                    cout << "There is nothing currently in the " << i_path << " index." << endl;
                }
                in.close();


            }
                break;
            case 3:
                //Clear the indices
            {
                int check = 0;
                cout << "Are you sure? (i'm sure: 1, Go back: any other integer)" << endl;
                cin >> check;

                if (check == 1) {
                    ofstream clear_terms(
                            "/mnt/c/Users/wnahl/OneDrive/Desktop/Classwork/2022 Spring/CS 2342/22s-final-project-will-nahley-2/persistence_index/PersistenceIndex.txt");
                    ofstream clear_persons(
                            "/mnt/c/Users/wnahl/OneDrive/Desktop/Classwork/2022 Spring/CS 2342/22s-final-project-will-nahley-2/persistence_index/PersonIndex.txt");
                    ofstream clear_orgs(
                            "/mnt/c/Users/wnahl/OneDrive/Desktop/Classwork/2022 Spring/CS 2342/22s-final-project-will-nahley-2/persistence_index/OrgIndex.txt");

                    clear_terms.clear();
                    clear_persons.clear();
                    clear_orgs.clear();

                    cout << "Indices have been cleared." << endl;
                }
            }

                break;
            case 4:
                //View statistics of search engine
            {
                cout << "Number of unique articles indexed: " << total_num_articles() << endl;
                cout << "Number of unique terms indexed: " << total_num_words_indexed() << endl;
                cout << "Number of unique orgs indexed: " << total_unique_orgs() << endl;
                cout << "Number of unique people indexed: " << total_unique_persons() << endl;
            }
                break;
            case 5:
                //Quit
                break;

            default:
                cout << "Not a valid selection..." << endl;
                break;
        }


    } while (choice != 5);

}


int SearchEngine::total_num_articles() {
    IndexHandler temp("NA", "/mnt/c/Users/wnahl/OneDrive/Desktop/JSONData/archive/archive", 't');
    return temp.get_unique_articles();
}

int SearchEngine::total_num_words_indexed() {
    ifstream in ("/mnt/c/Users/wnahl/OneDrive/Desktop/Classwork/2022 Spring/CS 2342/22s-final-project-will-nahley-2/persistence_index/PersistenceIndex.txt");
    int counter = 0;
    string cur_line;
    while (getline(in,cur_line, '\n')) {
        counter++;
    }
    return counter;

}
int SearchEngine::total_unique_orgs() {
    ifstream in ("/mnt/c/Users/wnahl/OneDrive/Desktop/Classwork/2022 Spring/CS 2342/22s-final-project-will-nahley-2/persistence_index/OrgIndex.txt");
    int counter = 0;
    string cur_line;
    while (getline(in,cur_line, '\n')) {
        counter++;
    }
    return counter;

}
int SearchEngine::total_unique_persons() {
    ifstream in ("/mnt/c/Users/wnahl/OneDrive/Desktop/Classwork/2022 Spring/CS 2342/22s-final-project-will-nahley-2/persistence_index/PersonIndex.txt");
    int counter = 0;
    string cur_line;
    while (getline(in,cur_line, '\n')) {
        counter++;
    }
    return counter;
}
