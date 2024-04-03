#ifndef JSON_LIB_STREAM_PARSER_HXX
#define JSON_LIB_STREAM_PARSER_HXX

#include <fstream>
#include <iterator>
#include <string>
#include <vector>

#include "common.hpp"

class StreamParser {
  private:
    std::ifstream f_in_stream_;
    std::istreambuf_iterator<char> f_in_it_;
    std::vector<JSONBlock> blocks_;

    inline void ParseUserEntry(JSONEntry<std::string>& entry);

    inline void ParseQuestionEntry(JSONEntry<std::string>& entry);

    inline void ParseScoreEntry(JSONEntry<int>& entry);

    inline void ParseBlock(JSONBlock& block);

  public:
    explicit StreamParser(const char* json_path)
        : f_in_stream_(json_path), f_in_it_(f_in_stream_) {}

    void Parse();

    std::vector<JSONBlock>& GetData();
};

#endif  // JSON_LIB_STREAM_PARSER_HXX
