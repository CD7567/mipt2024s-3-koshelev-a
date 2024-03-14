#include "json-lib/stream_parser.hxx"

namespace json_lib {

void StreamParser::ParseUserEntry(JSONEntry<std::string>& entry) {
    // Skip label and colon
    std::advance(f_in_it_, USER_LABEL_LENGTH + 1);

    // Read value
    for (size_t i = 0; i < USER_VALUE_LENGTH; ++i, ++f_in_it_) {
#ifndef DO_JSON_SKIP_WRITING
        entry.value_.push_back(*f_in_it_);
#endif
    }
}

void StreamParser::ParseQuestionEntry(JSONEntry<std::string>& entry) {
    // Skip label and colon
    std::advance(f_in_it_, QUESTION_LABEL_LENGTH + 1);

    // Read value
    for (size_t i = 0; i < QUESTION_VALUE_LENGTH; ++i, ++f_in_it_) {
#ifndef DO_JSON_SKIP_WRITING
        entry.value_.push_back(*f_in_it_);
#endif
    }
}

void StreamParser::ParseScoreEntry(JSONEntry<int>& entry) {
    entry.value_ = 0;

    // Skip label and colon
    std::advance(f_in_it_, SCORE_LABEL_LENGTH + 1);

    // Read value
    for (size_t i = 0; i < SCORE_VALUE_LENGTH; ++i, ++f_in_it_) {
#ifndef DO_JSON_SKIP_WRITING
        entry.value_ = entry.value_ * 10 + (*f_in_it_ - 48);
#endif
    }
}

inline void StreamParser::ParseBlock(JSONBlock& block) {
    // Skip opening bracket
    ++f_in_it_;

    ParseUserEntry(block.user_);

    // Skip comma
    ++f_in_it_;

    ParseQuestionEntry(block.question_);

    // Skip comma
    ++f_in_it_;

    ParseScoreEntry(block.score_);

    // Skip closing bracket
    ++f_in_it_;
}

void StreamParser::Parse() {
    f_in_it_ = std::istreambuf_iterator<char>(f_in_stream_);

    // Skip opening square bracket
    ++f_in_it_;

    // Read blocks
    while (!f_in_stream_.eof() && f_in_stream_.peek() != ']') {
        auto last = blocks_.emplace_back();
        ParseBlock(last);

        if (*f_in_it_ == ',') {
            ++f_in_it_;
        }
    }
}

std::vector<JSONBlock>& StreamParser::GetData() { return blocks_; }

}  // namespace json_lib
