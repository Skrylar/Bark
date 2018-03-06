#include "Bark.hpp"

// The "slug" is the unique identifier for your plugin and must never change after release, so choose wisely.
// It must only contain letters, numbers, and characters "-" and "_". No spaces.
// To guarantee uniqueness, it is a good idea to prefix the slug by your name, alias, or company name if available, e.g. "MyCompany-MyPlugin".
// The ZIP package must only contain one folder, with the name equal to the plugin's slug.
//----
// The plugin-wide instance of the Plugin class
Plugin *plugin;

void init(rack::Plugin *p) {
	plugin = p;
	p->slug = TOSTRING(SLUG);
	p->version = TOSTRING(VERSION);
	p->website = "https://github.com/Coirt/Bark";
	p->manual = "https://github.com/Coirt/Bark/blob/master/README.md";

	//			p->addModel(modelNAME);

//----Modules
	p->addModel(modelTrimLFO);
	//p->addModel(modelGain);
	//p->addModel(modelClipper);
	p->addModel(modelQuadLogic);
	//p->addModel(modelMixer);
//----Panel
	//p->addModel(modelSpaceX);
	p->addModel(modelPanel6);
	p->addModel(modelPanel10);
	p->addModel(modelPanel13);
}



/*
------------------------//In .cpp for Module------------------------------	

struct -NAME-Widget : ModuleWidget {
-NAME-Widget(-NAME- *module);
};

-NAME-Widget::-NAME-Widget(-NAME- *module) : MouduleWidget(module) {
box.size = Vec(xWidth, 380);
{
SVGPanel *panel = new SVGPanel();
panel->box.size = box.size;
setPanel(SVG::load(assetPlugin(plugin, "res/Bark-NAME-.svg")));
addChild(panel);
}

--------------------------------------------------------------------------
*/

				//At the end of .cpp of module e.g.
	/*		//	Model *modelBAR = Model::create<BAR, BARWidget>("Bidoo", "baR", "bAR compressor", DYNAMICS_TAG);

			//	Model *model-NAME- = Model::create<-NAME-,-NAME-Widget>("-FOLDER-", "-ShortName-", "-LongName-", THE_TAG);
	p->addModel(createModel<TrimLFOWidget>("Bark", "TrimLFO", "Trim LFO", LFO_TAG, UTILITY_TAG, LOGIC_TAG, DUAL_TAG));
	p->addModel(createModel<GainWidget>("Bark", "Gain", "Gain Knob", UTILITY_TAG, AMPLIFIER_TAG));
	p->addModel(createModel<QuadLogicWidget>("Bark", "QuadLogic", "Quad Logic", UTILITY_TAG, LOGIC_TAG));
	//p->addModel(createModel<ClipperWidget>("Bark", "Clipper", "Clip Gain Distort", UTILITY_TAG, AMPLIFIER_TAG, EFFECT_TAG));


	////////
	//Blanks
	////////
	p->addModel(createModel<Panel13Widget>("Bark", "Panel13", "Bark Panel 13", BLANK_TAG));
	p->addModel(createModel<Panel10Widget>("Bark", "Panel10", "Bark Panel 10", BLANK_TAG));
	p->addModel(createModel<Panel6Widget>("Bark", "Panel6", "Bark Panel 6", BLANK_TAG));
	

	// Any other plugin initialization may go here.
	// As an alternative, consider lazy-loading assets and lookup tables when your module is created to reduce startup times of Rack.
}
*/
