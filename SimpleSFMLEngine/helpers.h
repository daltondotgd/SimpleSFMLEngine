#pragma once

inline bool endsWith(const std::string &str, const std::string &suffix)
{
    return str.size() >= suffix.size() &&
        str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

inline bool startsWith(const std::string &str, const std::string &prefix)
{
    return str.size() >= prefix.size() &&
        str.compare(0, prefix.size(), prefix) == 0;
}
