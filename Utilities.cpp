// Name: Maryam Setayeshnia
// Seneca Student ID: 143893220
// Seneca email: msetayseshnia@myseneca.ca
// Date of completion: 2024-04-06
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include "Utilities.h"
using namespace std;
namespace seneca {
	char Utilities::m_delimiter{};

	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}
	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}
	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{

		if (m_delimiter == str[next_pos])
		{
			more = false;
			throw "Delimiter found at this position";
			
		}
		std::string token{};
		size_t pos = str.find(m_delimiter, next_pos);

		if (pos != std::string::npos)
		{
			token = str.substr(next_pos, pos - next_pos);
			trim(token);
			next_pos = pos + 1;
			more = true;
		}
		else
		{
			token = str.substr(next_pos);
			trim(token);
			next_pos = token.length();
			more = false;
		}
		
		if (token.length() > m_widthField)
		{
			setFieldWidth(token.size());
		}

		return token;
	}
	void Utilities::trim(std::string& str)
	{
		str.erase(0, str.find_first_not_of(' '));
		str.erase(str.find_last_not_of(' ') + 1);
	}
	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}
	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}
}