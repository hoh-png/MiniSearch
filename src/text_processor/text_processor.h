#ifndef TEXT_PROCESSOR_H
#define TEXT_PROCESSOR_H

#include <vector>
#include <string>
#include <map>

#ifdef TEXTPROCESSOR_EXPORTS
#   define TEXT_PROC_API __declspec(dllexport)
#else
#   define TEXT_PROC_API __declspec(dllimport)
#endif

struct DocInfo {
    int doc_id;
    std::map<std::string, int> word_tf;
};

struct Posting {
    int doc_id;
    int tf;
};

using InvertMap = std::map<std::string, std::vector<Posting>>;

TEXT_PROC_API void build_invert_index(const std::vector<DocInfo>& docs, const std::string& save_path);

TEXT_PROC_API InvertMap load_invert_index(const std::string& load_path);

TEXT_PROC_API int get_total_doc_count();

#endif