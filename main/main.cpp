#include "cadmium/simulation/root_coordinator.hpp"
#include <limits>
#include "include/top.hpp"

#ifndef NO_LOGGING
	#include "cadmium/simulation/logger/stdout.hpp"
	#include "cadmium/simulation/logger/csv.hpp"
#endif

using namespace cadmium;

int main() {
	
	std::shared_ptr<top_coupled> model = std::make_shared<top_coupled> ("top");
	auto rootCoordinator = RootCoordinator(model);

	#ifndef NO_LOGGING
	rootCoordinator.setLogger<STDOUTLogger>(";");
	// rootCoordinator.setLogger<CSVLogger>("trafficLightLog.csv", ";");
	#endif

	rootCoordinator.start();
	rootCoordinator.simulate(20.0);
	rootCoordinator.stop();	
	return 0;
}