#include <cassert>
#include <string>

#include "huffman_encoder.h"

auto main(int argc, char* argv[]) -> int {
    assert(argc >= 1);
    std::string filename = argv[1];  // 读取输入（也可在界面中拖动）
    zfish::HuffmanEncoder hec{filename};
    hec.run();
    getchar();

    return 0;
}
