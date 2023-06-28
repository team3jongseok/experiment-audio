#include <iostream>

#include "..\\opus-1.3.1\\include\opus.h"
#pragma comment(lib, "avrt.lib")
#pragma comment(lib, "Msdmo.lib")
#pragma comment(lib, "dmoguids.lib")
#pragma comment(lib, "uuid.lib")
#pragma comment(lib, "amstrmid.lib")
#pragma comment(lib, "wmcodecdspuuid.lib")
#ifdef _DEBUG
#pragma comment(lib,  "..\\built-libs\\opus-d.lib")
#else
#pragma comment(lib,  "..\\built-libs\\opus.lib")
#endif
#ifdef _DEBUG
#pragma comment(lib, "..\\built-libs\\webrtcVAD-d.lib")
#else
#pragma comment(lib, "..\\built-libs\\webrtcVAD.lib")
#endif

#define SAMPLE_RATE 16000
#define CHANNELS 1
#define BITS_PER_SAMPLE 16
#define FRAMES_PER_BUFFER 160
#define BYTES_PER_BUFFER (FRAMES_PER_BUFFER*sizeof(short))

int main()
{
    std::cout << "Hello World!\n";
}


