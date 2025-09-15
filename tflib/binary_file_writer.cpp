#include "binary_file_writer.h"

using namespace tflib;

binary_file_writer::binary_file_writer(){}
binary_file_writer::binary_file_writer(std::string_view file_name) : m_file{file_name.data(), std::ios::binary | std::ios::out}{}
binary_file_writer::binary_file_writer(std::ofstream& file) : m_file{std::move(file)}{}

void binary_file_writer::write_int8(int8_t i){
    m_file.write((const char*) &i, sizeof(int8_t));
}
void binary_file_writer::write_uint8(uint8_t i){

}
void binary_file_writer::write_int16(int16_t i){

}
void binary_file_writer::write_uint16(uint16_t i){

}
void binary_file_writer::write_int32(int32_t i){

}
void binary_file_writer::write_uint32(uint32_t i){

}
void binary_file_writer::write_int64(int64_t i){

}
void binary_file_writer::write_uint64(uint64_t i){

}
void binary_file_writer::write_string(std::string_view string){

}
void binary_file_writer::write(const char* data, size_t size){

}