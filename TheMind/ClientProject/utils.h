#pragma once

#define DEBUG_MODE 0

#define pDebug(msg, ...) { if (DEBUG_MODE) printf(msg, ##__VA_ARGS__); }

void clear();