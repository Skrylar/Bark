#include "Bark.hpp"
#include "dsp/digital.hpp"
#include "BAcomponents.hpp"
#include <sstream>
#include <iomanip>

struct LowFrequencyOscillator {
	float phase = 0.0f;
	float pw = 0.5f;
	float freq = 1.0f;
	bool offset = false;
	bool invert = false;
	SchmittTrigger resetTrigger;
	LowFrequencyOscillator() {
	
	}

	void setPitch(float pitch) {
		pitch = fminf(pitch, 8.0f);
		freq = powf(2.0f, pitch);
	}
	void setPulseWidth(float pw_) {
		const float pwMin = 0.01f;
		pw = clamp(pw_, pwMin, 1.0f - pwMin);
	}
	void setReset(float reset) {
		if (resetTrigger.process(reset / 0.01f)) {
			phase = 0.0f;
		}
	}
	void step(float dt) {
		float deltaPhase = fminf(freq * dt, 0.5f);
		phase += deltaPhase;
		if (phase >= 1.0f)
			phase -= 1.0f;
	}
	float sin() {
		if (offset)
			return 1.0f - cosf(2 * M_PI * phase) * (invert ? -1.0f : 1.0f);
		else
			return sinf(2 * M_PI * phase) * (invert ? -1.0f : 1.0f);
	}
	float tri(float x) {
		return 4.0f * fabsf(x - roundf(x));
	}
	float tri() {
		if (offset)
			return tri(invert ? phase - 0.5f : phase);
		else
			return -1.0f + tri(invert ? phase - 0.25f : phase - 0.75f);
	}
	float saw(float x) {
		return 2.0f * (x - roundf(x));
	}
	float saw() {
		if (offset)
			return invert ? 2.0f * (1.0f - phase) : 2.0f * phase;
		else
			return saw(phase) * (invert ? -1.0f : 1.0f);
	}
	float sqr() {
		float sqr = (phase < pw) ^ invert ? 1.0f : -1.0f;
		return offset ? sqr + 1.0f : sqr;
	}
	float light() {
		return sinf(2 * M_PI * phase);
	}
};

struct TrimLFO : Module {
	enum ParamIds
	{
		//Offset part
		OFFSET1_PARAM,
		OFFSET2_PARAM,
		//Internal Param for Logic?
		//LFO Part
		OFFSET_PARAM,
		INVERT_PARAM,
		FREQ_PARAM,
		FM1_PARAM,
		FM2_PARAM,
		PW_PARAM,
		PWM_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		//IN1_INPUT,  //Code needs to link Lfo In to Logic 1A, OFFSET_1 to Logic 1B, > Max to Logic 2A > OFFSET_2 to Logic 2B Min to Lfo out Port, Internally different waves need to link to Logic.
		FM1_INPUT,
		FM2_INPUT,
		RESET_INPUT,
		PW_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		OUT1_OUTPUT, //Offset L + sin Clamped to +-1v of offset
		OUT2_OUTPUT, //Offset R + sqr Clamped to +-1v of offset
		OUT1a_OUTPUT, //Normal Offset
		OUT2a_OUTPUT, //Normal Offset
		SIN_OUTPUT,
		TRI_OUTPUT,
		SAW_OUTPUT,
		SQR_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		PHASE_POS_LIGHT,
		PHASE_NEG_LIGHT,
		NUM_LIGHTS
	};

	LowFrequencyOscillator oscillator;
	float volts1 = 0.000f;
	float volts2 = 0.000f;
	float freqHz = 1.0f /** powf(0.25 / 8, 0.25 * 96)*/;

	//pitch += inputs[PITCH1_INPUT].value + inputs[PITCH2_INPUT].value;
	//pitch += inputs[FM_INPUT].value / 4.0;
	//float freqHz = 0.25 * powf(2.0, freqHz);
	//freqHz = clamp(freqHz, 0.0f, 20000.0f);;

	/*	
	// Compute the frequency from the pitch parameter and input
	float pitch = params[PITCH_PARAM].value;
	pitch += inputs[PITCH_INPUT].value;
	pitch = clamp(pitch, -4.0f, 4.0f);
	// The default pitch is C4
	float freq = 261.626f * powf(2.0f, pitch);
	*/

	TrimLFO() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
	void step() override;

};


void TrimLFO::step() {

	volts1 = clamp(params[OFFSET1_PARAM].value, -10.0f, 10.0f);
	volts2 = clamp(params[OFFSET2_PARAM].value, -10.0f, 10.0f);
	//float out1 = params[OFFSET1_PARAM].value;
	float out1 = params[OFFSET1_PARAM].value + oscillator.sin(); //Attenuvert? osc.sin
	float out2 = params[OFFSET2_PARAM].value + oscillator.sqr();
	float out1a = params[OFFSET1_PARAM].value;	//Normal +-10v
	float out2a = params[OFFSET2_PARAM].value;	//Normal +-10v
	
	out1 = clamp(out1, -10.0f, 10.0f);	//Limit to
	out2 = clamp(out2, -10.0f, 10.0f);
	out1a = clamp(out1a, -10.0f, 10.0f);
	out2a = clamp(out2a, -10.0f, 10.0f);
	outputs[OUT1_OUTPUT].value = out1;
	//out1 = volts;
	outputs[OUT2_OUTPUT].value = out2;
	//out2 = volts;
	outputs[OUT1a_OUTPUT].value = out1a;
	outputs[OUT2a_OUTPUT].value = out2a;
	oscillator.setPitch(params[FREQ_PARAM].value + params[FM1_PARAM].value * inputs[FM1_INPUT].value + params[FM2_PARAM].value * inputs[FM2_INPUT].value);
	oscillator.setPulseWidth(params[PW_PARAM].value + params[PWM_PARAM].value * inputs[PW_INPUT].value / 10.0f);
	oscillator.offset = (params[OFFSET_PARAM].value > 0.0f);
	oscillator.invert = (params[INVERT_PARAM].value <= 0.0f);
	oscillator.step(1.0 / engineGetSampleRate());
	oscillator.setReset(inputs[RESET_INPUT].value);

//				BLACK SCREEN BUG
//-------------------------------------------------------------
float frq = params[FREQ_PARAM].value;
frq = clamp(frq, -16.0f, 12.0f);
// The default pitch is C4// Default Frq is 0.25F
freqHz = -2.0f * powf(0.25f, frq);
//-------------------------------------------------------------

	/*
	float frq = params[FREQ_PARAM].value;
	frq = clamp(frq, -16.0f, 12.0f);
	// The default pitch is C4 // Default frequency is 0.25f
	freqHz = 0.25f * powf(2.0f, frq);
	*/


	
	//float freq = 1.0f;
	//freqHz = params[FREQ_PARAM].value;

	//float pitch = fmaxf(0.25f, 8.0f);
	//freqHz = pow(2.0, pitch) + params[FREQ_PARAM].value / 512;

	//freqHz = -0.25f *params[FREQ_PARAM].value / 2/** powf(2.0f, freqHz)*/;
	//freqHz = 0.25f * powf(0.25 / 8, 0.25 * 96);	// == 0.10 to 0.50
	//float freqHz = clamp(freqHz * engineGetSampleTime(), 1e-6f, 0.5f);		//Even VCO



	//volts1 = clamp(params[OFFSET1_PARAM].value, -10.0f, 10.0f);

	///OFFSET- TRIM ----
	//float offsetMin
	//float offsetMax
	//offsetMin = params[OFFSET1_PARAM].value;
	//offsetMax = params[OFFSET2_PARAM].value;


	outputs[SIN_OUTPUT].value = 5.0f * oscillator.sin();
	outputs[TRI_OUTPUT].value = 5.0f * oscillator.tri();
	outputs[SAW_OUTPUT].value = 5.0f * oscillator.saw();
	outputs[SQR_OUTPUT].value = 5.0f * oscillator.sqr();

	lights[PHASE_POS_LIGHT].setBrightnessSmooth(fmaxf(0.0f, oscillator.light()));
	lights[PHASE_NEG_LIGHT].setBrightnessSmooth(fmaxf(0.0f, -oscillator.light()));
}

struct FreqDisplayWidget : TransparentWidget {

	float *freqHz;
	std::shared_ptr<Font> font;

	FreqDisplayWidget() {
		font = Font::load(assetPlugin(plugin, "res/segoescb.ttf"));
	};

	void draw(NVGcontext *vg) override {
		// Background
		//NVGcolor backgroundColor = nvgRGB(0x20, 0x20, 0x20);
		NVGcolor backgroundColor = nvgRGB(97, 54, 57);
		NVGcolor borderColor = nvgRGB(0, 0, 0);
		nvgBeginPath(vg);
		nvgRoundedRect(vg, 0.0, 0.0, box.size.x, box.size.y, 0.75);
		nvgFillColor(vg, backgroundColor);
		nvgFill(vg);
		nvgStrokeWidth(vg, 0.75);
		nvgStrokeColor(vg, borderColor);
		nvgStroke(vg);
		// text 
		//NVGalign = 1 << 1;
		nvgTextAlign(vg, 1 << 1);
		nvgFontSize(vg, 18);
		nvgFontFaceId(vg, font->handle);
		nvgTextLetterSpacing(vg, 0.75);

		char display_string[10];
		sprintf(display_string, "%5.2f", *freqHz);

		Vec textPos = Vec(85.798f / 2, 10.673f);		//		3.0f, 17.0f

		NVGcolor textColor = nvgRGB(0xdf, 0xd2, 0x2c);
		nvgFillColor(vg, nvgTransRGBA(textColor, 16));
		nvgText(vg, textPos.x, textPos.y, "~~~~", NULL);

		textColor = nvgRGB(0xda, 0xe9, 0x29);
		nvgFillColor(vg, nvgTransRGBA(textColor, 16));
		nvgText(vg, textPos.x, textPos.y, "#0#0#", NULL);

		textColor = nvgRGB(93, 193, 57);
		nvgFillColor(vg, textColor);
		nvgText(vg, textPos.x, textPos.y, display_string, NULL);
		//nvgText(vg, textPos.x, textPos.y, to_display.str().c_str(), NULL);
	}
	/*
	//VOLTS DISPLAY
	VoltsDisplayWidget *display1 = new VoltsDisplayWidget();
	display1->box.pos = Vec(10, 50);
	display1->box.size = Vec(20, 10);
	display1->value = &module->volts;
	addChild(display1);*/
};

struct VoltsDisplayWidget : TransparentWidget {

	float *value;
	std::shared_ptr<Font> font;

	VoltsDisplayWidget() {
		font = Font::load(assetPlugin(plugin, "res/segoescb.ttf"));
	};

	void draw(NVGcontext *vg) override {
		// Background
		//NVGcolor backgroundColor = nvgRGB(0x20, 0x20, 0x20);
		NVGcolor backgroundColor = nvgRGB(97, 54, 57);
		NVGcolor borderColor = nvgRGB(0, 0, 0);
		nvgBeginPath(vg);
		nvgRoundedRect(vg, 0.0, 0.0, box.size.x, box.size.y, 0.75);
		nvgFillColor(vg, backgroundColor);
		nvgFill(vg);
		nvgStrokeWidth(vg, 0.75);
		nvgStrokeColor(vg, borderColor);
		nvgStroke(vg);
		// text 
		//NVGalign = 1 << 1;
		nvgTextAlign(vg, 1 << 1);
		nvgFontSize(vg, 18);
		nvgFontFaceId(vg, font->handle);
		nvgTextLetterSpacing(vg, 0.75);

		char display_string[10];
		sprintf(display_string, "%5.2f", *value);

		Vec textPos = Vec(25.0f, 10.0f);		//		85.798f, 13.673f 

		NVGcolor textColor = nvgRGB(0xdf, 0xd2, 0x2c);
		nvgFillColor(vg, nvgTransRGBA(textColor, 16));
		nvgText(vg, textPos.x, textPos.y, "~~~~", NULL);

		textColor = nvgRGB(0xda, 0xe9, 0x29);
		nvgFillColor(vg, nvgTransRGBA(textColor, 16));
		nvgText(vg, textPos.x, textPos.y, "#0#0#", NULL);

		textColor = nvgRGB(93, 193, 57);
		nvgFillColor(vg, textColor);
		nvgText(vg, textPos.x, textPos.y, display_string, NULL);
		//nvgText(vg, textPos.x, textPos.y, to_display.str().c_str(), NULL);
	}
	/*
	//VOLTS DISPLAY 
	VoltsDisplayWidget *display1 = new VoltsDisplayWidget();
	display1->box.pos = Vec(10, 50);
	display1->box.size = Vec(20, 10);
	display1->value = &module->volts;
	addChild(display1);
	*/
};


struct TrimLFOWidget : ModuleWidget {
	TrimLFOWidget(TrimLFO *module);
};

TrimLFOWidget::TrimLFOWidget(TrimLFO *module) : ModuleWidget(module) {
	setPanel(SVG::load(assetPlugin(plugin, "res/BarkTrimLFO.svg")));
	/*box.size = Vec(10 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);
	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/BarkTrimLFO.svg")));
		addChild(panel);
	}
		////////////
		//components
		////////////
		//----
		//	ModuleLightWidget::create	== Light
		//	Widget::create 				== Screw
		//	ParamWidget::create 			== Knob
		//	Port::create					== Port	
		//	    ""		<COMPONENT>(Vec(0, 0), (for port) = , Port::INPUT, or ,Port::OUTPUT , module, NAME::ENUM));
		// y = 380 == -up, +down
		//----*/
	//Ports---
		//Out---
		addOutput(Port::create<BarkOutPort350>(Vec(13.28f, 380 - 52.35f), Port::OUTPUT, module, TrimLFO::SIN_OUTPUT));
		addOutput(Port::create<BarkOutPort350>(Vec(46.58f, 380 - 52.35f), Port::OUTPUT, module, TrimLFO::SAW_OUTPUT));
		addOutput(Port::create<BarkOutPort350>(Vec(79.68f, 380 - 52.35f), Port::OUTPUT, module, TrimLFO::TRI_OUTPUT));
		addOutput(Port::create<BarkOutPort350>(Vec(113.245f, 380 - 52.35f), Port::OUTPUT, module, TrimLFO::SQR_OUTPUT));
		addOutput(Port::create<BarkOutPort350>(Vec(14.57f, 380 - 274.73f + 0.35f), Port::OUTPUT, module, TrimLFO::OUT1_OUTPUT));				//2v sin
		addOutput(Port::create<BarkOutPort350>(Vec(112.09f, 380 - 274.73f + 0.35f), Port::OUTPUT, module, TrimLFO::OUT2_OUTPUT));			//2v sqr
		addOutput(Port::create<BarkOutPort350>(Vec(42.11f + 0.35f, 380 - 274.73f + 0.35f), Port::OUTPUT, module, TrimLFO::OUT1a_OUTPUT));		//Offset1
		addOutput(Port::create<BarkOutPort350>(Vec(84.18f, 380 - 274.73f + 0.35f), Port::OUTPUT, module, TrimLFO::OUT2a_OUTPUT));			//Offset2
		//In---
		addInput(Port::create<BarkInPort350>(Vec(27.06f, 380 - 82.35f + 0.35f), Port::INPUT, module, TrimLFO::FM1_INPUT));
		addInput(Port::create<BarkInPort350>(Vec(63.25f, 380 - 82.35f + 0.35f), Port::INPUT, module, TrimLFO::FM2_INPUT));
		addInput(Port::create<BarkInPort350>(Vec(99.66f, 380 - 82.35f +0.35f), Port::INPUT, module, TrimLFO::PW_INPUT));
		addInput(Port::create<BarkInPort350>(Vec(119.89f, 380 - 163.35f + 0.7f), Port::INPUT, module, TrimLFO::RESET_INPUT));
		//Knobs---
		addParam(ParamWidget::create<BarkKnob92>(Vec(40.01f, 380 - 217.01f), module, TrimLFO::FREQ_PARAM, -16.0f, 12.0f, -2.0f));
		addParam(ParamWidget::create<BarkKnob40>(Vec(20.48f, 380 - 328.18f - 1.4f), module, TrimLFO::OFFSET1_PARAM, -10.0f, 10.0f, 10.0f));
		addParam(ParamWidget::create<BarkKnob40>(Vec(89.7f, 380 - 328.18f - 1.4f), module, TrimLFO::OFFSET2_PARAM, -10.0f, 10.0f, -10.0f));
		addParam(ParamWidget::create<BarkKnob26>(Vec(5.19f, 380 - 167.6f), module, TrimLFO::PW_PARAM, 0.0f, 1.0f, 0.5f));
		addParam(ParamWidget::create<BarkKnob26>(Vec(25.32f, 380 - 122.3f), module, TrimLFO::FM1_PARAM, 0.0f, 1.0f, 0.0f));
		addParam(ParamWidget::create<BarkKnob26>(Vec(61.65f, 380 - 122.3f), module, TrimLFO::FM2_PARAM, 0.0f, 1.0f, 0.0f));
		addParam(ParamWidget::create<BarkKnob26>(Vec(98.06f, 380 - 122.3f), module, TrimLFO::PWM_PARAM, 0.0f, 1.0f, 0.0f));
		//Switch---
		addParam(ParamWidget::create<BarkSwitch>(Vec(8.67f, 380 - 229.06f + 12.0f), module, TrimLFO::OFFSET_PARAM, 0.0f, 1.0f, 1.0f));
		addParam(ParamWidget::create<BarkSwitch>(Vec(117.57f, 380 - 229.06f + 12.0f), module, TrimLFO::INVERT_PARAM, 0.0f, 1.0f, 1.0f));	
		//Screw---
		addChild(Widget::create<BarkScrew3>(Vec(2, 3)));								//pos1
		addChild(Widget::create<BarkScrew1>(Vec(box.size.x - 13, 367.2f)));			//pos4
		//Light---
		addChild(ModuleLightWidget::create<SmallLight<GreenRedLight>>(Vec(71.93f, 380 - 230.22f), module, TrimLFO::PHASE_POS_LIGHT));

		//VOLTS DISPLAY : Taken From AS-TriggersMKI
		VoltsDisplayWidget *display1 = new VoltsDisplayWidget();
		display1->box.pos = Vec(15.009f, 33.05f);	//== -L/+R, +==D -==U ???
		display1->box.size = Vec(50.728f, 13.152f);	//20, 10 == Lenght, Width
		display1->value = &module->volts1;
		addChild(display1);
		VoltsDisplayWidget *display2 = new VoltsDisplayWidget();
		display2->box.pos = Vec(84.228f, 33.05f);	//== -L/+R, +==D -==U ???
		display2->box.size = Vec(50.728f, 13.152f);	//20, 10 == Lenght, Width
		display2->value = &module->volts2;
		addChild(display2);
		FreqDisplayWidget *display3 = new FreqDisplayWidget();			//Displays Int ??? Int to Hz?
		display3->box.pos = Vec(32.23f, 237.31f);	//== -L/+R, +==D -==U ???
		display3->box.size = Vec(85.798f, 13.673f);	//20, 10 == Lenght, Width
		display3->freqHz = &module->freqHz;
		addChild(display3);
}


Model *modelTrimLFO = Model::create<TrimLFO, TrimLFOWidget>("Bark", "TrimLFO", "Trim LFO", LFO_TAG, UTILITY_TAG, LOGIC_TAG, DUAL_TAG);
