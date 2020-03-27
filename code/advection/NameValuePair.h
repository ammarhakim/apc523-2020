/* Class to read input file */
#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>

class NameValuePair {
  public:
/** 
 * @param fname File containing data.
 */
    NameValuePair(const std::string& fname) {
      std::string line;
      // open file for reading
      std::ifstream file(fname.c_str());
      if (!file)
        throw std::runtime_error("NameValuePair::NameValuePair: Unable to open input file");
      // loop over each line in file
      while (std::getline(file, line)) {
        auto commentLoc = line.find('#');
        auto myLine = line.substr(0, commentLoc);
        if (myLine != "") {
          // only work on non-blank line: horribly ugly, but works
          auto eqLoc = myLine.find('=');
          std::string lhs, lhsStr, valueStr;
          lhsStr = myLine.substr(0, eqLoc);
          valueStr = myLine.substr(eqLoc+1, std::string::npos);
          std::istringstream lhsToken(lhsStr);
          lhsToken >> lhs;

          double value;
          std::istringstream tokens(valueStr);
          tokens >> value;
          nvmap[lhs] = value;
        }
      }
    }

/** 
 * @param name Name to lookup
 * @return value associated with name
 */
    double getValue(const std::string& name) const {
      auto itr = nvmap.find(name);
      if (itr != nvmap.end())
        return itr->second;
      throw std::runtime_error("NameValuePair::getValue: not found");
    }

/**
 * @param name Name to lookup
 * @return true if it exists, false otherwise
 */
    bool hasValue(const std::string& name) const {
      auto itr = nvmap.find(name);
      if (itr != nvmap.end())
        return true;
      return false;
    }

  private:
    /* Name -> value map */
    std::map<std::string, double> nvmap;
};
