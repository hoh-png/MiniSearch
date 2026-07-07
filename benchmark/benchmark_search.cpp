#include <benchmark/benchmark.h>
#include "query_engine.h"
#include "file_reader.h"

static void BM_ParseQuery_Simple(benchmark::State& state) {
    std::string query = "hello world";
    for (auto _ : state) {
        auto result = parseQuery(query);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_ParseQuery_Simple);

static void BM_ParseQuery_Phrase(benchmark::State& state) {
    std::string query = "hello \"machine learning\" world";
    for (auto _ : state) {
        auto result = parseQuery(query);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_ParseQuery_Phrase);

static void BM_CleanAndSplit(benchmark::State& state) {
    std::string text(state.range(0), 'a');
    for (auto _ : state) {
        auto words = cleanAndSplit(text);
        benchmark::DoNotOptimize(words);
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_CleanAndSplit)
    ->RangeMultiplier(2)
    ->Range(1024, 64 << 10)
    ->Complexity();

static void BM_ProcessTxtFolder(benchmark::State& state) {
    ResetDocId();
    for (auto _ : state) {
        DocData* docArr = nullptr;
        int docCount = 0;
        int ret = ProcessTxtFolder(".", &docArr, &docCount);
        benchmark::DoNotOptimize(ret);
        if (docArr) FreeDocDataArray(docArr, docCount);
    }
}
BENCHMARK(BM_ProcessTxtFolder);

BENCHMARK_MAIN();