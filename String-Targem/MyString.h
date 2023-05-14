#pragma once

#include <iostream>
#include <ostream>
#include <cstring>

using namespace std;

class MyString
{
	private:
		char* charBuffer = nullptr;
		unsigned int size = 0;

		friend ostream&	operator<<(ostream& os,	const MyString& str);
		friend istream& operator>>(istream& is, MyString& str);

	public:
		MyString() : charBuffer(nullptr), size(0)
		{
		}

		MyString(const char* const buffer)
		{
			size = strlen(buffer);
			charBuffer = new char[size + 1];
			strncpy_s(charBuffer, size + 1, buffer, size);
		}

		MyString(const MyString& str)
		{
			size = str.size;
			charBuffer = new char[size + 1];
			strncpy_s(charBuffer, size + 1, str.charBuffer, size);
		}

		MyString& operator=(const MyString& str)
		{
			clean_();

			size = str.size;
			charBuffer = new char[size + 1];
			strncpy_s(charBuffer, size + 1, str.charBuffer, size);
			return *this;
		}

		MyString(MyString&& dyingStr)
		{
			clean_();

			size = dyingStr.size;
			charBuffer = dyingStr.charBuffer;
			dyingStr.charBuffer = nullptr;
		}

		char& operator[](const size_t index) const
		{
			return charBuffer[index];
		}

		MyString& operator=(MyString&& dyingStr)
		{
			clean_();

			size = dyingStr.size;
			charBuffer = dyingStr.charBuffer;
			dyingStr.charBuffer = nullptr;

			return *this;
		}

		MyString operator+(const MyString& str)
		{
			MyString newStr;
			newStr.size = size + str.size;
			newStr.charBuffer = new char[newStr.size + 1];
			strncpy_s(newStr.charBuffer, size + 1, charBuffer, size);
			strncpy_s(newStr.charBuffer +size, str.size + 1, str.charBuffer, str.size);

			return newStr;
		}

		MyString& operator+=(const MyString& str) {

			MyString other{ new char(strlen(charBuffer) + 1) };
			(other.charBuffer, charBuffer);

			charBuffer = new char[strlen(charBuffer) + strlen(str.charBuffer) + 1];
			
			strcpy(charBuffer, other.charBuffer);
			strcpy(charBuffer, str.charBuffer);

			return *this;
		}

		friend istream& operator>> (istream& is, MyString& str)
		{
			char* buff = new char[1000];
			memset(&buff[0], 0, sizeof(buff));
			is >> buff;
			str = MyString{ buff };
			delete[] buff;
			return is;
		}

		friend ostream& operator<< (ostream& os, const MyString& str)
		{
			os << str.c_str();
			return os;
		}

		bool operator==(const MyString& str) const
		{
			if (size != str.size)
			{
				return false;
			}

			size_t n = 0;
			while (n < str.size && static_cast<char>(tolower(charBuffer[n])) == static_cast<char>(tolower(str.charBuffer[n])))
			{
				n++;
			}

			return (n == str.size);
		}

		bool operator>(const MyString& str) const
		{
			const auto min_length = (size < str.size) ? size : str.size;

			size_t n = 0;
			while ((n < min_length) && static_cast<char>(tolower(charBuffer[n])) == static_cast<char>(tolower(str.charBuffer[n])))
			{
				n++;
				if (n == min_length)
				{
					return (size > str.size);
				}
			}

			return static_cast<char>(tolower(charBuffer[n])) > static_cast<char>(tolower(str.charBuffer[n]));
		}

		bool operator<(const MyString& str) const
		{
			return !(*this == str) && !(*this > str);
		}

		
		unsigned int length()
		{
			return size;
		}

		const char* c_str() const
		{
			return charBuffer;
		}

		~MyString()
		{
			clean_();
		}

	private:
		void clean_()
		{
			if (charBuffer != nullptr)		
				delete[] charBuffer;
		
			size = 0;
		}
};