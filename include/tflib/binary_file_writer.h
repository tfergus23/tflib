#include <fstream>
#include <cstdint>

namespace tflib{
    class binary_file_writer {
    public:
        binary_file_writer();
        binary_file_writer(std::string_view file_name);
        binary_file_writer(std::ofstream& file);

        void write_int8(int8_t i);
        void write_uint8(uint8_t i);

        void write_int16(int16_t i);
        void write_uint16(uint16_t i);

        void write_int32(int32_t i);
        void write_uint32(uint32_t i);

        void write_int64(int64_t i);
        void write_uint64(uint64_t i);

        void write_string(std::string_view string);

        void write(const char* data, size_t size);
    private:
        std::ofstream m_file;
    };
}