#ifndef JSON_LIB_STREAM_PARSER_HXX
#define JSON_LIB_STREAM_PARSER_HXX

#include <cctype>
#include <fstream>
#include <vector>
#include <string>

#include "json-lib/common.hxx"

namespace json_lib {

class StreamParser {
  private:
    std::ifstream f_in_stream_;
    std::vector<JSONBlock> blocks_;

    inline void ParseUserEntry(JSONEntry<std::string>& entry);

    inline void ParseQuestionEntry(JSONEntry<std::string>& entry);

    inline void ParseScoreEntry(JSONEntry<int>& entry);

    inline void ParseBlock(JSONBlock& block);

  public:
    explicit StreamParser(const char* json_path) : f_in_stream_(json_path) {}

    void Parse();

    std::vector<JSONBlock>& GetData();
};

}  // namespace json_lib

#endif  // JSON_LIB_STREAM_PARSER_HXX
