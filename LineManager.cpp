// Name: Maryam Setayeshnia
// Seneca Student ID: 143893220
// Seneca email: msetayseshnia@myseneca.ca
// Date of completion: 2024-04-06
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"
#include "Workstation.h"
using namespace std;
namespace seneca {
    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
    {
		
		std::ifstream ifs(file);
		if (ifs.is_open())
		{
			std::string str, currSation, nextStation;

			while (std::getline(ifs, str))
			{
				Utilities ut;
				ut.setDelimiter('|');
				size_t next_pos = 0;
				bool more = true;
				currSation = ut.extractToken(str, next_pos, more);

				std::vector<Workstation*>::const_iterator currentstation = std::find_if(stations.cbegin(), stations.cend(), 
					[currSation](const Workstation* station) {
                    return station->getItemName() == currSation;
					});
				m_activeLine.push_back(*currentstation);

				if (more)
				{
					nextStation = ut.extractToken(str, next_pos, more);
					std::vector<Workstation*>::const_iterator nextstation = std::find_if(stations.cbegin(), stations.cend(), 
						[nextStation](const Workstation* station) {
                        return station->getItemName() == nextStation;
						});
					(*currentstation)->setNextStation(*nextstation);
				}
				// checks for the station that no station points to, which is the first st
				std::for_each(m_activeLine.begin(), m_activeLine.end(), [this](Workstation* curStation) {

					std::vector<Workstation*>::iterator prevStation = std::find_if(m_activeLine.begin(), m_activeLine.end(), 
					[curStation](Workstation* workstation) {
						return workstation->getNextStation() == curStation;
						});

					if (prevStation == m_activeLine.end())
					{
						m_firstStation = curStation;
					}
					});

				m_cntCustomerOrder = g_pending.size();
			}
			ifs.close();
		}
		else
		{
			throw std::invalid_argument("Cannot open the file!");
		}
    }
    void LineManager::reorderStations()
    {
        std::vector<Workstation*> sorted;

        Workstation* currStation = m_firstStation;
        while (currStation)
        {
            sorted.push_back(currStation);
            currStation = currStation->getNextStation();
        }
        m_activeLine = std::move(sorted);
    }
    bool LineManager::run(std::ostream& os)
    {
        static int cnt = 0;
        os << "Line Manager Iteration: " << ++cnt << std::endl;

        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        for (auto& station : m_activeLine)
            station->fill(os); 

        for (auto& station : m_activeLine)
            station->attemptToMoveOrder(); 
       
        return  m_cntCustomerOrder == (g_completed.size() + g_incomplete.size());
    }
    void LineManager::display(std::ostream& os) const
    {
        if (!m_activeLine.empty())
            for (auto& i : m_activeLine)
                i->display(os);
    }
}
