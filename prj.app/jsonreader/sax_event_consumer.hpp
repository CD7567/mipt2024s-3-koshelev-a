#ifndef JSON_SAX_EVENT_CONSUMER_HXX
#define JSON_SAX_EVENT_CONSUMER_HXX

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class SAXEventConsumer : public json::json_sax_t {
  public:
    std::vector<std::string> events;

    bool null() override {
#ifndef DO_JSON_SKIP_WRITING
        events.emplace_back("null()");
#endif
        return true;
    }

    bool boolean(bool value) override {
#ifndef DO_JSON_SKIP_WRITING
        events.push_back(
            "boolean(value=" + std::string(value ? "true" : "false") + ")");
#endif
        return true;
    }

    bool number_integer(number_integer_t value) override {
#ifndef DO_JSON_SKIP_WRITING
        events.push_back("number_integer(value=" + std::to_string(value) + ")");
#endif
        return true;
    }

    bool number_unsigned(number_unsigned_t value) override {
#ifndef DO_JSON_SKIP_WRITING
        events.push_back("number_unsigned(value=" + std::to_string(value) +
                         ")");
#endif
        return true;
    }

    bool number_float(number_float_t value, const string_t& string) override {
#ifndef DO_JSON_SKIP_WRITING
        events.push_back("number_float(value=" + std::to_string(value) +
                         ", string=" + string + ")");
#endif
        return true;
    }

    bool string(string_t& value) override {
#ifndef DO_JSON_SKIP_WRITING
        events.push_back("string(value=" + value + ")");
#endif
        return true;
    }

    bool start_object(std::size_t elements) override {
#ifndef DO_JSON_SKIP_WRITING
        events.push_back("start_object(elements=" + std::to_string(elements) +
                         ")");
#endif
        return true;
    }

    bool end_object() override {
#ifndef DO_JSON_SKIP_WRITING
        events.emplace_back("end_object()");
#endif
        return true;
    }

    bool start_array(std::size_t elements) override {
#ifndef DO_JSON_SKIP_WRITING
        events.push_back("start_array(elements=" + std::to_string(elements) +
                         ")");
#endif
        return true;
    }

    bool end_array() override {
#ifndef DO_JSON_SKIP_WRITING
        events.emplace_back("end_array()");
#endif
        return true;
    }

    bool key(string_t& value) override {
#ifndef DO_JSON_SKIP_WRITING
        events.push_back("key(value=" + value + ")");
#endif
        return true;
    }

    bool binary(json::binary_t&) override {
#ifndef DO_JSON_SKIP_WRITING
        events.emplace_back("binary(value=[...])");
#endif
        return true;
    }

    bool parse_error(std::size_t position, const std::string& last_token,
                     const json::exception& exception) override {
#ifndef DO_JSON_SKIP_WRITING
        events.push_back(
            "parse_error(position=" + std::to_string(position) +
            ", last_token=" + last_token +
            ",\n            exception=" + std::string(exception.what()) + ")");
#endif
        return false;
    }
};

#endif  // JSON_SAX_EVENT_CONSUMER_HXX
