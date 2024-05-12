// Name: Maryam Setayeshnia
// Seneca Student ID: 143893220
// Seneca email: msetayseshnia@myseneca.ca
// Date of completion: 2024-04-06
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H
#include "Station.h"
namespace seneca {
	struct Item
	{
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item(const std::string& src) : m_itemName(src) {};
	};
	class CustomerOrder {
		//instance variables:
		std::string m_name{};
		std::string m_product{};
		size_t m_cntItem{};
		Item** m_lstItem{};
		//class variable:
		static size_t m_widthField;
	public:
		CustomerOrder() = default;
		CustomerOrder(const std::string& str);
		CustomerOrder(const CustomerOrder& cp);
		CustomerOrder& operator=(const CustomerOrder& cp) = delete;
		CustomerOrder(CustomerOrder&& other) noexcept;
		CustomerOrder& operator=(CustomerOrder&& other) noexcept;
		~CustomerOrder();
		bool isOrderFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
	};
}
#endif // !SENECA_CUSTOMERORDER_H
