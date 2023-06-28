#pragma once
#ifndef __WAVEWRITER_H__
#define __WAVEWRITER_H__
#include <fstream>
#include <iostream>
 std::ofstream* OutputWaveOpen(const char* filename, WORD nChannels, DWORD nSamplesPerSec, WORD wBitsPerSample);
 DWORD OutputWaveWrite(std::ofstream* File, const char* Data, DWORD Length);
 void OutputWaveClose(std::ofstream* File);
#endif