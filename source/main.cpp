#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void replaceStringInBuffer(std::vector<char>& buffer, const std::string& target, const std::string& replacement) {
    std::string content(buffer.data());  // �� char ����ת��Ϊ std::string
    size_t pos = 0;

    // �滻���г��ֵ� target �ַ���
    while ((pos = content.find(target, pos)) != std::string::npos) {
        content.replace(pos, target.length(), replacement);
        pos += replacement.length();  // �ƶ�����һ��λ��
    }

    // ���滻������ݸ��»� buffer
    buffer.assign(content.begin(), content.end());
    buffer.push_back('\0');  // ����ַ���������
}

std::string toUpperCase(const std::string& input) {
    std::string output = input; // ����һ������ַ���
    for (char& c : output) {
        c = std::toupper(static_cast<unsigned char>(c)); // ��ÿ���ַ�ת��Ϊ��д
    }
    return output; // ����ת������ַ���
}

std::string capitalizeAndRemoveUnderscores(const std::string& input) {
    std::string output;
    bool capitalizeNext = true; // ��־λ������ȷ���Ƿ���Ҫ��д

    for (char c : input) {
        if (c == '_') {
            capitalizeNext = true; // �����»��ߣ�������һ���ַ�Ϊ��д
            continue; // �����»���
        }

        if (capitalizeNext) {
            output += std::toupper(static_cast<unsigned char>(c)); // ��д�ַ�
            capitalizeNext = false; // ���ñ�־λ
        }
        else {
            output += c; // ���Сд�ַ�
        }
    }

    return output;
}

void writeVectorToFile(const std::string& filename, const std::vector<char>& buffer) {
    std::ofstream file(filename, std::ios::binary); // �Զ�����ģʽ���ļ�
    if (!file.is_open()) {
        std::cerr << "�޷����ļ�: " << filename << std::endl;
        return;
    }

    // �� vector<char> ������д���ļ�
    file.write(buffer.data(), buffer.size() - 1);

    // �ر��ļ�
    file.close();
    std::cout << "�����ѳɹ�д���ļ�: " << filename << std::endl;
}
int main()
{
    string input;
    cout << "input file name:" << endl;
    cin >> input;

    string cpp_filename = "dolas_" + input + ".cpp";
    string h_filename = "dolas_" + input + ".h";

    // ���ļ�
    std::ifstream file("template.h");
    // ����ļ��Ƿ�ɹ���
    if (!file.is_open()) {
        std::cerr << "�޷����ļ�!" << std::endl;
        return 1;
    }
    // ��ȡ�ļ�����
    std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    // �ر��ļ�
    file.close();
    // ����ַ���������
    buffer.push_back('\0');

    string input_upper = toUpperCase(input);
    replaceStringInBuffer(buffer, "MACRONAME", input_upper);
    string className = capitalizeAndRemoveUnderscores(input);
    replaceStringInBuffer(buffer, "ClassName", className);

    writeVectorToFile(h_filename, buffer);

    // ���ļ�
    std::ifstream file2("template.cpp");
    // ����ļ��Ƿ�ɹ���
    if (!file2.is_open()) {
		std::cerr << "�޷����ļ�!" << std::endl;
		return 1;
	}
    // ��ȡ�ļ�����
    std::vector<char> buffer2((std::istreambuf_iterator<char>(file2)), std::istreambuf_iterator<char>());
    // �ر��ļ�
    file2.close();
    // ����ַ���������
    buffer2.push_back('\0');

    replaceStringInBuffer(buffer2, "header", input);
    replaceStringInBuffer(buffer2, "ClassName", className);

    writeVectorToFile(cpp_filename, buffer2);


    return 0;
}