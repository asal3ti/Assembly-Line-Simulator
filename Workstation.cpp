// Name: Maryam Setayeshnia
// Seneca Student ID: 143893220
// Seneca email: msetayseshnia@myseneca.ca
// Date of completion: 2024-04-06
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include "Station.h"
#include "Workstation.h"

using namespace std;
namespace seneca {
	 std::deque<CustomerOrder> g_pending;
	 std::deque<CustomerOrder> g_completed;
	 std::deque<CustomerOrder> g_incomplete;
	Workstation::Workstation(const std::string& name): Station(name)
	{
	}
	void Workstation::fill(std::ostream& os)
	{
		if (!m_orders.empty())
		{
			m_orders.front().fillItem(*this, os);
		}
	}
	bool Workstation::attemptToMoveOrder()
	{
		bool moved{};
		if (!m_orders.empty()) {
			if (m_orders.front().isItemFilled(getItemName()) || getQuantity() <= 0) 
			{
				if (m_pNextStation)
				{
					m_pNextStation->m_orders.push_back(std::move(m_orders.front()));
				}	
				else 
				{
					if (m_orders.front().isOrderFilled())
					{
						g_completed.push_back(std::move(m_orders.front()));
					}
					else
					{
						g_incomplete.push_back(std::move(m_orders.front()));
					}
				}	
				m_orders.pop_front();
				moved = true;
			}
		}
		else
		{
			moved = false;
		}
		return  moved;
	}
	void Workstation::setNextStation(Workstation* station)
	{
		m_pNextStation = station;
	}
	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}
	void Workstation::display(std::ostream& os) const
	{
		if (m_pNextStation)
			os << getItemName() << " --> " << m_pNextStation->getItemName() << endl;
		else
			os << getItemName() << " --> " << "End of Line" << endl;
	}
	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		m_orders.push_back(std::move(newOrder));
		return *this;
	}
}