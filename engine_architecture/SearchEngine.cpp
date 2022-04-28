#include "SearchEngine.h"

SearchEngine::SearchEngine() {
    search_path = "/mnt/c/Users/wnahl/sample_data_sets/size-10";
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

        cin >> choice;

        switch (choice) {
            case 1:
                //Query
                {
                    cout << "Please enter a query:" << endl;
                    string search_term;
                    cin >> search_term;
                    QueryProcessor query(search_term, search_path);

                    IndexHandler index_handler (search_term, search_path, 't');
                    vector<string> ids = index_handler.get_correct_documents();

                    cout << "The term '" << search_term << "' appears in " << ids.size() << " document(s):" << endl;
                    for (int i = 0; i < ids.size(); i++) {
                        cout << (i + 1) << ": " << ids[i] << endl;
                    }
                }
                break;
            case 2:
                //View index
                break;
            case 3:
                //Clear index
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
