#include "rack.hpp"


using namespace rack;

//Colour	
//	const NVGcolor BARK_ = nvgRGBA(0, 0, 0, 255);		//nvgRedGreenBlueAlpha == Transparency();
const NVGcolor BARK_GREEN1 = nvgRGBA(34, 124, 34, 255);		
const NVGcolor BARK_GREEN2 = nvgRGBA(66, 66, 36, 255);		
const NVGcolor BARK_GREEN3 = nvgRGBA(75, 83, 32, 255);		
const NVGcolor BARK_GREEN4 = nvgRGBA(73, 191, 0, 255);		//#1
const NVGcolor BARK_YELLOW = nvgRGBA(255, 220, 0, 255);		
const NVGcolor BARK_ORANGE1 = nvgRGBA(255, 150, 0, 255);		//#1
const NVGcolor BARK_ORANGE2 = nvgRGBA(255, 170, 0, 255);		
const NVGcolor BARK_ORANGE3 = nvgRGBA(243, 123, 0, 255);		
const NVGcolor BARK_RED1 = nvgRGBA(179, 15, 0, 255);			
const NVGcolor BARK_RED2 = nvgRGBA(186, 15, 0, 255);			//#1	
const NVGcolor BARK_RED3 = nvgRGBA(204, 15, 0, 255);			


extern Plugin *plugin;

/////////////////---------
//						extern Model *modelNAME;
////////////////----------

extern Model *modelTrimLFO;
//extern Model *modelGain;
//extern Model *modelClipper;
extern Model *modelQuadLogic;
//extern Model *modelSpaceX
extern Model *modelPanel6;
extern Model *modelPanel10;
extern Model *modelPanel13;


/////////////////---------
//						extern Model *modelNAME;
////////////////----------

//In .cpp
/*	struct -NAME-Widget : ModuleWidget {
-NAME-Widget(-NAME- *module) : ModuleWidget(module) {
	setPanel(SVG::load(assetPlugin(plugin, "res/-NAME-.svg")));
	////////////
	//components
	////////////
	//----
	//	ModuleLightWidget::create	== Light
	//	Widget::create 				== Screw
	//	ParamWidget::create 			== Knob
	//	Port::create					== Port	
	//	    ""		<COMPONENT>(Vec(0, 0), (for port) = , Port::INPUT, or ,Port::OUTPUT , module, -NAME-::ENUM));
	//----
*/
