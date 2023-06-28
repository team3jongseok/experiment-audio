#include <windows.h>
#include "WaveWriter.h"

template <typename Word>
static void write_word(std::ostream* outs, Word value, unsigned size = sizeof(Word))
{
    for (; size; --size, value >>= 8)
        outs->put(static_cast <char> (value & 0xFF));
}
std::ofstream* OutputWaveOpen(const char* filename, WORD nChannels, DWORD nSamplesPerSec, WORD wBitsPerSample)
{
    std::ofstream* File = NULL;
    try
    {
        File = new std::ofstream(filename, std::ios::binary | std::ios::trunc);
        // Write the file headers
        *File << "RIFF----WAVEfmt ";     // (chunk size to be filled in later)
        write_word(File, 16, sizeof(DWORD));  // no extension data
        write_word(File, 1, sizeof(WORD));  // PCM - integer samples
        write_word(File, nChannels, sizeof(WORD));  // two channels (stereo file)
        write_word(File, nSamplesPerSec, sizeof(DWORD));  // samples per second (Hz)
        write_word(File, (nSamplesPerSec * wBitsPerSample * nChannels) / 8, sizeof(DWORD));  // (Sample Rate * BitsPerSample * Channels) / 8
        write_word(File, (nChannels * wBitsPerSample) / 8, sizeof(WORD));  // data block size (size of two integer samples, one for each channel, in bytes)
        write_word(File, (nChannels * wBitsPerSample), sizeof(WORD));  // number of bits per sample (use a multiple of 8)
        *File << "data----";  // (chunk size to be filled in later)

    }
    catch (const std::exception& e) {
        std::cerr << "error: " << e.what();
    }
    return(File);
}
DWORD OutputWaveWrite(std::ofstream* File, const char* Data, DWORD Length)
{
    try
    {
        if (File == NULL) return(false);
        File->write(Data, Length);
    }
    catch (const std::exception& e) {
        std::cerr << "error: " << e.what();
        return(false);
    }
    return(true);
}
void OutputWaveClose(std::ofstream* File)
{
    try
    {
        if (File == NULL) return;
        size_t file_length = File->tellp();
        File->seekp(0 + 4);
        write_word(File, file_length - 8, 4);
        File->seekp(0 + 40);
        write_word(File, file_length - 44, 4);
        File->close();
    }
    catch (const std::exception& e) {
        std::cerr << "error: " << e.what();

    }
}