#include "Bark.hpp"
#include "BAcomponents.hpp"

struct Panel13 : Module {
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

	Panel13() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
	void step() override;
};

void Panel13::step()
{
}

struct Panel13Widget : ModuleWidget {
	Panel13Widget(Panel13 *module) : ModuleWidget(module) {
		setPanel(SVG::load(assetPlugin(plugin, "res/BarkPanel13.svg")));
		//screw
		addChild(Widget::create<BarkScrew2>(Vec(2, 3)));								//pos1
		addChild(Widget::create<BarkScrew1>(Vec(box.size.x - 13, 367.2)));			//pos4
	}
};

Model *modelPanel13 = Model::create<Panel13, Panel13Widget>("Bark", "Panel13", "Bark Panel 13", BLANK_TAG);

