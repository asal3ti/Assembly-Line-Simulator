// Name: Maryam Setayeshnia
// Seneca Student ID: 143893220
// Seneca email: msetayseshnia@myseneca.ca
// Date of completion: 2024-04-06
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SENECA_STATION_H
#define SENECA_STATION_H

namespace seneca {
	class Station {
		int m_id{};
		std::string m_name{};
		std::string m_desc{};
		unsigned int m_serialNum{};
		unsigned int m_stock{};
		//class variables:
		static size_t m_widthField;
		static size_t id_generator;
	public:
		Station(const std::string& str);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}
#endif // !SENECA_STATION_H
