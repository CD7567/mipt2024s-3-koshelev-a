#include "json-lib/stream_parser.hxx"

namespace json_lib {

void StreamParser::ParseUserEntry(JSONEntry<std::string>& entry) {
    char symb = 0;

    // Read label
    for (size_t i = 0; i < USER_LABEL_LENGTH; ++i) {
        f_in_stream_.read(&symb, 1);
    }

    // Read colon
    f_in_stream_.read(&symb, 1);

    // Read value
    for (size_t i = 0; i < USER_VALUE_LENGTH; ++i) {
        f_in_stream_.read(&symb, 1);
        entry.value_.push_back(symb);
    }
}

void StreamParser::ParseQuestionEntry(JSONEntry<std::string>& entry) {
    char symb = 0;

    // Read label
    for (size_t i = 0; i < QUESTION_LABEL_LENGTH; ++i) {
        f_in_stream_.read(&symb, 1);
    }

    // Read colon
    f_in_stream_.read(&symb, 1);

    // Read value
    for (size_t i = 0; i < QUESTION_VALUE_LENGTH; ++i) {
        f_in_stream_.read(&symb, 1);
        entry.value_.push_back(symb);
    }
}

void StreamParser::ParseScoreEntry(JSONEntry<int>& entry) {
    char symb = 0;

    entry.value_ = 0;

    // Read label
    for (size_t i = 0; i < SCORE_LABEL_LENGTH; ++i) {
        f_in_stream_.read(&symb, 1);
    }

    // Read colon
    f_in_stream_.read(&symb, 1);

    // Read value
    for (size_t i = 0; i < SCORE_VALUE_LENGTH; ++i) {
        f_in_stream_.read(&symb, 1);
        entry.value_ = entry.value_ * 10 + (symb - 48);
    }
}

inline void StreamParser::ParseBlock(JSONBlock& block) {
    char symb = 0;

    // Read opening bracket
    f_in_stream_.read(&symb, 1);

    ParseUserEntry(block.user_);

    // Read comma
    f_in_stream_.read(&symb, 1);

    ParseQuestionEntry(block.question_);

    // Read comma
    f_in_stream_.read(&symb, 1);

    ParseScoreEntry(block.score_);

    // Read closing bracket
    f_in_stream_.read(&symb, 1);
}

void StreamParser::Parse() {
    char symb = 0;

    // Read opening square bracket
    f_in_stream_.read(&symb, 1);

    // Read blocks
    while (!f_in_stream_.eof() && f_in_stream_.peek() != ']') {
        auto last = blocks_.emplace_back();
        ParseBlock(last);

        if (f_in_stream_.peek() == ',') {
            f_in_stream_.read(&symb, 1);
        }
    }
}

std::vector<JSONBlock>& StreamParser::GetData() { return blocks_; }

}  // namespace json_lib
