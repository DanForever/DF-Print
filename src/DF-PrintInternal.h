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

#ifndef __DF_PRINT_INTERNAL_H__
#define __DF_PRINT_INTERNAL_H__

#include <Arduino.h>

// Some Arduino platform implementations do not comprehensively cover the C++ standard, so we need to use string.h instead of cstring
#include <string.h>

#include "DF-StdUtility.h"

namespace DF
{
	namespace Internal
	{
		// Finds the location of the first argument specifier and prints all the text
		// that comes before it. If no specifier is found, prints the whole string
		// Format is modified to remove the text that was printed
		inline size_t PrintTextBeforeFirstArgumentSpecifier(const char*& format)
		{
			const char* argStart = strchr(format, '{');

			if (!argStart)
			{
				size_t count = Serial.print(format);
				format += count;
				return count;
			}

			size_t length = argStart - format;
			Serial.write(format, length);
			format += length;

			return length;
		}

		// Prints the argument and removes the argument specifier from format
		template <typename Arg>
		inline size_t PrintArgumentInPlaceOfSpecifier(const char*& format, Arg&& arg)
		{
			const char* argEnd = strchr(format, '}');

			if (argEnd)
				format = argEnd + 1;

			return Serial.print(DF::forward<Arg>(arg));
		}

		// This will print All the text before an argument specifier (e.g. {0}),
		// then the argument, and finally all the text that comes after the argument
		// up until the next argument specifier is detected, or the end of the string is reached
		//
		// Implementation note:
		// This is the main workhorse of the library, so as it's currently implemented, what
		// happens is that any time a string has more than one argument to be printed, there will
		// be no preceeding text for any argument other than the first, since the preceeding argument
		// also prints everything that comes afterwards.
		// (There may be a slightly more optimal way to implement this)
		template <typename Arg>
		inline size_t PrintTextWithArgument(const char*& format, Arg&& arg)
		{
			size_t charactersPrinted = 0;

			charactersPrinted += PrintTextBeforeFirstArgumentSpecifier(format);
			charactersPrinted += PrintArgumentInPlaceOfSpecifier(format, DF::forward<Arg>(arg));
			charactersPrinted += PrintTextBeforeFirstArgumentSpecifier(format);

			return charactersPrinted;
		}
	}
}

#endif // __DF_PRINT_INTERNAL_H__
