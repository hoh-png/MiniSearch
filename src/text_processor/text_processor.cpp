#include "text_processor.h"
#include <fstream>
static int global_total_docs = 0;

int get_total_doc_count() {
    return global_total_docs;
}

void build_invert_index(const std::vector<DocInfo>& docs, const std::string& save_path)
{
    InvertMap invert_table;
    global_total_docs = docs.size();

    for (const DocInfo& doc : docs)
    {
        for (const auto& word_pair : doc.word_tf)
        {
            const std::string& word = word_pair.first;
            int word_freq = word_pair.second;
            invert_table[word].push_back({doc.doc_id, word_freq});
        }
    }

    std::ofstream out_file(save_path, std::ios::binary);
    size_t word_count = invert_table.size();
    out_file.write((char*)&word_count, sizeof(size_t));

    for (const auto& entry : invert_table)
    {
        const std::string& word = entry.first;
        const std::vector<Posting>& post_list = entry.second;

        size_t word_len = word.size();
        out_file.write((char*)&word_len, sizeof(size_t));
        out_file.write(word.data(), word_len);

        size_t doc_num = post_list.size();
        out_file.write((char*)&doc_num, sizeof(size_t));

        for (const Posting& item : post_list)
        {
            out_file.write((char*)&item.doc_id, sizeof(int));
            out_file.write((char*)&item.tf, sizeof(int));
        }
    }
    out_file.close();
}

InvertMap load_invert_index(const std::string& load_path)
{
    InvertMap invert_table;
    std::ifstream in_file(load_path, std::ios::binary);
    if (!in_file.is_open())
    {
        return invert_table;
    }

    size_t word_count;
    in_file.read((char*)&word_count, sizeof(size_t));

    for (size_t i = 0; i < word_count; i++)
    {
        size_t word_len;
        in_file.read((char*)&word_len, sizeof(size_t));
        std::string word(word_len, ' ');
        in_file.read(&word[0], word_len);

        size_t doc_num;
        in_file.read((char*)&doc_num, sizeof(size_t));
        std::vector<Posting> post_list;

        for (size_t j = 0; j < doc_num; j++)
        {
            int did, tf;
            in_file.read((char*)&did, sizeof(int));
            in_file.read((char*)&tf, sizeof(int));
            post_list.push_back({did, tf});
        }
        invert_table[word] = post_list;
    }
    in_file.close();
    return invert_table;
}