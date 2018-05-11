#pragma once

using WordFrequency = std::map<std::string, int>;

WordFrequency CountFrequencyWords(std::istream &inputStrm, std::ostream &outputStrm);
void PrintWordFrequncy(std::ostream &output, const WordFrequency &wordFrequency);