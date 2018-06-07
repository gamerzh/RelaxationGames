#include "FootManTeam.h"
USING_NS_CC;
using namespace std;

FootManTeam* FootManTeam::m_instance = new FootManTeam();

FootManTeam* FootManTeam::getInstance()
{
	return m_instance;
}

vector<FootManProperty> FootManTeam::getFootManVector() {
	vector<FootManProperty> footManVector;
	FootManProperty foot1;
	foot1.name = "player1";
	foot1.footImage = "";
	foot1.runSpeed = 10;
	foot1.skillType = 0;
	footManVector.push_back(foot1)

}