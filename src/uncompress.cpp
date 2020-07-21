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

/* TODO: Pseudo decompression with ascii encoding and naive header (checkpoint)
 */
void pseudoDecompression(const string& inFileName, const string& outFileName) {
    ifstream theInFile;
    ofstream theOutFile;
    theInFile.open(inFileName, ios::binary);
    theOutFile.open(outFileName, ios::binary);
    unsigned char nextChar;
    string stringLine;
    vector<string> stringFile;
    vector<unsigned int> freqs(256);
    vector<unsigned char> temp;
    HCTree tree;

    // build tree
    for (int i = 0; i < 256; i++) {
        getline(theInFile, stringLine);
        stringFile.push_back(stringLine);
    }
    for (int i = 0; i < 256; i++) {
        freqs[i] = stoi(stringFile[i]);
    }

    tree.build(freqs);

    // decode

    // theInFile =
    // 10101010101010101010111111111111111111110111011101000000000000000000001100

    while (1) {
        if (theInFile.eof()) {
            break;
        }
        if (theInFile.peek() != -1) {
            theOutFile << tree.decode(theInFile);
        }
    }
}

/* TODO: True decompression with bitwise i/o and small header (final) */
void trueDecompression(const string& inFileName, const string& outFileName) {}

/* Main program that runs the decompression */
int main(int argc, char* argv[]) {
    cxxopts::Options options(argv[0],
                             "Uncompresses files using Huffman Encoding");
    options.positional_help(
        "./path_to_compressed_input_file ./path_to_output_file");

    bool isAscii = false;
    string inFileName, outFileName;
    options.allow_unrecognised_options().add_options()(
        "ascii", "Read input in ascii mode instead of bit stream",
        cxxopts::value<bool>(isAscii))("input", "",
                                       cxxopts::value<string>(inFileName))(
        "output", "", cxxopts::value<string>(outFileName))(
        "h,help", "Print help and exit.");

    options.parse_positional({"input", "output"});
    auto userOptions = options.parse(argc, argv);

    if (userOptions.count("help") || !FileUtils::isValidFile(inFileName) ||
        outFileName.empty()) {
        cout << options.help({""}) << std::endl;
        exit(0);
    }

    // if compressed file is empty, output empty file
    if (FileUtils::isEmptyFile(inFileName)) {
        ofstream outFile;
        outFile.open(outFileName, ios::out);
        outFile.close();
        exit(0);
    }

    if (isAscii) {
        pseudoDecompression(inFileName, outFileName);
    } else {
        trueDecompression(inFileName, outFileName);
    }

    return 0;
}
