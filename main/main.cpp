#include "cadmium/simulation/rt_root_coordinator.hpp"
#include <limits>
#include "include/top.hpp"

#ifdef ESP_PLATFORM
	#include <cadmium/simulation/rt_clock/ESPclock.hpp>
#else
	#include <cadmium/simulation/rt_clock/chrono.hpp>
#endif

#ifndef NO_LOGGING
	#include "cadmium/simulation/logger/stdout.hpp"
	#include "cadmium/simulation/logger/csv.hpp"
#endif

using namespace cadmium;

extern "C" {
	#ifdef ESP_PLATFORM
		void app_main() //starting point for ESP32 code
	#else
		int main()		//starting point for simulation code
	#endif
	{
	
		std::shared_ptr<top_coupled> model = std::make_shared<top_coupled> ("top");
		
		#ifdef ESP_PLATFORM
			cadmium::ESPclock clock;
			auto rootCoordinator = cadmium::RealTimeRootCoordinator<cadmium::ESPclock<double>>(model, clock);
		#else
			cadmium::ChronoClock clock;
			auto rootCoordinator = cadmium::RealTimeRootCoordinator<cadmium::ChronoClock<std::chrono::steady_clock>>(model, clock);
		#endif

		#ifndef NO_LOGGING
		rootCoordinator.setLogger<STDOUTLogger>(";");
		// rootCoordinator.setLogger<CSVLogger>("outputLog.csv", ";");
		#endif

		rootCoordinator.start();
		#ifdef ESP_PLATFORM
			rootCoordinator.simulate(std::numeric_limits<double>::infinity());
		#else
			rootCoordinator.simulate(23.0);
		#endif
		rootCoordinator.stop();	

		#ifndef ESP_PLATFORM
			return 0;
		#endif
	}
}