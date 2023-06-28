#pragma once

#include <array>
#include <string>
#include <string_view>

namespace zfish {

using CodeType = uint64_t;
using Byte = uint8_t;

// 码数
constexpr int kCodeNum = 256;
// 压缩识别符长度
constexpr int kLenOfZipName = 16;
// 文件名长度
constexpr int kLenOfFileName = 256;
// 文件大小值长度
constexpr int kLenOfFileSize = 8;
// 码频值长度
constexpr int kLenOfCodeFrequency = 8;
// 头文件信息长度
constexpr int kLenOfZipHeader =
    kLenOfZipName + kLenOfFileName + kLenOfFileSize + kLenOfCodeFrequency * kCodeNum;
// 压缩 识别符
constexpr std::string_view kZipName = "zzzfish";

// 码点
struct HuffmanCodePoint {
    Byte old_code{0};            // 旧码
    CodeType frequency{0};       // 频率
    CodeType new_code{0};        // 新码
    int length{0};               // 新码长度
    std::string new_code_str{};  // 新码字符串表示（debug用）
};

// Huffman 节点
struct HuffmanTreeNode {
    CodeType weight{0};                // 权重
    HuffmanCodePoint* point{nullptr};  // 指向码点（叶子节点才有指向）
    HuffmanTreeNode* left{nullptr};    // 左分支
    HuffmanTreeNode* right{nullptr};   // 右分支

    explicit HuffmanTreeNode(CodeType weight = 0, HuffmanCodePoint* point = nullptr,
                             HuffmanTreeNode* left = nullptr, HuffmanTreeNode* right = nullptr)
        : weight(weight), point(point), left(left), right(right) {}
};

// 自定义比较器，用于优先队列
struct CmparatorOfHuffmanTreeNode {
    auto operator()(HuffmanTreeNode*& lhs, HuffmanTreeNode*& rhs) const -> bool {
        return lhs->weight > rhs->weight;
    }
};

class HuffmanEncoder {
public:
    explicit HuffmanEncoder(const std::string& inputFileName, bool isCompress = false);
    ~HuffmanEncoder();

    // 禁止拷贝和移动
    HuffmanEncoder(const HuffmanEncoder&) = delete;
    HuffmanEncoder(HuffmanEncoder&&) noexcept = delete;
    auto operator=(const HuffmanEncoder&) -> HuffmanEncoder& = delete;
    auto operator=(HuffmanEncoder&&) noexcept -> HuffmanEncoder& = delete;

    /// 如果是未压缩的，则进行压缩，如果是压缩，则解压缩
    void run();

    // 统计频率
    void statisticalFrequency();

    // 构建 Huffman 树
    auto buildHuffmanTree() -> HuffmanTreeNode*;

    // 获得 Huffman 编码
    void initCodePoint(HuffmanTreeNode* node, CodeType new_code, const std::string& new_code_str,
                       int length);

    // 压缩文件
    void compress();

    // 搜索节点，辅助于解码
    auto findNode(HuffmanTreeNode*& node, Byte inputByte, int& pos) -> bool;

    // 解压缩
    void uncompress();

    // 打印哈夫曼编码信息
    void printHuffmanEncodeInfo();

    // 打印压缩或解压缩信息
    void printInfo(const char* type) const;

    // 获取输出文件名
    [[nodiscard]] auto getOutputFileName() const -> const std::string& {
        return output_filename_;
    }

    // 判断两个文件是否相等
    [[nodiscard]] static auto equalFile(const std::string& fileName1, const std::string& fileName2)
        -> bool;

private:
    // 释放节点
    void freeNode(HuffmanTreeNode* node);

    std::array<HuffmanCodePoint, kCodeNum> points_;  // 码
    HuffmanTreeNode* root_;                          // Huffman树根节点
    bool is_compressed_;                             // 是否压缩（用于多次压缩 ）

    std::string input_filename_;   // 输入文件名
    std::string output_filename_;  // 输出文件名
    CodeType input_filesize_;      // 输入文件大小
    CodeType output_filesize_;     // 输出文件大小
};

}  // namespace zfish
