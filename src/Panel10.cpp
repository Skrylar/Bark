#include "Bark.hpp"
#include "BAcomponents.hpp"

struct Panel10 : Module {
	enum ParamIds {
		NUM_PARAMS
	};
	enum InputIds {
		NUM_INPUTS
	};
	enum OutputIds {
		NUM_OUTPUTS
	};
	enum LightIds {
		BLINK_LIGHT,
		NUM_LIGHTS
	};

	Panel10() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
	void step() override;
};

void Panel10::step()
{
}

struct Panel10Widget : ModuleWidget {
	Panel10Widget(Panel10 *module) : ModuleWidget(module) {
		setPanel(SVG::load(assetPlugin(plugin, "res/BarkPanel10.svg")));
		//screw
		addChild(Widget::create<BarkScrew2>(Vec(2, 3)));								//pos1
		addChild(Widget::create<BarkScrew1>(Vec(box.size.x - 13, 367.2)));			//pos4
	}
};

Model *modelPanel10 = Model::create<Panel10, Panel10Widget>("Bark", "Panel10", "Bark Panel 10", BLANK_TAG);
