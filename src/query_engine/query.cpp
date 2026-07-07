#include "../headers/query.h"
#include <cctype>
#include <sstream>
#include <algorithm>

// 文本清洗、分词：转小写、剔除标点、按空格分割
std::vector<std::string> cleanAndSplit(const std::string& rawText)
{
    std::vector<std::string> wordList;
    std::stringstream iss(rawText);
    std::string word;

    while (iss >> word)
    {
        std::string cleanWord;
        for (char c : word)
        {
            if (isalpha(c))
                cleanWord += static_cast<char>(tolower(c));
        }
        if (!cleanWord.empty())
            wordList.push_back(cleanWord);
    }
    return wordList;
}

// 核心解析函数：识别双引号短语，区分检索类型
QueryResult parseQuery(const std::string& inputStr)
{
    QueryResult res;
    size_t leftQuote = inputStr.find('"');
    size_t rightQuote = inputStr.find('"', leftQuote + 1);

    // 存在成对双引号 → 短语检索模式
    if (leftQuote != std::string::npos && rightQuote != std::string::npos && rightQuote > leftQuote)
    {
        res.type = QueryType::PhraseSearch;
        // 截取引号内原始短语
        res.rawPhrase = inputStr.substr(leftQuote + 1, rightQuote - leftQuote - 1);
        // 短语分词，存入单词列表
        res.words = cleanAndSplit(res.rawPhrase);
    }
    // 无引号 → 普通关键词检索
    else
    {
        res.type = QueryType::NormalKeyword;
        res.rawPhrase = "";
        res.words = cleanAndSplit(inputStr);
    }
    return res;
}