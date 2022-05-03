//
// Created by wnahl on 5/2/2022.
//

#include "DSDoc.h"

using namespace std;

DSDoc::DSDoc(std::string filepath, std::vector<std::string> terms) {
    this->filepath = filepath;
    this->terms = terms;
    string cur_line;
    string whole_file;
    ifstream in(filepath);
    while (getline(in, cur_line)) {
        whole_file += cur_line + '\n';
    }
    in.close();
    doc.Parse(whole_file.c_str());
    relevancy = get_relevancy();
}

DSDoc::DSDoc(const DSDoc& other) {
    this->filepath = other.filepath;
    string cur_line;
    string whole_file;
    ifstream in(other.filepath);
    while (getline(in, cur_line)) {
        whole_file += cur_line + '\n';
    }
    in.close();
    this->doc.Parse(whole_file.c_str());
    this->relevancy = other.relevancy;
    this->terms = other.terms;
}

DSDoc& DSDoc::operator= (const DSDoc& other) {
    this->filepath = other.filepath;
    string cur_line;
    string whole_file;
    ifstream in(other.filepath);
    while (getline(in, cur_line)) {
        whole_file += cur_line + '\n';
    }
    in.close();
    this->doc.Parse(whole_file.c_str());
    this->relevancy = other.relevancy;
    this->terms = other.terms;
    return *this;
}

std::string DSDoc::get_title() {
    string title = doc["title"].GetString();
    return title;
}

std::string DSDoc::get_text() {
    string text = doc["text"].GetString();
    return text;
}

std::string DSDoc::get_publication() {
    string publication = doc["thread"]["site"].GetString();
    return publication;

}

std::string DSDoc::get_url() {
    string url = doc["url"].GetString();
    return url;
}

std::string DSDoc::get_date_published() {
    string date = doc["published"].GetString();
    return date;
}

double DSDoc::get_relevancy() {
    double relevancy = 0.0;
    double correct_words = 0;
    int total_words = 0;
    string text = doc["text"].GetString();

    string word = "";
    for (int i = 0; i < text.size(); i++) {
        if (text[i] == ' ') {
            //CHECK IF WORD IS STOP WORD?

            for (int j = 0; j < terms.size(); j++) {
                if (word == terms[j])
                    correct_words+= 1;
            }
            total_words++;
            word = "";
        } else {
            word += text[i];
        }
    }

    relevancy = correct_words/total_words;

    return relevancy;
}

bool DSDoc::operator<(const DSDoc &other) const {
    if (this->relevancy < other.relevancy ) {
        return true;
    }
    return false;
}


