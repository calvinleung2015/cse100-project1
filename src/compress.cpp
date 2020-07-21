/**
 * TODO: file header
 *
 * Author:
 */
#include <cxxopts.hpp>
#include <fstream>
#include <iostream>

#include "FileUtils.hpp"
#include "HCNode.hpp"
#include "HCTree.hpp"

/* TODO: add pseudo compression with ascii encoding and naive header
 * (checkpoint) */
void pseudoCompression(const string& inFileName, const string& outFileName) {
    ifstream theInFile;
    ofstream theOutFile;
    theInFile.open(inFileName, ios::binary);
    theOutFile.open(outFileName, ios::binary);
    unsigned char nextChar;

    // build tree
    map<unsigned char, int> mp;
    vector<unsigned int> freqs(256);
    vector<unsigned char> s;
    int count = 1;
    HCTree tree;

    while (1) {
        nextChar = theInFile.get();
        if (theInFile.eof()) {
            break;
        }
        s.push_back(nextChar);

        if (mp.find(nextChar)->first == nextChar) {
            mp.find(nextChar)->second++;
        } else {
            mp.insert(pair<unsigned char, int>(nextChar, count));
        }
    }

    for (map<unsigned char, int>::iterator it = mp.begin(); it != mp.end();
         ++it) {
        freqs[it->first] = it->second;
    }

    for (unsigned int i = 0; i < freqs.size(); i++) {
        theOutFile << freqs[i] << endl;
    }

    tree.build(freqs);
    ostringstream os;
    for (unsigned int i = 0; i < s.size(); i++) {
        tree.encode(s.at(i), os);
    }

    theOutFile << os.str();
}

/* TODO: True compression with bitwise i/o and small header (final) */
void trueCompression(const string& inFileName, const string& outFileName) {}

/* Main program that runs the compression */
int main(int argc, char* argv[]) {
    cxxopts::Options options(argv[0],
                             "Compresses files using Huffman Encoding");
    options.positional_help("./path_to_input_file ./path_to_output_file");

    bool isAsciiOutput = false;
    string inFileName, outFileName;
    options.allow_unrecognised_options().add_options()(
        "ascii", "Write output in ascii mode instead of bit stream",
        cxxopts::value<bool>(isAsciiOutput))(
        "input", "", cxxopts::value<string>(inFileName))(
        "output", "", cxxopts::value<string>(outFileName))(
        "h,help", "Print help and exit");

    options.parse_positional({"input", "output"});
    auto userOptions = options.parse(argc, argv);

    if (userOptions.count("help") || !FileUtils::isValidFile(inFileName) ||
        outFileName.empty()) {
        cout << options.help({""}) << std::endl;
        return 0;
    }

    // if original file is empty, output empty file
    if (FileUtils::isEmptyFile(inFileName)) {
        ofstream outFile;
        outFile.open(outFileName, ios::out);
        outFile.close();
        return 0;
    }

    if (isAsciiOutput) {
        pseudoCompression(inFileName, outFileName);
    } else {
        trueCompression(inFileName, outFileName);
    }

    return 0;
}