#include <iostream>
#include <list>
#include <string>
#include <unordered_set>
#include <cassert>

std::string get_complement(const std::string& nucleotide){
    /*
    Takes a nucleotide sequence as a string of the letters "A", "T", "C", and "G"
    and returns its complementary nucleotide as a string where "A" correlates to "T", "C" to "G"
    and "T" to "A" and "G" to "C" in the original inputted string.
    Args:
        nucleotide (str): A string representing a nucleotide sequence
    Returns:
        (str): A string representing the complement of the inputted nucleotide sequence
    */
    std::string comp = "";
    for (const char i : nucleotide) {
        if (i == 'A') {
            comp += 'T';
        }
        if (i == 'T') {
            comp += "A";
        }
        if (i == 'C') {
            comp += 'G';
        }
        if (i == 'G') {
            comp += 'C';
        }
    }

    return comp;
    }

std::string get_reverse_complement(std::string strand){
    /*
    Takes an inputted nucleotide sequence and returns its complement sequence reversed.
    Args:
        strand (str): A string representing a nucleotide sequence
    Returns:
        (str): A string representing the reversed complement sequence of the nucleotide
    */
    std::string rev(strand.rbegin(), strand.rend());
    return get_complement(rev);
}

std::string rest_of_orf(std::string strand){
    /*
    Takes an inputted nucleotide and returns an orf or open reading frame,
    meaning a nucleotide sequence that has a start codon as its beginning and a
    stop codon at its end, a multiple of 3 nucleotides greater than 3 away. If
    no stop codon is found, it returns an empty string.
    Args:
        strand (str): A nucleotide sequence
    Returns:
        (str): The first orf found within the strand, or an empty string
    */
    std::string total =  "";
    std::string slice = "";
    std::unordered_set<std::string> stop_codons = {"TAA", "TAG", "TGA"};
    for (char i : strand){
        total += i;
        slice += i;
        if (stop_codons.count(slice) > 0) {
            return total;
        }
        if (slice.length() > 2) {
            slice = "";
        }
    }
    return "";
    }

int main()
    {
        assert(get_complement("ATCG") == "TAGC");
        assert(get_reverse_complement("ATCG") == "CGAT");
        assert(rest_of_orf("ATGAAATAA") == "ATGAAATAA");   
    }
