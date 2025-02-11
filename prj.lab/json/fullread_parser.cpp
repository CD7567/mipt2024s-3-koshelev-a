#include "fullread_parser.hpp"

std::vector<JSONBlock>& FullreadParser::GetData() { return blocks_; }

void FullreadParser::ParseUserEntry(JSONEntry<std::string>& entry) {
    // Skip label, colon and opening quote
    std::advance(buffer_it_, USER_LABEL_LENGTH + 4);

    // Read value
#ifndef DO_JSON_SKIP_WRITING
    entry.value_.append(buffer_it_, buffer_it_ + USER_VALUE_LENGTH);
#endif

    // Skip value and closing quote
    std::advance(buffer_it_, USER_VALUE_LENGTH + 1);
}

void FullreadParser::ParseQuestionEntry(JSONEntry<std::string>& entry) {
    // Skip label, colon and opening quote
    std::advance(buffer_it_, QUESTION_LABEL_LENGTH + 4);

    // Read value
#ifndef DO_JSON_SKIP_WRITING
    entry.value_.append(buffer_it_, buffer_it_ + QUESTION_VALUE_LENGTH);
#endif

    // Skip value and closing quote
    std::advance(buffer_it_, QUESTION_VALUE_LENGTH + 1);
}

void FullreadParser::ParseScoreEntry(JSONEntry<int>& entry) {
    entry.value_ = 0;

    // Skip label and colon
    std::advance(buffer_it_, SCORE_LABEL_LENGTH + 3);

    // Read value
    for (size_t i = 0; i < SCORE_VALUE_LENGTH; ++i, ++buffer_it_) {
#ifndef DO_JSON_SKIP_WRITING
        entry.value_ = entry.value_ * 10 + (*buffer_it_ - 48);
#endif
    }
}

void FullreadParser::ParseBlock(JSONBlock& block) {
    // Skip opening bracket
    ++buffer_it_;

    ParseUserEntry(block.user_);

    // Skip comma
    ++buffer_it_;

    ParseQuestionEntry(block.question_);

    // Skip comma
    ++buffer_it_;

    ParseScoreEntry(block.score_);

    // Skip closing bracket
    ++buffer_it_;
}

void FullreadParser::Parse() {
    buffer_it_ = buffer_.begin();

    // Skip opening square bracket
    ++buffer_it_;

    // Read blocks
    while (*buffer_it_ != ']') {
        JSONBlock& last = blocks_.emplace_back();
        ParseBlock(last);

        if (*buffer_it_ == ',') {
            ++buffer_it_;
        }
    }
}
