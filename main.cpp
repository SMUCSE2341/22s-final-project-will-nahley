#include "engine_architecture/IndexHandler.h"
#include "engine_architecture/SearchEngine.h"

using namespace std;

int main() {

    SearchEngine search;
    search.go();

    string path = "/mnt/c/Users/wnahl/OneDrive/Desktop/JSONData/archive/archive/Half_data";
    IndexHandler h("finance", path, 't');
    h.populate_tree();

    return 0;
}
