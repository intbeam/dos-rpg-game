/* Copyright 2021 Intbeam

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#ifndef _MAIN_HPP
#include <stdio.h>

#include "vgadisplayadapter.hpp"
#include "vgapixelwriter.hpp"
#include "spritemanager.hpp"
#include "tgaimagereader.hpp"
#include "pixelrasterizer.hpp"

#include "keyboarddevicereader.hpp"
#include "inputmapper.hpp"
#include "inputmanager.hpp"
#include "controlmapper.hpp"

#include "tilemanager.hpp"

#include "map.hpp"

#include "viewport.hpp"

#include "actor.hpp"
#include "scene.hpp"


// main prototype
int main(int argc, char** argv);

#endif
