#pragma once
#include <vector>
#include <jansson.h>
#include <iostream>

using namespace std;		//rack

/////////////////////////
//Module custom resources
/////////////////////////
//struct FILENAME : SVGScrew {
//	FILENAME() {
//		sw->svg = SVG::load(assetPlugin(plugin, "FILELOCATION"));	//Location will be in res/  or res/FOLDER
//		sw->wrap();
//		box.size = sw->box.size;		//box.size = Vec(r1, r2);
//	}
//};
//			"res/components/		NAME.svg"

namespace rack {
	////Screw
	struct BarkScrew1 : SVGScrew {
		BarkScrew1() {
			sw->svg = SVG::load(assetPlugin(plugin, "res/components/BarkScrew1.svg"));
			sw->wrap();
			box.size = sw->box.size;
		}
	};

	struct BarkScrew2 : SVGScrew {
		BarkScrew2() {
			sw->svg = SVG::load(assetPlugin(plugin, "res/components/BarkScrew2.svg"));
			sw->wrap();
			box.size = sw->box.size;
		}
	};

	struct BarkScrew3 : SVGScrew {
		BarkScrew3() {
			sw->svg = SVG::load(assetPlugin(plugin, "res/components/BarkScrew3.svg"));
			sw->wrap();
			box.size = sw->box.size;
		}
	};

	struct BarkScrew4 : SVGScrew {
		BarkScrew4() {
			sw->svg = SVG::load(assetPlugin(plugin, "res/components/BarkScrew4.svg"));
			sw->wrap();
			box.size = sw->box.size;
		}
	};

	////Switch----
	//	struct FILENAME : SVGSwitch, ToggleSwitch {
	//		FILENAME() {
	//	addFrame(SVG::load(assetPlugin(plugin, "res/components/FILENAME.svg")));	//	State=0
	//	addFrame(SVG::load(assetPlugin(plugin, "res/components/FILENAME.svg")));	//	State=1
	//}
	//};
	//------------------------------------------------------
	struct BarkSwitch : SVGSwitch, ToggleSwitch {
		BarkSwitch() {
			addFrame(SVG::load(assetPlugin(plugin, "res/components/BarkSwitch_0.svg")));			//	State=0
			addFrame(SVG::load(assetPlugin(plugin, "res/components/BarkSwitch_1.svg")));			//	State=1
			//sw->wrap();
			//box.size = sw->box.size;
		}
	};


	////Port----
	//Port In
	struct BarkInPort : SVGPort {
		BarkInPort() {
			background->svg = SVG::load(assetPlugin(plugin, "res/components/BarkInPort.svg"));
			background->wrap();
			box.size = background->box.size;
		}
	};

	struct BarkInPort1 : SVGPort {
		BarkInPort1() {
			background->svg = SVG::load(assetPlugin(plugin, "res/components/BarkInPort1.svg"));
			background->wrap();
			box.size = background->box.size;
		}
	};

	struct BarkInPort2 : SVGPort {
		BarkInPort2() {
			background->svg = SVG::load(assetPlugin(plugin, "res/components/BarkInPort2.svg"));
			background->wrap();
			box.size = background->box.size;
		}
	};

	struct BarkPatchPortIn : SVGPort {
		BarkPatchPortIn() {
			background->svg = SVG::load(assetPlugin(plugin, "res/components/BarkPatchPortIn.svg"));
			background->wrap();
			box.size = background->box.size;
		}
	};

	struct BarkInPort350 : SVGPort {
		BarkInPort350() {
			background->svg = SVG::load(assetPlugin(plugin, "res/components/BarkInPort350.svg"));
			background->wrap();
			box.size = background->box.size;
		}
	};


	//Port Out
	struct BarkOutPort : SVGPort {
		BarkOutPort() {
			background->svg = SVG::load(assetPlugin(plugin, "res/components/BarkOutPort.svg"));
			background->wrap();
			box.size = background->box.size;
		}
	};

	struct BarkOutPort1 : SVGPort {
		BarkOutPort1() {
			background->svg = SVG::load(assetPlugin(plugin, "res/components/BarkOutPort1.svg"));
			background->wrap();
			box.size = background->box.size;
		}
	};

	struct BarkOutPort2 : SVGPort {
		BarkOutPort2() {
			background->svg = SVG::load(assetPlugin(plugin, "res/components/BarkOutPort2.svg"));
			background->wrap();
			box.size = background->box.size;
		}
	};

	struct BarkPatchPortOut : SVGPort {
		BarkPatchPortOut() {
			background->svg = SVG::load(assetPlugin(plugin, "res/components/BarkPatchPortOut.svg"));
			background->wrap();
			box.size = background->box.size;
		}
	};

	struct BarkOutPort350 : SVGPort {
		BarkOutPort350() {
			background->svg = SVG::load(assetPlugin(plugin, "res/components/BarkOutPort350.svg"));
			background->wrap();
			box.size = background->box.size;
		}
	};

	////Knobs

	struct BarkKnob24 : SVGKnob {
		BarkKnob24() {
			minAngle = -0.835 * M_PI;
			maxAngle = 0.831 * M_PI;
			sw->svg = SVG::load(assetPlugin(plugin, "res/components/BarkKnob24.svg"));
			sw->wrap();
			box.size = sw->box.size;
		}
	};

	struct BarkKnob26 : SVGKnob {
		BarkKnob26() {
			minAngle = -0.829 * M_PI;
			maxAngle = 0.831 * M_PI;
			sw->svg = SVG::load(assetPlugin(plugin, "res/components/BarkKnob26.svg"));
			sw->wrap();
			box.size = sw->box.size;
		}
	};

	struct BarkKnob30 : SVGKnob {
		BarkKnob30() {
			minAngle = -0.835 * M_PI;
			maxAngle = 0.831 * M_PI;
			sw->svg = SVG::load(assetPlugin(plugin, "res/components/BarkKnob30.svg"));
			sw->wrap();
			box.size = sw->box.size;
		}
	};

	struct BarkKnob40 : SVGKnob {
		BarkKnob40() {
			minAngle = -0.835 * M_PI;
			maxAngle = 0.831 * M_PI;
			sw->svg = SVG::load(assetPlugin(plugin, "res/components/BarkKnob40.svg"));
			sw->wrap();
			box.size = sw->box.size;
		}
	};

	struct BarkKnob57 : SVGKnob {
		BarkKnob57() {
			minAngle = -0.835 * M_PI;
			maxAngle = 0.831 * M_PI;
			sw->svg = SVG::load(assetPlugin(plugin, "res/components/BarkKnob57.svg"));
			sw->wrap();
			box.size = sw->box.size;
		}
	};

	struct BarkKnob70 : SVGKnob {
		BarkKnob70() {
			minAngle = -0.835 * M_PI;
			maxAngle = 0.831 * M_PI;
			sw->svg = SVG::load(assetPlugin(plugin, "res/components/BarkKnob70.svg"));
			sw->wrap();
			box.size = sw->box.size;
		}
	};

	struct BarkKnob84 : SVGKnob {
		BarkKnob84() {
			minAngle = -0.835 * M_PI;
			maxAngle = 0.831 * M_PI;
			sw->svg = SVG::load(assetPlugin(plugin, "res/components/BarkKnob84.svg"));
			sw->wrap();
			box.size = sw->box.size;
		}
	};

	struct BarkKnob92 : SVGKnob {
		BarkKnob92() {
			minAngle = -0.835 * M_PI;
			maxAngle = 0.831 * M_PI;
			sw->svg = SVG::load(assetPlugin(plugin, "res/components/BarkKnob92.svg")); //90.25px
			sw->wrap();
			box.size = sw->box.size;
		}
	};
}