
#ifndef __COUT_STREAM_CONVERTOR_H__
#define __COUT_STREAM_CONVERTOR_H__

#include <iostream>
#include <sstream>
#include <fstream>

namespace KYTools {
    class StreamTools {
    private:
        std::streambuf* _oriCoutBuff = nullptr;
        std::stringstream _coutSSBuf;

        inline void __clear_buffer() {
            this->_coutSSBuf.str("");
            this->_coutSSBuf.clear();
        }
    public:
        inline StreamTools() = default;
        inline StreamTools(StreamTools&) = default;

        ~StreamTools() {
            this->close_cout_buffer();
        }

        inline void open_cout_buffer() {
            this->_oriCoutBuff = std::cout.rdbuf();
            std::cout.rdbuf(this->_coutSSBuf.rdbuf());
        }

        inline void to_file(const std::string& fileNameOut) {
            std::ofstream outFile(fileNameOut);
            outFile << this->_coutSSBuf.rdbuf();
            outFile.close();
        }

        inline std::streambuf* get_stream_buffer() const {
            return this->_coutSSBuf.rdbuf();
        }
        inline void close_cout_buffer() {
            std::cout.rdbuf(this->_oriCoutBuff);
            this->__clear_buffer();
        }
    };
} // namespace KYTools


#endif