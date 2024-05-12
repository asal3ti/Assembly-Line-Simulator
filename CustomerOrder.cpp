// Name: Maryam Setayeshnia
// Seneca Student ID: 143893220
// Seneca email: msetayseshnia@myseneca.ca
// Date of completion: 2024-04-06
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <iomanip>
#include "Utilities.h"
#include "CustomerOrder.h"
using namespace std;
namespace seneca {
	size_t CustomerOrder::m_widthField = 0;
	CustomerOrder::CustomerOrder(const std::string& str)
	{
		Utilities ut;
		size_t next_pos = 0;
		bool more = true;
		//extract name
		m_name = ut.extractToken(str, next_pos, more);
		//extract orderName
		m_product = ut.extractToken(str, next_pos, more);
		//extract the list of items
		size_t listStart = next_pos;
		while (more)
		{
			ut.extractToken(str, next_pos, more);
			m_cntItem++;
		}
		more = true;
		m_lstItem = new Item * [m_cntItem];
		next_pos = listStart;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			m_lstItem[i] = new Item(ut.extractToken(str, next_pos, more));
		}
		//
		if (ut.getFieldWidth() > CustomerOrder::m_widthField)
		{
			m_widthField = ut.getFieldWidth();
		}
	}
	CustomerOrder::CustomerOrder(const CustomerOrder& cp)
	{
		throw "can not make copies";
	}
	CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept
	{
		*this = std::move(other);
	}
	CustomerOrder& CustomerOrder::operator=( CustomerOrder&& other) noexcept
	{
		//1. self_assignment check
		if (this != &other)
		{
			// clean up
			for (size_t i = 0; i < m_cntItem; i++)
			{
				delete m_lstItem[i];
			}
			delete[] m_lstItem;
			// shallow copy
			m_name = other.m_name;
			m_product = other.m_product;
			m_cntItem = other.m_cntItem;
			m_lstItem = other.m_lstItem;

			// emptying 
			other.m_cntItem = 0;
			other.m_lstItem = nullptr;
			other.m_name = "";
			other.m_product = "";
		}
		return *this;
	}
	CustomerOrder::~CustomerOrder()
	{
		for (size_t i = 0; i < m_cntItem; i++)
		{
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
	}
	bool CustomerOrder::isOrderFilled() const
	{
		bool filled = true;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (!(m_lstItem[i]->m_isFilled))
			{
				filled = false;
			}
		}
		return filled;
	}
	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		bool filled = true;
		for (size_t i = 0; i < m_cntItem && filled; i++)
			if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled)
				filled = false;

		return filled;
	}
	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		bool done = false;

		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled && !done)
			{
				if (station.getQuantity() > 0)
				{
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					done = true;
					os << "    Filled ";
				}
				else
				{
					os << "    Unable to fill ";
				}
				os << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
			}
		}
	}
	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << '\n';
		for (size_t i = 0u; i < m_cntItem; ++i)
		{
			os << '[' << std::setw(6) << std::setfill('0') << std::right << m_lstItem[i]->m_serialNumber << "] ";
			os << std::setfill(' ') << std::setw(m_widthField - 1) << std::left << m_lstItem[i]->m_itemName << "  - ";
			if (m_lstItem[i]->m_isFilled == false)
			{
				os << "TO BE FILLED\n";
			}
			else
			{
				os << "FILLED\n";
			}
		}
	}
}