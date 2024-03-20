#ifndef JSON_LIB_BUFFERED_PARSER_HXX
#define JSON_LIB_BUFFERED_PARSER_HXX

#include <fstream>
#include <string>
#include <vector>

#include "json-lib/common.hxx"

namespace json_lib {

class FullreadParser {
  private:
    std::ifstream f_in_stream_;
    std::vector<JSONBlock> blocks_;
    std::string buffer_;
    std::string::iterator buffer_it_;

    inline void ParseUserEntry(JSONEntry<std::string>& entry);

    inline void ParseQuestionEntry(JSONEntry<std::string>& entry);

    inline void ParseScoreEntry(JSONEntry<int>& entry);

    inline void ParseBlock(JSONBlock& block);

  public:
    explicit FullreadParser(const char* json_path) : f_in_stream_(json_path) {
        std::getline(f_in_stream_, buffer_);
    }

    void Parse();

    std::vector<JSONBlock>& GetData();
};

}  // namespace json_lib

#endif  // JSON_LIB_BUFFERED_PARSER_HXX
