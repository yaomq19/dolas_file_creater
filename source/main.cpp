#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void replaceStringInBuffer(std::vector<char>& buffer, const std::string& target, const std::string& replacement) {
    std::string content(buffer.data());  // 将 char 数组转换为 std::string
    size_t pos = 0;

    // 替换所有出现的 target 字符串
    while ((pos = content.find(target, pos)) != std::string::npos) {
        content.replace(pos, target.length(), replacement);
        pos += replacement.length();  // 移动到下一个位置
    }

    // 将替换后的内容更新回 buffer
    buffer.assign(content.begin(), content.end());
    buffer.push_back('\0');  // 添加字符串结束符
}

std::string toUpperCase(const std::string& input) {
    std::string output = input; // 创建一个输出字符串
    for (char& c : output) {
        c = std::toupper(static_cast<unsigned char>(c)); // 将每个字符转换为大写
    }
    return output; // 返回转换后的字符串
}

std::string capitalizeAndRemoveUnderscores(const std::string& input) {
    std::string output;
    bool capitalizeNext = true; // 标志位，用于确定是否需要大写

    for (char c : input) {
        if (c == '_') {
            capitalizeNext = true; // 遇到下划线，设置下一个字符为大写
            continue; // 跳过下划线
        }

        if (capitalizeNext) {
            output += std::toupper(static_cast<unsigned char>(c)); // 大写字符
            capitalizeNext = false; // 重置标志位
        }
        else {
            output += c; // 添加小写字符
        }
    }

    return output;
}

void writeVectorToFile(const std::string& filename, const std::vector<char>& buffer) {
    std::ofstream file(filename, std::ios::binary); // 以二进制模式打开文件
    if (!file.is_open()) {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return;
    }

    // 将 vector<char> 的内容写入文件
    file.write(buffer.data(), buffer.size() - 1);

    // 关闭文件
    file.close();
    std::cout << "内容已成功写入文件: " << filename << std::endl;
}
int main()
{
    string input;
    cout << "input file name:" << endl;
    cin >> input;

    string cpp_filename = "dolas_" + input + ".cpp";
    string h_filename = "dolas_" + input + ".h";

    // 打开文件
    std::ifstream file("template.h");
    // 检查文件是否成功打开
    if (!file.is_open()) {
        std::cerr << "无法打开文件!" << std::endl;
        return 1;
    }
    // 读取文件内容
    std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    // 关闭文件
    file.close();
    // 添加字符串结束符
    buffer.push_back('\0');

    string input_upper = toUpperCase(input);
    replaceStringInBuffer(buffer, "MACRONAME", input_upper);
    string className = capitalizeAndRemoveUnderscores(input);
    replaceStringInBuffer(buffer, "ClassName", className);

    writeVectorToFile(h_filename, buffer);

    // 打开文件
    std::ifstream file2("template.cpp");
    // 检查文件是否成功打开
    if (!file2.is_open()) {
		std::cerr << "无法打开文件!" << std::endl;
		return 1;
	}
    // 读取文件内容
    std::vector<char> buffer2((std::istreambuf_iterator<char>(file2)), std::istreambuf_iterator<char>());
    // 关闭文件
    file2.close();
    // 添加字符串结束符
    buffer2.push_back('\0');

    replaceStringInBuffer(buffer2, "header", input);
    replaceStringInBuffer(buffer2, "ClassName", className);

    writeVectorToFile(cpp_filename, buffer2);


    return 0;
}