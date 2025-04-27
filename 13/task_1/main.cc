#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

std::string bytesToHexString(const std::vector<uint8_t>& Bytes) {
    std::ostringstream OSS;
    OSS << std::hex << std::uppercase << std::setfill('0');
    
    for (uint8_t Byte : Bytes) {
        OSS << std::setw(2) << static_cast<unsigned>(Byte);
    }
    
    return OSS.str();
}

int main() {
    std::vector<uint8_t> Bytes = {0xBA, 0xAD};
    std::string HexStr = bytesToHexString(Bytes);
    
    std::cout << HexStr << std::endl;
    return 0;
}