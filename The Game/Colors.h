#pragma once
#include <cstdlib>

const float black[]		= { 0.0f, 0.0f, 0.0f, 1.0f };
const float red[]		= { 1.0f, 0.0f, 0.0f, 0.0f };
const float red2[]		= { 0.5f, 0.0f, 0.0f, 0.0f };
const float red3[]		= { 0.2f, 0.0f, 0.0f, 0.0f };
const float green[]		= { 0.0f, 1.0f, 0.0f, 0.0f };
const float green2[]	= { 0.0f, 0.5f, 0.0f, 0.0f };
const float green3[]	= { 0.0f, 0.2f, 0.0f, 0.0f };
const float blue[]		= { 0.0f, 0.0f, 1.0f, 0.0f };
const float blue2[]		= { 0.0f, 0.0f, 0.5f, 0.0f };
const float blue3[]		= { 0.0f, 0.0f, 0.2f, 0.0f };
const float yellow[]	= { 1.0f, 1.0f, 0.0f, 0.0f };
const float yellow2[]	= { 0.5f, 0.5f, 0.0f, 0.0f };
const float yellow3[]	= { 0.2f, 0.2f, 0.0f, 0.0f };
const float orange[]	= { 1.0f, 0.647f, 0.0f, 0.0f };
const float white[]		= { 1.0f, 1.0f, 1.0f, 1.0f };
const float brown[]		= { 0.38f, 0.2f, 0.07f, 0.0f };
const float gray[]		= { 0.8f, 0.8f, 0.8f, 0.0f };
const float gray2[]		= { 0.5f, 0.5f, 0.5f, 0.0f };
const float gray3[]		= { 0.2f, 0.2f, 0.2f, 0.0f };
const float maroon5[]	= { 0.41f, 0.12f, 0.0f, 0.0f };

// return a color for even/odd brick in appropriate color scheme
const float* colorScheme(const int color_scheme, const bool even);