# Joeltronics Monosynth

*name likely to change*

Inspired by analog synths such as:

* Moog Prodigy, Rogue, MG-1, and Sub Phatty
* Arturia Microbrute/Minibrute
* Novation Bass Station 2

The main goal is for this to be super accessible and easy to get a good sound out of. Of course, I also don't want it to only have 1 or 2 good sounds with no variation, so hopefully I can find a good tradeoff between accessibility and versatility. One thing's for sure - it's not meant to be a powerful "do everything" monster synth (though that might be coming next once I'm happy enough with this one to call it 1.0).

## Synthesis Features

* 2 Oscillators + sub
* Variable oscillator shape: pulse width modulation for square wave, and some sort of other similar timbral control for saw & tri waves
* Analog imperfections: slight tuning instability, slightly imperfect oscillator waveforms
* Dirtiness: ring mod, filter overdrive, post-filter distortion
* High quality: anti-aliased oscillators, zero-delay feedback filter, upsampling

## Status

It doesn't work yet - there's no sound engine. The GUI controls are pretty much all there, but none of them are hooked up yet, and the GUI is currently really quite and possibly a bit confusing; I plan on fixing this eventually.

## Plugin features planned for 1.0

* Fully automatable parameters - so if you want an extra LFO, you could always use automation to act as one
* "Underneath the panel" controls - I don't want to rely heavily on these, as accessibility is one of my main goals. But I also don't want the front panel to be too cluttered, so there are a few things I have in mind for "page 2". They could almost be treated like "mods" to a hardware synth.

## Features not planned for 1.0

These are all features I'm considering possibly adding in the future, but don't plan on implementing right away:

* Built-in patch storage & management - in the meantime, most DAWs should support it (once I implement state saving, anyway, which is planned for 1.0)
* More monophony priority modes
* Polyphony & unison
* Sequencer & arpeggiator
