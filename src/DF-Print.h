/*
* MIT License
* Copyright (c) 2022 Daniel Neve
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#ifndef __DF_PRINT_H__
#define __DF_PRINT_H__

#ifndef DF_DISABLE_DEBUG_PRINT
#	define DEBUG_PRINT(format, ...) ::DF::Print(format, ##__VA_ARGS__)
#	define DEBUG_PRINTLN(format, ...) ::DF::Println(format, ##__VA_ARGS__)
#else
#	define DEBUG_PRINT(format, ...)
#	define DEBUG_PRINTLN(format, ...)
#endif

#include <cstring>

#include "DF-PrintInternal.h"

namespace DF
{
	inline size_t Print(const char* text)
	{
		return Serial.print(text);
	}

	inline size_t Println(const char* text)
	{
		return Serial.println(text);
	}

	template <typename Arg>
	inline size_t Print(const char* format, Arg&& arg)
	{
		return Internal::PrintTextWithArgument(format, arg);
	}

	template <typename Arg, typename... Args>
	inline size_t Print(const char* format, Arg&& arg, Args... args)
	{
		size_t charactersPrinted = 0;

		charactersPrinted += Internal::PrintTextWithArgument(format, std::forward<Arg>(arg));
		charactersPrinted += Print(format, std::forward<Args>(args)...);

		return charactersPrinted;
	}

	template <typename... Args>
	inline size_t Print(const char* format, Args... args)
	{
		size_t charactersPrinted = 0;

		charactersPrinted += Print(format, std::forward<Args>(args)...);

		return charactersPrinted;
	}

	template <typename... Args>
	inline size_t Println(const char* format, Args... args)
	{
		size_t charactersPrinted = 0;

		charactersPrinted += Print(format, std::forward<Args>(args)...);
		charactersPrinted += Serial.println("");
		// Alternatively, could do Serial.write("\r\n"); - more efficient? Is it worth making that string be read from PROGMEM?

		return charactersPrinted;
	}
}

#endif // __DF_PRINT_H__
