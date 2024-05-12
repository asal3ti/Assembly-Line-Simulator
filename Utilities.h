// Name: Maryam Setayeshnia
// Seneca Student ID: 143893220
// Seneca email: msetayseshnia@myseneca.ca
// Date of completion: 2024-04-06
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H

namespace seneca{
	class Utilities {
		size_t m_widthField{};
		static  char m_delimiter;
	public:
		//memeber functions:
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		void trim(std::string& str);
		//class functions: 
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
	};
}
#endif // !SENECA_UTILITES_H
