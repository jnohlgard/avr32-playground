#include "system/streams.hpp"

// gout and uout have to be manually bound to a framebuffer/usart before using.
FramebufferConsole gout;
USARTStream uout;
