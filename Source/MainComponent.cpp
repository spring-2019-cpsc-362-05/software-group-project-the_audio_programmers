/*
	This file was auto-generated!
  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================

MainComponent::MainComponent() : keyboardComponent(keyboardState, MidiKeyboardComponent::horizontalKeyboard),
startTime(Time::getMillisecondCounterHiRes() * 0.001)
{
	setOpaque(true);

	addAndMakeVisible(midiInputListLabel);
	midiInputListLabel.setText("MIDI Input:", dontSendNotification);
	midiInputListLabel.attachToComponent(&midiInputList, true);


	addAndMakeVisible(midiInputList);
	midiInputList.setTextWhenNoChoicesAvailable("No MIDI Inputs Enabled");
	auto midiInputs = MidiInput::getDevices();
	midiInputList.addItemList(midiInputs, 1);

	// find the first enabled device and use that by default
	for (auto midiInput : midiInputs)
	{
		if (deviceManager.isMidiInputEnabled(midiInput))
		{
			setMidiInput(midiInputs.indexOf(midiInput));
			break;
		}
	}

	// if no enabled devices were found just use the first one in the list
	if (midiInputList.getSelectedId() == 0)
		setMidiInput(0);
	addAndMakeVisible(keyboardComponent);
	keyboardState.addListener(this);

	
	
	//**************************Filter UI*******************************************************************//
	
	resonanceSlider.setSliderStyle(Slider::SliderStyle::Rotary); //configure sliders' properties
	resonanceSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 120, resonanceSlider.getTextBoxHeight());
	resonanceSlider.setRange(0, 1);
	resonanceSlider.setValue(0.5);
	resonanceLabel.setText("Resonance", dontSendNotification);
	resonanceLabel.attachToComponent(&resonanceSlider, false);
	resonanceSlider.addListener(this);				//use listener class to detect our changes to the slider values
	addAndMakeVisible(resonanceSlider);
	addAndMakeVisible(resonanceLabel);									//Make sliders & labels visible

	driveSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	driveSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 120, driveSlider.getTextBoxHeight());
	driveSlider.setRange(1, 10);
	driveSlider.setValue(1);
	driveLabel.setText("Drive", dontSendNotification);
	driveLabel.attachToComponent(&driveSlider, false);
	driveSlider.addListener(this);
	addAndMakeVisible(driveSlider);
	addAndMakeVisible(driveLabel);

	cutoffFrequencySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	cutoffFrequencySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 120, cutoffFrequencySlider.getTextBoxHeight());
	cutoffFrequencySlider.setRange(20, 12000);
	cutoffFrequencySlider.setValue(6000);
	cutoffFrequencySlider.setSkewFactorFromMidPoint(6000.0);
	cutoffFrequencySlider.setTextValueSuffix(" Hz");
	cutfrequencyLabel.setText("Cutoff Frequency", dontSendNotification);
	cutfrequencyLabel.attachToComponent(&cutoffFrequencySlider, false);
	cutoffFrequencySlider.addListener(this);
	addAndMakeVisible(cutfrequencyLabel);
	addAndMakeVisible(cutoffFrequencySlider);

	passFilterButton.setButtonText("low pass");
	passFilterButton.setToggleState(false, NotificationType::dontSendNotification);
	passFilterLabel.setText("Pass Filter", dontSendNotification);
	passFilterLabel.attachToComponent(&passFilterButton, false);
	passFilterButton.addListener(this);
	addAndMakeVisible(passFilterButton);
	addAndMakeVisible(passFilterLabel);

	lfoFilterButton.setButtonText("off"); //Do we want this off by default? 
	lfoFilterButton.setToggleState(false, NotificationType::dontSendNotification);
	lfoFilterButton.addListener(this);
	lfoFilterLabel.setText("LFO Filter", dontSendNotification);
	lfoFilterLabel.attachToComponent(&lfoFilterButton, false);
	addAndMakeVisible(lfoFilterButton);
	addAndMakeVisible(lfoFilterLabel);

	lfoFrequencySlider.setSliderStyle(Slider::SliderStyle::Rotary);
	lfoFrequencySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 120, lfoFrequencySlider.getTextBoxHeight());
	lfoFrequencySlider.setRange(0, 20);
	lfoFrequencySlider.setValue(3);
	lfoFrequencySlider.setTextValueSuffix(" Hz");
	lfoFrequencySlider.addListener(this);
	lfoFrequencyLabel.setText("LFO Frequency", dontSendNotification);
	lfoFrequencyLabel.attachToComponent(&lfoFrequencySlider, false);
	addAndMakeVisible(lfoFrequencyLabel);
	addAndMakeVisible(lfoFrequencySlider);


	
	//**********************************************************************************************************//

	//**************************Oscillator UI*******************************************************************//
	masterVolumeSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	masterVolumeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 120, masterVolumeSlider.getTextBoxHeight());
	masterVolumeSlider.setRange(0, 100, 1);                //These values need to be changed
	masterVolumeSlider.setValue(100);
	masterVolumeSlider.addListener(this);
	masterVolumeLabel.setText("Volume", dontSendNotification);
	masterVolumeLabel.attachToComponent(&masterVolumeSlider, false);
	addAndMakeVisible(masterVolumeSlider);
	addAndMakeVisible(masterVolumeLabel);
		
		
	oscillator1.setButtonText("sine");
	oscillator1.setToggleState(false, NotificationType::dontSendNotification);
	oscillator1.addListener(this);
	osc1Label.setText("Oscillator 1", dontSendNotification);
	osc1Label.attachToComponent(&oscillator1, false);
	addAndMakeVisible(oscillator1);
	addAndMakeVisible(osc1Label);


	//**********************************************************************************************************//
	//*******************************Delay UI*******************************************************************//
	delayButton.setButtonText("off"); // Do we want to start with no delay?
	delayButton.setToggleState(false, NotificationType::dontSendNotification);
	delayButton.addListener(this);
	delayLabel.setText("Delay", dontSendNotification);
	delayLabel.attachToComponent(&delayButton, false);
	addAndMakeVisible(delayButton);
	addAndMakeVisible(delayLabel);

	delayMixSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	delayMixSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 120, delayMixSlider.getTextBoxHeight()); //Do we need a textbox here?
	delayMixSlider.setRange(0, 1);            //These values need to be changed
	delayMixSlider.setValue(0.5);                 //These values need to be changed
	delayMixSlider.setTextValueSuffix(" %");      //These values need to be changed
	delayMixSlider.addListener(this);
	delayMixLabel.setText("Delay Level", dontSendNotification);
	delayMixLabel.attachToComponent(&delayMixSlider, false);
	addAndMakeVisible(delayMixSlider);
	addAndMakeVisible(delayMixLabel);

	delayFeedbackSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	delayFeedbackSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 120, delayFeedbackSlider.getTextBoxHeight());
	delayFeedbackSlider.setRange(0, 1);              //These values need to be changed
	delayFeedbackSlider.setValue(0.5);                   //These values need to be changed
	delayFeedbackSlider.setTextValueSuffix(" ");        //These values need to be changed
	delayFeedbackSlider.addListener(this);
	delayFeedbackLabel.setText("Feedback", dontSendNotification);
	delayFeedbackLabel.attachToComponent(&delayFeedbackSlider, false);
	addAndMakeVisible(delayFeedbackSlider);
	addAndMakeVisible(delayFeedbackLabel);

	delayTimeSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	delayTimeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 120, delayTimeSlider.getTextBoxHeight()); //Do we need a textbox here?
	delayTimeSlider.setRange(0, 1.9);            //These values need to be changed
	delayTimeSlider.setValue(0.75);                 //These values need to be changed
	delayTimeSlider.setTextValueSuffix("");      //These values need to be changed
	delayTimeSlider.addListener(this);
	delayTimeLabel.setText("Delay Time", dontSendNotification);
	delayTimeLabel.attachToComponent(&delayTimeSlider, false);
	addAndMakeVisible(delayTimeSlider);
	addAndMakeVisible(delayTimeLabel);


	//**********************************************************************************************************//
	//******************************Reverb UI*******************************************************************//	
	reverbButton.setButtonText("off"); // Do we want to start with no reverb?
	reverbButton.setToggleState(false, NotificationType::dontSendNotification);
	reverbButton.addListener(this);
	reverbLabel.setText("Reverb", dontSendNotification);
	reverbLabel.attachToComponent(&reverbButton, false);
	addAndMakeVisible(reverbButton);
	addAndMakeVisible(reverbLabel);

	reverbMixSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	reverbMixSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 120, reverbMixSlider.getTextBoxHeight()); //Do we need a textbox here?
	reverbMixSlider.setRange(0, 1);            //These values need to be changed
	reverbMixSlider.setValue(0.5);                 //These values need to be changed
	reverbMixSlider.setTextValueSuffix(" %");      //These values need to be changed
	reverbMixSlider.addListener(this);
	reverbMixLabel.setText("Dry/Wet", dontSendNotification);
	reverbMixLabel.attachToComponent(&reverbMixSlider, false);
	addAndMakeVisible(reverbMixSlider);
	addAndMakeVisible(reverbMixLabel);

	reverbLevelSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	reverbLevelSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 120, reverbLevelSlider.getTextBoxHeight());
	reverbLevelSlider.setRange(0, 1);              //These values need to be changed
	reverbLevelSlider.setValue(0.5);                   //These values need to be changed
	reverbLevelSlider.setTextValueSuffix(" ");        //These values need to be changed
	reverbLevelSlider.addListener(this);
	reverbLevelLabel.setText("Room Size", dontSendNotification);
	reverbLevelLabel.attachToComponent(&reverbLevelSlider, false);
	addAndMakeVisible(reverbLevelSlider);
	addAndMakeVisible(reverbLevelLabel);

	reverbDampingSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	reverbDampingSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 120, reverbDampingSlider.getTextBoxHeight()); //Do we need a textbox here?
	reverbDampingSlider.setRange(0, 1);            //These values need to be changed
	reverbDampingSlider.setValue(0.5);                 //These values need to be changed
	reverbDampingSlider.setTextValueSuffix("");      //These values need to be changed
	reverbDampingSlider.addListener(this);
	reverbDampingLabel.setText("Damping", dontSendNotification);
	reverbDampingLabel.attachToComponent(&reverbDampingSlider, false);
	addAndMakeVisible(reverbDampingSlider);
	addAndMakeVisible(reverbDampingLabel);
	//**********************************************************************************************************//

	addAndMakeVisible(visualiser);

	setSize(800, 700);


	// specify the number of input and output channels that we want to open
	setAudioChannels(0, 2);
}

MainComponent::~MainComponent()
{
	// This shuts down the audio device and clears the audio source.
	keyboardState.removeListener(this);
	deviceManager.removeMidiInputCallback(MidiInput::getDevices()[midiInputList.getSelectedItemIndex()], this);
	shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	dsp::ProcessSpec spec;
	spec.sampleRate = sampleRate;
	spec.maximumBlockSize = 512;
	spec.numChannels = 2;
	// This function will be called when the audio device is started, or when
	// its settings (i.e. sample rate, block size, etc) are changed.
	
	wave.initialise([](float x) { return std::sin(x); }, 128);
	lfo.initialise([](float x) { return std::sin(x); }, 128);
	wave.prepare(spec);
	lfo.prepare(spec);
	rvwet = 0.5;
	rvdry = 0.5;
	dlwet = 0.5;
	rvp.wetLevel = 0;
	rvp.dryLevel = 1;
	lp1.prepare(spec);
	rv6.prepare(spec);
	rv6.setParameters(rvp);
	
	lp1.setMode(dsp::LadderFilter<float>::Mode::LPF24);
	lp1.setCutoffFrequencyHz(5000.0f);
	lp1.setResonance(0.7f);
	lvl.prepare(spec);
	dd3.prepare(spec);
	dd3.setWetLevel(0);
	// You can use this function to initialise any resources you might need,
	// but be careful - it will be called on the audio thread, not the GUI thread.

	// For more details, see the help for AudioProcessor::prepareToPlay()
	visualiser.clear();
}

void MainComponent::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{

	float* leftSpeaker = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);//start of buffer fill
	float* rightSpeaker = bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);
	float* channels[] = { leftSpeaker, rightSpeaker };

	/*for (int sample = 0; sample < bufferToFill.buffer->getNumSamples(); ++sample){
		double theWave = wave.SawWave(sample, 440, 0.25); ////input to saw wave function might be a good start to apply MIDI

		leftSpeaker[sample] = rightSpeaker[sample] = theWave;

	}*/
	// Your audio-processing code goes here!


	dsp::AudioBlock<float> ab1 = dsp::AudioBlock<float>(channels, 2, bufferToFill.buffer->getNumSamples());
	dsp::ProcessContextReplacing<float> pc = dsp::ProcessContextReplacing<float>(ab1);
	// For more details, see the help for AudioProcessor::getNextAudioBlock()
	if(currentNotes.size() > 0) {
     	wave.process(pc);
		
     	
    }
	
	if (lfoFilterState) {
		
		
		auto lfoOut = lfo.processSample(0.0f);
		auto cutoffFreqHz = jmap(lfoOut, -1.0f, 1.0f, 1000.0f, (float)cutoffFrequencySlider.getValue());       // [6]
		lp1.setCutoffFrequencyHz(cutoffFreqHz);
		lfoCounter = 30;
		
	}
	lp1.process(pc);
	

	lvl.process(pc);

	dd3.process(pc);
	
	
	rv6.process(pc);
	
	
	// Right now we are not producing any data, in which case we need to clear the buffer
	// (to prevent the output of random noise)
	//bufferToFill.clearActiveBufferRegion(); ///had to comment this out it was killing output
	visualiser.pushBuffer(bufferToFill);
}

void MainComponent::releaseResources()
{
	// This will be called when the audio device stops, or when it is being
	// restarted due to a setting change.

	// For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint(Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

	// You can add your drawing code here!

}

void MainComponent::resized()
{
	//=========================Slider Sizing and positioning============================
	Rectangle<int> area = getLocalBounds();	//This rectangle is used to scalably map sliders on screen

	Rectangle<int> keyboadMidiArea = area.removeFromTop(area.getHeight() / 5); //Keyboard and midi message box placed at top third of the screen
	midiInputList.setBounds(keyboadMidiArea.removeFromTop(30).removeFromRight(getWidth() - 150).reduced(8));
	keyboardComponent.setBounds(keyboadMidiArea.removeFromTop(80).reduced(8));

	visualiser.setBounds(area.removeFromTop(150));
	area.removeFromTop(40); // This separates the keyboard and the audio visualizer

	Rectangle<int> filterSection = area.removeFromTop(90); //First row will house the filters section
	area.removeFromTop(40); // This separates the Filter and oscillator section. Purely aesthetic
	Rectangle<int> oscillatorSection = area.removeFromTop(90);//Second row will house oscillator section
	area.removeFromTop(40); // This separates the Filter and oscillator section. Purely aesthetic
	Rectangle<int> reverbAndDelaySection = area.removeFromTop(90); //Third row will house the delay and reverb sections
	area.removeFromTop(40); // This separates the Filter and oscillator section. Purely aesthetic

	//**************************Filter UI********************************************************//
	filterSection.removeFromLeft(110); //spacing, aesthetic

	lfoFilterButton.setBounds(filterSection.removeFromLeft(80));

	lfoFrequencySlider.setBounds(filterSection.removeFromLeft(80));

	passFilterButton.setBounds(filterSection.removeFromLeft(80));

	filterSection.removeFromLeft(80); //spacing, aesthetic

	cutoffFrequencySlider.setBounds(filterSection.removeFromLeft(100));

	resonanceSlider.setBounds(filterSection.removeFromLeft(80));

	driveSlider.setBounds(filterSection.removeFromLeft(80));
	//******************************************************************************************//
	//**************************Oscillator UI***************************************************//
	oscillatorSection.removeFromLeft(190); //spacing, aesthetic

	masterVolumeSlider.setBounds(oscillatorSection.removeFromLeft(70));

	oscillatorSection.removeFromLeft(170); //spacing, aesthetic
	
	oscillator1.setBounds(oscillatorSection.removeFromLeft(80));

	//******************************************************************************************//
	//**************************Delay UI********************************************************//
	reverbAndDelaySection.removeFromLeft(30); //spacing, aesthetic

	delayButton.setBounds(reverbAndDelaySection.removeFromLeft(80));

	delayTimeSlider.setBounds(reverbAndDelaySection.removeFromLeft(80));

	delayMixSlider.setBounds(reverbAndDelaySection.removeFromLeft(80));

	delayFeedbackSlider.setBounds(reverbAndDelaySection.removeFromLeft(80));
	//******************************************************************************************//
	//**************************Reverb UI*******************************************************//
	reverbAndDelaySection.removeFromLeft(80);

	reverbButton.setBounds(reverbAndDelaySection.removeFromLeft(80));

	reverbDampingSlider.setBounds(reverbAndDelaySection.removeFromLeft(80));

	reverbMixSlider.setBounds(reverbAndDelaySection.removeFromLeft(80));

	reverbLevelSlider.setBounds(reverbAndDelaySection.removeFromLeft(80));

	//******************************************************************************************//

}
void MainComponent::setMidiInput(int index)
{
	auto list = MidiInput::getDevices();

	deviceManager.removeMidiInputCallback(list[lastInputIndex], this);

	auto newInput = list[index];

	if (!deviceManager.isMidiInputEnabled(newInput))
		deviceManager.setMidiInputEnabled(newInput, true);

	deviceManager.addMidiInputCallback(newInput, this);
	midiInputList.setSelectedId(index + 1, dontSendNotification);

	lastInputIndex = index;
}

void MainComponent::handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message)
{
	const ScopedValueSetter<bool> scopedInputFlag(isAddingFromMidiInput, true);
	keyboardState.processNextMidiEvent(message);
	postMessageToList(message, source->getName());
}

void MainComponent::handleNoteOn(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity)
{
	currentNotes.insert(midiNoteNumber);
	auto m = MidiMessage::noteOn(midiChannel, midiNoteNumber, velocity);
	m.setTimeStamp(Time::getMillisecondCounterHiRes() * 0.001);
	postMessageToList(m, "On-Screen Keyboard");
	wave.setFrequency(m.getMidiNoteInHertz(midiNoteNumber, 440));
	
	lvl.setGainLinear(velocity*volumeMult);


}

void MainComponent::handleNoteOff(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float /*velocity*/)
{
	currentNotes.erase(midiNoteNumber);

	auto m = MidiMessage::noteOff(midiChannel, midiNoteNumber);
	m.setTimeStamp(Time::getMillisecondCounterHiRes() * 0.001);
	postMessageToList(m, "On-Screen Keyboard");

	if (currentNotes.size() > 0) {
		std::set<int>::iterator highestNote = currentNotes.end();
		--highestNote;
		wave.setFrequency(m.getMidiNoteInHertz(*highestNote, 440));
	}

}
