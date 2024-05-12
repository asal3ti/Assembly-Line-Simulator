// Name: Maryam Setayeshnia
// Seneca Student ID: 143893220
// Seneca email: msetayseshnia@myseneca.ca
// Date of completion: 2024-04-06
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <string>
#include <iomanip>
#include "Utilities.h"
#include "Station.h"
using namespace std;
namespace seneca {
	size_t Station::m_widthField = 0;
	size_t Station:: id_generator = 0;
	seneca::Station::Station(const std::string& str)
	{
		Utilities ut;
		size_t next_pos =0;
		bool more = true;
		// extracting the name
		m_name = ut.extractToken(str, next_pos, more);
		// extracting the serial number
		m_serialNum = stoul(ut.extractToken(str, next_pos, more));
		// extracting the quantity in stock
		m_stock = stoul(ut.extractToken(str, next_pos, more));
		// updating the m_widthField
		m_widthField = std::max(m_widthField, ut.getFieldWidth());
		// extracting the description
		m_desc = ut.extractToken(str, next_pos, more);
		// getting an id
		m_id = ++id_generator;
	}
	const std::string& Station::getItemName() const
	{
		return m_name;
	}
	size_t Station::getNextSerialNumber()
	{
		return m_serialNum++;
	}
	size_t Station::getQuantity() const
	{
		return m_stock;
	}
	void Station::updateQuantity()
	{
		(m_stock > 0) ? m_stock -= 1 : m_stock;
	}
	void Station::display(std::ostream& os, bool full) const
	{
		if (!full)
		{
			os << setw(3) << setfill('0') << right << m_id << " | " 
				<< setw(m_widthField) << setfill(' ') << left << m_name << " | " 
				<< setw(6) << setfill('0') << right << m_serialNum << " | ";
		}
		else
		{
			os << setw(3) << setfill('0') << right << m_id << " | "
				<< setw(m_widthField) << setfill(' ') << left << m_name << " | "
				<< setw(6) << setfill('0') << right << m_serialNum << " | "
			    << setw(4) << setfill(' ') << right << m_stock << " | "
			    << left << m_desc;
		}
		os << endl;
	}
}